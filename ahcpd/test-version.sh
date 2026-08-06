#!/bin/sh

# shellcheck shell=busybox

case "$PKG_NAME" in
ahcpd)
	# ahcpd does not provide any option to report its version.
	# Check that the binary starts and prints its usage instead.
	ahcpd 2>&1 | grep -F "Syntax: ahcpd"
	;;

*)
	echo "Untested package: $PKG_NAME" >&2
	exit 1
	;;
esac
