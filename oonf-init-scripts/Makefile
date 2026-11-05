# SPDX-License-Identifier: GPL-2.0-only

include $(TOPDIR)/rules.mk

PKG_NAME:=oonf-init-scripts
PKG_VERSION:=0.9.1
PKG_RELEASE:=1

PKG_MAINTAINER:=Matthias Tarasiewicz <mt@riat.at>
PKG_LICENSE:=GPL-2.0-only

include $(INCLUDE_DIR)/package.mk

define Package/oonf-init-scripts
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=OLSR.org network framework
  TITLE:=Common OONF startup scripts
  PKGARCH:=all
  URL:=https://www.olsr.org/
  DEPENDS:=+jshn +ubus +uci
endef

define Package/oonf-init-scripts/description
  Shared shell helpers sourced by the OONF init scripts.
endef

define Build/Compile
endef

define Package/oonf-init-scripts/install
	$(INSTALL_DIR) $(1)/lib/functions
	$(INSTALL_DATA) ./files/oonf_init.sh    $(1)/lib/functions/oonf_init.sh
	$(INSTALL_DATA) ./files/oonf_hotplug.sh $(1)/lib/functions/oonf_hotplug.sh
endef

$(eval $(call BuildPackage,oonf-init-scripts))
