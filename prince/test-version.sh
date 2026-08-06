#!/bin/sh

# shellcheck shell=busybox

case "$PKG_NAME" in
prince)
	# prince requires a configuration file and does not provide any
	# option to report its version
	exit 0
	;;

*)
	echo "Untested package: $PKG_NAME" >&2
	exit 1
	;;
esac
