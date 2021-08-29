#!/bin/sh

. /lib/functions.sh

log() {
    local msg="$1"
    logger -t owmd -s "$msg"
}

main() {
    log "started!"

    config_load owmd
    config_get cfg_interval general interval 600
    config_get server general server api.openwifi.net
    config_get port general port 80

    while :;
    do
        owm $server $port
        sleep $cfg_interval
    done
}

main
