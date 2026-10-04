#!/bin/sh

# shellcheck shell=busybox

case "$PKG_NAME" in
vis)
	# The version of vis is derived from the source date and git
	# hash, which the binary does not report. Check that the binary
	# starts and prints its version banner instead.
	vis -v 2>&1 | grep -F "B.A.T.M.A.N."
	;;

*)
	echo "Untested package: $PKG_NAME" >&2
	exit 1
	;;
esac
