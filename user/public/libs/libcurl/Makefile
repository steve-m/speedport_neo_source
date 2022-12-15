
#CC	= gcc
#AR	= ar
ARFLAGS	= cr
OPENSSL_DIR = $(PUBLIC_APPSPATH)/libs/openssl-$(OPENSSL_VER)
CFLAGS += -I./ -I./inc/ -I$(OPENSSL_DIR)/include -I$(PRIVATE_APPSPATH)/include
CFLAGS += -Wall -O2 -DHTTP_ONLY -DHAVE_CONFIG_H -DOPENSSL_NO_KRB5 -DCURL_DISABLE_VERBOSE_STRINGS -fPIC
#CFLAGS += -DREDIRECT_IFACE
#LDFLAGS	= -shared

# Spec request that the DNS queries for TR069's domain must be 
# forwarded to dns server of MGT WAN.
#CFLAGS += -DSCM_SYNC_DNRD
CFLAGS += -DNO_SHARE_LIB
CFLAGS += -D__SC_BUILD__

OBJS = base64.o cookie.o formdata.o hostip.o memdebug.o progress.o \
	select.o sendf.o share.o ssluse.o strequal.o strerror.o transfer.o \
	timeval.o strtok.o hash.o llist.o inet_ntop.o inet_pton.o \
	connect.o url.o strtoofft.o netrc.o content_encoding.o \
	speedcheck.o getinfo.o if2ip.o escape.o md5.o hostares.o hostsyn.o \
	hostip4.o hostip6.o mprintf.o getenv.o hostthre.o parsedate.o

OBJS += easy.o multi.o
OBJS += http.o http_chunks.o http_digest.o http_negotiate.o http_ntlm.o

OBJS += ftp.o
#OBJS += dict.o telnet.o

#LIBS   += -L$(OPENSSL_DIR) -lssl -lcrypto

#TARGET = libcurl.a

#$(TARGET):$(OBJS) $(LIBS)
#	$(AR) $(ARFLAGS) $@ $(OBJS)

TARGET = libcurl.so
$(TARGET):$(OBJS) 
#	$(CC) -o $@ $(LDFLAGS) $^
	$(CC) -Os -s -shared -fPIC $(LDFLAGS) -o $@ -Wl,-soname,$@ $(OBJS)

clean: 
	-rm -f $(OBJS) $(TARGET)

install:
	mkdir -p $(INSTALLDIR)/usr/local/
	cp -f ca-bundle.crt $(INSTALLDIR)/usr/local/
	cp -f $(TARGET) $(INSTALLDIR)/lib

%.o.%.c:
	$(CC) $(CFLAGS) -c $^
#---------------------------------------
