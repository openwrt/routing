#!/bin/sh

# shellcheck shell=busybox

case "$PKG_NAME" in
cjdns)
	# cjdroute crashes on some of the emulated CI targets (i386 and
	# arm) long before it prints anything, so it cannot be executed
	# here. Check that the packaged version is the one compiled into
	# the binary, which is what `cjdroute --version` reports.
	strings /usr/sbin/cjdroute | grep -F "$PKG_VERSION"
	;;

cjdns-tests)
	# The test binary does not provide version information
	exit 0
	;;

*)
	echo "Untested package: $PKG_NAME" >&2
	exit 1
	;;
esac
