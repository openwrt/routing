# SPDX-License-Identifier: GPL-2.0-only
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
# Copyright (C) 2022 - 2024 BlueWave Projects and Services  <licence@blue-wave.net>
#

include $(TOPDIR)/rules.mk

PKG_NAME:=mesh11sd
PKG_VERSION:=4.0.1
PKG_RELEASE:=1

PKG_MAINTAINER:=Rob White <rob@blue-wave.net>
PKG_LICENSE:=GPL-2.0-or-later
PKG_LICENSE_FILES:=LICENSE

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://codeload.github.com/opennds/mesh11sd/tar.gz/v$(PKG_VERSION)?
PKG_HASH:=8029a0e41487d322b1bb20df05fc3ef2073b1239977f2b430b20fe7cabfe71de
PKG_BUILD_DIR:=$(BUILD_DIR)/mesh11sd-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

define Package/mesh11sd
  SUBMENU:=Captive Portals
  SECTION:=net
  CATEGORY:=Network
  TITLE:=Dynamic 802.11s Mesh Configuration Daemon
  PKGARCH:=all
  URL:=https://github.com/opennds/mesh11sd
endef

define Package/mesh11sd/description
  Mesh11sd is a dynamic parameter configuration daemon for 802.11s mesh networks.
  It was originally designed to leverage 802.11s mesh networking at Captive Portal venues.
  This is the open source version and it enables easy and automated mesh network operation with multiple mesh nodes.
  It allows all mesh parameters supported by the wireless driver to be set in the uci config file.
  Settings take effect immediately without having to restart the wireless network.
  Mesh paths are stabilised when node coverage areas overlap and rssi thresholds and tx power can be dynamically adjusted.
  Default settings give rapid and reliable layer 2 mesh convergence.
  Without mesh11sd, many mesh parameters cannot be set in the uci wireless config file as the mesh interface must be up before the parameters can be set.
  Some of those that are supported, would fail to be implemented when the network is (re)started resulting in errors or dropped nodes.
  The mesh11sd daemon can dynamically check configured parameters and set them as required.
  In auto_config mode, upstream wan connectivity is checked (eg Internet feed) and when not present, layer 2 peer mode is autonomously enabled,
  and when it is present, layer 3 portal mode is enabled. This allows the same simple router configuration to be used on all meshnodes in the layer 2 mesh.
  Remote terminal sessions and remote file transfers are supported using the meshnode mac address as an identifier.
  This version does not require a Captive Portal to be running.
endef

define Package/mesh11sd/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/mesh11sd $(1)/usr/sbin
	$(INSTALL_CONF) $(PKG_BUILD_DIR)/linux_openwrt/mesh11sd/files/etc/config/mesh11sd $(1)/etc/config/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/linux_openwrt/mesh11sd/files/etc/init.d/mesh11sd $(1)/etc/init.d/
endef

define Package/mesh11sd/conffiles
/etc/config/mesh11sd
endef

define Build/Compile
endef

$(eval $(call BuildPackage,mesh11sd))
