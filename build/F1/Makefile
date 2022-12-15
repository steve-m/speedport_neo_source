##############################################################
#	F1 Project makefile 
#	Usage:  make kernel source bootcode
##############################################################

export TOPDIR = $(shell pwd)/../..
export BUILDPATH=$(TOPDIR)/build/F1
export BUILD_COMMON=$(TOPDIR)/build/Common
export HOSTTOOLS_DIR = $(TOPDIR)/bsp/hostTools
export PROFILE = 963268GWV

include $(BUILDPATH)/rules.mk

new_all:
	@sed -i "s/export FW_VERSION = \([0-9][0-9]\).\([0-9][0-9]\).[0-9]\([0-9][0-9]\).\([0-9]\)/export FW_VERSION = \1.\2.0\3.\4/" product/F1/config.mk
	$(MAKE) all
	make image_build

all: 
	@echo 'make <kernel/source>';
	make kernel
	make rootfs_prep
	make user_shared
	make public_libs
	make sc_driver
	make public_apps
	make user_private
	make sc_module_version

sc_module_version:
	@rm -rf $(INSTALLDIR)/etc/moduleversion;
	@cp -f $(BUILDPATH)/moduleversion.mk $(INSTALLDIR)/etc/moduleversion

kernel: 
	@echo "export PROFILE=$(PROFILE)" > $(BSP_DIR)/PROFILE.make
	@echo $(PROFILE) > $(BSP_DIR)/.last_profile
	@cd $(BSP_DIR); make sc_kernel;

user_shared:
	cd $(TOPDIR)/user/shared && $(MAKE)

public_libs:
	cd $(TOPDIR)/user/public/libs && $(MAKE)

public_apps:
	cd $(TOPDIR)/user/public/apps && $(MAKE)

user_private:
	#cd $(TOPDIR)/user/private && $(MAKE)

user_build:
	@echo Makeing user
	cd $(TOPDIR)/user && $(MAKE)

user_clean:
	@echo Clean user
	cd $(TOPDIR)/user && $(MAKE) clean

sc_driver:
	@cd $(BSP_DIR); make sc_driver;
	
rootfs_prep:
	@echo prepare the rootfs
	cd $(BUILDPATH)
	test -d $(INSTALL_ROOT) || tar zxf target.tgz 
	test -d $(INSTALL_ROOT) || mkdir $(INSTALL_ROOT)
#	rm -rf $(INSTALL_ROOT)/* && rm -rf rootfs
#	tar -zxf $(TOPDIR)/rootfs/common.tgz
#	-cp -Rf rootfs/* $(INSTALL_ROOT) && rm -rf rootfs
#	cp -Rf $(TOPDIR)/rootfs/$(PRODUCT_TYPE)/* $(INSTALL_ROOT)/usr
	cp -af $(CROSS_DIR)/lib/*.so* $(INSTALL_ROOT)/lib
	cp -af $(CROSS_DIR)/usr/mips-linux/lib/*.so* $(INSTALL_ROOT)/lib
	rm -rf $(INSTALL_ROOT)/dev/*
	./makeDevs
	ln -sf /tmp/passwd  $(INSTALL_ROOT)/etc/passwd
	ln -sf /tmp/group  $(INSTALL_ROOT)/etc/group
	ln -sf /tmp/shadow  $(INSTALL_ROOT)/etc/shadow
	ln -sf /var/resolv.conf  $(INSTALL_ROOT)/etc/resolv.conf
	ln -sf /tmp/gateways $(INSTALL_ROOT)/etc/gateways
	ln -sf /tmp/mtools.conf $(INSTALL_ROOT)/etc/mtools.conf
	ln -sf /tmp/home $(INSTALL_ROOT)/home

rootfs_build:
	@echo make root file system
	cd $(BUILDPATH)
	find rootfs.build/ -name .svn | xargs rm -rf
	find rootfs.build/ -name .cvsignore | xargs rm -rf
	find rootfs.build/ -name CVS | xargs rm -rf
	find rootfs.build/ -name Makefile | xargs rm -rf
	find rootfs.build/ -name _desktop.ini | xargs rm -rf
	echo "$(FW_BOOT_VERSION)" > rootfs.build/etc/boot_version
	echo "$(FW_DSL_VERSION)" > rootfs.build/etc/dsl_version
	echo "$(FW_EXTRA_VERSION) (build @ `export LC_TIME=C; date +'%F, %T'`)" > rootfs.build/etc/extra_version
	echo "$(SC_MODULE)" > rootfs.build/etc/hw_id
	echo "$(SC_MANUFACTOR)" > rootfs.build/etc/oem_id
	echo "$(MODEL_NAME)" > rootfs.build/etc/modelname
	echo "$(PRODUCT_NAME)" > rootfs.build/etc/productname
	echo "$(PRODUCT_CLASS)" > rootfs.build/etc/productclass
	@echo sync broadcom target root filesystem
	-$(STRIP) -s $(INSTALL_ROOT)/usr/sbin/*
	-$(STRIP) -s $(INSTALL_ROOT)/lib/*
	@echo make jffs2 filesystem
	cp -fv $(BSP_DIR)/vmlinux.lz $(INSTALL_ROOT)/
	echo -e "/vmlinux.lz" > $(INSTALL_ROOT)/nocomprlist
	echo -e "/kernel_cksum" >> $(INSTALL_ROOT)/nocomprlist
	echo -e "/cferam" > $(BUILDPATH)/product/F1/image/nocomprlist
	echo -e "/cferam_bk" >> $(BUILDPATH)/product/F1/image/nocomprlist
	chmod +w $(INSTALL_ROOT)/usr/etc/fstab
	mkdir -p -m 777 $(INSTALL_ROOT)/config/nvram
	chmod 777 $(INSTALL_ROOT)/config
	cp $(BUILD_COMMON)/dectmodel.bin $(BUILDPATH)/APP_DATA/dect/Dect_fw
	cp $(BUILD_COMMON)/dectmodel.bin $(BUILDPATH)/product/F1/image/
	-@echo -e '\E[32;40m'"Making jffs2 filesystem for 128M flash" && tput sgr0
	$(HOSTTOOLS_DIR)/mkfs.jffs2 -b -p -n -e 131072 -r $(INSTALL_ROOT) -o $(BUILDPATH)/rootfs.jffs2 -N $(INSTALL_ROOT)/nocomprlist
	$(HOSTTOOLS_DIR)/mkfs.jffs2 -b -p -n -e 131072 -r $(BUILDPATH)/EMPTY -o $(BUILDPATH)/empty.jffs2 -N $(INSTALL_ROOT)/nocomprlist
	$(HOSTTOOLS_DIR)/mkfs.jffs2 -b -p -n -e 131072 -r $(BUILDPATH)/APP_DATA -o $(BUILDPATH)/app_dat.jffs2 -N $(INSTALL_ROOT)/nocomprlist
ifeq ($(SC_FBIMAGE), 1)
	cp $(BUILDPATH)/rootfs.jffs2 $(BUILDPATH)/product/F1/image/rootfs_fb.jffs2 -v
else
	cp $(BUILDPATH)/rootfs.jffs2 $(BUILDPATH)/product/F1/image/ -v
endif
	cp $(BUILDPATH)/empty.jffs2 $(BUILDPATH)/product/F1/image/xml_cfg.jffs2 -v
	cp $(BUILDPATH)/app_dat.jffs2 $(BUILDPATH)/product/F1/image/app_dat.jffs2 -v
	rm -fv $(INSTALL_ROOT)/nocomprlist
	rm -fv $(BUILDPATH)/empty.jffs2
	rm -fv $(BUILDPATH)/rootfs.jffs2

image_build: rootfs_build
	cd $(BUILDPATH)/product/F1/image ; ./bb

rel_image_build: rootfs_build
	cd $(BUILDPATH)/product/F1/image ; ./bb release

fb:
	sed -i "s/export FW_VERSION = \([0-9][0-9]\).\([0-9][0-9]\).[0-9]\([0-9][0-9]\).\([0-9]\)/export FW_VERSION = \1.\2.3\3.\4/" product/F1/config.mk
	$(MAKE) -C $(TOPDIR)/user/private clean
	$(MAKE) all SC_FBIMAGE=1
	$(MAKE) image_build SC_FBIMAGE=1

emc:
	$(MAKE) -C $(TOPDIR)/user/private clean
	sed -i "s/export FW_VERSION = \([0-9][0-9]\).\([0-9][0-9]\).[0-9]\([0-9][0-9]\).\([0-9]\)/export FW_VERSION = \1.\2.3\3.\4/" product/F1/config.mk
	$(MAKE) all SC_EMC=1
	$(MAKE) rel_image_build

kernel_clean:
	@cd $(BSP_DIR); make clean;

all_clean: kernel_clean user_clean

release:
	@sed -i "s/export FW_VERSION = \([0-9][0-9]\).\([0-9][0-9]\).[0-9]\([0-9][0-9]\).\([0-9]\)/export FW_VERSION = \1.\2.0\3.\4/" product/F1/config.mk
	$(MAKE) all
	$(MAKE) rel_image_build


APP_TRY_DIR :=
APP_TRY_DIR += $(TOPDIR)/user/shared/libs
APP_TRY_DIR += $(TOPDIR)/user/private/apps
APP_TRY_DIR += $(TOPDIR)/user/private/libs
APP_TRY_DIR += $(TOPDIR)/user/public/apps
APP_TRY_DIR += $(TOPDIR)/user/public/libs
app:
	@if [ "n"$(APP_DIR) != "n" ]; then \
	    for d in $(APP_TRY_DIR); do \
	    	if [ -d "$$d/$(APP_DIR)" ]; then\
		    $(MAKE) -C $$d/$(APP_DIR)/;\
		    exit 0;\
		else \
			echo "$$d/$(APP_DIR) not exist!";\
		fi;\
	    done;\
	else \
	    echo "usage: make app APP_DIR=<DIR>";\
	    echo "	e.x: make app APP_DIR=cml";\
	fi;



