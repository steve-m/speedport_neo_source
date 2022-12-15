#
#Rootfs squash or jffs2, now jffs2 is not supported
#

export ROOTFSTYPE=jffs2
export SC_DUALIMAGE = 1
export SC_NAND_FLASH_SIZE = 128

export PRODUCT_NAME = Speedport_NEO
export VENDOR_CODE =
export FW_VERSION = .2.6.003.0

export MODEL_NAME = Speedport NEO
export PRODUCT_CLASS = DTWSIMPLY1VR

#
#SC Module Name and ODM Name
#
export SC_MODULE = F1

export SC_ANNEX ?= B

#
#FW versions
#
export FW_EXTRA_VERSION =P2
export FW_BOOT_VERSION = 3.07.0
ifeq ($(SC_ANNEX), A)
export FW_DSL_VERSION = A2pv6F038j_rc6.d24h
else
export FW_DSL_VERSION = B2pv6F039p.d26a
endif

#
# Define the Features Here
#
export DT_SMART_SETUP = 0
export DT_LED_DEMO = 0
export SC_GPON = 0
export SC_OMCI = 0
export SC_IPHOST = 0
export CONFIG_SCM_SUPPORT = 1
export SC_SUPPORT_ERICSSON = 1
export SC_MIXVENDOR_SPT = 1
export SC_DMM = 0
export SC_SUPPORT_CATV = 0

export SC_WIFI = 1
export SC_WSC = 0
#please do not enable VOIP &SLIC_TEST at the same time

export SC_VOIP = 1
export VOIP_FXS = 0
export VOIP_DECT = 1
export LAN_PBX = 0
export NEO_VOICE = 0
export VOIP_NAPTR = 0

export SC_SLIC_TEST = 0
export SC_VOIP_LINE_EXCHANGE = 1

export SC_OD69 = 1

export SC_SWITCHTYPE = 

export SC_ROUTER = 1
export SC_MULTIWAN = 1
export SC_QUICK_TABLE = 0
export SC_HW_NAT = 0
export SC_DATA_RATE = 1

export SC_SNMP = 0
export SC_BFTPD = 0
export SC_TR069 = 1
export SC_OD69_CERT = 0
export SC_TR064 = 1
export SC_TR064_V2 = 1
export SC_TR064_V1 = 0
export SC_TR232 = 0
export SC_SSHD = 0
export SC_DROPBEAR = 0
export SC_USB_STORAGE = 0
export SC_FON = 1
export 3G_FEATURE = 0

export SC_FBIMAGE = 0
export COC_POWERSAVE = 1

export DSL_MODEM = 0

#wifi chip: realtek, atheros, brcm
export SC_WIFI_CHIP = brcm

export SC_IPV6 = 1
export SC_DDNS = 1

export RFT620_DEAMON_BOARD = 1

# OLT send reboot command to ONU via OMCI, The ONU do reboot until 120 seconds later.
# Change only wait 5 seconds before the reboot.
export SCM_OMCI_REBOOT = 1
# Modify the queue size to 128 for NAT performatnce
export SCM_QUEUE_SIZE = 1
export SCM_IGMP_SNOOP = 1
export SCM_PACKET_MARK = 1
export SC_HOMEPLUG = 1
export SC_IEEE1905 = 1

# Define Openssl version
export OPENSSL_VER = 1.0.2k
export WIFI_CERT_TEST = 0

CFLAGS += -D$(SC_MODULE) -D$(SC_SUPPORT_MODULE)
CFLAGS += -DSC_MODULE=\"$(SC_MODULE)\"

ifeq ($(CONFIG_SCM_SUPPORT), 1)
CFLAGS += -DCONFIG_SCM_SUPPORT
endif

ifeq ($(SC_NAND_FLASH_SIZE), 128)
CFLAGS += -DSUPPORT_NAND_FLASH_128M
endif

ifeq ($(RFT620_DEAMON_BOARD), 1)
CFLAGS += -DRFT620_DEAMON_BOARD
endif

ifeq ($(SC_MIXVENDOR_SPT), 1)
CFLAGS += -DSC_MIXVENDOR_SPT
endif

ifeq ($(SC_GPON), 1)
CFLAGS += -DSUPPORT_GPON
endif

ifeq ($(SC_OMCI), 1)
CFLAGS += -DSUPPORT_OMCI
endif

ifeq ($(SC_WIFI), 1)
CFLAGS += -DSUPPORT_WIFI
ifeq ($(SC_WIFI_CHIP), realtek)
CFLAGS += -DSUPPORT_WIFI_RTL
endif
ifeq ($(SC_WIFI_CHIP), atheros)
CFLAGS += -DSUPPORT_WIFI_ATH
endif
ifeq ($(SC_WIFI_CHIP), brcm)
CFLAGS += -DSUPPORT_WIFI_BCM
endif
endif

ifeq ($(SC_VOIP), 1)

CFLAGS += -DSUPPORT_VOIP

ifeq ($(VOIP_FXS), 1)
CFLAGS += -DSUPPORT_VOIP_FXS
endif

ifeq ($(VOIP_NAPTR), 1)
CFLAGS += -DSUPPORT_VOIP_NAPTR
endif

ifeq ($(VOIP_DECT), 1)
CFLAGS += -DVOIP_DECT
#CFLAGS += -DSUPPORT_FXS_AS_DECT
#CFLAGS += -DSUPPORT_DECT_ULE
#CFLAGS += -DSUPP_ACTIVE_SYNC
#CFLAGS += -DHS_NAME_CODE_UTF8
CFLAGS += -DIF_F1
CFLAGS += -DSUPP_DECT_POWER_REDUCTION
endif

ifeq ($(LAN_PBX), 1)
CFLAGS += -DSUPP_LOCAL_PBX

ifeq ($(NEO_VOICE), 1)
CFLAGS += -DSUPP_NEO_VOICE
endif

endif

endif

ifeq ($(SC_ROUTER), 1)
CFLAGS += -DSUPPORT_ROUTER
endif

ifeq ($(SC_QUICK_TABLE), 1)
CFLAGS += -DSUPPORT_QTBL
endif

ifeq ($(SC_HW_NAT), 1)
CFLAGS += -DSUPPORT_HWNAT
endif

ifeq ($(SC_DATA_RATE), 1)
CFLAGS += -DSUPPORT_DATA_RATE
endif

ifeq ($(SC_MULTIWAN), 1)
CFLAGS += -DSUPPORT_MULTIWAN
CFLAGS += -DSUPPORT_MULTIWAN_DOMAIN
CFLAGS += -DSUPPORT_MULTIWAN_NTP_BINDIP
endif

ifeq ($(SC_SNMP), 1)
CFLAGS += -DSUPPORT_SNMP
endif

ifeq ($(SC_BFTPD), 1)
CFLAGS += -DSUPPORT_BFTPD
endif

ifeq ($(SC_TR069), 1)
CFLAGS += -DSUPPORT_TR069
endif

ifeq ($(SC_OD69_CERT), 1)
CFLAGS += -DSUPPORT_OD69_CERT
endif

ifeq ($(SC_TR064), 1)
CFLAGS += -DSUPPORT_TR064
endif

ifeq ($(SC_TR064_V2), 1)
CFLAGS += -DSUPPORT_TR064_V2
endif

ifeq ($(SC_TR064_V1), 1)
CFLAGS += -DSUPPORT_TR064_V1
endif

ifeq ($(SC_TR232), 1)
CFLAGS += -DSUPPORT_TR232
endif

ifeq ($(SC_SSHD), 1)
CFLAGS += -DSUPPORT_SSHD
endif

ifeq ($(SC_DROPBEAR), 1)
CFLAGS += -DSUPPORT_DROPBEAR
endif

ifeq ($(SC_DUALIMAGE), 1)
CFLAGS += -DSUPPORT_DUALIMAGE
endif

ifeq ($(SC_IPV6), 1)
CFLAGS += -DSUPPORT_IPV6
endif

ifeq ($(SC_DDNS), 1)
CFLAGS += -DSUPPORT_DDNS
endif

ifeq ($(SCM_PACKET_MARK), 1)
CFLAGS += -DSCM_PACKET_MARK
endif

ifeq ($(SC_USB_STORAGE), 1)
CFLAGS += -DSUPPORT_USB_STORAGE
endif

ifeq ($(SC_FON), 1)
CFLAGS += -DSUPPORT_FON
endif

ifeq ($(3G_FEATURE), 1)
CFLAGS += -D_3G_FEATURE_
endif

ifeq ($(SC_FBIMAGE), 1)
CFLAGS += -D_SC_FBIMAGE_
endif

ifeq ($(COC_POWERSAVE), 1)
CFLAGS += -DCOC_POWERSAVE
endif

ifeq ($(DSL_MODEM), 1)
CFLAGS += -DDSL_MODEM
endif

ifeq ($(SC_EMC), 1)
CFLAGS += -D_SC_EMC_
endif

ifeq ($(SC_HOMEPLUG), 1)
CFLAGS += -D_SC_HOMEPLUG_
endif

ifeq ($(SC_IEEE1905), 1)
CFLAGS += -D_SC_IEEE1905_
endif

ifeq ($(SC_OD69), 1)
CFLAGS += -DSUPPORT_OD69
endif

#Only DT use TR181 now , you can use SC_CUSTOMER or HW_STARTER or HW_ALLIN to enable SC_USE_TR098.
ifneq ($(SC_CUSTOMER), DT)
export SC_USE_TR098 = 1
CFLAGS += -DSC_USE_TR098
endif

ifeq ($(WIFI_CERT_TEST),1)
CFLAGS += -D_WIFI_CERT_TEST_
CFLAGS += -DWPS20_LOGO
endif

ifeq ($(DT_SMART_SETUP), 1)
    CFLAGS += -DDT_SMART_SETUP
endif

CFLAGS += -D_SC_ABUSE_DETECT_FORCE_OFF_

export CFLAGS

