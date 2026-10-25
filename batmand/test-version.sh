#!/bin/sh

case "$PKG_NAME" in
batmand)
	batmand -v 2>&1 | grep -q "^B.A.T.M.A.N. $(echo "$PKG_VERSION" | sed 's/.*~//')"
	;;

*)
	echo "Untested package: $PKG_NAME" >&2
	exit 1
	;;
esac
