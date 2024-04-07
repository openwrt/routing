include $(TOPDIR)/rules.mk

PKG_NAME:=pimbd
PKG_RELEASE:=4

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/Oryon/pimbd.git
PKG_SOURCE_DATE:=2018-06-19
PKG_SOURCE_VERSION:=dbf4e5913b06e3160f506df15e6a047a403a5f21
PKG_MIRROR_HASH:=ed794402da1959e0c8cdf819a8bd7370f9bb092e62b33d96f94ad1228a4975d7

PKG_MAINTAINER:=Pierre Pfister <pierre.pfister@darou.fr>
PKG_LICENSE:=Apache-2.0
PKG_LICENSE_FILES:=LICENSE

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

# Spammy debug builds for now
CMAKE_OPTIONS += -DL_LEVEL=7 \
		 -DWITH_LIBUBOX=1

define Package/pimbd
  SECTION:=net
  CATEGORY:=Network
  TITLE:=PIM BIDIR daemon
  URL:=https://github.com/Oryon/pimbd.git
  DEPENDS+=@IPV6
  DEPENDS+=netifd
endef

define Package/pimbd/description
  This package provides a daemon which implements the Protocol Independent
  Multicast BIDIR routing protocol. Note that a routing protocol must be
  installed and running in order for PIM to function.
endef

define Package/pimbd/install
	$(INSTALL_DIR) $(1)/usr/sbin/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/pimbd $(1)/usr/sbin/pimbd
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/generic/pimbc.sh $(1)/usr/sbin/pimbc
	ln -s pimbd $(1)/usr/sbin/pimb-ipc
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/pimbd.init $(1)/etc/init.d/pimbd
	$(INSTALL_DIR) $(1)/etc/uci-defaults
	$(INSTALL_BIN) files/firewall-uci.sh $(1)/etc/uci-defaults/99_pimbd_firewall
	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_CONF) ./files/pimb.config $(1)/etc/config/pimb
endef

$(eval $(call BuildPackage,pimbd))
