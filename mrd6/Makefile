#
# Copyright (C) 2006-2011 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=mrd6
PKG_RELEASE:=$(AUTORELEASE)

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/hugosantos/mrd6.git
PKG_SOURCE_DATE:=2013-11-30
PKG_SOURCE_VERSION:=c805eb33255dbc0b6647d463c6c67d1c9d3105a0
PKG_MIRROR_HASH:=976243b967c18fcbf64d26158898245264c6d03d498826b104e6c92406a8f64f

PKG_MAINTAINER:=Steven Barth <cyrus@openwrt.org>
PKG_LICENSE:=GPL-2.0-or-later
PKG_LICENSE_FILES:=COPYING

PKG_INSTALL:=1
PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk

define Package/mrd6
  SECTION:=net
  CATEGORY:=Network
  TITLE:=IPv6 multicast routing daemon
  URL:=http://fivebits.net/proj/mrd6
  DEPENDS:=@IPV6 +libstdcpp
endef

define Package/mrd6/description
 Multicast is becoming a major component in next generation networks, used 
 in several scenarios, from video broadcasting to multimedia conferencing. 
 In order to be implemented, new technology needs supporting hardware and 
 software across a set of devices and systems. MRD6 is an implementation of 
 a modular IPv6 Multicast Routing Framework for the Linux operating system 
 and provides MLDv2 (as well as MLDv1), PIM-SM and MBGP support.
endef

MRD6_MAKEFLAGS:= \
	$(TARGET_CONFIGURE_OPTS) \
	OPTIMIZE=yes \
	SPACE_OPTIMIZE=yes \
	FULL_STATIC=no \
	CFLAGS="$(TARGET_CFLAGS) $(TARGET_CPPFLAGS) -DNO_INET6_OPTION -fno-builtin -fno-rtti" \
	LDFLAGS="$(TARGET_LDFLAGS) -ldl -lm" \
	MODULE_CXX="\$$$$(CC) -shared \$$$$(CXXFLAGS) \$$$$(LDFLAGS)" \
	DESTDIR="$(PKG_INSTALL_DIR)" \
	PREFIX="/usr"

define Build/Compile
	+$(MAKE) $(PKG_JOBS) -C $(PKG_BUILD_DIR)/src $(MRD6_MAKEFLAGS) all
endef

define Build/Install
	$(MAKE) -C $(PKG_BUILD_DIR)/src $(MRD6_MAKEFLAGS) install
endef

define Package/mrd6/conffiles
/etc/mrd6.conf
endef

define Package/mrd6/install
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_CONF) ./files/mrd6.conf $(1)/etc
	$(INSTALL_BIN) ./files/mrd6.init $(1)/etc/init.d/mrd6
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/sbin/mrd $(1)/usr/sbin/mrd6
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/mrd6sh $(1)/usr/bin/mrd6sh
	$(INSTALL_DIR) $(1)/usr/lib/mrd6
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/lib/mrd6/bgp.so $(1)/usr/lib/mrd6/bgp.so
endef

$(eval $(call BuildPackage,mrd6))
