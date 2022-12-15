
# -----------------------------------------------------------------|
# sercomm add
# -----------------------------------------------------------------|

SC_BUILD=1
EXT_CPU_ARCH_NAME=mips32
export EXT_CPU_ARCH_NAME

# Setup sc build options.
ifeq ($(SC_BUILD),1)
BCM_DIR = $(shell pwd)/bin
LIBDIR = $(CROSS_DIR)/lib
SC_LIB_PATH = -L$(FS_DIR)/lib -L$(BCM_DIR)
export BCM_DIR LIBDIR SC_LIB_PATH
export BUILD_WLCTL_SHLIB=1
export SC_BUILD=1
export DSLCPE_WLCSM_EXT=1
endif
WIRELESS_DRIVER_PATH=$(BRCMDRIVERS_DIR)/broadcom/net/wl/bcm9$(BRCM_CHIP)
INC_WIRELESS_DRIVER_PATH=$(WIRELESS_DRIVER_PATH)/include
SHARED_WIRELESS_DRIVER_PATH=$(WIRELESS_DRIVER_PATH)/build/wlobj-wlconfig_lx_wl_dslcpe_pci_ap_2nv-kdb/shared
SHARED_WIRELESS_ROUTER_PATH=$(WIRELESS_DRIVER_PATH)/router/shared
BCMWIFI_WIRELESS_ROUTER_PATH=$(WIRELESS_DRIVER_PATH)/shared/bcmwifi/src
BCM_INSTALL_DIR=$(shell pwd)/targets/$(PROFILE)/fs.install/

$(warning MAKEFILE_LIST: $(MAKEFILE_LIST))
this_dir:= $(dir $(lastword $(MAKEFILE_LIST)))
include $(this_dir)/PROFILE.make

#BUILD_DIR = $(shell pwd)
#include make.common

help:
	@echo "make help      --> show usage, sercomm modified"
	@echo "make sc_kernel --> build vmlinux.lz"
	@echo "make clean     --> clean kernel"
	@echo "make sc_driver --> install drivers"      
	@echo "make sc_GPL    --> GPL release"  
	@echo "make bcm_fw    --> build bcm code"  
	@echo "make bcm_clean --> clean bcm code"  
	@echo "make note      --> driver change note"

GPL_DIR=/root/fw/GPL

note:
	@cat README
	
sc_GPL:
	@echo
	@echo "<-- GPL for bcm kernel -->"
	@echo " GPL_DIR = $(GPL_DIR) "
#-- copy files --
	make clean
	cp -ra ./  $(GPL_DIR)/kernel
#-- remove files -- 
	rm -rf $(GPL_DIR)/kernel/bin
	rm -rf $(GPL_DIR)/kernel/userapps
	rm -f $(GPL_DIR)/kernel/shared
	cp -ra ../../Bootcode/bcm963xx_cfe_src_010037_1021/shared $(GPL_DIR)/kernel/
#-- remove not open bcm drivers --
	rm -rf $(GPL_DIR)/kernel/bcmdrivers/broadcom/atm
	rm -rf $(GPL_DIR)/kernel/bcmdrivers/broadcom/atmbondingeth
	rm -rf $(GPL_DIR)/kernel/bcmdrivers/broadcom/net
	rm -rf $(GPL_DIR)/kernel/bcmdrivers/broadcom/char/adsl
	rm -rf $(GPL_DIR)/kernel/bcmdrivers/broadcom/char/atmapi        
	rm -rf $(GPL_DIR)/kernel/bcmdrivers/broadcom/char/atmapi        
	rm -rf $(GPL_DIR)/kernel/bcmdrivers/broadcom/char/atmbonding    
	rm -rf $(GPL_DIR)/kernel/bcmdrivers/broadcom/char/bcmprocfs     
	rm -rf $(GPL_DIR)/kernel/bcmdrivers/broadcom/char/profiler      
#-- copy needed headers --
	@mkdir -p $(GPL_DIR)/kernel/bcmdrivers/broadcom/char/adsl/impl1/softdsl
	@cp bcmdrivers/broadcom/char/adsl/impl1/AdslCoreMap.h $(GPL_DIR)/kernel/bcmdrivers/broadcom/char/adsl/impl1/
	@cp bcmdrivers/broadcom/char/adsl/impl1/softdsl/AdslCoreDefs.h $(GPL_DIR)/kernel/bcmdrivers/broadcom/char/adsl/impl1/softdsl/
	@cp bcmdrivers/broadcom/char/adsl/impl1/softdsl/AdslXfaceData.h $(GPL_DIR)/kernel/bcmdrivers/broadcom/char/adsl/impl1/softdsl/
	@cp bcmdrivers/broadcom/char/adsl/impl1/softdsl/CircBuf.h $(GPL_DIR)/kernel/bcmdrivers/broadcom/char/adsl/impl1/softdsl/
	@mkdir -p $(GPL_DIR)/kernel/bcmdrivers/broadcom/char/adsl/impl1/adslcore6348 
	@cp bcmdrivers/broadcom/char/adsl/impl1/adslcore6348/adsl_defs.h $(GPL_DIR)/kernel/bcmdrivers/broadcom/char/adsl/impl1/adslcore6348 
	@mkdir -p $(GPL_DIR)/kernel/bcmdrivers/broadcom/char/adsl/impl1/adslcore6348B 
	@cp bcmdrivers/broadcom/char/adsl/impl1/adslcore6348B/adsl_defs.h $(GPL_DIR)/kernel/bcmdrivers/broadcom/char/adsl/impl1/adslcore6348B
	@mkdir -p $(GPL_DIR)/kernel/bcmdrivers/broadcom/char/adsl/impl1/adslcore6348C
	@cp bcmdrivers/broadcom/char/adsl/impl1/adslcore6348C/adsl_defs.h $(GPL_DIR)/kernel/bcmdrivers/broadcom/char/adsl/impl1/adslcore6348C
#-- linux config --
	sed 's/CONFIG_BCM_ENET=m/# CONFIG_BCM_ENET is not set/' $(GPL_DIR)/kernel/kernel/linux/.config >  $(GPL_DIR)/kernel/kernel/linux/.config2
	sed 's/CONFIG_BCM_WLAN=m/# CONFIG_BCM_WLAN is not set/' $(GPL_DIR)/kernel/kernel/linux/.config2 >  $(GPL_DIR)/kernel/kernel/linux/.config3
	sed 's/CONFIG_BCM_ADSL=m/# CONFIG_BCM_ADSL is not set/' $(GPL_DIR)/kernel/kernel/linux/.config3 >       $(GPL_DIR)/kernel/kernel/linux/.config4 
	sed 's/CONFIG_BCM_ATMAPI=m/# CONFIG_BCM_ATMAPI is not set/' $(GPL_DIR)/kernel/kernel/linux/.config4 >   $(GPL_DIR)/kernel/kernel/linux/.config  

	rm -f $(GPL_DIR)/kernel/kernel/linux/.config2
	rm -f $(GPL_DIR)/kernel/kernel/linux/.config3
	rm -f $(GPL_DIR)/kernel/kernel/linux/.config4
	rm -f $(GPL_DIR)/kernel/kernel/linux/.config_4M
	rm -f $(GPL_DIR)/kernel/kernel/linux/.config_8M

	echo PROJ_DIR_KERNEL_SRC=kernel/kernel/linux >> $(GPL_DIR)/Rules.mak
	echo "export PROJ_DIR_KERNEL_SRC" >> $(GPL_DIR)/Rules.mak
	cp vmlinux.lz $(GPL_DIR)/

sc_kernel:  vmlinux.lz_only  
	@echo -e "\\e[36m -- make kernel done --\e[0m"	
	@echo

sc_GPL_build2:
	cp vmlinux.lz ../vmlinux.lz
        
sc_GPL_build: vmlinux.lz_only sc_GPL_build2
	@echo -e "\\e[36m -- make kernel done --\e[0m"	
	@echo

sc_modules:
	@echo -e "\\e[36m -- make kernel modules --\e[0m"	
	@echo

#-------------------------------------------
sc_driver: sc_prepare sc_modules sc_modules_install data-model cms_sc adsl_sc vlan_sc ethsw_sc ethctl_sc spu_sc fapctl_sc snoopctl_sc fc_sc pwrctl_sc homeplug_sc sc_wlan smd_sc ieee1905_sc sc_tmsctl sc_iqctl #vodsl_sc voctl_sc
	@echo BUILD_DIR=$(BUILD_DIR)
	@echo FS_DIR=$(FS_DIR)
	@echo BCM_DIR=$(BCM_DIR)                
	@echo SC_LIB_PATH=$(SC_LIB_PATH)

	cp -af $(BCM_DIR)/libiqctl.so $(FS_DIR)/lib/
	cp -af $(BCM_DIR)/iqctl $(FS_DIR)/usr/sbin/
	cp -af $(BCM_DIR)/tmsctl $(FS_DIR)/usr/sbin/
	cp -af $(BCM_DIR)/pktflow.ko $(FS_DIR)/lib/modules/
	cp -af $(BCM_DIR)/bcmxtmcfg.ko $(FS_DIR)/lib/modules/
	cp -af $(BCM_DIR)/bcmxtmrtdrv.ko $(FS_DIR)/lib/modules/
ifeq ($(strip $(BRCM_DRIVER_FAP)),m)
	cp -af $(BCM_DIR)/bcmfap.ko $(FS_DIR)/lib/modules/
endif
	cp -af $(BCM_DIR)/adsldd.ko $(FS_DIR)/lib/modules/
	cp -af $(BCM_DIR)/bcm_enet.ko $(FS_DIR)/lib/modules/
	cp -af $(BCM_DIR)/bcm_ingqos.ko $(FS_DIR)/lib/modules/
	cp -af $(BCM_DIR)/bcm_bpm.ko $(FS_DIR)/lib/modules/
	cp -af $(BCM_DIR)/pwrmngtd.ko $(FS_DIR)/lib/modules/
	cp -af $(BCM_DIR)/chipinfo.ko $(FS_DIR)/lib/modules/
	cp -af $(BCM_DIR)/p8021ag.ko $(FS_DIR)/lib/modules/
	cp -af $(BCM_DIR)/nciTMSkmod.ko $(FS_DIR)/lib/modules/
ifeq ($(PRODUCT_TYPE), F1)
	cp -af $(BCM_DIR)/bcmarl.ko $(FS_DIR)/lib/modules/
	cp -af $(BCM_DIR)/wfd.ko $(FS_DIR)/lib/modules/
endif
	cp -af $(BCM_DIR)/wl.ko $(FS_DIR)/lib/modules/
	cp -af $(BCM_DIR)/dhd.ko $(FS_DIR)/lib/modules/
	cp -af $(BCM_DIR)/wlemf.ko $(FS_DIR)/lib/modules/
	cp -af $(BCM_DIR)/wlcsm.ko $(FS_DIR)/lib/modules/
	cp -af $(BCM_DIR)/wlevt $(FS_DIR)/usr/sbin/
#	cp -af $(BCM_DIR)/libwlbcmcrypto.so $(FS_DIR)/lib/
#	cp -af $(BCM_DIR)/libwlbcmshared.so $(FS_DIR)/lib/
#	cp -af $(BCM_DIR)/sc_priority.ko $(FS_DIR)/lib/modules/

	@if [ -e $(BCM_DIR)/libwlbcmcrypto.so ]; then\
		echo "copy libwlbcmcrypto.so from $(BCM_DIR) to $(FS_DIR)";\
		cp -af $(BCM_DIR)/libwlbcmcrypto.so $(FS_DIR)/lib/;\
	fi
	@if [ -e $(BCM_DIR)/libwlbcmshared.so ]; then\
		echo "copy libwlbcmshared.so from $(BCM_DIR) to $(FS_DIR)";\
		cp -af $(BCM_DIR)/libwlbcmshared.so $(FS_DIR)/lib/;\
	fi
	@if [ -e $(FS_DIR)/usr/etc/wlan ]; then\
		rm -rf $(FS_DIR)/usr/etc/wlan ;\
	fi
#	@if [ -e $(BCM_DIR)/wsc_config_1a_ap.txt ]; then\
		cp -af $(BCM_DIR)/wsc_config_1a_ap.txt $(FS_DIR)/usr/etc ;\
	fi
	@if [ -e $(BCM_DIR)/wps_monitor	]; then\
		cp -af $(BCM_DIR)/wps_monitor  $(FS_DIR)/usr/sbin ;\
	fi

	@if [ -e $(BCM_DIR)/libwps.so ]; then\
		echo "copy libwps.so from $(BCM_DIR) to $(FS_DIR)";\
		cp -af $(BCM_DIR)/libwps.so $(FS_DIR)/lib/;\
	fi
	@if [ -e $(BCM_DIR)/libwlupnp.so ]; then\
		echo "copy libwlupnp.so from $(BCM_DIR) to $(FS_DIR)";\
		cp -af $(BCM_DIR)/libwlupnp.so $(FS_DIR)/lib/;\
	fi
	@if [ -e $(BCM_DIR)/igd ]; then\
		echo "copy igd from $(BCM_DIR) to $(FS_DIR)";\
		cp -af $(BCM_DIR)/igd $(FS_DIR)/usr/sbin;\
	fi
	@if [ -e $(BCM_DIR)/libupnp ]; then\
		echo "copy bcmupnp from $(BCM_DIR) to $(FS_DIR)";\
		cp -af $(BCM_DIR)/libwlupnp.so $(FS_DIR)/lib/;\
	fi
	@if [ -e $(BCM_DIR)/eapd ]; then\
		echo "copy eapd from $(BCM_DIR) to $(FS_DIR)";\
		cp -af $(BCM_DIR)/eapd $(FS_DIR)/usr/sbin;\
	fi
	@if [ -e $(BCM_DIR)/acsd ]; then\
		echo "copy acsd from $(BCM_DIR) to $(FS_DIR)";\
		cp -af $(BCM_DIR)/acsd $(FS_DIR)/usr/sbin;\
	fi
	@if [ -e $(BCM_DIR)/acs_cli ]; then\
		echo "copy acs_cli from $(BCM_DIR) to $(FS_DIR)";\
		cp -af $(BCM_DIR)/acs_cli $(FS_DIR)/usr/sbin;\
	fi
	@if [ -e $(BCM_DIR)/lld2d ]; then\
		echo "copy lld2d from $(BCM_DIR) to $(FS_DIR)";\
		cp -af $(BCM_DIR)/lld2d $(FS_DIR)/usr/sbin;\
	fi

	mkdir -p $(FS_DIR)/usr/etc/wlan/;\
	cp -av $(WIRELESS_DRIVER_PATH)/bcm*_map.bin $(FS_DIR)/usr/etc/wlan/

	cp -af $(BCM_DIR)/libcms_msg.so $(FS_DIR)/lib
	cp -af $(BCM_DIR)/libcms_util.so $(FS_DIR)/lib
	cp -af $(BCM_DIR)/libcms_boardctl.so $(FS_DIR)/lib
	cp -af $(BCM_DIR)/libcms_core.so $(FS_DIR)/lib
	cp -af $(BCM_DIR)/libcms_cli.so $(FS_DIR)/lib
	cp -af $(BCM_DIR)/libcms_dal.so $(FS_DIR)/lib
	cp -af $(BCM_DIR)/libcms_qdm.so $(FS_DIR)/lib
	 
	mkdir -p $(FS_DIR)/usr/etc/adsl/
	cp -af $(BCM_DIR)/adsl_phy.bin $(FS_DIR)/usr/etc/adsl/
	cp -af $(BCM_DIR)/xdslctl $(FS_DIR)/bin/
	cp -af $(BCM_DIR)/adslctl $(FS_DIR)/bin/
	cp -af $(BCM_DIR)/libxdslctl.so $(FS_DIR)/lib/
	cp -af $(BCM_DIR)/dsldiagd $(FS_DIR)/bin/
	cp -af $(BCM_DIR)/xtmctl $(FS_DIR)/bin/
	cp -af $(BCM_DIR)/xtm $(FS_DIR)/bin/
	cp -af $(BCM_DIR)/libatmctl.so $(FS_DIR)/lib
	cp -af $(BCM_DIR)/ethctl $(FS_DIR)/bin/
	cp -af $(BCM_DIR)/ethswctl $(FS_DIR)/bin/
	

#	cp $(BCM_DIR)/br_qos.ko $(FS_DIR)/lib/modules/

	cp -af $(BCM_DIR)/bcmvlan.ko $(FS_DIR)/lib/modules/
	cp -af $(BCM_DIR)/vlanctl $(FS_DIR)/bin/
	cp -af $(BCM_DIR)/libvlanctl.so $(FS_DIR)/lib/
	cp -af $(BCM_DIR)/libethswctl.so $(FS_DIR)/lib/
	cp -af $(BCM_DIR)/smd $(FS_DIR)/usr/sbin
	cp -af $(BCM_DIR)/spuctl $(FS_DIR)/bin/
	cp -af $(BCM_DIR)/libspuctl.so $(FS_DIR)/lib/

	cp -af $(BCM_DIR)/{fc,fcctl} $(FS_DIR)/bin
	cp -af $(BCM_DIR)/libfcctl.so $(FS_DIR)/lib
	
	cp -af $(BCM_DIR)/pwrctl $(FS_DIR)/bin
	cp -af $(BCM_DIR)/libpwrctl.so $(FS_DIR)/lib
	
	cp -af $(BCM_DIR)/libsnoopctl.so $(FS_DIR)/lib

	cp -af $(BCM_DIR)/libfapctl.so $(FS_DIR)/lib
	cp -af $(BCM_DIR)/libmdm.so $(FS_DIR)/lib
	cp -af $(BCM_DIR)/libnanoxml.so $(FS_DIR)/lib

	cp -af $(BCM_DIR)/fapctl $(FS_DIR)/bin
ifeq ($(BUILD_HOMEPLUG), y)
	mkdir -p $(FS_DIR)/etc/plcboot
	mkdir -p $(FS_DIR)/data/
	cp -af $(BCM_DIR)/plcnvm $(FS_DIR)/bin
	cp -af $(BCM_DIR)/plcboot $(FS_DIR)/bin
	cp -af $(BCM_DIR)/libethswctl.so $(FS_DIR)/lib
	cp -af $(BCM_DIR)/libhomeplugctl.so $(FS_DIR)/lib
	cp -af $(BCM_DIR)/libhomeplugctl_drv.so $(FS_DIR)/lib
	cp -af $(BCM_DIR)/homeplugd $(FS_DIR)/bin
	cp -af $(BCM_DIR)/homeplugctl $(FS_DIR)/bin
endif
	cp -af $(BCM_DIR)/ebtables $(FS_DIR)/bin
	cp -af $(BCM_DIR)/libebt*.so $(FS_DIR)/lib
	cp -af $(BCM_DIR)/ethertypes $(FS_DIR)/etc

ifeq ($(BUILD_IEEE1905), y)
	cp -af $(BCM_DIR)/libfbctl.so $(FS_DIR)/lib
	cp -af $(BCM_DIR)/ieee1905 $(FS_DIR)/bin
endif

	cp -af $(BUILD_DIR)/bcmdrivers/broadcom/char/secosdrv/bcm9$(BRCM_CHIP)/secosdrv.ko $(FS_DIR)/lib/modules
ifneq ($(strip $(BUILD_VODSL)),)
	cp -af $(BUILD_DIR)/bcmdrivers/broadcom/char/endpoint/bcm9$(BRCM_CHIP)/endpointdd.ko $(FS_DIR)/lib/modules
	#cp -af $(BUILD_DIR)/bcmdrivers/broadcom/char/endpoint/bcm9$(BRCM_CHIP)/endptdrv/endptdrv.ko $(FS_DIR)/lib/modules
	#cp -af $(BUILD_DIR)/bcmdrivers/broadcom/char/endpoint/bcm9$(BRCM_CHIP)/haushost/haushost.ko $(FS_DIR)/lib/modules
	#cp -af $(BUILD_DIR)/bcmdrivers/broadcom/char/endpoint/bcm9$(BRCM_CHIP)/gwcommon/gwcommon.ko $(FS_DIR)/lib/modules
	#cp -af $(BUILD_DIR)/bcmdrivers/opensource/char/pcmshim/bcm9$(BRCM_CHIP)/pcmshim.ko $(FS_DIR)/lib/modules
endif
	cp -af $(BUILD_DIR)/userspace/public/libs/libsrv/libsrv.so $(FS_DIR)/lib

	@echo -e "\\e[36m -- sc_driver --\e[0m"	

vmlinux.lz_only : prebuild_checks profile_saved_check sanity_check \
      create_install kernelbuild modbuild kernelbuildlite hosttools vmlinux.lz_gen

vmlinux.lz_gen:
	@rm -f ./vmlinux
	@rm -f ./vmlinux.bin
	@rm -f ./vmlinux.lz
	cp $(KERNEL_DIR)/vmlinux . ; \
	$(STRIP) --remove-section=.note --remove-section=.comment vmlinux; \
	$(OBJCOPY) -O binary vmlinux vmlinux.bin; \
	$(HOSTTOOLS_DIR)/cmplzma -k -2 vmlinux vmlinux.bin vmlinux.lz

sc_prepare:
	if [ -d $(BCM_DIR) ]; then\
		rm -rf $(BCM_DIR);\
		mkdir $(BCM_DIR);\
	else\
		mkdir $(BCM_DIR);\
	fi

cms_sc:
	$(MAKE) -C userspace/public/include/
	$(MAKE) -C userspace/private/libs/cms_core
	$(MAKE) -C userspace/private/libs/cms_cli
	$(MAKE) -C userspace/private/libs/cms_dal
	$(MAKE) -C userspace/private/libs/cms_qdm
	$(MAKE) -C userspace/public/libs/cms_msg
	$(MAKE) -C userspace/public/libs/cms_util
	$(MAKE) -C userspace/public/libs/cms_boardctl
	cp userspace/private/libs/cms_core/libcms_core.so $(BCM_DIR)
	cp userspace/private/libs/cms_cli/libcms_cli.so $(BCM_DIR)
	cp userspace/private/libs/cms_dal/libcms_dal.so $(BCM_DIR)
	cp userspace/private/libs/cms_qdm/libcms_qdm.so $(BCM_DIR)
	cp userspace/public/libs/cms_msg/libcms_msg.so $(BCM_DIR)
	cp userspace/public/libs/cms_util/libcms_util.so $(BCM_DIR)
	cp userspace/public/libs/cms_boardctl/libcms_boardctl.so $(BCM_DIR)
	 
nvram_lib:
	$(MAKE) -C userspace/private/apps/wlan/nvram libnvram
	$(MAKE) -C userspace/private/apps/wlan/nvram nvram
	cp userspace/private/apps/wlan/nvram/libnvram.so $(BCM_DIR)
	cp userspace/private/apps/wlan/nvram/nvram $(BCM_DIR)


wlcsm_lib:
	$(MAKE) -C userspace/private/apps/wlan/wlcsm libwlcsm.so
	cp userspace/private/apps/wlan/wlcsm/libwlcsm.so $(BCM_DIR)
	
nas_sc:
	$(MAKE) -C $(BRCMDRIVERS_DIR)/broadcom/net/wl/bcm9$(BRCM_CHIP)/router/nas dynamic
	install -m 755 $(BRCMDRIVERS_DIR)/broadcom/net/wl/bcm9$(BRCM_CHIP)/router/nas/nas $(BCM_DIR)
	$(STRIP) $(BUILD_DIR)/bin/nas
        
acsd_sc:
	$(MAKE) -C $(BRCMDRIVERS_DIR)/broadcom/net/wl/bcm9$(BRCM_CHIP)/router/acsd dynamic
	install -m 755  $(BRCMDRIVERS_DIR)/broadcom/net/wl/bcm9$(BRCM_CHIP)/router/acsd/acsd $(BCM_DIR)
	$(STRIP) $(BCM_DIR)/acsd
	install -m 755  $(BRCMDRIVERS_DIR)/broadcom/net/wl/bcm9$(BRCM_CHIP)/router/acsd/acs_cli $(BCM_DIR)
	$(STRIP) $(BCM_DIR)/acs_cli

 
wlctl_sc:
	$(MAKE) -C $(BRCMDRIVERS_DIR)/broadcom/net/wl/bcm9$(BRCM_CHIP)/wl/exe dynamic
	install -m 755 $(BRCMDRIVERS_DIR)/broadcom/net/wl/bcm9$(BRCM_CHIP)/wl/exe/wlctl $(BCM_DIR) 
	$(STRIP) $(BCM_DIR)/wlctl
	cp -av $(BRCMDRIVERS_DIR)/broadcom/net/wl/bcm9$(BRCM_CHIP)/wl/exe/libwlctl.so $(BCM_DIR) 
	mkdir -p $(BCM_DIR)/wlan_map
	cp -av $(SHARED_WIRELESS_DRIVER_PATH)/bcm*_map.bin $(BCM_DIR)/wlan_map
	$(MAKE) -C $(WIRELESS_DRIVER_PATH)/router/shared install
	$(MAKE) -C $(WIRELESS_DRIVER_PATH)/bcmcrypto install
	cp -av $(WIRELESS_DRIVER_PATH)/router/shared/libwlbcmshared.so $(BCM_DIR)
	cp -av $(WIRELESS_DRIVER_PATH)/bcmcrypto/libwlbcmcrypto.so $(BCM_DIR)
	cp -av $(WIRELESS_DRIVER_PATH)/wl/exe/libwlctl.so $(BCM_DIR)

wps_sc:
	$(MAKE) -C $(BRCMDRIVERS_DIR)/broadcom/net/wl/bcm9$(BRCM_CHIP)/router/libupnp install
	install -m 755 $(BRCMDRIVERS_DIR)/broadcom/net/wl/bcm9$(BRCM_CHIP)/router/libupnp/libwlupnp.so $(BCM_DIR)
	$(MAKE) -C $(BRCMDRIVERS_DIR)/broadcom/net/wl/bcm9$(BRCM_CHIP)/wps dynamic
	install -m 755 $(BRCMDRIVERS_DIR)/broadcom/net/wl/bcm9$(BRCM_CHIP)/wps/libwps.so $(BCM_DIR)
	install -m 755 $(BRCMDRIVERS_DIR)/broadcom/net/wl/bcm9$(BRCM_CHIP)/wps/wps_monitor $(BCM_DIR)
	$(MAKE) -C $(BRCMDRIVERS_DIR)/broadcom/net/wl/bcm9$(BRCM_CHIP)/router/eapd dynamic
	install -m 755 $(BRCMDRIVERS_DIR)/broadcom/net/wl/bcm9$(BRCM_CHIP)/router/eapd/eapd $(BCM_DIR)
	$(MAKE) -C $(BRCMDRIVERS_DIR)/broadcom/net/wl/bcm9$(BRCM_CHIP)/router/lltd dynamic
	install -m 755  $(BRCMDRIVERS_DIR)/broadcom/net/wl/bcm9$(BRCM_CHIP)/router/lltd/lld2d $(BCM_DIR)

wl_sc: wlcsm_lib nvram_lib wlctl_sc nas_sc  wps_sc acsd_sc

qos_sc:
	@echo "sc_qos"
	cd $(KERNEL_DIR); $(MAKE) M=$(BRCMDRIVERS_DIR)/broadcom/sc_priority modules

homeplug_sc:
	$(MAKE) -C $(BUILD_DIR)/userspace/private/libs/nanoxml
	cp -af $(BUILD_DIR)/userspace/private/libs/nanoxml/libnanoxml.so $(BCM_DIR)
ifeq ($(BUILD_HOMEPLUG), y)
	$(MAKE) -C $(BUILD_DIR)/userspace/private/libs/ethswctl/
	install -m 755 $(BUILD_DIR)/userspace/private/libs/ethswctl/libethswctl.so $(BCM_DIR)
	$(MAKE) -C $(BUILD_DIR)/userspace/private/apps/plcnvm dynamic 
	install -m 755 $(BUILD_DIR)/userspace/private/apps/plcnvm/plcnvm $(BCM_DIR)
	$(MAKE) -C $(BUILD_DIR)/userspace/private/apps/plcboot dynamic
	install -m 755 $(BUILD_DIR)/userspace/private/apps/plcboot/plcboot $(BCM_DIR)
	$(MAKE) -C $(BUILD_DIR)/userspace/private/libs/homeplugctl dynamic 
	install -m 755 $(BUILD_DIR)/userspace/private/libs/homeplugctl/libhomeplugctl.so $(BCM_DIR)
	$(MAKE) -C $(BUILD_DIR)/userspace/private/libs/homeplugctl_drv dynamic 
	install -m 755 $(BUILD_DIR)/userspace/private/libs/homeplugctl_drv/libhomeplugctl_drv.so $(BCM_DIR)
	$(MAKE) -C $(BUILD_DIR)/userspace/private/apps/homeplugd dynamic 
	install -m 755 $(BUILD_DIR)/userspace/private/apps/homeplugd/homeplugd $(BCM_DIR)
	$(MAKE) -C $(BUILD_DIR)/userspace/private/apps/homeplugctl dynamic 
	install -m 755 $(BUILD_DIR)/userspace/private/apps/homeplugctl/homeplugctl $(BCM_DIR)
endif
	$(MAKE) -C $(BUILD_DIR)/userspace/gpl/apps/ebtables install
	install -m 0755 $(BUILD_DIR)/userspace/gpl/apps/ebtables/ebtables-v2.0.10-4/ebtables $(BCM_DIR)
	install -m 0755 $(BUILD_DIR)/userspace/gpl/apps/ebtables/ebtables-v2.0.10-4/extensions/libebt*.so $(BCM_DIR)
	install -m 0755 $(BUILD_DIR)/userspace/gpl/apps/ebtables/ebtables-v2.0.10-4/libebt*.so $(BCM_DIR)
	install -m 0755 $(BUILD_DIR)/userspace/gpl/apps/ebtables/ebtables-v2.0.10-4/ethertypes $(BCM_DIR)
ieee1905_sc:
ifeq ($(BUILD_IEEE1905), y)
	$(MAKE) -C $(BUILD_DIR)/userspace/private/libs/fbctl dynamic 
	install -m 755 $(BUILD_DIR)/userspace/private/libs/fbctl/libfbctl.so $(BCM_DIR)
	$(MAKE) -C $(BUILD_DIR)/userspace/private/apps/ieee1905 dynamic 
	install -m 755 $(BUILD_DIR)/userspace/private/apps/ieee1905/ieee1905 $(BCM_DIR)
endif

adsl_sc:
	cp  $(BRCMDRIVERS_DIR)/broadcom/char/adsl/bcm9$(BRCM_CHIP)/adsl_phy.bin $(BCM_DIR)
	$(MAKE) -C $(BUILD_DIR)/userspace/private/libs/atmctl
	cp -af $(BUILD_DIR)/userspace/private/libs/atmctl/libatmctl.so $(BCM_DIR)
	$(MAKE) -C $(BUILD_DIR)/userspace/private/libs/fapctl
	cp -af $(BUILD_DIR)/userspace/private/libs/fapctl/libfapctl.so $(BCM_DIR)
	$(MAKE) -C $(BUILD_DIR)/userspace/private/apps/atmctl
	install -m 755 $(BUILD_DIR)/userspace/private/apps/atmctl/xtmctl $(BCM_DIR)
	$(STRIP) $(BCM_DIR)/xtmctl 
	ln -sf xtmctl $(BCM_DIR)/xtm
	$(MAKE) -C $(BUILD_DIR)/userspace/private/libs/xdslctl
	cp -af $(BUILD_DIR)/userspace/private/libs/xdslctl/libxdslctl.so $(BCM_DIR)
	$(MAKE) -C $(BUILD_DIR)/userspace/private/apps/xdslctl
	install -m 755 $(BUILD_DIR)/userspace/private/apps/xdslctl/xdslctl $(BCM_DIR)
	$(STRIP) $(BCM_DIR)/xdslctl
	ln -sf xdslctl $(BCM_DIR)/adslctl
	ln -sf xdslctl $(BCM_DIR)/adsl
	$(MAKE) -C $(BUILD_DIR)/userspace/private/apps/dsldiagd
	install -m 755 $(BUILD_DIR)/userspace/private/apps/dsldiagd/dsldiagd $(BCM_DIR)
	$(STRIP) $(BCM_DIR)/dsldiagd


vlan_sc:
	$(MAKE) -C $(BUILD_DIR)/userspace/private/libs/vlanctl
	cp -af $(BUILD_DIR)/userspace/private/libs/vlanctl/libvlanctl.so $(BCM_DIR)
	$(MAKE) -C $(BUILD_DIR)/userspace/private/apps/vlanctl
	install -m 755 $(BUILD_DIR)/userspace/private/apps/vlanctl/vlanctl $(BCM_DIR)
	$(STRIP) $(BCM_DIR)/vlanctl

spu_sc:
	$(MAKE) -C $(BUILD_DIR)/userspace/private/libs/spuctl
	cp -af $(BUILD_DIR)/userspace/private/libs/spuctl/libspuctl.so $(BCM_DIR)
	$(MAKE) -C $(BUILD_DIR)/userspace/private/apps/spuctl
	install -m 755 $(BUILD_DIR)/userspace/private/apps/spuctl/spuctl $(BCM_DIR)
	$(STRIP) $(BCM_DIR)/spuctl

ethsw_sc:
	$(MAKE) -C $(BUILD_DIR)/userspace/private/libs/ethswctl
	cp -af $(BUILD_DIR)/userspace/private/libs/ethswctl/libethswctl.so $(BCM_DIR)
	$(MAKE) -C $(BUILD_DIR)/userspace/private/apps/ethswctl
	install -m 755 $(BUILD_DIR)/userspace/private/apps/ethswctl/ethswctl $(BCM_DIR)
	$(STRIP) $(BCM_DIR)/ethswctl
	
ethctl_sc:
	$(MAKE) -C $(BUILD_DIR)/userspace/private/apps/ethctl
	install -m 755 $(BUILD_DIR)/userspace/private/apps/ethctl/ethctl $(BCM_DIR)
	$(STRIP) $(BCM_DIR)/ethctl

smd_sc:
	$(MAKE) -C $(BUILD_DIR)/userspace/private/apps/smd
	install -m 755 $(BUILD_DIR)/userspace/private/apps/smd/smd $(BCM_DIR)
	$(STRIP) $(BCM_DIR)/smd

ifneq ($(strip $(BUILD_VODSL)),)
vodsl_sc:
	$(MAKE) -C $(BUILD_DIR)/userspace/private/apps/vodsl sc
voctl_sc:
	$(MAKE) -C $(SC_ROOT)/apps/voctl clean
	$(MAKE) -C $(SC_ROOT)/apps/voctl
else
vodsl_sc voctl_sc:
	@echo "voice not enabled, skip building $@"
endif

fapctl_sc:
	$(MAKE) -C $(BUILD_DIR)/userspace/private/apps/fapctl
	install -m 755 $(BUILD_DIR)/userspace/private/apps/fapctl/fapctl $(BCM_DIR)
	$(STRIP) $(BCM_DIR)/fapctl

snoopctl_sc:
	$(MAKE) -C $(BUILD_DIR)/userspace/private/libs/snoopctl
	cp -af $(BUILD_DIR)/userspace/private/libs/snoopctl/libsnoopctl.so $(BCM_DIR)

fc_sc:
	$(MAKE) -C $(BUILD_DIR)/userspace/private/libs/fcctl
	cp -af 	$(BUILD_DIR)/userspace/private/libs/fcctl/libfcctl.so $(BCM_DIR)
	$(MAKE) -C $(BUILD_DIR)/userspace/private/apps/fcctl
	install -m 755 $(BUILD_DIR)/userspace/private/apps/fcctl/fcctl $(BCM_DIR)
	$(STRIP) $(BCM_DIR)/fcctl
	ln -sf fcctl $(BCM_DIR)/fc

pwrctl_sc:
	$(MAKE) -C $(BUILD_DIR)/userspace/private/libs/pwrctl
	cp -af $(BUILD_DIR)/userspace/private/libs/pwrctl/libpwrctl.so $(BCM_DIR)
	$(MAKE) -C $(BUILD_DIR)/userspace/private/apps/pwrctl
	install -m 755 $(BUILD_DIR)/userspace/private/apps/pwrctl/pwrctl $(BCM_DIR)
	$(STRIP) $(BCM_DIR)/pwrctl

sc_tmsctl:
	$(MAKE) -C $(BUILD_DIR)/userspace/private/apps/tmsctl
	install -m 755 $(BUILD_DIR)/userspace/private/apps/tmsctl/tmsctl $(BCM_DIR)

sc_iqctl:
	$(MAKE) -C $(BUILD_DIR)/userspace/private/libs/iqctl
	$(MAKE) -C $(BUILD_DIR)/userspace/private/apps/iqctl
	cp -af $(BUILD_DIR)/userspace/private/libs/iqctl/libiqctl.so $(BCM_DIR)
	cp -af $(BUILD_DIR)/userspace/private/apps/iqctl/iqctl $(BCM_DIR)

sc_wlan:
	$(MAKE) -C $(BUILD_DIR)/userspace/private/libs/mdm
	cp -af $(BUILD_DIR)/userspace/private/libs/mdm/libmdm.so $(BCM_DIR)
	$(MAKE) -C data-model
	$(MAKE) -C $(BUILD_DIR)/userspace/private/apps/wlan all
	cp -af $(BUILD_DIR)/userspace/private/apps/wlan/wlevt_9$(BRCM_CHIP)GWV.save $(BCM_DIR)/wlevt

sc_modules_install:
# net
	cp -af $(BRCMDRIVERS_DIR)/broadcom/char/pktflow/bcm9$(BRCM_CHIP)/pktflow.ko $(BCM_DIR)
	cp -af $(BRCMDRIVERS_DIR)/broadcom/char/xtmcfg/bcm9$(BRCM_CHIP)/bcmxtmcfg.ko $(BCM_DIR)
ifeq ($(strip $(BRCM_DRIVER_FAP)),m)
	cp -af $(BRCMDRIVERS_DIR)/broadcom/char/fap/bcm9$(BRCM_CHIP)/bcmfap.ko $(BCM_DIR)
endif
	cp -af $(BRCMDRIVERS_DIR)/broadcom/char/adsl/bcm9$(BRCM_CHIP)/adsldd.ko $(BCM_DIR)
	cp -af $(BRCMDRIVERS_DIR)/broadcom/char/vlan/bcm9$(BRCM_CHIP)/bcmvlan.ko $(BCM_DIR)
	cp -af $(BRCMDRIVERS_DIR)/opensource/net/enet/bcm9$(BRCM_CHIP)/bcm_enet.ko $(BCM_DIR)
	cp -af $(BRCMDRIVERS_DIR)/opensource/net/xtmrt/bcm9$(BRCM_CHIP)/bcmxtmrtdrv.ko $(BCM_DIR)
	cp -af $(BRCMDRIVERS_DIR)/broadcom/net/wl/bcm9$(BRCM_CHIP)/wl.ko $(BCM_DIR)
	cp -af $(BRCMDRIVERS_DIR)/broadcom/net/wl/bcm9$(BRCM_CHIP)/wlcsm.ko $(BCM_DIR)
	cp -af $(BRCMDRIVERS_DIR)/broadcom/net/wl/bcm9$(BRCM_CHIP)/dhd.ko $(BCM_DIR)
	cp -af $(BRCMDRIVERS_DIR)/broadcom/net/wl/bcm9$(BRCM_CHIP)/wlemf.ko $(BCM_DIR)
	cp -af $(BRCMDRIVERS_DIR)/broadcom/char/ingqos/bcm9$(BRCM_CHIP)/bcm_ingqos.ko $(BCM_DIR)
	cp -af $(BRCMDRIVERS_DIR)/broadcom/char/bpm/bcm9$(BRCM_CHIP)/bcm_bpm.ko $(BCM_DIR)
	cp -af $(BRCMDRIVERS_DIR)/broadcom/char/pwrmngt/bcm9$(BRCM_CHIP)/pwrmngtd.ko $(BCM_DIR)
	cp -af $(BRCMDRIVERS_DIR)/broadcom/char/chipinfo/impl1/chipinfo.ko $(BCM_DIR)
	cp -af $(BRCMDRIVERS_DIR)/broadcom/char/p8021ag/impl1/p8021ag.ko $(BCM_DIR)
	cp -af $(BRCMDRIVERS_DIR)/broadcom/char/tms/impl1/nciTMSkmod.ko $(BCM_DIR)
ifeq ($(PRODUCT_TYPE), F1)
	cp -af $(BRCMDRIVERS_DIR)/broadcom/char/arl/bcm9$(BRCM_CHIP)/bcmarl.ko $(BCM_DIR)
	cp -af $(BRCMDRIVERS_DIR)/opensource/net/wfd/bcm9$(BRCM_CHIP)/wfd.ko $(BCM_DIR)
endif

# voice
ifneq ($(strip $(BUILD_VODSL)),)
#	cp -af $(BRCMDRIVERS_DIR)/broadcom/char/dspapp/bcm9$(BRCM_CHIP)/dspdd.ko $(BCM_DIR)
	cp -af $(BRCMDRIVERS_DIR)/broadcom/char/endpoint/bcm9$(BRCM_CHIP)/endpointdd.ko $(BCM_DIR)
	#cp -af $(BRCMDRIVERS_DIR)/broadcom/char/endpoint/bcm9$(BRCM_CHIP)/endptdrv/endptdrv.ko $(BCM_DIR)
	#cp -af $(BRCMDRIVERS_DIR)/broadcom/char/endpoint/bcm9$(BRCM_CHIP)/haushost/haushost.ko $(BCM_DIR)
	#cp -af $(BRCMDRIVERS_DIR)/broadcom/char/endpoint/bcm9$(BRCM_CHIP)/gwcommon/gwcommon.ko $(BCM_DIR)
ifneq ($(strip $(BRCM_VODSL_DECT)),)
#	cp -af $(BRCMDRIVERS_DIR)/broadcom/char/dect/bcm9$(BRCM_CHIP)/dect.ko $(BCM_DIR)
endif
endif
	echo "Stripping kernel modules..."
# Modules that need parameters cannot be stripped
	eval "find $(BCM_DIR) -name '*.ko' ! -name 'ip*.ko' |xargs $(STRIP) --strip-unneeded"
# However do strip debug symbols, in case debug symbols are included
#	eval "find $(BCM_DIR) -name 'ip*.ko' |xargs $(STRIP) --strip-debug"

show:
	@echo Profile=$(PROFILE)  
	@echo WL=$(WL)  

sc_help:
#	@more Readme_allen.txt
	@echo
	@echo "-----------------------------------------------------------"
	@echo "make sc_adsl: display usage to change ATM driver/ adsl phy"


sc_adsl:
	@echo " CMD             ATM driver             ADSL phy"
	@echo " -------------   --------------------   -----------"
	@echo " make sc_adsl_1: 4.02.01 org            4.02.01 org"

	@echo		
	@echo	"Reference:"	
	@echo " DGN3300A    AdslDrv_Linux3_A2x020e  a2pb023b"

.PHONY: sc_adsl_rm_link
	
sc_adsl_rm_link:
	rm -f bcmdrivers/broadcom/char/adsl/impl1
	rm -f bcmdrivers/broadcom/include/bcm963xx
	rm -f userspace/private/apps/xdslctl
    
sc_adsl_1: sc_adsl_rm_link
	@echo " ... link to 4.02L.01 original code ... "
#	ln -sf impl1_org bcmdrivers/broadcom/char/adsl/impl1
	ln -sf impl1_20k_rc2 bcmdrivers/broadcom/char/adsl/impl1
	ln -sf bcm963xx_org bcmdrivers/broadcom/include/bcm963xx
	ln -sf xdslctl_org userspace/private/apps/xdslctl
    
_chmod:
	@chmod 774 $(TARGETS_DIR)/buildFS

cfg_nd33: _chmod sc_adsl_1
	rm -f targets/96358GW/96358GW
	cp targets/96358GW/96358GWA  targets/96358GW/96358GW
	cp kernel/linux/.config_ND kernel/linux/.config
	rm -f shared/opensource/include/bcm963xx/bcm_hwdefs.h
	ln -sf bcm_hwdefs_8m.h shared/opensource/include/bcm963xx/bcm_hwdefs.h

cfg_nd33b: _chmod sc_adsl_1
	rm -f targets/96358GW/96358GW
	cp targets/96358GW/96358GWB  targets/96358GW/96358GW
	cp kernel/linux/.config_ND kernel/linux/.config
	rm -f shared/opensource/include/bcm963xx/bcm_hwdefs.h
	ln -sf bcm_hwdefs_8m.h shared/opensource/include/bcm963xx/bcm_hwdefs.h

cfg_nd33sp: _chmod sc_adsl_1
	rm -f targets/96358GW/96358GW
	cp targets/96358GW/96358GWA  targets/96358GW/96358GW
	cp kernel/linux/.config_ND16 kernel/linux/.config
	rm -f shared/opensource/include/bcm963xx/bcm_hwdefs.h
	ln -sf bcm_hwdefs_16m.h shared/opensource/include/bcm963xx/bcm_hwdefs.h

cfg_nd33NAsp: _chmod sc_adsl_1
	rm -f targets/96358GW/96358GW
	cp targets/96358GW/96358GWA  targets/96358GW/96358GW
	cp kernel/linux/.config_ND16 kernel/linux/.config
	rm -f shared/opensource/include/bcm963xx/bcm_hwdefs.h
	ln -sf bcm_hwdefs_16m.h shared/opensource/include/bcm963xx/bcm_hwdefs.h

cfg_nd33bsp: _chmod sc_adsl_1
	rm -f targets/96358GW/96358GW
	cp targets/96358GW/96358GWB  targets/96358GW/96358GW
	cp kernel/linux/.config_ND16 kernel/linux/.config
	rm -f shared/opensource/include/bcm963xx/bcm_hwdefs.h
	ln -sf bcm_hwdefs_16m.h shared/opensource/include/bcm963xx/bcm_hwdefs.h

clean_bcm_links:
	@echo -e "\\e[36m -- clean_bcm_links --\e[0m"	
	rm -f bcmdrivers/opensource/char/serial/bcm9$(BRCM_CHIP)
	rm -f bcmdrivers/opensource/char/board/bcm963xx/bcm9$(BRCM_CHIP)
	rm -f bcmdrivers/broadcom/atm/bcm9$(BRCM_CHIP)
	rm -f bcmdrivers/broadcom/net/wl/bcm9$(BRCM_CHIP)
	rm -f bcmdrivers/broadcom/net/enet/bcm9$(BRCM_CHIP)
	rm -f bcmdrivers/broadcom/char/adsl/bcm9$(BRCM_CHIP)
	rm -f bcmdrivers/broadcom/char/atmapi/bcm9$(BRCM_CHIP)
	rm -f bcmdrivers/broadcom/char/bcmprocfs/bcm9$(BRCM_CHIP)
	
