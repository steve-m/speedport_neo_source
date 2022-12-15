#TARGET_PREFIX=marc
all:
	#$(MAKE)	CLIENT=0 TARGET=$(TARGET_PREFIX) -C upnp 
	$(MAKE)	CLIENT=0 -C upnp 
install:
	cp -f upnp/bin/$(TARGET_PREFIX)/* $(INSTALLDIR)/lib
clean:
	$(MAKE) TARGET=$(TARGET_PREFIX) -C upnp clean
