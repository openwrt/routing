#!/bin/sh

. /lib/functions.sh
. /lib/functions/network.sh

CHECK_INTERVAL=$1
shift
WATCHDOG_TIMEOUT=$1
shift
USE_WATCHDOG=$1
shift
SAVE_LOGS=$1
shift
INTERFACES="$*"

ACTIVE=0
NO_NEIGHBORS_COUNT=0
MIN_KICK=5

log() {
    local msg="$1"
    logger -t naywatch "$msg"
}

write_logs() {
    save_log() {
        eval $1 > /root/$(date +%s)-"$1".log
    }
    config_load naywatch
    config_list_foreach general save_cmd save_log
    sync
}

neighbors_available() {
    local phy

    for interface in $INTERFACES; do
        network_get_physdev phy $interface > /dev/null 2>&1
        linklocal=$(ip -6 a list dev $phy | grep "scope link" | awk '{print $2}' | sed 's/\/64//') 2> /dev/null
        ips=$(ping ff02::1%$phy -w5 -W5 -c2 | awk '/from/{print($4)}' | sed 's/.$//') 2> /dev/null
        for ip in $ips; do
            if [ $ip != $linklocal ] && [ $(owipcalc $ip linklocal) -eq 1 ]; then
                echo 1
                return 0
            fi
        done
    done

    echo 0
}

activate_watchdog() {
    # disable openwrt instrumentation:
    ubus call system watchdog '{"magicclose":true,"stop":true,"timeout":'${WATCHDOG_TIMEOUT}'}' > /dev/null
    exec 3>/dev/watchdog
}

reboot_now() {
    # copied from watch-cat
    reboot &

    [ "$1" -ge 1 ] && {
        sleep "$1"
        echo 1 >/proc/sys/kernel/sysrq
        echo b >/proc/sysrq-trigger
    }
}

no_neighbors() {
    log "No Neighbors Available!"

    NO_NEIGHBORS_COUNT=$(($NO_NEIGHBORS_COUNT+1))

    if [ $ACTIVE -eq 0 ]; then
        return 0
    fi

    if [ $SAVE_LOGS -eq 1 ]; then
        log "Saving Logs!"
        write_logs
    fi

    if [ $USE_WATCHDOG -eq 0 ] && [ $NO_NEIGHBORS_COUNT -gt $MIN_KICK ]; then
        reboot_now 10
    fi
}

log "Naywatch Started!"

neighbors() {
    if [ $ACTIVE -eq 0 ]; then
        log "Naywatch Activated!"
    fi
    ACTIVE=1
    NO_NEIGHBORS_COUNT=0
    if [ $USE_WATCHDOG -eq 1 ]; then
        echo 1 >&3
    fi
}

not_active() {
    if [ $USE_WATCHDOG -eq 1 ]; then
        echo 1 >&3
    fi 
}

if [ $USE_WATCHDOG -eq 1 ]; then
    activate_watchdog
fi

while [ 1 ]; do
    # first sleep
    sleep $CHECK_INTERVAL

    has_neighbor=$(neighbors_available)
    if [ $has_neighbor -eq 0 ] && [ $ACTIVE -eq 1 ]; then
        no_neighbors
    elif [ $has_neighbor -eq 1 ]; then
        neighbors
    else
        not_active
    fi
done

exit 0
