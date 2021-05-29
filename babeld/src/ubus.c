#include <stdint.h>
#include <stdlib.h>
#include <sys/select.h>

#include <libubus.h>
#include <libubox/blob.h>
#include <libubox/blobmsg.h>
#include <libubox/list.h>

#include <arpa/inet.h>
#include <net/if.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include "babeld.h"
#include "configuration.h"
#include "interface.h"
#include "kernel.h"
#include "local.h"
#include "message.h"
#include "neighbour.h"
#include "net.h"
#include "resend.h"
#include "route.h"
#include "source.h"
#include "util.h"
#include "version.h"
#include "xroute.h"

#include "ubus.h"

// Definition of header variable whether to enable ubus bindings.
int ubus_bindings = 0;

// Shared state maintained throughout calls to handle ubus messages.
static struct ubus_context *shared_ctx;

// List of exported routes (to be used with ubox's list helpers).
struct xroute_list_entry {
  struct list_head list;
  struct xroute *xroute;
};

// List of received routes (to be used with ubox's list helpers).
struct route_list_entry {
  struct list_head list;
  struct babel_route *route;
};

// List of neighbours (to be used with ubox's list helpers).
struct neighbour_list_entry {
  struct list_head list;
  struct neighbour *neighbour;
};

// Sends a babel info message on ubus socket.
static int babeld_ubus_babeld_info(struct ubus_context *ctx_local,
                                   struct ubus_object *obj,
                                   struct ubus_request_data *req,
                                   const char *method, struct blob_attr *msg) {
  struct blob_buf b = {0};
  void *prefix;
  char host[64];
  int ret;

  blob_buf_init(&b, 0);
  blobmsg_add_string(&b, "babeld-version", BABELD_VERSION);
  blobmsg_add_string(&b, "my-id", format_eui64(myid));
  if (!gethostname(host, sizeof(host)))
    blobmsg_add_string(&b, "host", host);

  ret = ubus_send_reply(ctx_local, req, b.head);
  if (ret)
    fprintf(stderr, "Failed to send reply: %s\n", ubus_strerror(ret));

  return ret;
}

// Appends an exported route message entry to the buffer.
static void babeld_add_xroute_buf(struct xroute *xroute, struct blob_buf *b) {
  void *prefix;

  prefix = blobmsg_open_table(b, format_prefix(xroute->prefix, xroute->plen));

  blobmsg_add_string(b, "src-prefix",
                     format_prefix(xroute->src_prefix, xroute->src_plen));
  blobmsg_add_u32(b, "metric", xroute->metric);
  blobmsg_close_table(b, prefix);
}

// Sends an exported routes message on ubus socket, splitting apart IPv4 and
// IPv6 routes.
static int babeld_ubus_get_xroutes(struct ubus_context *ctx_local,
                                   struct ubus_object *obj,
                                   struct ubus_request_data *req,
                                   const char *method, struct blob_attr *msg) {
  struct blob_buf b = {0};
  struct xroute_stream *xroutes;
  struct xroute_list_entry *cur, *tmp;
  void *ipv4, *ipv6;
  int ret;
  LIST_HEAD(xroute_ipv4_list);
  LIST_HEAD(xroute_ipv6_list);

  xroutes = xroute_stream();
  if (xroutes) {
    while (1) {
      struct xroute *xroute = xroute_stream_next(xroutes);
      if (xroute == NULL)
        break;

      struct xroute_list_entry *xr =
          calloc(1, sizeof(struct xroute_list_entry));
      xr->xroute = xroute;

      if (v4mapped(xroute->prefix)) {
        list_add(&xr->list, &xroute_ipv4_list);
      } else {
        list_add(&xr->list, &xroute_ipv6_list);
      }
    }
    xroute_stream_done(xroutes);
  }

  blob_buf_init(&b, 0);
  ipv4 = blobmsg_open_table(&b, "IPv4");
  list_for_each_entry_safe(cur, tmp, &xroute_ipv4_list, list) {
    babeld_add_xroute_buf(cur->xroute, &b);
    list_del(&cur->list);
    free(cur);
  }
  blobmsg_close_table(&b, ipv4);

  ipv6 = blobmsg_open_table(&b, "IPv6");
  list_for_each_entry_safe(cur, tmp, &xroute_ipv6_list, list) {
    babeld_add_xroute_buf(cur->xroute, &b);
    list_del(&cur->list);
    free(cur);
  }
  blobmsg_close_table(&b, ipv6);

  ret = ubus_send_reply(ctx_local, req, b.head);
  if (ret)
    fprintf(stderr, "Failed to send reply: %s\n", ubus_strerror(ret));

  return ret;
}

// Appends an route message entry to the buffer.
static void babeld_add_route_buf(struct babel_route *route,
                                 struct blob_buf *b) {
  void *prefix;
  char channels[100];

  if (route->channels_len == 0) {
    channels[0] = '\0';
  } else {
    int i, j = 0;
    snprintf(channels, sizeof(channels), " chan (");
    j = strlen(channels);
    for (i = 0; i < route->channels_len; i++) {
      if (i > 0)
        channels[j++] = ',';
      snprintf(channels + j, sizeof(channels) - j, "%u",
               (unsigned)route->channels[i]);
      j = strlen(channels);
    }
    snprintf(channels + j, sizeof(channels) - j, ")");
  }

  prefix = blobmsg_open_table(
      b, format_prefix(route->src->prefix, route->src->plen));

  blobmsg_add_string(
      b, "src-prefix",
      format_prefix(route->src->src_prefix, route->src->src_plen));
  blobmsg_add_u32(b, "route_metric", route_metric(route));
  blobmsg_add_u32(b, "route_smoothed_metric", route_smoothed_metric(route));
  blobmsg_add_u32(b, "refmetric", route->refmetric);
  blobmsg_add_string(b, "id", format_eui64(route->src->id));
  blobmsg_add_u32(b, "seqno", (uint32_t)route->seqno);
  blobmsg_add_string(b, "channels", channels);
  blobmsg_add_u32(b, "age", (int)(now.tv_sec - route->time));
  blobmsg_add_string(b, "via", format_address(route->neigh->address));
  if (memcmp(route->nexthop, route->neigh->address, 16) != 0)
    blobmsg_add_string(b, "nexthop", format_address(route->nexthop));

  blobmsg_add_u8(b, "installed", route->installed);
  blobmsg_add_u8(b, "feasible", route_feasible(route));

  blobmsg_close_table(b, prefix);
}

// Sends received routes message on ubus socket, splitting apart IPv4 and IPv6
// routes.
static int babeld_ubus_get_routes(struct ubus_context *ctx_local,
                                  struct ubus_object *obj,
                                  struct ubus_request_data *req,
                                  const char *method, struct blob_attr *msg) {
  struct blob_buf b = {0};
  struct route_stream *routes;
  struct route_list_entry *cur, *tmp;
  void *prefix, *ipv4, *ipv6;
  int ret;
  LIST_HEAD(route_ipv4_list);
  LIST_HEAD(route_ipv6_list);

  blob_buf_init(&b, 0);

  routes = route_stream(0);
  if (routes) {
    while (1) {
      struct babel_route *route = route_stream_next(routes);
      if (route == NULL)
        break;
      struct route_list_entry *r = calloc(1, sizeof(struct route_list_entry));
      r->route = route;

      if (v4mapped(route->src->prefix)) {
        list_add(&r->list, &route_ipv4_list);
      } else {
        list_add(&r->list, &route_ipv6_list);
      }
    }
    route_stream_done(routes);
  }

  blob_buf_init(&b, 0);
  ipv4 = blobmsg_open_table(&b, "IPv4");
  list_for_each_entry_safe(cur, tmp, &route_ipv4_list, list) {
    babeld_add_route_buf(cur->route, &b);
    list_del(&cur->list);
    free(cur);
  }
  blobmsg_close_table(&b, ipv4);

  ipv6 = blobmsg_open_table(&b, "IPv6");
  list_for_each_entry_safe(cur, tmp, &route_ipv6_list, list) {
    babeld_add_route_buf(cur->route, &b);
    list_del(&cur->list);
    free(cur);
  }
  blobmsg_close_table(&b, ipv6);

  ret = ubus_send_reply(ctx_local, req, b.head);
  if (ret)
    fprintf(stderr, "Failed to send reply: %s\n", ubus_strerror(ret));

  return ret;
}

// Appends an neighbour entry to the buffer.
static void babeld_add_neighbour_buf(struct neighbour *neigh,
                                     struct blob_buf *b) {
  void *neighbour;

  neighbour = blobmsg_open_table(b, format_address(neigh->address));
  blobmsg_add_string(b, "dev", neigh->ifp->name);
  blobmsg_add_u32(b, "hello-reach", neigh->hello.reach);
  blobmsg_add_u32(b, "uhello-reach", neigh->uhello.reach);
  blobmsg_add_u32(b, "rxcost", neighbour_rxcost(neigh));
  blobmsg_add_u32(b, "txcost", neigh->txcost);
  blobmsg_add_string(b, "rtt", format_thousands(neigh->rtt));
  blobmsg_add_u32(b, "channel", neigh->ifp->channel);
  blobmsg_add_u8(b, "if_up", if_up(neigh->ifp));
  blobmsg_close_table(b, neighbour);
}

// Sends neighbours message on ubus socket, splitting apart IPv4 and IPv6
// neighbours.
static int babeld_ubus_get_neighbours(struct ubus_context *ctx_local,
                                      struct ubus_object *obj,
                                      struct ubus_request_data *req,
                                      const char *method,
                                      struct blob_attr *msg) {
  struct blob_buf b = {0};
  struct neighbour *neigh;
  struct neighbour_list_entry *cur, *tmp;
  void *ipv4, *ipv6;
  int ret;
  LIST_HEAD(neighbour_ipv4_list);
  LIST_HEAD(neighbour_ipv6_list);

  blob_buf_init(&b, 0);

  FOR_ALL_NEIGHBOURS(neigh) {
    struct neighbour_list_entry *n =
        calloc(1, sizeof(struct neighbour_list_entry));
    n->neighbour = neigh;
    if (v4mapped(neigh->address)) {
      list_add(&n->list, &neighbour_ipv4_list);
    } else {
      list_add(&n->list, &neighbour_ipv6_list);
    }
  }

  blob_buf_init(&b, 0);

  ipv4 = blobmsg_open_table(&b, "IPv4");
  list_for_each_entry_safe(cur, tmp, &neighbour_ipv4_list, list) {
    babeld_add_neighbour_buf(cur->neighbour, &b);
    list_del(&cur->list);
    free(cur);
  }
  blobmsg_close_table(&b, ipv4);

  ipv6 = blobmsg_open_table(&b, "IPv6");
  list_for_each_entry_safe(cur, tmp, &neighbour_ipv6_list, list) {
    babeld_add_neighbour_buf(cur->neighbour, &b);
    list_del(&cur->list);
    free(cur);
  }
  blobmsg_close_table(&b, ipv6);

  ret = ubus_send_reply(ctx_local, req, b.head);
  if (ret)
    fprintf(stderr, "Failed to send reply: %s\n", ubus_strerror(ret));

  return ret;
}

// List of functions we expose via the ubus bus.
static const struct ubus_method babeld_methods[] = {
    UBUS_METHOD_NOARG("get_info", babeld_ubus_babeld_info),
    UBUS_METHOD_NOARG("get_xroutes", babeld_ubus_get_xroutes),
    UBUS_METHOD_NOARG("get_routes", babeld_ubus_get_routes),
    UBUS_METHOD_NOARG("get_neighbours", babeld_ubus_get_neighbours),
};

// Definition of the ubus object type.
static struct ubus_object_type babeld_object_type =
    UBUS_OBJECT_TYPE("babeld", babeld_methods);

// Object we announce via the ubus bus.
static struct ubus_object babeld_object = {
    .name = "babeld",
    .type = &babeld_object_type,
    .methods = babeld_methods,
    .n_methods = ARRAY_SIZE(babeld_methods),
};

// Registers handlers for babel methods in the global ubus context.
static bool ubus_init_object() {
  int ret;

  ret = ubus_add_object(shared_ctx, &babeld_object);
  if (ret) {
    fprintf(stderr, "Failed to add object: %s\n", ubus_strerror(ret));
    return false;
  }

  return true;
}

// Initializes the global ubus context, connecting to the bus to be able to
// receive and send messages.
static bool babeld_ubus_init(void) {
  if (shared_ctx)
    return true;

  shared_ctx = ubus_connect(NULL);
  if (!shared_ctx)
    return false;

  return true;
}

void ubus_notify_route(struct babel_route *route, int kind) {
  struct blob_buf b = {0};
  char method[50]; // possible methods are route.change, route.add, route.flush

  if (!babeld_object.has_subscribers)
    return;

  if (!route)
    return;

  if (!shared_ctx)
    return;

  blob_buf_init(&b, 0);
  babeld_add_route_buf(route, &b);
  snprintf(method, sizeof(method), "route.%s", local_kind(kind));
  ubus_notify(shared_ctx, &babeld_object, method, b.head, -1);
}

void ubus_notify_xroute(struct xroute *xroute, int kind) {
  struct blob_buf b = {0};
  char method[50]; // possible methods are xroute.change, xroute.add,
                   // xroute.flush

  if (!babeld_object.has_subscribers)
    return;

  if (!xroute)
    return;

  if (!shared_ctx)
    return;

  blob_buf_init(&b, 0);
  babeld_add_xroute_buf(xroute, &b);
  snprintf(method, sizeof(method), "xroute.%s", local_kind(kind));
  ubus_notify(shared_ctx, &babeld_object, method, b.head, -1);
}

void ubus_notify_neighbour(struct neighbour *neigh, int kind) {
  struct blob_buf b = {0};
  char method[50]; // possible methods are neigh.change, neigh.add, neigh.flush

  if (!babeld_object.has_subscribers)
    return;

  if (!neigh)
    return;

  if (!shared_ctx)
    return;

  blob_buf_init(&b, 0);
  babeld_add_neighbour_buf(neigh, &b);
  snprintf(method, sizeof(method), "neigh.%s", local_kind(kind));
  ubus_notify(shared_ctx, &babeld_object, method, b.head, -1);
}

void babeld_ubus_receive(fd_set *readfds) {
  if (!shared_ctx)
    return;
  if (FD_ISSET(shared_ctx->sock.fd, readfds))
    ubus_handle_event(shared_ctx);
}

int babeld_ubus_add_read_sock(fd_set *readfds, int maxfd) {
  if (!shared_ctx)
    return maxfd;

  FD_SET(shared_ctx->sock.fd, readfds);
  return MAX(maxfd, shared_ctx->sock.fd);
}

bool babeld_add_ubus() {
  if (!babeld_ubus_init()) {
    fprintf(stderr, "Failed to initialize ubus!\n");
    return false;
  }

  if (!ubus_init_object()) {
    fprintf(stderr, "Failed to add objects to ubus!\n");
    return false;
  }

  return true;
}
