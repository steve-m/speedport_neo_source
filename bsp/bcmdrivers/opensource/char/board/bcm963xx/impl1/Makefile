# Makefile for the bcm963xx board drivers
#


obj-y := board.o bcm63xx_flash.o bcm63xx_led.o bcm63xx_gpio.o pushbutton.o

ifneq ($(strip $(BUILD_IEEE1905)),)
obj-y += ieee1905_module.o    
endif

ifneq ($(findstring _$(strip $(BRCM_CHIP))_,,_63268_63138_63148_6838_),)

ifneq ($(strip $(BUILD_6802_MOCA)),)
    obj-y += bbsi/bbsi.o    
    obj-y += bbsi/bbsiExecSeq.o   
    obj-y += moca/6802/init.o   
    
else
    obj-y += spidevices.o
endif

endif

ifneq ($(strip $(CONFIG_BCM_CPLD1)),)
    obj-y += bcmcpld1.o
	EXTRA_CFLAGS += -DCONFIG_BCM_CPLD1
endif

ifneq ($(strip $(BUILD_BRCM_FTTDP)),)
    obj-y += dsldsp_operation.o
	EXTRA_CFLAGS += -DBRCM_FTTDP
endif
 
EXTRA_CFLAGS += -I. -I$(INC_BRCMDRIVER_PUB_PATH)/$(BRCM_BOARD) -I$(INC_BRCMSHARED_PUB_PATH)/$(BRCM_BOARD) -I$(INC_BRCMSHARED_PUB_PATH)/$(BRCM_BOARD)
ifneq ($(findstring _$(strip $(BRCM_CHIP))_,,_63138_63148_6838_),)
EXTRA_CFLAGS += -I$(INC_BRCMSHARED_PUB_PATH)/pmc
endif
EXTRA_CFLAGS += -Werror -Wfatal-errors
EXTRA_CFLAGS += -g

ifneq ($(strip $(CONFIG_BCM_WLAN)),)
	EXTRA_CFLAGS += -DWIRELESS
endif

ifeq ($(SC_MODULE), Entry2)
	EXTRA_CFLAGS += -DEntry2
endif

-include $(TOPDIR)/Rules.make

clean:
	rm -f core *.o *.a *.s

