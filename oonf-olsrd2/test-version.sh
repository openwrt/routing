#!/bin/sh

# shellcheck shell=busybox

case "$PKG_NAME" in
oonf-olsrd2)
	# No upstream release tag exists for the tracked OONF master commit, so
	# PKG_VERSION is OpenWrt's standard <date>~<short-commit> snapshot string.
	# The build injects the commit via -D OONF_LIB_GIT, and olsrd2 reports it
	# in its -v output ("Git commit: <hash>"), so verify the binary reports the
	# pinned commit rather than skipping the check.
	olsrd2 -v 2>&1 | grep -F "${PKG_VERSION##*~}"
	;;
*)
	echo "Untested package: $PKG_NAME" >&2
	exit 1
	;;
esac
