# Makefile for toolchain building
REL_VER_MAJOR=1
REL_VER_MINOR=2

BR_VER=2011.11
UCLIBC_VER=0.9.32
LINUX_VER=3.4
GCC_VER=4.6
BINUTILS_VER=2.21
ARCH ?= all

ifeq ($(strip $(BCM_TOOLCHAIN_VER)),)
BCM_TOOLCHAIN_VER=Rel$(REL_VER_MAJOR).$(REL_VER_MINOR)
endif
ifeq ($(strip $(TOOLCHAIN_TOP)),)
TOOLCHAIN_TOP=/opt/toolchains
endif


TOOLCHAIN_SRC_NAME=crosstools-gcc-$(GCC_VER)-linux-$(LINUX_VER)-uclibc-$(UCLIBC_VER)-binutils-$(BINUTILS_VER)-sources
TOOLCHAIN_ARM_NAME=crosstools-arm-gcc-$(GCC_VER)-linux-$(LINUX_VER)-uclibc-$(UCLIBC_VER)-binutils-$(BINUTILS_VER)-NPTL
TOOLCHAIN_MIPS_NAME=crosstools-mips-gcc-$(GCC_VER)-linux-$(LINUX_VER)-uclibc-$(UCLIBC_VER)-binutils-$(BINUTILS_VER)
TOOLCHAIN_MIPSEL_NAME=crosstools-mipsel-gcc-$(GCC_VER)-linux-$(LINUX_VER)-uclibc-$(UCLIBC_VER)-binutils-$(BINUTILS_VER)

export BR_VER UCLIBC_VER LINUX_VER GCC_VER BINUTILS_VER TOOLCHAIN_TOP ARCH

all: sanity_check
	cd ./src;./build
ifeq ($(ARCH), $(filter $(ARCH),mips all))
	echo "#define BCM_TOOLCHAIN_VERSION \"$(BCM_TOOLCHAIN_VER)\"" >  $(TOOLCHAIN_TOP)/$(TOOLCHAIN_MIPS_NAME)/usr/include/bcm_toolver.h
	echo "#define BCM_TOOLCHAIN_MAJOR $(REL_VER_MAJOR)" >>  $(TOOLCHAIN_TOP)/$(TOOLCHAIN_MIPS_NAME)/usr/include/bcm_toolver.h
	echo "#define BCM_TOOLCHAIN_MINOR $(REL_VER_MINOR)" >>  $(TOOLCHAIN_TOP)/$(TOOLCHAIN_MIPS_NAME)/usr/include/bcm_toolver.h
	cp $(TOOLCHAIN_TOP)/$(TOOLCHAIN_MIPS_NAME)/usr/include/bcm_toolver.h $(TOOLCHAIN_TOP)/$(TOOLCHAIN_MIPS_NAME)/usr/mips-linux/sysroot/usr/include/bcm_toolver.h
endif
ifeq ($(ARCH), $(filter $(ARCH),arm all))
	echo "#define BCM_TOOLCHAIN_VERSION \"$(BCM_TOOLCHAIN_VER)\"" >  $(TOOLCHAIN_TOP)/$(TOOLCHAIN_ARM_NAME)/usr/include/bcm_toolver.h
	echo "#define BCM_TOOLCHAIN_MAJOR $(REL_VER_MAJOR)" >>  $(TOOLCHAIN_TOP)/$(TOOLCHAIN_ARM_NAME)/usr/include/bcm_toolver.h
	echo "#define BCM_TOOLCHAIN_MINOR $(REL_VER_MINOR)" >>  $(TOOLCHAIN_TOP)/$(TOOLCHAIN_ARM_NAME)/usr/include/bcm_toolver.h
	cp $(TOOLCHAIN_TOP)/$(TOOLCHAIN_ARM_NAME)/usr/include/bcm_toolver.h $(TOOLCHAIN_TOP)/$(TOOLCHAIN_ARM_NAME)/usr/arm-linux/sysroot/usr/include/bcm_toolver.h
endif
ifeq ($(ARCH), $(filter $(ARCH),mipsel all))
	echo "#define BCM_TOOLCHAIN_VERSION \"$(BCM_TOOLCHAIN_VER)\"" >  $(TOOLCHAIN_TOP)/$(TOOLCHAIN_MIPSEL_NAME)/usr/include/bcm_toolver.h
	echo "#define BCM_TOOLCHAIN_MAJOR $(REL_VER_MAJOR)" >>  $(TOOLCHAIN_TOP)/$(TOOLCHAIN_MIPSEL_NAME)/usr/include/bcm_toolver.h
	echo "#define BCM_TOOLCHAIN_MINOR $(REL_VER_MINOR)" >>  $(TOOLCHAIN_TOP)/$(TOOLCHAIN_MIPSEL_NAME)/usr/include/bcm_toolver.h
	cp $(TOOLCHAIN_TOP)/$(TOOLCHAIN_MIPSEL_NAME)/usr/include/bcm_toolver.h $(TOOLCHAIN_TOP)/$(TOOLCHAIN_MIPSEL_NAME)/usr/mipsel-linux/sysroot/usr/include/bcm_toolver.h
endif
	@echo toolchain build done!

sanity_check:
	@if [ ! -e ./src/buildroot-$(BR_VER) ]; then \
		echo Untarring buildroot-$(BR_VER) source...; \
		(tar xfjk $(TOOLCHAIN_SRC_NAME).tar.bz2 2> /dev/null || true); \
	fi

mips_clean:
ifeq ($(ARCH), $(filter $(ARCH),mips all))
	rm -f $(TOOLCHAIN_MIPS_NAME)*.tar.bz2
	@if [ -e $(TOOLCHAIN_TOP)/$(TOOLCHAIN_MIPS_NAME) ]; then \
		rm -r -f $(TOOLCHAIN_TOP)/$(TOOLCHAIN_MIPS_NAME)/*; \
	fi
endif

arm_clean:
ifeq ($(ARCH), $(filter $(ARCH),arm all))
	rm -f $(TOOLCHAIN_ARM_NAME)*.tar.bz2
	@if [ -e $(TOOLCHAIN_TOP)/$(TOOLCHAIN_ARM_NAME) ]; then \
		rm -r -f $(TOOLCHAIN_TOP)/$(TOOLCHAIN_ARM_NAME)/*; \
	fi
endif

mipsel_clean:
ifeq ($(ARCH), $(filter $(ARCH),mipsel all))
	rm -f $(TOOLCHAIN_MIPSEL_NAME)*.tar.bz2
	@if [ -e $(TOOLCHAIN_TOP)/$(TOOLCHAIN_MIPSEL_NAME) ]; then \
		rm -r -f $(TOOLCHAIN_TOP)/$(TOOLCHAIN_MIPSEL_NAME)/*; \
	fi
endif

mips_release:
ifeq ($(ARCH), $(filter $(ARCH),mips all))
	rm -f $(TOOLCHAIN_MIPS_NAME)*.tar.bz2
	tar cfjP $(TOOLCHAIN_MIPS_NAME).$(BCM_TOOLCHAIN_VER).tar.bz2 $(TOOLCHAIN_TOP)/$(TOOLCHAIN_MIPS_NAME)/
endif

arm_release:
ifeq ($(ARCH), $(filter $(ARCH),arm all))
	rm -f $(TOOLCHAIN_ARM_NAME)*.tar.bz2
	tar cfjP $(TOOLCHAIN_ARM_NAME).$(BCM_TOOLCHAIN_VER).tar.bz2 $(TOOLCHAIN_TOP)/$(TOOLCHAIN_ARM_NAME)/
endif

mipsel_release:
ifeq ($(ARCH), $(filter $(ARCH),mipsel all))
	rm -f $(TOOLCHAIN_MIPSEL_NAME)*.tar.bz2
	tar cfjP $(TOOLCHAIN_MIPSEL_NAME).$(BCM_TOOLCHAIN_VER).tar.bz2 $(TOOLCHAIN_TOP)/$(TOOLCHAIN_MIPSEL_NAME)/
endif


clean: mips_clean arm_clean mipsel_clean
	@if [ -e ./src/buildroot-$(BR_VER) ]; then \
		rm -r -f ./src/buildroot-$(BR_VER); \
	fi

release: mips_release arm_release mipsel_release
	rm -f $(TOOLCHAIN_SRC_NAME).tar.bz2
	$(MAKE) -i -C ./src/buildroot-$(BR_VER) clean 2> /dev/null
	tar \
	--exclude=src/buildroot-$(BR_VER)/.config \
	--exclude=src/buildroot-$(BR_VER)/.config.old \
	--exclude=src/buildroot-$(BR_VER)/..config.tmp \
	--exclude=src/buildroot-$(BR_VER)/toolchain/uClibc/uClibc-$(UCLIBC_VER).brcm.config \
	-c -j -f $(TOOLCHAIN_SRC_NAME).tar.bz2 Makefile src/
ifeq ($(ARCH), $(filter $(ARCH),mips all))
	@tar --no-overwrite-dir -x -j -P -f $(TOOLCHAIN_MIPS_NAME).$(BCM_TOOLCHAIN_VER).tar.bz2
endif
ifeq ($(ARCH), $(filter $(ARCH),arm all))
	@tar --no-overwrite-dir -x -j -P -f $(TOOLCHAIN_ARM_NAME).$(BCM_TOOLCHAIN_VER).tar.bz2
endif
ifeq ($(ARCH), $(filter $(ARCH),mipsel all))
	@tar --no-overwrite-dir -x -j -P -f $(TOOLCHAIN_MIPSEL_NAME).$(BCM_TOOLCHAIN_VER).tar.bz2
endif
