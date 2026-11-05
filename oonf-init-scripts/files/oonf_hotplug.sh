#!/bin/sh

case "${ACTION}" in
    ifup)
		[ -x "/etc/init.d/${DAEMON}" ] && /etc/init.d/${DAEMON} enabled && {
			logger -t "${DAEMON}[hotplug]" -p daemon.info 'reloading configuration'
			/etc/init.d/${DAEMON} reload
		}
	;;
esac
