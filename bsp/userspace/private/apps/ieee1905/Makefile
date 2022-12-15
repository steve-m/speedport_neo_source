EXE = ieee1905
dynamic: generic_exe_install

clean:
	rm -f ieee1905


ieee1905:
	cp ieee1905_$(PROFILE).save ieee1905

CURR_DIR := $(shell pwd)
BUILD_DIR := $(subst /userspace, /userspace,$(CURR_DIR))
BUILD_DIR := $(word 1, $(BUILD_DIR))
include $(BUILD_DIR)/make.common
