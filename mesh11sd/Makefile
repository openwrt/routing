# SPDX-License-Identifier: GPL-2.0-only
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
# Copyright (C) 2022 - 2025 BlueWave Projects and Services  <licence@blue-wave.net>
#

include $(TOPDIR)/rules.mk

PKG_NAME:=mesh11sd
PKG_VERSION:=5.1.3
PKG_RELEASE:=1

PKG_MAINTAINER:=Rob White <rob@blue-wave.net>
PKG_LICENSE:=GPL-2.0-or-later
PKG_LICENSE_FILES:=LICENSE

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://codeload.github.com/opennds/mesh11sd/tar.gz/v$(PKG_VERSION)?
PKG_HASH:=aad1087b2b3e739293188896e1809727a9a4c4046aba2fb70f9d6d6042d92e9d

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
  Mesh11sd is a package that autonomously configures and manages all aspects of an 802.11s mesh network and its connected nodes.
  The package acts as a service daemon, dynamically setting mesh parameters across all nodes.
  It is particularly useful for simplifying setup, reducing manual configuration, and improving network reliability.
  Support for point to multi-point vxlan tunneling over the wireless backhaul is included as standard.
  A guest/iot type network is auto-configured without requiring complex vlan setup.
  If required, custom vlan trunking over the vxlan tunnel is supported.
  Mesh-gate access point usage is collected in a central database on the mesh portal.
  A command line interface is provided for reporting in json format output.
  An optional Customer/Client Premises Equipment (CPE) mode, greatly simplifies rollout of community WISP projects.
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
