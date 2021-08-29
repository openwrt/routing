include $(TOPDIR)/rules.mk

PKG_NAME:=owm
PKG_VERSION:=1
PKG_RELEASE:=$(AUTORELEASE)

PKG_MAINTAINER:=Nick Hainke <vincent@systemli.org>
PKG_LICENSE:=GPL-2.0-only

include $(INCLUDE_DIR)/package.mk

define Package/owm
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=Open Wireless Map Client
  PKGARCH:=all
endef

define Package/owm/description
Sends data to open wireless map.
endef

define Package/owmd
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=Open Wireless Map Daemon
  PKGARCH:=all
  DEPENDS:=+owm
endef

define Package/owmd/description
Send Periodically updates to Open Wireless Map
endef

define Package/owmd/conffiles
/etc/config/owmd
endef

define Build/Compile
endef

define Package/owm/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) ./files/owm.sh $(1)/usr/bin/owm
endef

define Package/owmd/install
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/owmd.init $(1)/etc/init.d/owmd
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) ./files/owmd.sh $(1)/usr/bin/owmd
	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_DATA) ./files/owmd.config $(1)/etc/config/owmd
endef

$(eval $(call BuildPackage,owm))
$(eval $(call BuildPackage,owmd))
