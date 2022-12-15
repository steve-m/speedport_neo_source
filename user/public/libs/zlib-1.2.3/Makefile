# Makefile for zlib
# Copyright (C) 1995-2005 Jean-loup Gailly.
# For conditions of distribution and use, see copyright notice in zlib.h

# To compile and test, type:
#    ./configure; make test
# The call of configure is optional if you don't have special requirements
# If you wish to build zlib as a shared library, use: ./configure -s

# To use the asm code, type:
#    cp contrib/asm?86/match.S ./match.S
#    make LOC=-DASMV OBJA=match.o

# To install /usr/local/lib/libz.* and /usr/local/include/zlib.h, type:
#    make install
# To install in $HOME instead of /usr/local, use:
#    make install prefix=$HOME

#CC=gcc
#CC = mipsel-uclibc-gcc
#STRIP = mipsel-uclibc-strip
#CROSS = ../../tools/mipsel-linux-uclibc/bin/mipsel-uclibc-
#CC = $(CROSS)gcc
#STRIP = $(CROSS)strip


# For GV26
#
#include ../../Rules.mak
#CROSS=$(_CROSS)
#CC             = $(CROSS)gcc
#AR             = $(CROSS)ar
#AS             = $(CROSS)as
#LD             = $(CROSS)ld
#NM             = $(CROSS)nm
#STRIP          = $(CROSS)strip

CFLAGS  = -Os -s -Wall -fPIC
#CFLAGS=-fPIC -O3 -DUSE_MMAP
#CFLAGS=-O -DMAX_WBITS=14 -DMAX_MEM_LEVEL=7
#CFLAGS=-g -DDEBUG
#CFLAGS=-O3 -Wall -Wwrite-strings -Wpointer-arith -Wconversion \
#           -Wstrict-prototypes -Wmissing-prototypes

LDFLAGS=-L. libz.so
LDSHARED=$(CC) -shared -Wl,-soname,libz.so
CPP=$(CC) -E

#DESTLIB = ../../target/lib
DESTLIB = $(INSTALLDIR)/lib

LIBS=libz.so
SHAREDLIB=libz.so

AR=ar rc
RANLIB=ranlib
TAR=tar
SHELL=/bin/sh
EXE=

prefix =/usr/local
exec_prefix =${prefix}
libdir =${exec_prefix}/lib
includedir =${prefix}/include
mandir =${prefix}/share/man
man3dir = ${mandir}/man3

OBJS = adler32.o compress.o crc32.o gzio.o uncompr.o deflate.o trees.o \
       zutil.o inflate.o infback.o inftrees.o inffast.o
#OBJS = adler32.o crc32.o compress.o uncompr.o deflate.o trees.o \
#       inflate.o zutil.o inffast.o inftrees.o

OBJA =
# to use the asm code: make OBJA=match.o

# move objs to examples
OBJB = gzio.o infback.o

TEST_OBJS = example.o minigzip.o

all: example$(EXE) minigzip$(EXE) 

check: test
test: all
	@LD_LIBRARY_PATH=.:$(LD_LIBRARY_PATH) ; export LD_LIBRARY_PATH; \
	echo hello world | ./minigzip | ./minigzip -d || \
	  echo '		*** minigzip test FAILED ***' ; \
	if ./example; then \
	  echo '		*** zlib test OK ***'; \
	else \
	  echo '		*** zlib test FAILED ***'; \
	fi

libz.a: $(OBJS) $(OBJA)
	$(AR) $@ $(OBJS) $(OBJA)
	-@ ($(RANLIB) $@ || true) >/dev/null 2>&1

match.o: match.S
	$(CPP) match.S > _match.s
	$(CC) -c _match.s
	mv _match.o match.o
	rm -f _match.s

$(SHAREDLIB): $(OBJS)
	$(LDSHARED) -o $@ $(OBJS)
	$(STRIP) $(SHAREDLIB)

#example$(EXE): example.o $(LIBS)
#	$(CC) $(CFLAGS) -o $@ example.o $(LDFLAGS)

#minigzip$(EXE): minigzip.o $(LIBS)
#	$(CC) $(CFLAGS) -o $@ minigzip.o $(LDFLAGS)

example$(EXE): example.o $(LIBS) $(OBJB)
	$(CC) $(CFLAGS) -o $@ example.o $(LDFLAGS) $(OBJB)

minigzip$(EXE): minigzip.o $(LIBS) $(OBJB)
	$(CC) $(CFLAGS) -o $@ minigzip.o $(LDFLAGS) $(OBJB)

install: 
	cp libz.so $(DESTLIB)
	ln -sf libz.so $(INSTALLDIR)/lib/libz.so.1
#	cp example ../../target/usr/sbin
#	cp minigzip ../../target/usr/sbin

mostlyclean: clean
clean:
	rm -f *.o *~ example$(EXE) minigzip$(EXE) \
	   libz.* foo.gz so_locations \
	   _match.s maketree contrib/infback9/*.o

maintainer-clean: distclean
distclean: clean
	cp -p Makefile.in Makefile
	cp -p zconf.in.h zconf.h
	rm -f .DS_Store

tags:
	etags *.[ch]

depend:
	makedepend -- $(CFLAGS) -- *.[ch]

# DO NOT DELETE THIS LINE -- make depend depends on it.

adler32.o: zlib.h zconf.h
compress.o: zlib.h zconf.h
crc32.o: crc32.h zlib.h zconf.h
deflate.o: deflate.h zutil.h zlib.h zconf.h
example.o: zlib.h zconf.h
gzio.o: zutil.h zlib.h zconf.h
inffast.o: zutil.h zlib.h zconf.h inftrees.h inflate.h inffast.h
inflate.o: zutil.h zlib.h zconf.h inftrees.h inflate.h inffast.h
infback.o: zutil.h zlib.h zconf.h inftrees.h inflate.h inffast.h
inftrees.o: zutil.h zlib.h zconf.h inftrees.h
minigzip.o: zlib.h zconf.h
trees.o: deflate.h zutil.h zlib.h zconf.h trees.h
uncompr.o: zlib.h zconf.h
zutil.o: zutil.h zlib.h zconf.h
