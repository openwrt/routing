include $(TOPDIR)/rules.mk

PKG_NAME:=sroamd
PKG_SOURCE_DATE:=2021-07-27
PKG_RELEASE:=$(AUTORELEASE)

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/jech/sroamd.git
PKG_SOURCE_VERSION:=b5ce12633afcf9f0dce5bbeeca3ff20475cd17e4
PKG_MIRROR_HASH:=96020ff3e1d983f203e3971fa7378be4d244bf8d12969e46f31098aa6bf67f00

PKG_MAINTAINER:=Nick Hainke <vincent@systemli.org>
PKG_LICENSE:=MIT
PKG_LICENSE_FILES:=LICENCE

include $(INCLUDE_DIR)/package.mk

define Package/sroamd
  SECTION:=net
  CATEGORY:=Network
  TITLE:=Sroamd (Simple Roaming Daemon)
  URL:=https://github.com/jech/sroamd
  DEPENDS:=+libnl-core +libnl-genl +libnl-route
endef

define Package/sroamd/description
Sroamd makes it possible to seamlessly roam between IP links (e.g. WiFi
access points) with no changes to clients.  There is no central controller,
and no tunnelling is involved.

The daemon implements a custom DHCPv4 server, an IPv4 RA server and
a custom peer-to-peer flooding algorithm.  It depends on hostapd for
link-layer configuration, and a routing protocol able to efficiently deal
with host routes (for example Babel).
endef

define Package/sroamd/conffiles
/etc/config/sroamd
endef

MAKE_FLAGS+= \
	CFLAGS="$(TARGET_CFLAGS) $(TARGET_CPPFLAGS) -I$(STAGING_DIR)/usr/include/libnl3"

define Package/sroamd/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/sroamd $(1)/usr/sbin/sroamd
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/sroamd.init $(1)/etc/init.d/sroamd
	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_CONF) ./files/sroamd.config $(1)/etc/config/sroamd
endef

$(eval $(call BuildPackage,sroamd))
