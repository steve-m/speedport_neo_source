# Makefile for mini_httpd

# CONFIGURE: If you are using a SystemV-based operating system, such as
# Solaris, you will need to uncomment this definition.
#SYSV_LIBS =    -lnsl -lsocket

# CONFIGURE: Some systems don't need -lcrypt, and indeed they get an
# error if you try to link with it.  If you get an error about libcrypt
# not found, try commenting out this definition.
CRYPT_LIB =    -lcrypt

# CONFIGURE: If you want to compile in support for https, uncomment these
# definitions.  You will need to have already built OpenSSL, available at
# http://www.openssl.org/  Make sure the SSL_TREE definition points to the
# tree with your OpenSSL installation - depending on how you installed it,
# it may be in /usr/local instead of /usr/local/ssl.
USE_OPENSSL_LIB=1

SSL_DEFS +=	-DUSE_SSL
ifeq ($(USE_OPENSSL_LIB),1)
OPENSSL_DIR = $(PUBLIC_APPSPATH)/libs/openssl-$(OPENSSL_VER)
SSL_DEFS +=     -DOPEN_SSL
SSL_INC =       -I$(OPENSSL_DIR)/include -I$(PRIVATE_APPSPATH)/include -I$(SHARED_APPSPATH)/include
SSL_LIBS =      -L$(OPENSSL_DIR) -L$(INSTALLDIR)/lib -lssl -lcrypto -lcrypt
else
SSL_TREE =	../matrixssl-1-8-1
SSL_DEFS +=	-DMATRIX_SSL -DHAVE_MATRIXSSL
SSL_INC =	-I${SSL_TREE}/include -I$(PRIVATE_APPSPATH) -I$(SHARED_APPSPATH)/include
SSL_LIBS =	-L${SSL_TREE}/lib -L$(INSTALLDIR)/lib
endif

BINDIR =	/usr/local/sbin
MANDIR =	/usr/local/man
CDEFS =		${SSL_DEFS} ${SSL_INC} 
CFLAGS +=	-O2 -s ${CDEFS}
#CFLAGS =	-g ${CDEFS}
LDFLAGS =	-s
#LDFLAGS =	-g
LDLIBS =	${SSL_LIBS} ${SYSV_LIBS} ${CRYPT_LIB} -lscutil -lscnvram -lsal
ifneq ($(USE_OPENSSL_LIB),1)
LIBS=  -lutil -lpthread -L../matrixssl-1-8-1 -lmatrixssl
endif
#all:		mini_httpd #htpasswd

ifeq ($(USE_OPENSSL_LIB),1)
mini_httpd: http_user.o mini_httpd.o match.o tdate_parse.o auth.o
	${CC} ${CFLAGS} ${LDFLAGS}  http_user.o mini_httpd.o auth.o match.o tdate_parse.o ${LDLIBS} -o mini_httpd
else
mini_httpd:	make_links http_user.o mini_httpd.o auth.o match.o tdate_parse.o matrixssl_helper.o https.o shutils.o
	${CC} ${CFLAGS} $(LIBS) ${LDFLAGS} http_user.o mini_httpd.o auth.o match.o tdate_parse.o matrixssl_helper.o shutils.o https.o ${LDLIBS} -o mini_httpd
endif

install:mini_httpd
	install -D mini_httpd $(INSTALLDIR)/usr/sbin/mini_httpd
	$(STRIP) $(INSTALLDIR)/usr/sbin/mini_httpd
ifeq ($(USE_OPENSSL_LIB),1)
	cp -f mini_httpd_openssl.pem $(INSTALLDIR)/usr/sbin/certSrv.pem
endif
    
mini_httpd.o:	mini_httpd.c version.h port.h match.h tdate_parse.h mime_encodings.h mime_types.h matrixssl_helper.h https.h shutils.h
	${CC} ${CFLAGS} -c mini_httpd.c

ifeq ($(SC_HTTP_LOGIN_COOKIE),1)
auth.o:	auth_cookie.c version.h port.h match.h tdate_parse.h mime_encodings.h mime_types.h matrixssl_helper.h https.h shutils.h
	${CC} ${CFLAGS} -c auth_cookie.c -o auth.o
else
auth.o:	auth.c version.h port.h match.h tdate_parse.h mime_encodings.h mime_types.h matrixssl_helper.h https.h shutils.h
	${CC} ${CFLAGS} -c auth.c -o auth.o
endif

match.o:	match.c match.h
	${CC} ${CFLAGS} -c match.c

tdate_parse.o:	tdate_parse.c tdate_parse.h
	${CC} ${CFLAGS} -c tdate_parse.c

mime_encodings.h: mime_encodings.txt
	rm -f mime_encodings.h
	sed < mime_encodings.txt > mime_encodings.h \
	  -e 's/#.*//' -e 's/[ 	]*$$//' -e '/^$$/d' \
	  -e 's/[ 	][ 	]*/", 0, "/' -e 's/^/{ "/' -e 's/$$/", 0 },/'

mime_types.h: mime_types.txt
	rm -f mime_types.h
	sed < mime_types.txt > mime_types.h \
	  -e 's/#.*//' -e 's/[ 	]*$$//' -e '/^$$/d' \
	  -e 's/[ 	][ 	]*/", 0, "/' -e 's/^/{ "/' -e 's/$$/", 0 },/'


htpasswd:	htpasswd.o
	gcc ${CFLAGS} ${LDFLAGS} htpasswd.o ${CRYPT_LIB} -o htpasswd

htpasswd.o:	htpasswd.c
	gcc ${CFLAGS} -c htpasswd.c

http_user.o: http_user.c
	${CC} ${CFLAGS} -c http_user.c

cert:		mini_httpd.pem
mini_httpd.pem:	mini_httpd.cnf
	openssl req -new -x509 -days 3650 -nodes -config mini_httpd.cnf -out mini_httpd.pem -keyout mini_httpd.pem
	openssl x509 -subject -dates -fingerprint -noout -in mini_httpd.pem
	chmod 600 mini_httpd.pem


clean:
	rm -f mini_httpd mime_encodings.h mime_types.h htpasswd mini_httpd.rnd *.o core core.* *.core

tar:
	@name=`sed -n -e '/SERVER_SOFTWARE/!d' -e 's,.*mini_httpd/,mini_httpd-,' -e 's, .*,,p' version.h` ; \
	  rm -rf $$name ; \
	  mkdir $$name ; \
	  tar cf - `cat FILES` | ( cd $$name ; tar xfBp - ) ; \
	  chmod 644 $$name/Makefile $$name/mime_encodings.txt $$name/mime_types.txt ; \
	  chmod 755 $$name/contrib $$name/contrib/redhat-rpm ; \
	  tar cf $$name.tar $$name ; \
	  rm -rf $$name ; \
	  gzip $$name.tar

make_links:
#	./mklnks
