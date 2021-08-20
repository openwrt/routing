/* Please avoid adding hacks here - instead add it to mac80211/backports.git */

#undef CONFIG_MODULE_STRIPPED

#include <linux/version.h>	/* LINUX_VERSION_CODE */
#include <linux/types.h>

#if LINUX_VERSION_IS_LESS(5, 10, 0)

#include <linux/if_bridge.h>

struct batadv_br_ip {
	union {
		__be32  ip4;
#if IS_ENABLED(CONFIG_IPV6)
		struct in6_addr ip6;
#endif
	} dst;
	__be16          proto;
	__u16           vid;
};

struct batadv_br_ip_list {
	struct list_head list;
	struct batadv_br_ip addr;
};

#if 0
/* "static" dropped to force compiler to evaluate it as part of multicast.c
 * might need to be added again and then called in some kind of dummy
 * compat.c in case this header is included in multiple files.
 */
inline void __batadv_br_ip_list_check(void)
{
	BUILD_BUG_ON(sizeof(struct batadv_br_ip_list) != sizeof(struct br_ip_list));
	BUILD_BUG_ON(offsetof(struct batadv_br_ip_list, list) != offsetof(struct br_ip_list, list));
	BUILD_BUG_ON(offsetof(struct batadv_br_ip_list, addr) != offsetof(struct br_ip_list, addr));

	BUILD_BUG_ON(sizeof(struct batadv_br_ip) != sizeof(struct br_ip));
	BUILD_BUG_ON(offsetof(struct batadv_br_ip, dst.ip4) != offsetof(struct br_ip, u.ip4));
	BUILD_BUG_ON(offsetof(struct batadv_br_ip, dst.ip6) != offsetof(struct br_ip, u.ip6));
	BUILD_BUG_ON(offsetof(struct batadv_br_ip, proto) != offsetof(struct br_ip, proto));
	BUILD_BUG_ON(offsetof(struct batadv_br_ip, vid) != offsetof(struct br_ip, vid));
}
#endif

#define br_ip batadv_br_ip
#define br_ip_list batadv_br_ip_list

#endif /* LINUX_VERSION_IS_LESS(5, 10, 0) */

#if LINUX_VERSION_IS_LESS(5, 14, 0)

#include <net/addrconf.h>

#if IS_ENABLED(CONFIG_IPV6)
static inline bool
br_multicast_has_router_adjacent(struct net_device *dev, int proto)
{
	struct list_head bridge_mcast_list = LIST_HEAD_INIT(bridge_mcast_list);
	struct br_ip_list *br_ip_entry, *tmp;
	int ret;

	if (proto != ETH_P_IPV6)
		return true;

	ret = br_multicast_list_adjacent(dev, &bridge_mcast_list);
	if (ret < 0)
		return true;

	ret = false;

	list_for_each_entry_safe(br_ip_entry, tmp, &bridge_mcast_list, list) {
		if (br_ip_entry->addr.proto == htons(ETH_P_IPV6) &&
		    ipv6_addr_is_ll_all_routers(&br_ip_entry->addr.dst.ip6))
			ret = true;

		list_del(&br_ip_entry->list);
		kfree(br_ip_entry);
	}

	return ret;
}
#else
static inline bool
br_multicast_has_router_adjacent(struct net_device *dev, int proto)
{
	return true;
}
#endif

#endif /* LINUX_VERSION_IS_LESS(5, 14, 0) */

/* <DECLARE_EWMA> */

#include <linux/version.h>
#include_next <linux/average.h>

#include <linux/bug.h>

#ifdef DECLARE_EWMA
#undef DECLARE_EWMA
#endif /* DECLARE_EWMA */

/*
 * Exponentially weighted moving average (EWMA)
 *
 * This implements a fixed-precision EWMA algorithm, with both the
 * precision and fall-off coefficient determined at compile-time
 * and built into the generated helper funtions.
 *
 * The first argument to the macro is the name that will be used
 * for the struct and helper functions.
 *
 * The second argument, the precision, expresses how many bits are
 * used for the fractional part of the fixed-precision values.
 *
 * The third argument, the weight reciprocal, determines how the
 * new values will be weighed vs. the old state, new values will
 * get weight 1/weight_rcp and old values 1-1/weight_rcp. Note
 * that this parameter must be a power of two for efficiency.
 */

#define DECLARE_EWMA(name, _precision, _weight_rcp)			\
	struct ewma_##name {						\
		unsigned long internal;					\
	};								\
	static inline void ewma_##name##_init(struct ewma_##name *e)	\
	{								\
		BUILD_BUG_ON(!__builtin_constant_p(_precision));	\
		BUILD_BUG_ON(!__builtin_constant_p(_weight_rcp));	\
		/*							\
		 * Even if you want to feed it just 0/1 you should have	\
		 * some bits for the non-fractional part...		\
		 */							\
		BUILD_BUG_ON((_precision) > 30);			\
		BUILD_BUG_ON_NOT_POWER_OF_2(_weight_rcp);		\
		e->internal = 0;					\
	}								\
	static inline unsigned long					\
	ewma_##name##_read(struct ewma_##name *e)			\
	{								\
		BUILD_BUG_ON(!__builtin_constant_p(_precision));	\
		BUILD_BUG_ON(!__builtin_constant_p(_weight_rcp));	\
		BUILD_BUG_ON((_precision) > 30);			\
		BUILD_BUG_ON_NOT_POWER_OF_2(_weight_rcp);		\
		return e->internal >> (_precision);			\
	}								\
	static inline void ewma_##name##_add(struct ewma_##name *e,	\
					     unsigned long val)		\
	{								\
		unsigned long internal = READ_ONCE(e->internal);	\
		unsigned long weight_rcp = ilog2(_weight_rcp);		\
		unsigned long precision = _precision;			\
									\
		BUILD_BUG_ON(!__builtin_constant_p(_precision));	\
		BUILD_BUG_ON(!__builtin_constant_p(_weight_rcp));	\
		BUILD_BUG_ON((_precision) > 30);			\
		BUILD_BUG_ON_NOT_POWER_OF_2(_weight_rcp);		\
									\
		WRITE_ONCE(e->internal, internal ?			\
			(((internal << weight_rcp) - internal) +	\
				(val << precision)) >> weight_rcp :	\
			(val << precision));				\
	}

/* </DECLARE_EWMA> */
