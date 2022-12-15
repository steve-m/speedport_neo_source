PROGRAMS = stunnel

SSLDIR = $(PUBLIC_APPSPATH)/libs/openssl-$(OPENSSL_VER)
#SSLDIR = /home/marc/VD168/user/public/apps/openssl-0.9.8l
CFLAGS += -O2 -Wall -Wextra -Wno-long-long -pedantic
CFLAGS += -DHAVE_CONFIG_H
CFLAGS += -D_SC_BUILD_
CFLAGS += -I. -I$(SSLDIR)/include -I$(PRIVATE_APPSPATH)/include -I$(SHARED_APPSPATH)/include
CFLAGS += -pthread

LDFLAGS += -L$(SSLDIR)/ -L$(INSTALLDIR)/lib
LDFLAGS += -lssl -lcrypto -ldl -lutil -lscnvram

common_headers = common.h prototypes.h version.h

OBJS = env.o
OBJS += str.o
OBJS += file.o
OBJS += client.o
OBJS += log.o
OBJS += options.o
OBJS += protocol.o
OBJS += network.o
OBJS += resolver.o
OBJS += ssl.o
OBJS += ctx.o
OBJS += verify.o
OBJS += sthreads.o
OBJS += fd.o
OBJS += stunnel.o
OBJS += pty.o
OBJS += libwrap.o


all: $(PROGRAMS)

$(PROGRAMS) : $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS)

%.o: %.c $(common_headers)
	$(CC) $(CFLAGS) -o $@ -c $<

install :
	$(STRIP) $(PROGRAMS)
	cp -f $(PROGRAMS) $(INSTALLDIR)/usr/sbin
#	cp -f stunnel.pem $(INSTALLDIR)/usr/sbin
	
clean:
	rm -rf $(PROGRAMS) $(OBJS)
