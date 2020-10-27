/* Please avoid adding hacks here - instead add it to mac80211/backports.git */

#undef CONFIG_MODULE_STRIPPED

#include <linux/version.h>	/* LINUX_VERSION_CODE */
#include <linux/types.h>

#if LINUX_VERSION_CODE < KERNEL_VERSION(4, 15, 0)

#include <linux/netdevice.h>

#define netdev_master_upper_dev_link(dev, upper_dev, upper_priv, upper_info, extack) ({\
	BUILD_BUG_ON(extack != NULL); \
	netdev_master_upper_dev_link(dev, upper_dev, upper_priv, upper_info); \
})

#endif /* < KERNEL_VERSION(4, 15, 0) */


#if LINUX_VERSION_CODE < KERNEL_VERSION(4, 16, 0)

#ifndef sizeof_field
#define sizeof_field(TYPE, MEMBER) sizeof((((TYPE *)0)->MEMBER))
#endif

#endif /* < KERNEL_VERSION(4, 16, 0) */


#if LINUX_VERSION_CODE < KERNEL_VERSION(5, 1, 0)

#include_next <linux/igmp.h>
#include_next <net/addrconf.h>

static inline int batadv_ipv6_mc_check_mld1(struct sk_buff *skb)
{
	return ipv6_mc_check_mld(skb, NULL);
}

static inline int batadv_ipv6_mc_check_mld2(struct sk_buff *skb,
					    struct sk_buff **skb_trimmed)
{
	return ipv6_mc_check_mld(skb, skb_trimmed);
}

#define ipv6_mc_check_mld_get(_1, _2, ipv6_mc_check_mld_name, ...) ipv6_mc_check_mld_name
#define ipv6_mc_check_mld(...) \
	ipv6_mc_check_mld_get(__VA_ARGS__, batadv_ipv6_mc_check_mld2, batadv_ipv6_mc_check_mld1)(__VA_ARGS__)

static inline int batadv_ip_mc_check_igmp1(struct sk_buff *skb)
{
	return ip_mc_check_igmp(skb, NULL);
}

static inline int batadv_ip_mc_check_igmp2(struct sk_buff *skb,
					   struct sk_buff **skb_trimmed)
{
	return ip_mc_check_igmp(skb, skb_trimmed);
}

#define ip_mc_check_igmp_get(_1, _2, ip_mc_check_igmp_name, ...) ip_mc_check_igmp_name
#define ip_mc_check_igmp(...) \
	ip_mc_check_igmp_get(__VA_ARGS__, batadv_ip_mc_check_igmp2, batadv_ip_mc_check_igmp1)(__VA_ARGS__)

#endif /* < KERNEL_VERSION(5, 1, 0) */


#if LINUX_VERSION_CODE < KERNEL_VERSION(4, 15, 0)

#define batadv_softif_slave_add(__dev, __slave_dev, __extack) \
	batadv_softif_slave_add(__dev, __slave_dev)

#endif /* < KERNEL_VERSION(4, 15, 0) */


#if LINUX_VERSION_CODE < KERNEL_VERSION(5, 0, 0)

static inline int batadv_access_ok(int type, const void __user *p,
				   unsigned long size)
{
	return access_ok(type, p, size);
}

#ifdef access_ok
#undef access_ok
#endif

#define access_ok_get(_1, _2, _3 , access_ok_name, ...) access_ok_name
#define access_ok(...) \
	access_ok_get(__VA_ARGS__, access_ok3, access_ok2)(__VA_ARGS__)

#define access_ok2(addr, size)	batadv_access_ok(VERIFY_WRITE, (addr), (size))
#define access_ok3(type, addr, size)	batadv_access_ok((type), (addr), (size))

#endif /* < KERNEL_VERSION(5, 0, 0) */

#if LINUX_VERSION_CODE < KERNEL_VERSION(5, 4, 0)

#ifndef fallthrough
#if __GNUC__ > 7 && !defined(__CHECKER__)
# define fallthrough                    __attribute__((__fallthrough__))
#else
# define fallthrough                    do {} while (0)  /* fallthrough */
#endif
#endif

#endif /* < KERNEL_VERSION(5, 4, 0) */

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
