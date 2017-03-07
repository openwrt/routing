include $(TOPDIR)/rules.mk

PKG_NAME:=prince
PKG_VERSION:=v0.3.2
PKG_RELEASE:=1
PKG_MD5SUM=453a1e1db1d060a7bd103492c3e44e85
PKG_MIRROR_HASH=4ad2e16512e74121d8221e0325e742b2dbc0b91f64106a0fe117160d07abf889
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)
PKG_USE_MIPS16:=0
PKG_SOURCE_PROTO:=git
PKG_SOURCE:=prince-$(PKG_VERSION).tar.xz
PKG_SOURCE_URL:=https://github.com/AdvancedNetworkingSystems/poprouting.git
PKG_SOURCE_VERSION:=v0.3.2
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_SOURCE_VERSION)
PKG_LICENSE:=MIT
include $(INCLUDE_DIR)/package.mk

define Package/prince
	SECTION :=net
	CATEGORY :=Network
	SUBMENU :=Routing and Redirection
	MANTAINER :=Gabriele Gemmi <gabriel@autistici.org>
	TITLE :=PopRouting daemon
	URL :=https://github.com/gabri94/poprouting
	DEPENDS := +libjson-c +libpthread
endef

define Package/prince/description
Prince is an open source implementation of the PopRouting Algorithm.
It has been developed as a Google Summer of Code Project in collaboration with Freifunk and the University of Trento.

It works by fetching topology data from a Link State routing daemon(OONF, OLSR, OSPF, etc),
calculating the betweenness centrality using the topology, then using these data to compute the
the timer's optimal values. Finally the timers are pushed back to the routing daemon.
Currently it only supports OLSRd2 (aka OONF).
endef

define Package/prince/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/output/prince $(1)/usr/sbin/
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/output/libprince_oonf_c.so $(1)/usr/lib/
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/openwrt/prince.init $(1)/etc/init.d/prince
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/prince/conf/default.conf $(1)/etc/prince.conf
endef


$(eval $(call BuildPackage,prince))
