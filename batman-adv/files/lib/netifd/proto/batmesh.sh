#!/bin/sh

. /lib/functions.sh
. ../netifd-proto.sh
init_proto "$@"

bat_load_module()
{
	[ -d "/sys/module/batman_adv/" ] && return
	load_modules /etc/modules.d/*-crc16 /etc/modules.d/*-crypto* /etc/modules.d/*-lib-crc* /etc/modules.d/*-batman-adv*
}

proto_batmesh_init_config() {
	proto_config_add_string "aggregated_ogms"
	proto_config_add_string "ap_isolation"
	proto_config_add_string "bonding"
	proto_config_add_string "bridge_loop_avoidance"
	proto_config_add_string "distributed_arp_table"
	proto_config_add_string "fragmentation"
	proto_config_add_string "gw_bandwidth"
	proto_config_add_string "gw_mode"
	proto_config_add_string "gw_sel_class"
	proto_config_add_string "hop_penalty"
	proto_config_add_string "network_coding"
	proto_config_add_string "log_level"
	proto_config_add_string "orig_interval"
	proto_config_add_string "vis_mode"
}

proto_batmesh_setup() {
	local config="$1"
	local mesh="$2"
	local aggregated_ogms ap_isolation bonding bridge_loop_avoidance distributed_arp_table fragmentation
	local gw_bandwidth gw_mode gw_sel_class hop_penalty network_coding log_level orig_interval vis_mode
	
	json_get_vars aggregated_ogms ap_isolation bonding bridge_loop_avoidance distributed_arp_table fragmentation
	json_get_vars gw_bandwidth gw_mode gw_sel_class hop_penalty network_coding log_level orig_interval vis_mode

	[ -n "$aggregate_ogms" ] && echo $aggregate_ogms > /sys/class/net/$mesh/mesh/aggregate_ogms
	[ -n "$ap_isolation" ] && echo $ap_isolation > /sys/class/net/$mesh/mesh/ap_isolation
	[ -n "$bonding" ] && echo $bonding > /sys/class/net/$mesh/mesh/bonding
	[ -n "$bridge_loop_avoidance" ] && echo $bridge_loop_avoidance > /sys/class/net/$mesh/mesh/bridge_loop_avoidance 2>&-
	[ -n "$distributed_arp_table" ] && echo $distributed_arp_table > /sys/class/net/$mesh/mesh/distributed_arp_table 2>&-
	[ -n "$fragmentation" ] && echo $fragmentation > /sys/class/net/$mesh/mesh/fragmentation
	[ -n "$gw_bandwidth" ] && echo $gw_bandwidth > /sys/class/net/$mesh/mesh/gw_bandwidth
	[ -n "$gw_mode" ] && echo $gw_mode > /sys/class/net/$mesh/mesh/gw_mode
	[ -n "$gw_sel_class" ] && echo $gw_sel_class > /sys/class/net/$mesh/mesh/gw_sel_class
	[ -n "$hop_penalty" ] && echo $hop_penalty > /sys/class/net/$mesh/mesh/hop_penalty
	[ -n "$network_coding" ] && echo $network_coding > /sys/class/net/$mesh/mesh/network_coding 2>&-
	[ -n "$log_level" ] && echo $log_level > /sys/class/net/$mesh/mesh/log_level 2>&-
	[ -n "$orig_interval" ] && echo $orig_interval > /sys/class/net/$mesh/mesh/orig_interval
	[ -n "$vis_mode" ] && echo $vis_mode > /sys/class/net/$mesh/mesh/vis_mode

	proto_init_update "$mesh" 1
	proto_send_update "$config"
}

add_protocol batmesh
