# SPDX-License-Identifier: GPL-2.0-only

include $(TOPDIR)/rules.mk

PKG_NAME:=oonf-olsrd2
PKG_RELEASE:=1

PKG_MAINTAINER:=Matthias Tarasiewicz <mt@riat.at>
PKG_LICENSE:=BSD-3-Clause
PKG_LICENSE_FILES:=LICENSE

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/OLSR/OONF.git
PKG_SOURCE_DATE:=2026-08-06
PKG_SOURCE_VERSION:=477e716110ee210f9ce03a75ecacd55a06fd600f
PKG_MIRROR_HASH:=06fe29b22d2286e8809f17727f0789152148535d212c0b785828b6678f71e254

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk


# ref https://stackoverflow.com/a/10571900/3990041
SPACE:=$(subst ,, )
CMAKE_OPTIONAL_PLUGINS:=$(subst $(SPACE),;,$(strip \
        $(if $(filter y,$(CONFIG_OONF_NHDP_AUTOLL4)),auto_ll4,) \
        $(if $(filter y,$(CONFIG_OONF_OLSRV2_LAN_IMPORT)),lan_import,) \
        $(if $(filter y,$(CONFIG_OONF_OLSRV2_ROUTE_MODIFIER)),route_modifier,) \
        $(if $(filter y,$(CONFIG_OONF_GENERIC_DLEP_ROUTER)),dlep,) \
        $(if $(filter y,$(CONFIG_OONF_GENERIC_REMOTECONTROL)),remotecontrol,) \
        $(if $(filter y,$(CONFIG_OONF_OLSRV2_MPR)),mpr,) \
        $(if $(filter y,$(CONFIG_OONF_GENERIC_HTTP)),http,) \
        $(if $(filter y,$(CONFIG_OONF_OLSRV2_LAN)),olsrv2_lan,) \
        $(if $(filter y,$(CONFIG_OONF_OLSRV2_OLD_LAN)),olsrv2_old_lan,) \
    ))

BUILD_TYPE:=$(if $(filter y,$(CONFIG_DEBUG)),Debug,Release)

CMAKE_OPTIONS+=-D CMAKE_BUILD_TYPE:String=$(BUILD_TYPE) \
               -D OONF_NO_WERROR:Bool=true \
               -D OONF_LOGGING_LEVEL:String=debug \
               -D OONF_NO_TESTING:Bool=true \
               -D UCI:Bool=true \
               -D OONF_APP_DEFAULT_CFG_HANDLER:String=uci \
               -D OONF_STATIC_PLUGINS:String="class;callback;clock;duplicate_set;layer2;packet_socket;rfc5444;socket;stream_socket;telnet;timer;viewer;os_clock;os_fd;os_interface;os_routing;os_system;nhdp;olsrv2;ff_dat_metric;neighbor_probing;nl80211_listener;link_config;layer2info;systeminfo;cfg_uciloader;cfg_compact;nhdpinfo;olsrv2info;netjsoninfo;${CMAKE_OPTIONAL_PLUGINS}" \
               -D OONF_LIB_GIT:String=$(PKG_SOURCE_VERSION) \
               -D VERSION_SUB_TAG:String=$(PKG_SOURCE_DATE) \
               -D INSTALL_LIB_DIR:Path=lib/oonf \
               -D INSTALL_INCLUDE_DIR:Path=include/oonf \
               -D INSTALL_CMAKE_DIR:Path=lib/oonf \
               -D CMAKE_PREFIX_PATH=$(STAGING_DIR)/usr \
               -D CMAKE_GENERATOR=Ninja

define Package/oonf-olsrd2
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=OLSR.org network framework
  TITLE:=OLSRv2 routing agent (olsrd2)
  URL:=https://www.olsr.org/
  DEPENDS:=+librt +libnl-tiny +libnl-genl +libuci +oonf-init-scripts
  MENU:=1
endef

define Package/oonf-olsrd2/config
	source "$(SOURCE)/Config.in"
endef

Build/Compile=$(call Build/Compile/Default,olsrd2_static)

Build/Install=

define Build/Install
	$(INSTALL_BIN) -D $(PKG_BUILD_DIR)/$(MAKE_PATH)/olsrd2_static $(PKG_INSTALL_DIR)/usr/sbin/olsrd2;
endef

TARGET_CFLAGS += -I$(STAGING_DIR)/usr/include -I${STAGING_DIR}/usr/include/libnl-tiny -I${STAGING_DIR}/usr/include/libnl3

define Package/oonf-olsrd2/install
	$(INSTALL_DIR) $(1)/usr/sbin $(1)/etc/init.d $(1)/etc/hotplug.d/iface $(1)/etc/config
	$(INSTALL_BIN)  $(PKG_BUILD_DIR)/olsrd2_static $(1)/usr/sbin/olsrd2
	$(INSTALL_BIN)  ./files/olsrd2.init     $(1)/etc/init.d/olsrd2
	$(INSTALL_DATA) ./files/olsrd2.hotplug  $(1)/etc/hotplug.d/iface/50-olsrd2
	$(INSTALL_CONF) ./files/olsrd2.uci      $(1)/etc/config/olsrd2
endef

define Package/oonf-olsrd2/postinst
#!/bin/sh
[ -z "$$IPKG_INSTROOT" ] && /etc/init.d/olsrd2 enable
exit 0
endef

define Package/oonf-olsrd2/conffiles
/etc/config/olsrd2
endef

$(eval $(call BuildPackage,oonf-olsrd2))
