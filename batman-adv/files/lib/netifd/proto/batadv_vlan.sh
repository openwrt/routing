#!/bin/sh

[ -n "$INCLUDE_ONLY" ] || {
	. /lib/functions.sh
	. ../netifd-proto.sh
	init_proto "$@"
}

proto_batadv_vlan_init_config() {
	proto_config_add_string 'device'
	proto_config_add_boolean 'ap_isolation:bool'
}

proto_batadv_vlan_setup() {
	local config="$1"
	local iface="$2"

	# batadv_vlan options
	local device
	local ap_isolation

	json_get_vars device
	json_get_vars ap_isolation

	batadv_iface="${device%.*}"

	( proto_add_host_dependency "$config" '' "$batadv_iface" )

	batctl vlan "$device" ap_isolation "${ap_isolation:-0}"
	proto_init_update "$iface" 1
	proto_send_update "$config"
}

proto_batadv_vlan_teardown() {
	local cfg="$1"
}

add_protocol batadv_vlan
