/*
    IPC integration of babeld with OpenWrt.
    
    The ubus interface offers following functions:
    - get_info
    - get_neighbours
    - get_xroutes
    - get_routes
    
    All output is divided into IPv4 and IPv6.
*/

#include <libubus.h>

// Whether to enable ubus bindings (boolean option).
extern int ubus_bindings;

/**
 * Initialize ubus interface.
 *
 * Connect to the ubus daemon and expose the ubus functions.
 *
 * @return if initializing ubus was successful
 */
bool babeld_add_ubus();

/**
 * Add ubus socket to given filedescriptor set.
 *
 * We need to check repeatedly if the ubus socket has something to read.
 * The functions allows to add the ubus socket to the normal while(1)-loop of babeld.
 *
 * @param readfs: the filedescriptor set
 * @param maxfd: the current maximum file descriptor
 * @return the maximum file descriptor
 */
int babeld_ubus_add_read_sock(fd_set* readfds, int maxfd);


/**
 * Check and process ubus socket.
 *
 * If the ubus-socket signals that data is available, the ubus_handle_event is called.
 */
void babeld_ubus_receive(fd_set* readfds);
