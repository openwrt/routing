# 
# Copyright (C) 2009-2017 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.

include $(TOPDIR)/rules.mk

PKG_NAME:=bird
PKG_VERSION:=2.0.0
PKG_RELEASE:=1

PKG_SOURCE:=bird-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=ftp://bird.network.cz/pub/bird
PKG_MD5SUM:=a76300e1dabd9ae7178f12219ce7dc265438e48cc2d55667a94e00caf7028351
PKG_BUILD_DEPENDS:=libncurses libreadline
PKG_MAINTAINER:=Álvaro Fernández Rojas <noltari@gmail.com>

PKG_LICENSE:=GPL-2.0

include $(INCLUDE_DIR)/package.mk

define Package/bird/Default/description
BIRD is an internet routing daemon which manages TCP/IP routing tables
with support of modern routing protocols, easy to use configuration
interface and powerful route filtering language. It is lightweight and
efficient and therefore appropriate for small embedded routers.

endef

define Package/bird
  TITLE:=The BIRD Internet Routing Daemon
  URL:=http://bird.network.cz/
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=Routing and Redirection
  DEPENDS:=+libpthread
endef

define Package/birdc
  TITLE:=The BIRD command-line client
  URL:=http://bird.network.cz/
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=Routing and Redirection
  DEPENDS:=+bird +libreadline +libncurses
endef

define Package/birdcl
  TITLE:=The BIRD lightweight command-line client
  URL:=http://bird.network.cz/
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=Routing and Redirection
  DEPENDS:=+bird
endef

define Package/bird/description
$(call Package/bird/Default/description)

BIRD supports OSPFv2, RIPv2 and BGP protocols for IPv4 and
OSPFv3, RIPng and BGP protocols for IPv6.

In BGP, BIRD supports communities, multiprotocol extensions, MD5
authentication, 32bit AS numbers and could act as a route server or a
route reflector. BIRD also supports multiple RIBs, multiple kernel
routing tables and redistribution between the protocols with a powerful
configuration syntax.
endef

define Package/birdc/description
$(call Package/bird/Default/description)

This is a BIRD command-line client. It is used to send commands to BIRD,
commands can perform simple actions such as enabling/disabling of
protocols, telling BIRD to show various information, telling it to show
a routing table filtered by a filter, or asking BIRD to reconfigure.

Unless you can't afford dependency on ncurses and readline, you
should install BIRD command-line client together with BIRD.
endef

define Package/birdcl/description
$(call Package/bird/Default/description)

This is a BIRD lightweight command-line client. It is used to send commands
to BIRD, commands can perform simple actions such as enabling/disabling of
protocols, telling BIRD to show various information, telling it to show
a routing table filtered by a filter, or asking BIRD to reconfigure.
endef

CONFIGURE_ARGS += --with-linux-headers="$(LINUX_DIR)"

define Package/bird/conffiles
/etc/bird.conf
/etc/bird4.conf
/etc/bird6.conf
endef

define Package/bird/install
	$(INSTALL_DIR)  $(1)/usr/sbin
	$(INSTALL_BIN)  $(PKG_BUILD_DIR)/bird $(1)/usr/sbin/
	$(INSTALL_DIR)  $(1)/etc
	$(INSTALL_DATA) ./files/bird.conf $(1)/etc/
	$(INSTALL_DATA) ./files/bird4.conf $(1)/etc/
	$(INSTALL_DATA) ./files/bird6.conf $(1)/etc/
	$(INSTALL_DIR)  $(1)/etc/init.d
	$(INSTALL_BIN)  ./files/bird.init $(1)/etc/init.d/bird
endef

define Package/birdc/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/birdc $(1)/usr/sbin/
endef

define Package/birdcl/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/birdcl $(1)/usr/sbin/
endef

$(eval $(call BuildPackage,bird))
$(eval $(call BuildPackage,birdc))
$(eval $(call BuildPackage,birdcl))
