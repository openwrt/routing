# SPDX-License-Identifier: GPL-2.0-only

include $(TOPDIR)/rules.mk

PKG_NAME:=bird3
PKG_VERSION:=3.3.1
PKG_RELEASE:=1

PKG_SOURCE:=bird-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://bird.nic.cz/download/
PKG_HASH:=d5a8d651d6184c18252954932bb249dfee1fd213b3665cdd86226ac45edc0190

PKG_MAINTAINER:=Toke Høiland-Jørgensen <toke@toke.dk>, Nick Hainke <vincent@systemli.org>
PKG_LICENSE:=GPL-2.0-or-later

PKG_BUILD_DEPENDS:=ncurses readline
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(BUILD_VARIANT)/bird-$(PKG_VERSION)

PKG_CONFIG_DEPENDS := \
	CONFIG_BIRD3_PROTO_AGGREGATOR \
	CONFIG_BIRD3_PROTO_BABEL \
	CONFIG_BIRD3_PROTO_BFD \
	CONFIG_BIRD3_PROTO_BGP \
	CONFIG_BIRD3_PROTO_BMP \
	CONFIG_BIRD3_PROTO_L3VPN \
	CONFIG_BIRD3_PROTO_OSPF \
	CONFIG_BIRD3_PROTO_PERF \
	CONFIG_BIRD3_PROTO_RADV \
	CONFIG_BIRD3_PROTO_RIP \
	CONFIG_BIRD3_PROTO_RPKI

include $(INCLUDE_DIR)/package.mk

BUILD_VARIANT?=full

# Infrastructure protocols included in every variant unconditionally.
BIRD3_INFRA := mrt,pipe,static

# Predefined protocol sets for prebuilt package variants
BIRD3_PROTOCOLS_bgp   := bgp,rpki,bfd,$(BIRD3_INFRA)
BIRD3_PROTOCOLS_ospf  := ospf,bfd,$(BIRD3_INFRA)
BIRD3_PROTOCOLS_babel := babel,$(BIRD3_INFRA)
BIRD3_PROTOCOLS_mesh  := babel,bgp,$(BIRD3_INFRA)

# For the full variant, assemble the protocol list from Config.in selections.
ifeq ($(BUILD_VARIANT),full)
  BIRD3_PROTOCOLS := $(BIRD3_INFRA)
  ifdef CONFIG_BIRD3_PROTO_AGGREGATOR
    BIRD3_PROTOCOLS := $(BIRD3_PROTOCOLS),aggregator
  endif
  ifdef CONFIG_BIRD3_PROTO_BABEL
    BIRD3_PROTOCOLS := $(BIRD3_PROTOCOLS),babel
  endif
  ifdef CONFIG_BIRD3_PROTO_BFD
    BIRD3_PROTOCOLS := $(BIRD3_PROTOCOLS),bfd
  endif
  ifdef CONFIG_BIRD3_PROTO_BGP
    BIRD3_PROTOCOLS := $(BIRD3_PROTOCOLS),bgp
  endif
  ifdef CONFIG_BIRD3_PROTO_BMP
    BIRD3_PROTOCOLS := $(BIRD3_PROTOCOLS),bmp
  endif
  ifdef CONFIG_BIRD3_PROTO_L3VPN
    BIRD3_PROTOCOLS := $(BIRD3_PROTOCOLS),l3vpn
  endif
  ifdef CONFIG_BIRD3_PROTO_OSPF
    BIRD3_PROTOCOLS := $(BIRD3_PROTOCOLS),ospf
  endif
  ifdef CONFIG_BIRD3_PROTO_PERF
    BIRD3_PROTOCOLS := $(BIRD3_PROTOCOLS),perf
  endif
  ifdef CONFIG_BIRD3_PROTO_RADV
    BIRD3_PROTOCOLS := $(BIRD3_PROTOCOLS),radv
  endif
  ifdef CONFIG_BIRD3_PROTO_RIP
    BIRD3_PROTOCOLS := $(BIRD3_PROTOCOLS),rip
  endif
  ifdef CONFIG_BIRD3_PROTO_RPKI
    BIRD3_PROTOCOLS := $(BIRD3_PROTOCOLS),rpki
  endif
else
  BIRD3_PROTOCOLS := $(BIRD3_PROTOCOLS_$(BUILD_VARIANT))
endif

CONFIGURE_ARGS += --disable-libssh --with-protocols=$(BIRD3_PROTOCOLS)
TARGET_LDFLAGS += -latomic

define Package/bird3/Default
  URL:=https://bird.nic.cz/
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=Routing and Redirection
  DEPENDS:=+libpthread +libatomic
  CONFLICTS:=bird2
  PROVIDES:=bird3
endef

define Package/bird3/Default/description
BIRD is an internet routing daemon which manages TCP/IP routing tables
with support of modern routing protocols, easy to use configuration
interface and powerful route filtering language. It is lightweight and
efficient and therefore appropriate for small embedded routers.
endef

define Package/bird3
  $(call Package/bird3/Default)
  TITLE:=The BIRD Internet Routing Daemon (v3)
  VARIANT:=full
  CONFLICTS:=bird2 bird3-bgp bird3-ospf bird3-babel bird3-mesh
endef

define Package/bird3/config
  source "$(SOURCE)/Config.in"
endef

define Package/bird3/description
$(call Package/bird3/Default/description)

BIRD supports OSPFv2, RIPv2, Babel and BGP protocols for IPv4 and
OSPFv3, RIPng, Babel and BGP protocols for IPv6.

In BGP, BIRD supports communities, multiprotocol extensions, MD5
authentication, 32bit AS numbers and could act as a route server or a
route reflector. BIRD also supports multiple RIBs, multiple kernel
routing tables and redistribution between the protocols with a powerful
configuration syntax.

This is the 3.0 branch of Bird which is a multithreaded rewrite.
endef

define Package/bird3-bgp
  $(call Package/bird3/Default)
  TITLE:=The BIRD Internet Routing Daemon (v3) - BGP/RPKI/BFD
  VARIANT:=bgp
  CONFLICTS:=bird2 bird3 bird3-ospf bird3-babel bird3-mesh
endef

Package/bird3-bgp/description = $(Package/bird3/Default/description)

define Package/bird3-ospf
  $(call Package/bird3/Default)
  TITLE:=The BIRD Internet Routing Daemon (v3) - OSPF/BFD
  VARIANT:=ospf
  CONFLICTS:=bird2 bird3 bird3-bgp bird3-babel bird3-mesh
endef

Package/bird3-ospf/description = $(Package/bird3/Default/description)

define Package/bird3-babel
  $(call Package/bird3/Default)
  TITLE:=The BIRD Internet Routing Daemon (v3) - Babel
  VARIANT:=babel
  CONFLICTS:=bird2 bird3 bird3-bgp bird3-ospf bird3-mesh
endef

Package/bird3-babel/description = $(Package/bird3/Default/description)

define Package/bird3-mesh
  $(call Package/bird3/Default)
  TITLE:=The BIRD Internet Routing Daemon (v3) - Babel+BGP mesh
  VARIANT:=mesh
  CONFLICTS:=bird2 bird3 bird3-bgp bird3-ospf bird3-babel
endef

define Package/bird3-mesh/description
$(call Package/bird3/Default/description)

Size-optimized variant for mesh networks running Babel for routing and
BGP for overlay services such as hostname distribution.
endef

define Package/bird3c
  TITLE:=The BIRD command-line client (v3)
  URL:=https://bird.nic.cz/
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=Routing and Redirection
  DEPENDS:=+bird3 +libreadline +libncurses
  CONFLICTS:=bird2
  VARIANT:=full
endef

define Package/bird3c/description
This is a BIRD command-line client. It is used to send commands to BIRD,
commands can perform simple actions such as enabling/disabling of
protocols, telling BIRD to show various information, telling it to show
a routing table filtered by a filter, or asking BIRD to reconfigure.

Unless you can't afford dependency on ncurses and readline, you
should install BIRD command-line client together with BIRD.
endef

define Package/bird3cl
  TITLE:=The BIRD lightweight command-line client (v3)
  URL:=https://bird.nic.cz/
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=Routing and Redirection
  DEPENDS:=+bird3
  CONFLICTS:=bird2
  VARIANT:=full
endef

define Package/bird3cl/description
This is a BIRD lightweight command-line client. It is used to send commands
to BIRD, commands can perform simple actions such as enabling/disabling of
protocols, telling BIRD to show various information, telling it to show
a routing table filtered by a filter, or asking BIRD to reconfigure.
endef

define Package/bird3/conffiles
/etc/bird.conf
/etc/bird4.conf
/etc/bird6.conf
endef

Package/bird3-bgp/conffiles   = $(Package/bird3/conffiles)
Package/bird3-ospf/conffiles  = $(Package/bird3/conffiles)
Package/bird3-babel/conffiles = $(Package/bird3/conffiles)
Package/bird3-mesh/conffiles  = $(Package/bird3/conffiles)

define Package/bird3/install
	$(INSTALL_DIR)  $(1)/usr/sbin
	$(INSTALL_BIN)  $(PKG_BUILD_DIR)/bird $(1)/usr/sbin/
	$(INSTALL_DIR)  $(1)/etc
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/doc/bird.conf.example $(1)/etc/bird.conf
	$(INSTALL_DIR)  $(1)/etc/init.d
	$(INSTALL_BIN)  ./files/bird.init $(1)/etc/init.d/bird
endef

Package/bird3-bgp/install   = $(Package/bird3/install)
Package/bird3-ospf/install  = $(Package/bird3/install)
Package/bird3-babel/install = $(Package/bird3/install)
Package/bird3-mesh/install  = $(Package/bird3/install)

define Package/bird3c/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/birdc $(1)/usr/sbin/
endef

define Package/bird3cl/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/birdcl $(1)/usr/sbin/
endef

$(eval $(call BuildPackage,bird3))
$(eval $(call BuildPackage,bird3-bgp))
$(eval $(call BuildPackage,bird3-ospf))
$(eval $(call BuildPackage,bird3-babel))
$(eval $(call BuildPackage,bird3-mesh))
$(eval $(call BuildPackage,bird3c))
$(eval $(call BuildPackage,bird3cl))
