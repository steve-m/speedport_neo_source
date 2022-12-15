VERSION=1.0.2

freplace = $(shell if [ ! -d `dirname $(2)` ]; then mkdir -p `dirname $(2)`; fi; cp $(1) $(2))
BUILDIR:=$(shell pwd)/build
BASE_CONFIGS= --program-prefix="" --program-suffix="" --prefix=/tmp \
         --sysconfdir=/etc --exec-prefix=/usr --bindir=/usr/bin \
         --datadir=/usr/share --includedir=/usr/include \
         --infodir=/usr/share/info --libdir=/usr/lib \
         --libexecdir=/usr/lib --localstatedir=/var \
         --mandir=/usr/share/man --sbindir=/usr/sbin \
         --enable-shared --disable-static \
         --with-gnu-ld --host=mips-linux --target=mips-linux \
	 CC=${CROSS_COMPILE}gcc \
	 AR=${CROSS_COMPILE}ar \
	 AS=${CROSS_COMPILE}as \
	 LD=${CROSS_COMPILE}ld \
	 STRIP=${CROSS_COMPILE}strip \
	 RANLIB=${CROSS_COMPILE}ranlib

FONAPI_CONFIGS=$(BASE_CONFIGS) 
CHILLOUT_CONFIGS=$(BASE_CONFIGS) \
	CPPFLAGS=-I$(PUBLIC_APPSPATH)/libs/libdaemon/build/tmp/include \
	LDFLAGS=-L$(PUBLIC_APPSPATH)/libs/libdaemon/build/usr/lib/ 
FONSMCD_CONFIGS=$(BASE_CONFIGS)
XL2TPD_CONFIGS=$(BASE_CONFIGS) \
	CFLAGS=-DUSE_KERNEL CPPFLAGS=-DSUPPORT_FON	
COOVA_MOD_CONFIGS=$(BASE_CONFIGS) 
COOVA_CONFIGS=$(BASE_CONFIGS) \
         --enable-binstatusfile --enable-ipwhitelist \
         --enable-uamdomainfile --enable-redirdnsreq \
	 --enable-modules --disable-accounting-onoff \
	 --disable-dhcpradius --disable-debug
# Optional: --enable-multiroute


all:
	make chilli
	make fonsmcd
	make chilloutd
	make chillout.so
	make xl2tpd
	make pppd
	make fon-api.so
	make fonap

chilli:
	-mkdir -p $(BUILDIR)
	cd src/coova/ && [ -e ./configure ] || sh bootstrap
	cd src/coova/ && [ -e ./Makefile ] || ./configure $(COOVA_CONFIGS)
	make -C src/coova/ -f Makefile
	make -C src/coova/ DESTDIR=$(BUILDIR) install
	$(STRIP) $(BUILDIR)/usr/sbin/chilli*
	$(STRIP) $(BUILDIR)/usr/lib/lib*.so*
	cp -f $(BUILDIR)/usr/sbin/chilli $(INSTALL_ROOT)/usr/sbin/
	cp -f $(BUILDIR)/usr/sbin/chilli_radconfig $(INSTALL_ROOT)/usr/sbin/
	cp -f $(BUILDIR)/usr/sbin/chilli_query $(INSTALL_ROOT)/usr/sbin/
	cp -f $(BUILDIR)/usr/sbin/chilli_opt $(INSTALL_ROOT)/usr/sbin/
	cp -af $(BUILDIR)/usr/lib/lib*.so* $(INSTALL_ROOT)/lib/
#	$(call freplace,files/coova/chilli.conf.in, $(INSTALL_ROOT)/etc/chilli.conf)
#	$(call freplace,files/coova/chilli.cron.in, $(INSTALL_ROOT)/etc/cron.daily/chilli)
#	$(call freplace,files/coova/chilli.init.in, $(INSTALL_ROOT)/etc/init.d/chilli)
#	$(call freplace,files/coova/chilli.default.in, $(INSTALL_ROOT)/etc/default/chilli)

fonsmcd: 
	-mkdir -p $(BUILDIR)
	#cd src/fonsmcd/ && [ -e ./configure ] || sh bootstrap
	#cd src/fonsmcd/ && ./configure $(FONSMCD_CONFIGS)
	make -C src/fonsmcd/ -f Makefile
	make -C src/fonsmcd/ DESTDIR=$(BUILDIR) install
	$(STRIP) $(BUILDIR)/usr/sbin/fonsmcd
	cp -f $(BUILDIR)/usr/sbin/fonsmcd $(INSTALL_ROOT)/usr/sbin/
#	cp -f files/fonsmcd/fon_mac $(INSTALL_ROOT)/etc/fon_mac  
#	cp -f files/fonsmcd/fon_keyword $(INSTALL_ROOT)/etc/fon_keyword
	cp -f files/fonsmcd/fon_device $(INSTALL_ROOT)/etc/fon_device
	cp -f files/fonsmcd/fon_version $(INSTALL_ROOT)/etc/fon_version
	cp -f files/fonsmcd/fon_revision $(INSTALL_ROOT)/etc/fon_revision
	cp -f files/fonsmcd/public_sm_rsa_key.pem $(INSTALL_ROOT)/etc/public_sm_rsa_key.pem
#	cp -f files/fonsmcd/fonsmcd.conf $(INSTALL_ROOT)/etc/fonsmcd.conf
#	cp -f files/fonsmcd/fonsmcd.init $(INSTALL_ROOT)/etc/init.d/fonsmcd
	cp -f files/fonsmcd/fonsmcd_online $(INSTALL_ROOT)/usr/sbin/
	cp -f files/fonsmcd/fonsmcd_offline $(INSTALL_ROOT)/usr/sbin/

fon-api.so:
	-mkdir -p $(BUILDIR)
	cd src/fon-api/ && [ -e ./configure ] || sh bootstrap
	cd src/fon-api/ && [ -f ./Makefile ] || ./configure $(FONAPI_CONFIGS)
	make -C src/fon-api/ -f Makefile
	make -C src/fon-api/ DESTDIR=$(BUILDIR) install
	-mkdir $(INSTALL_ROOT)/usr/lib/coova-chilli
	$(STRIP) $(BUILDIR)/usr/lib/coova-chilli/fon-api.so
	cp -a $(BUILDIR)/usr/lib/coova-chilli/fon-api.so $(INSTALL_ROOT)/usr/lib/coova-chilli/
	$(STRIP) $(BUILDIR)/usr/sbin/fonctl
	cp -a $(BUILDIR)/usr/sbin/fonctl $(INSTALL_ROOT)/usr/sbin/
	cp -a src/fon-api/api-example.sh $(INSTALL_ROOT)/usr/sbin/
	chmod +x $(INSTALL_ROOT)/usr/sbin/api-example.sh

chillout.so:
	-mkdir -p $(BUILDIR)
	cd src/chillout-mod/ && [ -e ./configure ] || sh bootstrap
	cd src/chillout-mod/ && [ -e ./Makefile ] || ./configure $(COOVA_MOD_CONFIGS)
	make -C src/chillout-mod/ -f Makefile
	make -C src/chillout-mod/ DESTDIR=$(BUILDIR) install
	$(STRIP) $(BUILDIR)/usr/lib/coova-chilli/chillout.so
	-mkdir $(INSTALL_ROOT)/usr/lib/coova-chilli
	cp -a $(BUILDIR)/usr/lib/coova-chilli/chillout.so $(INSTALL_ROOT)/usr/lib/coova-chilli/
	#strip -K chillout_module deb/usr/lib/coova-chilli/chillout.so

chilloutd: 
	-mkdir -p $(BUILDIR)
	cd src/chillout/ && [ -e ./configure ] || sh bootstrap
	cd src/chillout/ && [ -e ./Makefile ] || ./configure $(CHILLOUT_CONFIGS)
	make -C src/chillout/ -f Makefile
	make -C src/chillout/ DESTDIR=$(BUILDIR) install
	$(STRIP) $(BUILDIR)/usr/sbin/chillout*
	$(STRIP) $(BUILDIR)/usr/lib/libchillout*.so*
	cp -f $(BUILDIR)/usr/sbin/chillout* $(INSTALL_ROOT)/usr/sbin/
	cp -af $(BUILDIR)/usr/lib/libchillout*.so* $(INSTALL_ROOT)/usr/lib/
	cp -f src/chillout/rule.sh $(INSTALL_ROOT)/usr/sbin/rule.sh

xl2tpd: 
	-mkdir -p $(BUILDIR)
	cd src/xl2tpd/ && [ -e ./configure ] || sh bootstrap
	cd src/xl2tpd/ && [ -e ./Makefile ] || ./configure $(XL2TPD_CONFIGS)
	make -C src/xl2tpd/ -f Makefile
	make -C src/xl2tpd/ DESTDIR=$(BUILDIR) install
	$(STRIP) $(BUILDIR)/usr/sbin/xl2tpd
	cp -f $(BUILDIR)/usr/sbin/xl2tpd $(INSTALL_ROOT)/usr/sbin/
	cp -f files/etc/xl2tpd.conf $(INSTALL_ROOT)/etc/xl2tpd.conf
	-mkdir -p $(INSTALL_ROOT)/etc/ppp
	cp -f files/etc/ppp/*.* $(INSTALL_ROOT)/etc/ppp/

pppd:
	-mkdir $(BUILDIR)
	cd src/ppp && [ -e ./Makefile ] || ./configure --prefix=/usr
	make -C src/ppp
	$(STRIP) src/ppp/pppd/pppd
	cp src/ppp/pppd/pppd $(INSTALL_ROOT)/usr/sbin/fon_pppd
	$(STRIP) src/ppp/pppd/plugins/passwordfd.so
	cp src/ppp/pppd/plugins/passwordfd.so $(INSTALL_ROOT)/lib/fon_passwordfd.so
	
fonap:
	-mkdir -p $(INSTALL_ROOT)/etc/fon/www
	cp -f files/www/wait.html $(INSTALL_ROOT)/etc/fon/www/wait.html
	cp -f files/www/wait.gif $(INSTALL_ROOT)/etc/fon/www/wait.gif
	cp -f files/www/fon.png $(INSTALL_ROOT)/etc/fon/www/fon.png
#	-mkdir -p $(INSTALL_ROOT)/etc/default
#	cp -f files/fonap/fonap.default $(INSTALL_ROOT)/etc/default/fonap
#	-mkdir -p $(INSTALL_ROOT)/etc/init.d
#	cp -f files/fonap/fonap.init $(INSTALL_ROOT)/etc/init.d/fonap
#	cp -f files/fonap/firewall.fonap $(INSTALL_ROOT)/etc/firewall.fonap
	-mkdir -p $(INSTALL_ROOT)/etc/fon
	cp -f files/fonap/fon_* $(INSTALL_ROOT)/etc/fon/
	cp -f files/fonap/*.sh $(INSTALL_ROOT)/etc/fon/
	cp -f files/fonsmcd/fonsmcd.init $(INSTALL_ROOT)/etc/fon/fon_smcd

install:

clean:
	-make -C src/chillout distclean
	-make -C src/fonsmcd distclean
	-make -C src/coova distclean
	-rm -f src/coova/Makefile
	-make -C src/xl2tpd distclean
	-make -C src/ppp clean
	-make -C src/chillout-mod distclean
	-rm -fR build/

