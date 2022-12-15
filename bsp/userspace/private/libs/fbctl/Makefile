LIB = libfbctl.so
default: dynamic


libfbctl.so:
	cp libfbctl.so_$(PROFILE).save libfbctl.so

dynamic: generic_private_lib_install

clean:
	rm -f libfbctl.so

CURR_DIR := $(shell pwd)
BUILD_DIR := $(subst /userspace, /userspace,$(CURR_DIR))
BUILD_DIR := $(word 1, $(BUILD_DIR))
include $(BUILD_DIR)/make.common
