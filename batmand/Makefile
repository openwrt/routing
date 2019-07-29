#
# Copyright (C) 2008-2011 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=batmand

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://git.open-mesh.org/batmand.git
PKG_REV:=b67a7087b51d7a5e90d27ac39116d1f57257c86e
PKG_VERSION:=1440
PKG_RELEASE:=1
PKG_LICENSE:=GPL-2.0

PKG_SOURCE_VERSION:=$(PKG_REV)
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE:=$(PKG_SOURCE_SUBDIR).tar.gz
PKG_MIRROR_HASH:=ceb8e0e399f79b1b663594fcf9642e1efc40e696a7604daf709c77da9b6ec52f
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_SOURCE_SUBDIR)

include $(INCLUDE_DIR)/package.mk

define Package/batmand
  URL:=https://www.open-mesh.org/
  MAINTAINER:=Corinna "Elektra" Aichele <onelektra@gmx.net>
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=Routing and Redirection
  DEPENDS:=+libpthread +kmod-tun
  TITLE:=B.A.T.M.A.N. layer 3 routing daemon
endef

define Package/batmand/description
B.A.T.M.A.N. layer 3 routing daemon
endef

MAKE_FLAGS += \
	EXTRA_CFLAGS='-DDEBUG_MALLOC -DMEMORY_USAGE -DPROFILE_DATA -DREVISION_VERSION=\"\ rv$(PKG_REV)\" -D_GNU_SOURCE' \
	REVISION="$(PKG_REV)" \
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
