#!/bin/sh

# shellcheck shell=busybox

case "$PKG_NAME" in
ohybridproxy|zonestitcher)
	# The package version is derived from the source date and git
	# hash, which the binaries do not report
	exit 0
	;;

*)
	echo "Untested package: $PKG_NAME" >&2
	exit 1
	;;
esac
