# File: bcmdrivers/char/secosdrv/bcm963268/Makefile
#
# Makefile for the BCM63xx secosdrv module
#

obj-m += secosdrv.o
secosdrv-objs += secos_km.o

#Do we need to add the include path?
#EXTRA_CFLAGS += -I. -I$(INC_BRCMDRIVER_PUB_PATH)/$(BRCM_BOARD) -I$(INC_BRCMDRIVER_PRIV_PATH)/$(BRCM_BOARD) -I$(INC_BRCMSHARED_PUB_PATH)/$(BRCM_BOARD) -I$(INC_BRCMSHARED_PRIV_PATH)/$(BRCM_BOARD) -I$(INC_BRCMBOARDPARMS_PATH)/$(BRCM_BOARD)


EXTRA_CFLAGS += -I$(obj)
EXTRA_CFLAGS += -I$(BUILD_DIR)/userspace/private/apps/vgw/secos -I$(BUILD_DIR)/userspace/private/apps/vgw/include

EXTRA_CFLAGS += -Werror -Wall


clean:
	rm -f core *.o *.a *.s .*.cmd *.ko
	rm -f $(BCM_DIR)/secosdrv.ko




