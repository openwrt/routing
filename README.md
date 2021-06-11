# OpenWrt Routing Feed

## Description

This OpenWrt package feed contains community maintained routing packages.

## Usage


This repository is intended to be layered on-top of an OpenWrt buildroot.
If you do not have an OpenWrt buildroot installed, see the documentation at:
[OpenWrt Buildroot – Installation][1] on the OpenWrt support site.

This feed is enabled by default. To install all its package definitions, run:

```
./scripts/feeds update routing
./scripts/feeds install -a -p routing
```

[1]: https://openwrt.org/docs/guide-developer/build-system/install-buildsystem
