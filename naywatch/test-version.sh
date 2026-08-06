#!/bin/sh

# shellcheck shell=busybox

case "$PKG_NAME" in
naywatch)
	# naywatch is a watchdog shell script which does not provide any
	# option to report its version. It must not be executed during
	# the CI runtime tests, since it may trigger a reboot.
	exit 0
	;;

*)
	echo "Untested package: $PKG_NAME" >&2
	exit 1
	;;
esac
