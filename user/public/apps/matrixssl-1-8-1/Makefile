#
#	Makefile for MatrixSSL library
#	Builds optimized shared library by default.
#	See comments below for building a debug library.
#	Copyright (c) PeerSec Networks, 2002-2006. All Rights Reserved.
#

RANLIB  = ranlib
O       = .o
SO      = .so
A       = .a
E       =

LIBRARY	= libmatrixssl$(SO)
STATIC	= libmatrixsslstatic$(A)

OBJECTS	= \
		cipherSuite$(O) \
		matrixSsl$(O) \
		sslDecode$(O) \
		sslEncode$(O) \
		sslv3$(O) \
		sslSocket$(O)\
		os/debug$(O) \
		os/linux/linux$(O)	\
		crypto/peersec/arc4$(O) \
		crypto/peersec/base64$(O) \
		crypto/peersec/des3$(O) \
		crypto/peersec/md5$(O) \
		crypto/peersec/md2$(O) \
		crypto/peersec/mpi$(O) \
		crypto/peersec/rsa$(O) \
		crypto/peersec/sha1$(O) \
		pki/asn1$(O) \
		pki/rsaPki$(O) \
		pki/x509$(O)

#
#	Debug flags (Define MATRIXSSL_DEBUG in shell to build debug)
#	bash:	export MATRIXSSL_DEBUG=1
#			unset MATRIXSSL_DEBUG
#	tcsh:	setenv MATRIXSSL_DEBUG 1
#			unsetenv MATRIXSSL_DEBUG
#
#MATRIXSSL_DEBUG = 1
ifdef MATRIXSSL_DEBUG
DFLAGS	= -g -Wall -Winline -Wdisabled-optimization -DDEBUG -fPIC
STRIP	= test 
else
DFLAGS	= -Os -fPIC
#DFLAGS	= -O3
endif

ifdef MATRIXSSL_PROFILE
DFLAGS	+= -g -pg
STRIP	= test
endif

#
#	Override variables for compilation on x86-64 (AMD64, Nacona, etc)
#
ifeq ($(shell uname -m),x86_64)
DFLAGS  += -march=k8 -fPIC -DFP_64BIT -DTFM_X86_64 -DRDTSC
endif

#
#	Compile options
#
SHARED	= -shared 
CFLAGS  = $(DFLAGS) -DLINUX -I./
LDFLAGS += -lc -lpthread

#
#	Override variables for compilation on Mac OS X (Darwin)
#
ifeq ($(shell uname),Darwin)
CC	= cc
SO	= .dylib
SHARED	= -dynamiclib
CFLAGS += -DOSX -isystem -I/usr/include
LDFLAGS += -flat_namespace -install_name @executable_path/../src/$(LIBRARY)
STRIP = test
endif

#
#	Override variables for compilation on uClinux (example only)
#
ifdef UCLINUX
CC		= /opt/brcm/hndtools-mipsel-uclibc/bin/mipsel-uclibc-gcc
STRIP	= /opt/brcm/hndtools-mipsel-uclibc/bin/mipsel-uclibc-strip
endif

all: compile

compile: $(OBJECTS) $(LIBRARY) $(STATIC)

#
# Manual dependencies
#
*.o: matrixSsl.h matrixCommon.h matrixInternal.h matrixConfig.h Makefile
os/*.o: matrixInternal.h matrixConfig.h Makefile os/osLayer.h os/psMalloc.h
os/linux/*.o: matrixInternal.h matrixConfig.h Makefile os/osLayer.h
crypto/peersec/*.o: matrixInternal.h matrixConfig.h Makefile \
					crypto/peersec/mpi.h \
					crypto/cryptoLayer.h crypto/peersec/pscrypto.h
pki/*.o: matrixInternal.h matrixConfig.h Makefile \
			pki/matrixPki.h pki/pkiInternal.h
#
# Build the library
#
$(LIBRARY): $(OBJECTS)
	$(CC) $(SHARED) -o $@ $^ $(LDFLAGS)
	$(STRIP) $(LIBRARY)

#
# Build the static library
#
$(STATIC): $(OBJECTS)
	$(AR) -rcuv $@ $^
	$(RANLIB) $@



install:
	cp -rf libmatrixssl.so $(INSTALLDIR)/lib
	cp -rf privkeySrv.pem $(INSTALLDIR)/usr/sbin
	cp -rf certSrv.pem $(INSTALLDIR)/usr/sbin

#
#	Clean up all generated files
#
clean:
	rm -f $(LIBRARY) $(OBJECTS) $(STATIC)
