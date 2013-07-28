#!/bin/sh

. /lib/functions.sh
. ../netifd-proto.sh
init_proto "$@"

bat_load_module()
{
	[ -d "/sys/module/batman_adv/" ] && return
	load_modules /etc/modules.d/*-crc16 /etc/modules.d/*-crypto* /etc/modules.d/*-lib-crc* /etc/modules.d/*-batman-adv*
}

proto_batadv_init_config() {
	proto_config_add_string "mesh"
}

proto_batadv_setup() {
	local config="$1"
	local iface="$2"

	local mesh
	json_get_vars mesh

	bat_load_module

	echo "$mesh" > "/sys/class/net/$iface/batman_adv/mesh_iface"
	proto_init_update "$iface" 1
	proto_send_update "$config"
}

proto_batadv_teardown() {
	local config="$1"
	local iface="$2"

	echo "none" > "/sys/class/net/$iface/batman_adv/mesh_iface" || true
}

add_protocol batadv
