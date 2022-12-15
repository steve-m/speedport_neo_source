SUBDIRS = 

SUBDIRS += zlib-1.2.3
SUBDIRS += libdaemon
SUBDIRS += udns-0.2
SUBDIRS += libjson-c-v0.10
SUBDIRS += libixml
ifeq ($(SC_TR064),1)
SUBDIRS += libupnp-lsdcc
endif
SUBDIRS +=
SUBDIRS += libcurl
SUBDIRS += openssl-$(OPENSSL_VER)
ifeq ($(DT_SMART_SETUP), 1)
    SUBDIRS += libjsonrpc
endif

all:
	make applications

applications::

	@for i in ${SUBDIRS} ;  do                                                    \
            echo "-----------------------------------------------------------------"; \
            echo -e "\033[;34m                         $$i                 \033[;0m"; \
            echo "-----------------------------------------------------------------"; \
            if test "$$i" = "tcp_wrappers_7.6"; then       \
                make -C $$i linux || exit 1;                \
            else                                            \
            make -C $$i || exit 1 ;                     \
            make -C $$i install || exit 1 ;                                      \
            fi;                                           \
	done

install:

clean:
	@for i in $(SUBDIRS) ; do $(MAKE) -C $$i clean || exit 1; done

