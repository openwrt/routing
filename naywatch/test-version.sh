#!/bin/sh

# shellcheck shell=busybox

case "$PKG_NAME" in
naywatch)
	# naywatch takes positional arguments (check interval, watchdog
	# timeout, ...), not options, so a probe flag ends up as the
	# check interval and the script enters its monitoring loop
	# instead of reporting anything, until the probe timeout kills
	# it.
	exit 0
	;;

*)
	echo "Untested package: $PKG_NAME" >&2
	exit 1
	;;
esac
