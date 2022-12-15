LIB = libhomeplugctl_drv.so
default: dynamic


libhomeplugctl_drv.so:
	cp libhomeplugctl_drv.so_$(PROFILE).save libhomeplugctl_drv.so

dynamic: generic_private_lib_install

clean:
	rm -f libhomeplugctl_drv.so

CURR_DIR := $(shell pwd)
BUILD_DIR := $(subst /userspace, /userspace,$(CURR_DIR))
BUILD_DIR := $(word 1, $(BUILD_DIR))
include $(BUILD_DIR)/make.common
