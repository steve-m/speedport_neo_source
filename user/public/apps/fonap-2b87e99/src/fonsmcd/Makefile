CFLAGS = -Wall -fno-builtin -fno-strict-aliasing -O2 -fomit-frame-pointer -funroll-loops -pipe -DFONAP -Idjbdns/ -I./
CFLAGS += -I$(PUBLIC_APPSPATH)/libs/libdaemon/build/tmp/include -L$(PUBLIC_APPSPATH)/libs/libdaemon/build/usr/lib/ 
CFLAGS += -I$(PRIVATE_APPSPATH)/include -L$(INSTALLDIR)/lib 

djbdns= \
dns_dfd.c dns_domain.c dns_dtda.c dns_ip.c dns_ipq.c dns_mx.c \
dns_name.c dns_nd.c dns_packet.c dns_random.c dns_rcip.c dns_rcrw.c \
dns_resolve.c dns_sortip.c dns_transmit.c dns_txt.c \
alloc.c alloc_re.c stralloc_catb.c stralloc_cats.c stralloc_copy.c \
stralloc_eady.c stralloc_opyb.c stralloc_opys.c stralloc_pend.c \
byte_chr.c byte_copy.c byte_diff.c byte_zero.c case_diffb.c \
fmt_ulong.c ip4_scan.c scan_ulong.c str_chr.c str_len.c str_start.c \
uint16_pack.c uint16_unpack.c uint32_unpack.c \
error.c ndelay_on.c open_read.c openreadclose.c readclose.c \
socket_bind.c socket_conn.c socket_tcp.c socket_udp.c \
tai_pack.c taia_add.c taia_approx.c taia_frac.c taia_less.c \
taia_now.c taia_pack.c taia_sub.c taia_uint.c \
env.c iopause.c \
socket_bind6.c socket_connect6.c socket_tcp6.c socket_udp6.c \
ip6_scan.c ip6_fmt.c dns_nd6.c dns_ip6.c dns_sortip6.c scan_xlong.c fmt_xlong.c ip4_fmt.c

djbnds_SRC=$(patsubst %.c, djbdns/%.c, $(djbdns))

SOURCES= $(djbnds_SRC) \
aes.c base16.c base32.c base64.c base85.c bigint.c fonrsa.c \
fonsmcd.c hash.c log.c poption.c protocol.c rmd160.c urandom.c

DEPS= djbnds/iopause.h djbnds/select.h djbnds/uint32.h djbnds/uint64.h \
base16.h base32.h base64.h base85.h bigint.h \
bigint_impl.h fonrsa.h hash.h log.h poption.h protocol.h rmd160.h urandom.h \
aes.h 

LDADD = -ldaemon 
#-ldjbdns

all: fonsmcd

djbnds/iopause.h: djbdns/iopause.h1 djbdns/iopause.h2
	( ( $(CC) -o trypoll djbdns/trypoll.c && ./trypoll ) >/dev/null 2>&1 \
	&& cat djbdns/iopause.h2 || cat djbdns/iopause.h1 ) >djbdns/iopause.h
	-rm -f trypoll

djbnds/select.h:
	( $(CC) -o trysysel.o -c djbdns/tryssysel.c >/dev/null 2>&1 \
	&& cat djbdns/select.h1 || cat djbdns/select.h2 ) >djbdns/select.h
	-rm -f trysysel.o

djbnds/uint32.h:
	( ( $(CC) -o tryulong32 djbdns/tryulong32.c && ./tryulong32 ) >/dev/null 2>&1 \
	&& cat djbdns/uint32.h2 || cat djbdns/uint32.h1 ) >djbdns/uint32.h
	-rm -f tryulong32

djbnds/uint64.h:
	( ( $(CC) -o tryulong64 djbdns/tryulong64.c && ./tryulong64 ) >/dev/null 2>&1 \
	&& cat djbdns/uint64.h2 || cat djbdns/uint64.h1 ) > djbdns/uint64.h
	-rm -f tryulong64


fonsmcd: $(DEPS) $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o fonsmcd $(LDADD)

install: fonsmcd
	mkdir -p $(DESTDIR)/usr/sbin
	cp fonsmcd $(DESTDIR)/usr/sbin/fonsmcd

clean:
	rm -f *.o fonsmcd

.PHONY: install

# libdjbdns.a: $(LIBDNS) $(LIBALLOC) $(LIBBYTE) $(LIBUNIX) $(LIBENV) 
# $(LIBTAI) $(LIBMISC) $(SYSDEPS)
