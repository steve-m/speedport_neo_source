
SUBDIRS =

SUBDIRS += busybox
SUBDIRS += bridge-utils
SUBDIRS += udhcpd
SUBDIRS += ppp-2.4.5
SUBDIRS += iptables
SUBDIRS += iproute2
SUBDIRS += matrixssl-1-8-1
SUBDIRS += mini_httpd-1.17beta1
SUBDIRS += dnsmasq-2.60
ifeq ($(SC_DDNS), 1)
SUBDIRS += ddns
endif
ifeq ($(SC_FON), 1)
SUBDIRS += fonap-2b87e99
endif
#SUBDIRS	+= fetchmail-6.3.24
SUBDIRS	+= fetchmail
SUBDIRS += wget-1.10.2
ifeq ($(SC_WIFI), 1)
ifeq ($(SC_WIFI_CHIP), realtek)
    SUBDIRS += wireless_tools_rtl
endif
endif
ifeq ($(SC_IPV6),1)
SUBDIRS += radvd-1.8.5
SUBDIRS += nadvd
SUBDIRS += rsdvd
SUBDIRS += dhcpv6
endif
ifeq ($(SC_TR064),1)
SUBDIRS += stunnel-4.53
endif
SUBDIRS += bind-9.9.1-P2

all:
	make applications

applications::

	@for i in ${SUBDIRS} ;  do                                                    \
            echo "-----------------------------------------------------------------"; \
            echo -e "\033[;34m                         $$i                 \033[;0m"; \
            echo "-----------------------------------------------------------------"; \
            make -C $$i || exit 1 ;                     \
            make -C $$i install || exit 1 ;                                      \
	done

install:

clean:
	@for i in $(SUBDIRS) ; do $(MAKE) -C $$i clean || exit 1; done

