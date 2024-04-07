#
# Copyright (C) 2014 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.

include $(TOPDIR)/rules.mk

PKG_NAME:=minimalist-pcproxy
PKG_RELEASE:=7

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/fingon/minimalist-pcproxy.git
PKG_SOURCE_DATE:=2014-12-12
PKG_SOURCE_VERSION:=2d6d1b0b0a3b79a9b4a9b0a7606a84600a967bcb
PKG_MIRROR_HASH:=26dcfe5fa2a4924a02830c243cf59d61055f43ec3df8eb77e86d74acf9ac034f

PKG_MAINTAINER:=Markus Stenberg <fingon@iki.fi>
PKG_LICENSE:=BSD-3-Clause
PKG_LICENSE_FILES:=LICENSE

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/minimalist-pcproxy
  SECTION:=net
  CATEGORY:=Network
  TITLE:=Lightweight PCP proxy
  URL:=https://github.com/fingon/minimalist-pcproxy
  DEPENDS:=+libubox @IPV6
endef

define Package/minimalist-pcproxy/description
  This package contains a daemon which can be used to forward
  PCP (Port Control Protocol - RFC6887) requests requests to PCP remote servers.

  In and of itself, it is not very useful, but combined with hnetd+miniupnpd
  it allows for control of NAT forwarding and firewall pinholes from multiple
  hops away.
endef

define Package/minimalist-pcproxy/install
	$(INSTALL_DIR) $(1)/usr/sbin/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/minimalist-pcproxy $(1)/usr/sbin/
	$(INSTALL_DIR) $(1)/etc/uci-defaults
	$(INSTALL_BIN) ./files/minimalist-pcproxy.defaults $(1)/etc/uci-defaults/x-minimalist-pcproxy.defaults
endef

define Package/minimalist-pcproxy/postinst
#!/bin/sh
[ -n "$${IPKG_INSTROOT}" ] || {
	(. /etc/uci-defaults/x-minimalist-pcproxy.defaults) && rm -f /etc/uci-defaults/x-minimalist-pcproxy.defaults
}
exit 0
endef

$(eval $(call BuildPackage,minimalist-pcproxy))
