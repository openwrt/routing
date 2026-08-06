#!/bin/sh

# shellcheck shell=busybox

case "$PKG_NAME" in
pimbd)
	# The package version is derived from the source date and git
	# hash, which the binary does not report
	exit 0
	;;

*)
	echo "Untested package: $PKG_NAME" >&2
	exit 1
	;;
esac
