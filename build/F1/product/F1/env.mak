export CROSS_DIR = /opt/toolchains/crosstools-mips-gcc-4.6-linux-3.4-uclibc-0.9.32-binutils-2.21
export TOOLPREFIX=/opt/toolchains/crosstools-mips-gcc-4.6-linux-3.4-uclibc-0.9.32-binutils-2.21/usr/bin/mips-linux-
export KERNELARCH=mips
export ARCH=mips

# DIR setting

export BSP_DIR=$(TOPDIR)/bsp

export ROOT = $(TOPDIR)
export TARGET_HOME = $(ROOT)

export BINDIR=$(TARGET_DIR)/usr/sbin
export LIBDIR=$(TARGET_DIR)/usr/lib/

export FS_DIR  = $(BUILDPATH)/rootfs.build
export HOSTTOOLS_DIR = $(TOPDIR)/bsp/hostTools

export ROOTFS = $(FS_DIR)

# filename setting
export ROOT_IMG :=target.squashfs

#
# Cross infomation
#
CROSS_COMPILE   = $(TOOLPREFIX)
AS		= $(CROSS_COMPILE)as
LD		= $(CROSS_COMPILE)ld
CC		= $(CROSS_COMPILE)gcc
CPP		= $(CROSS_COMPILE)gcc -E
AR		= $(CROSS_COMPILE)ar
NM		= $(CROSS_COMPILE)nm
RANLIB      	= $(CROSS_COMPILE)ranlib
STRIP		= $(CROSS_COMPILE)strip
OBJCOPY		= $(CROSS_COMPILE)objcopy
OBJDUMP		= $(CROSS_COMPILE)objdump
CXX		= $(CROSS_COMPILE)g++

export CROSS_COMPILE AS LD CC CPP AR NM RANLIB STRIP OBJCOPY OBJDUMP CXX
