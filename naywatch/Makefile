# SPDX-License-Identifier: GPL-2.0-only
#
# Copyright (C) 2021 Nick Hainke <vincent@systemli.org>
#

include $(TOPDIR)/rules.mk

PKG_NAME:=naywatch
PKG_VERSION:=1
PKG_RELEASE:=$(AUTORELEASE)

PKG_MAINTAINER:=Nick Hainke <vincent@systemli.org>
PKG_LICENSE:=GPL-2.0-only

include $(INCLUDE_DIR)/package.mk

define Package/naywatch
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=Watchdog for IPv6 links
  PKGARCH:=all
  DEPENDS:=@IPV6 +owipcalc
endef

define Package/naywatch/description
Reboots or triggers watchdog if no link local neighbor is available.
endef

define Package/naywatch/conffiles
/etc/config/naywatch
endef

define Build/Compile
endef

define Package/naywatch/install
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/naywatch.init $(1)/etc/init.d/naywatch
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) ./files/naywatch.sh $(1)/usr/bin/naywatch
	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_DATA) ./files/naywatch.config $(1)/etc/config/naywatch
endef

$(eval $(call BuildPackage,naywatch))
