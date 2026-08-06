#!/bin/sh

# shellcheck shell=busybox

case "$PKG_NAME" in
bmx7)
	# The version of bmx7 is derived from the source date, which the
	# binary does not report. Running `bmx7 -v` is not suitable for
	# CI either, as it first generates the node RSA key, which can
	# take a very long time on emulated architectures.
	exit 0
	;;

bmx7-*)
	# Plugins are libraries and do not provide version information
	exit 0
	;;

*)
	echo "Untested package: $PKG_NAME" >&2
	exit 1
	;;
esac
