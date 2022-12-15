#
#PRODUCT_TYPE: RFT620  RFT620_SERCOMM
#
ifndef PRODUCT_TYPE
export PRODUCT_TYPE = F1
endif

ifndef SC_OEM
export SC_OEM = DT
endif
CFLAGS += -D$(SC_OEM)
CFLAGS += -DSC_OEM=\"$(SC_OEM)\"

#
# Customer currently supported: DT MT OTE
#
ifndef SC_CUSTOMER
export SC_CUSTOMER = DT
endif
CFLAGS += -D$(SC_CUSTOMER)
CFLAGS += -DSC_CUSTOMER_$(SC_CUSTOMER)
CFLAGS += -DSC_CUSTOMER=\"$(SC_CUSTOMER)\"

#
# Include the specific configuration files from the config.boardtype file
# here.  This removes the need to set environmental variables through a
# script before building
#
include $(BUILDPATH)/product/$(PRODUCT_TYPE)/oem/$(SC_OEM)/config.mk
include $(BUILDPATH)/product/$(PRODUCT_TYPE)/customer/$(SC_CUSTOMER)/config.mk
include $(BUILDPATH)/product/$(PRODUCT_TYPE)/env.mak
include $(BUILDPATH)/product/$(PRODUCT_TYPE)/config.mk

ifndef SC_SUPPORT_MODULE
SC_SUPPORT_MODULE=$(SC_MODULE)
endif
export SC_SUPPORT_MODULE

#
# Put in safety checks here to ensure all required variables are defined in
# the configuration file
#

ifndef TOOLPREFIX
#error "Must specify TOOLPREFIX value"
endif

ifndef KERNELARCH
#error "Must specify KERNELARCH value"
endif

#
# Other environmental variables that are configured as per the configuration file
# specified above.  These contain all platform specific configuration items.
#
export INSTALL_ROOT = $(FS_DIR)
export MODULEPATH=$(INSTALL_ROOT)/lib/modules
export KERNEL_DIR = $(TOPDIR)/bsp/kernel/linux-3.4rt

export KERNELDIR=$(KERNEL_DIR)
export KERNEL_SRC=$(KERNEL_DIR)
export KERNEL_INC=$(KERNEL_DIR)/include

export MAKEARCH=$(MAKE)

export APPSPATH = $(TOPDIR)/user
export PRIVATE_APPSPATH = $(TOPDIR)/user/private
export PUBLIC_APPSPATH = $(TOPDIR)/user/public
export SHARED_APPSPATH = $(TOPDIR)/user/shared
export DEBUG_APPSPATH = $(TOPDIR)/user/debug
export TFTPPATH = $(BUILDPATH)
export INSTALLDIR = $(INSTALL_ROOT)
export TARGETDIR = $(INSTALL_ROOT)
export DESTDIR = $(INSTALL_ROOT)

#export PATH:=$(TOPDIR)/build/util:${PATH}

