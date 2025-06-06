BTOP_PKG_BUILD_DIR=$(TOP)/btop
BTOP_STAGING_DIR=$(TOP)/_staging
BTOP_PKG_INSTALL:=1
BTOP_CMAKE_OPTIONS+=VERBOSE=0 -DBUILD_LUA=OFF -DBTOP_LTO=ON \
		    -DCMAKE_BUILD_TYPE=release \
		    -DCMAKE_AR=${GCCAR} \
		    -DBTOP_GPU=false \
		    -DCMAKE_RANLIB=${GCCRANLIB}


#BTOP_EXTRA_CFLAGS=-I$(TOP) -I$(STAGING_DIR)/usr/include -I$(TOP)/shared -L$(STAGING_DIR)/usr/lib -I$(TOP)/libnl-tiny/include  $(MIPS16_OPT) $(THUMB) -DNEED_PRINTF -ffunction-sections -fdata-sections -Wl,--gc-sections $(LTO)
#BTOP_EXTRA_LDFLAGS=-ljson-c -L$(TOP)/libubox/ -L$(TOP)/libnl-tiny -lnl-tiny  -ffunction-sections -fdata-sections -Wl,--gc-sections $(LDLTO)
BTOP_EXTRA_CFLAGS=$(MIPS16_OPT) $(THUMB) -DNEED_PRINTF -ffunction-sections -fdata-sections -Wl,--gc-sections $(LTO)
BTOP_EXTRA_LDFLAGS=-ffunction-sections -fdata-sections -Wl,--gc-sections $(LDLTO)

btop-configure:
	mkdir -p $(TOP)/btop/build
	cd $(TOP)/btop/build && $(call CMakeClean_ext,$(BTOP_PKG_BUILD_DIR))
	$(call CMakeConfigure_ext,$(BTOP_PKG_BUILD_DIR),$(BTOP_STAGING_DIR),$(BTOP_CMAKE_OPTIONS),$(BTOP_EXTRA_CFLAGS),$(BTOP_EXTRA_LDFLAGS),)

btop:
	$(MAKE) -C btop/build

btop-install:
	install -D btop/build/btop $(INSTALLDIR)/btop/usr/sbin/btop

btop-clean:
	if [ -e "$(BTOP_PKG_BUILD_DIR)/build/Makefile" ]; then $(MAKE) -C btop/build clean ; fi
