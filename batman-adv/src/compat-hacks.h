/* Please avoid adding hacks here - instead add it to mac80211/backports.git */

#undef CONFIG_MODULE_STRIPPED

#include <linux/version.h>	/* LINUX_VERSION_CODE */
#include <linux/types.h>

#if LINUX_VERSION_IS_LESS(6, 0, 0)

#define __vstring(item, fmt, ap) __dynamic_array(char, item, 256)
#define __assign_vstr(dst, fmt, va) \
	WARN_ON_ONCE(vsnprintf(__get_dynamic_array(dst), 256, fmt, *va) >= 256)

#endif /* LINUX_VERSION_IS_LESS(6, 0, 0) */

#if LINUX_VERSION_IS_LESS(6, 2, 0)

#include <linux/random.h>

#define genl_split_ops genl_ops

static inline u32 batadv_get_random_u32_below(u32 ep_ro)
{
	return prandom_u32_max(ep_ro);
}

#define get_random_u32_below batadv_get_random_u32_below

#endif /* LINUX_VERSION_IS_LESS(6, 2, 0) */

#if LINUX_VERSION_IS_LESS(6, 4, 0)

#include <linux/if_vlan.h>

/* Prefer this version in TX path, instead of
 * skb_reset_mac_header() + vlan_eth_hdr()
 */
static inline struct vlan_ethhdr *skb_vlan_eth_hdr(const struct sk_buff *skb)
{
	return (struct vlan_ethhdr *)skb->data;
}

#endif /* LINUX_VERSION_IS_LESS(6, 4, 0) */

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
