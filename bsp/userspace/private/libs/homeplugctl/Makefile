LIB = libhomeplugctl.so
default: dynamic


libhomeplugctl.so:
	cp libhomeplugctl.so_$(PROFILE).save libhomeplugctl.so

dynamic: generic_private_lib_install

clean:
	rm -f libhomeplugctl.so

CURR_DIR := $(shell pwd)
BUILD_DIR := $(subst /userspace, /userspace,$(CURR_DIR))
BUILD_DIR := $(word 1, $(BUILD_DIR))
include $(BUILD_DIR)/make.common
