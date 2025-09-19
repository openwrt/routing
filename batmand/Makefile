#
# Copyright (C) 2008-2011 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=batmand
PKG_RELEASE:=1

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://git.open-mesh.org/batmand.git
PKG_MIRROR_HASH:=bb8b74bea9f70ae91b3ef3ef089aa3149e3f5335b6e1db31ea7870d899b0a176
PKG_SOURCE_VERSION:=2f62b17d4132f82c4716b672101eb7faa916192a
PKG_SOURCE_DATE:=2022-12-31

PKG_LICENSE:=GPL-2.0-only
PKG_MAINTAINER:=Corinna Aichele <onelektra@gmx.net>

PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk

define Package/batmand
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=Routing and Redirection
  TITLE:=B.A.T.M.A.N. layer 3 routing daemon
  URL:=https://www.open-mesh.org/
  DEPENDS:=+libpthread +kmod-tun
endef

define Package/batmand/description
B.A.T.M.A.N. layer 3 routing daemon
endef

MAKE_FLAGS += \
	EXTRA_CFLAGS='-DDEBUG_MALLOC -DMEMORY_USAGE -DPROFILE_DATA -DREVISION_VERSION=\"\ rv$(PKG_SOURCE_VERSION)\" -D_GNU_SOURCE' \
	REVISION="$(PKG_SOURCE_VERSION)" \
	CC="$(TARGET_CC)" \
	UNAME="Linux" \
	batmand

define Package/batmand/install
	$(INSTALL_DIR) $(1)/usr/sbin $(1)/etc/config $(1)/etc/init.d
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/batmand $(1)/usr/sbin/
	$(INSTALL_BIN) ./files/etc/init.d/batmand $(1)/etc/init.d
	$(INSTALL_DATA) ./files/etc/config/batmand $(1)/etc/config
endef

define Package/batmand/conffiles
/etc/config/batmand
endef

$(eval $(call BuildPackage,batmand))
