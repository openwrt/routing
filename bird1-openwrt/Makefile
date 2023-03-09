# SPDX-License-Identifier: GPL-3.0-or-later
#
# Copyright (C) 2014-2017 Eloi Carbó <eloicaso@openmailbox.org>
# Copyright (C) 2022-2023 Roger Pueyo Centelles <roger.pueyo@guifi.net>
#

include $(TOPDIR)/rules.mk

BIRD1_PKG := bird1
BIRD1_IPV4_PKG := $(BIRD1_PKG)-ipv4
BIRD1_IPV6_PKG := $(BIRD1_PKG)-ipv6
BIRD4 := bird4
BIRD6 := bird6

PKG_NAME := $(BIRD1_PKG)-openwrt
PKG_IPV4_NAME := $(BIRD1_IPV4_PKG)-openwrt
PKG_IPV6_NAME := $(BIRD1_IPV6_PKG)-openwrt
PKG_VERSION := 0.3
PKG_RELEASE := 5
PKG_BUILD_DIR := $(BUILD_DIR)/$(PKG_NAME)
PKG_LICENSE := GPL-3.0-or-later

PKG_UCI_NAME := $(BIRD1_PKG)-uci
PKG_LUCI_NAME := $(BIRD1_PKG)-luci
PKG_IPV4_UCI_NAME := $(BIRD1_IPV4_PKG)-uci
PKG_IPV6_UCI_NAME := $(BIRD1_IPV6_PKG)-uci
PKG_IPV4_LUCI_NAME := luci-app-$(BIRD1_IPV4_PKG)
PKG_IPV6_LUCI_NAME := luci-app-$(BIRD1_IPV6_PKG)

include $(INCLUDE_DIR)/package.mk

define Build/Prepare
endef

define Build/Compile
endef

define Package/$(PKG_UCI_NAME)/Default
  TITLE:=The BIRD UCI module (v1.6)
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=Routing and Redirection
  MAINTAINER:=Roger Pueyo Centelles <roger.pueyo@guifi.net>
  URL:=https://github.com/openwrt/bird1-openwrt/
  DEPENDS:=+libuci +uci
endef

define Package/$(PKG_LUCI_NAME)/Default
  TITLE:=LuCI support for BIRD (v1.6)
  SECTION:=luci
  CATEGORY:=LuCI
  SUBMENU:=3. Applications
  MAINTAINER:=Roger Pueyo Centelles <roger.pueyo@guifi.net>
  URL:=https://github.com/openwrt/bird1-openwrt/
  DEPENDS:=+luci-base +luci-compat
endef

define Package/$(PKG_UCI_NAME)/description
$(BIRD1_PKG) UCI integration module
endef

define Package/$(PKG_LUCI_NAME)/description
$(BIRD1_PKG) application for LuCI
endef

define Package/$(PKG_IPV4_UCI_NAME)
$(call Package/$(PKG_UCI_NAME)/Default)
  TITLE+= (IPv4)
  DEPENDS+= +$(BIRD1_IPV4_PKG)
endef

define Package/$(PKG_IPV6_UCI_NAME)
$(call Package/$(PKG_UCI_NAME)/Default)
  TITLE+= (IPv6)
  DEPENDS+= +$(BIRD1_IPV6_PKG)
endef

define Package/$(PKG_IPV4_LUCI_NAME)
$(call Package/$(PKG_LUCI_NAME)/Default)
  TITLE+= (IPv4)
  DEPENDS+= +$(PKG_IPV4_UCI_NAME)
endef

define Package/$(PKG_IPV6_LUCI_NAME)
$(call Package/$(PKG_LUCI_NAME)/Default)
  TITLE+= (IPv6)
  DEPENDS+= +$(PKG_IPV6_UCI_NAME)
endef

define Package/$(PKG_IPV4_UCI_NAME)/conffiles
/etc/config/$(BIRD4)
endef

define Package/$(PKG_IPV6_UCI_NAME)/conffiles
/etc/config/$(BIRD6)
endef

define Package/$(PKG_IPV4_UCI_NAME)/install
	$(INSTALL_DIR) $(1)/etc/$(BIRD4)/init.d
	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_DIR) $(1)/etc/$(BIRD4)/filters
	$(INSTALL_DIR) $(1)/etc/$(BIRD4)/functions
	$(INSTALL_BIN) ./$(PKG_IPV4_NAME)/src/init.d/$(BIRD4)* $(1)/etc/$(BIRD4)/init.d/
	$(CP) ./$(PKG_IPV4_NAME)/src/uci-defaults/* $(1)/etc/$(BIRD4)/init.d/
	$(INSTALL_CONF) ./$(PKG_IPV4_NAME)/src/config/$(BIRD4) $(1)/etc/config/
endef

define Package/$(PKG_IPV6_UCI_NAME)/install
	$(INSTALL_DIR) $(1)/etc/$(BIRD6)/init.d
	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_DIR) $(1)/etc/$(BIRD6)/filters
	$(INSTALL_DIR) $(1)/etc/$(BIRD6)/functions
	$(INSTALL_BIN) ./$(PKG_IPV6_NAME)/src/init.d/$(BIRD6)* $(1)/etc/$(BIRD6)/init.d/
	$(CP) ./$(PKG_IPV6_NAME)/src/uci-defaults/* $(1)/etc/$(BIRD6)/init.d/
	$(INSTALL_CONF) ./$(PKG_IPV6_NAME)/src/config/$(BIRD6) $(1)/etc/config/
endef

define Package/$(PKG_IPV4_UCI_NAME)/postinst
#!/bin/sh
if [ -z "$${IPKG_INSTROOT}" ]; then
    ( . /etc/$(BIRD4)/init.d/bird-uci-install-init.d $(BIRD4) ) && rm -f /etc/$(BIRD4)/init.d/bird-uci-install-init.d
    ( . /etc/$(BIRD4)/init.d/99-relocate-filters $(BIRD4) ) && rm -f /etc/$(BIRD4)/init.d/99-relocate-filters
    if [ -f /etc/sysupgrade.conf ] && ! grep $(BIRD4) /etc/sysupgrade.conf; then
        echo /etc/config/$(BIRD4) >> /etc/sysupgrade.conf
        echo /etc/$(BIRD4)/filters/ >> /etc/sysupgrade.conf
        echo /etc/$(BIRD4)/functions/ >> /etc/sysupgrade.conf
    fi
fi
endef

define Package/$(PKG_IPV6_UCI_NAME)/postinst
#!/bin/sh
if [ -z "$${IPKG_INSTROOT}" ]; then
    ( . /etc/$(BIRD6)/init.d/bird-uci-install-init.d $(BIRD6) ) && rm -f /etc/$(BIRD6)/init.d/bird-uci-install-init.d
    ( . /etc/$(BIRD6)/init.d/99-relocate-filters $(BIRD6) ) && rm -f /etc/$(BIRD6)/init.d/99-relocate-filters
    if [ -f /etc/sysupgrade.conf ] && ! grep $(BIRD6) /etc/sysupgrade.conf; then
        echo /etc/config/$(BIRD6) >> /etc/sysupgrade.conf
        echo /etc/$(BIRD6)/filters/ >> /etc/sysupgrade.conf
        echo /etc/$(BIRD6)/functions/ >> /etc/sysupgrade.conf
    fi
fi
endef

$(eval $(call BuildPackage,$(PKG_IPV4_UCI_NAME)))
$(eval $(call BuildPackage,$(PKG_IPV6_UCI_NAME)))

define Package/$(PKG_IPV4_LUCI_NAME)/install
	$(INSTALL_DIR) $(1)/usr/lib/lua/luci/controller/
	$(INSTALL_DIR) $(1)/usr/lib/lua/luci/model/cbi/$(BIRD4)/
	$(INSTALL_DIR) $(1)/usr/lib/lua/luci/view/$(BIRD4)/
	$(CP) ./$(PKG_IPV4_NAME)/src/model/* $(1)/usr/lib/lua/luci/model/cbi/$(BIRD4)/
	$(CP) ./$(PKG_IPV4_NAME)/src/controller/* $(1)/usr/lib/lua/luci/controller/
	$(CP) ./$(PKG_IPV4_NAME)/src/view/* $(1)/usr/lib/lua/luci/view/$(BIRD4)/
endef

define Package/$(PKG_IPV6_LUCI_NAME)/install
	$(INSTALL_DIR) $(1)/usr/lib/lua/luci/controller/
	$(INSTALL_DIR) $(1)/usr/lib/lua/luci/model/cbi/$(BIRD6)/
	$(INSTALL_DIR) $(1)/usr/lib/lua/luci/view/$(BIRD6)/
	$(CP) ./$(PKG_IPV6_NAME)/src/model/* $(1)/usr/lib/lua/luci/model/cbi/$(BIRD6)/
	$(CP) ./$(PKG_IPV6_NAME)/src/controller/* $(1)/usr/lib/lua/luci/controller/
	$(CP) ./$(PKG_IPV6_NAME)/src/view/* $(1)/usr/lib/lua/luci/view/$(BIRD6)/
endef

$(eval $(call BuildPackage,$(PKG_IPV4_LUCI_NAME)))
$(eval $(call BuildPackage,$(PKG_IPV6_LUCI_NAME)))
