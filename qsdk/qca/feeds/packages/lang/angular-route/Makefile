include $(TOPDIR)/rules.mk

PKG_NAME:=angular-route
PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=git://github.com/angular/bower-angular-route.git
PKG_BRANCH:=master
PKG_RELEASE:=v1.2.0-rc.3

PKG_REV:=e548b5b
PKG_VERSION:=0.1-g$(PKG_REV)

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE_VERSION:=$(PKG_REV)
PKG_SOURCE_MIRROR:=none
PKG_BUILD_PARALLEL:=0

include $(INCLUDE_DIR)/package-version-override.mk
include $(INCLUDE_DIR)/package.mk

define Package/angular-route
  SECTION:=language-javascript
  CATEGORY:=Languages
  SUBMENU:=JavaScript
  TITLE:=Angular-Route
  URL:=http://angularjs.org/
  DEPENDS:=+angular
endef

define Package/angular-route/description
 Angular URL Routing mechanism.
endef

define Build/Configure
endef

define Build/Compile
endef

define Package/angular-route/install
	$(INSTALL_DIR) $(1)/www/js/
	cp $(PKG_BUILD_DIR)/angular-route.min.js $(1)/www/js/
endef

$(eval $(call BuildPackage,angular-route))