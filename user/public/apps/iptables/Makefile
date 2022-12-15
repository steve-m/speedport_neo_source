APP = iptables-1.4.16.3
CFLAGS += -s -Os -Wno-strict-aliasing -D_SC_BUILD_

all: prepare configure build install

PFX_EXT := TCPMSS SKIPLOG string length limit standard conntrack tcp udp NFQUEUE dscp DSCP mac mark MARK connmark CONNMARK owner policy layer7 DC multiport helper sc_mark SC_MARK PORTTRIG recent
PF4_EXT := icmp LOG DNAT MASQUERADE REDIRECT SNAT YNAHELPER REJECT
PF6_EXT := ah dst eui64 frag hbh hl icmp6 ipv6header mh rt HL LOG REJECT

prepare:
	@if [ ! -e $(APP)/INSTALL ]; then \
	    echo "Untarring original $(APP) source"; \
	    (tar xkjf $(APP).tar.bz2 2> /dev/null || true); \
	    echo "Applying patches to $(APP)"; \
	    patch -p1 -b -s -d$(APP) < $(APP).patch; \
	    if [ $$? -ne 0 ]; then \
	         exit 1; \
	    fi; \
	fi


configure:
	echo "Checking configure on $(APP)/configure"; \
	    if [ -e $(APP)/configure ]; then \
	        echo "Running configure on $(APP)"; \
	        echo "building to $(INSTALL_ROOT)"; \
	        cd $(APP); \
	        export PKG_CONFIG_LIBDIR=$(INSTALL_ROOT)/lib/; \
	        ./configure --host=mips-linux-uclibc \
	        --target=mips-linux-uclibc \
			--disable-devel \
			--disable-shared \
			--enable-ipv6 \
			--with-ksource=$(KERNEL_DIR) \
			--with-kernel=$(KERNEL_DIR) \
			--with-pfxmods="$(PFX_EXT)" \
			--with-pf4mods="$(PF4_EXT)" \
			--with-pf6mods="$(PF6_EXT)" \
	        LDFLAGS=-L$(INSTALL_ROOT)/lib/; \
	    fi

build:
	cd $(APP); $(MAKE) -j1

install:
	install -m 755 $(APP)/iptables/xtables-multi $(INSTALL_ROOT)/bin
	ln -sf xtables-multi $(INSTALL_ROOT)/bin/iptables
	ln -sf xtables-multi $(INSTALL_ROOT)/bin/ip6tables

# NOTE: make clean from within app does not do a proper job, so wiping out
# entire directory to ensure consistency.
clean:
	-$(MAKE) -C $(APP) clean
	rm -f $(INSTALL_ROOT)/bin/iptables
	rm -f $(INSTALL_ROOT)/bin/ip6tables
	rm -f $(INSTALL_ROOT)/bin/xtables-multi

# The next line is a hint to our release scripts
# GLOBAL_RELEASE_SCRIPT_CALL_DISTCLEAN
distclean: clean
