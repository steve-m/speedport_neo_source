APPSRCPATH=fetchmail-6.3.24

all:    
	make build
	
build:
	if test -e ./$(APPSRCPATH)/Makefile; then \
		$(MAKE) -C ./$(APPSRCPATH); \
	else \
		cd ./$(APPSRCPATH); \
		./configure --host=mips-linux CC=$(CC) CFLAGS="-g -O2 -I$(PUBLIC_APPSPATH)/libs/openssl-$(OPENSSL_VER)/" LDFLAGS="-L$(PUBLIC_APPSPATH)/libs/openssl-$(OPENSSL_VER)/" LEXLIB="-lfl" LIBICONV="-liconv" LIBS="-lcrypt -lresolv" LIBOBJS="$(LIBOBJDIR)strlcpy$U.o $(LIBOBJDIR)strlcat$U.o" --with-ssl="$(PUBLIC_APPSPATH)/libs/openssl-$(OPENSSL_VER)" ;\
 		$(MAKE); \
	fi
	
install:
	install -D ./$(APPSRCPATH)/fetchmail $(INSTALLDIR)/usr/sbin/fetchmail
	ln -sf /var/hosts	$(INSTALLDIR)/etc/hosts

clean:
	if test -e ./$(APPSRCPATH)/Makefile; then \
		$(MAKE) -C ./$(APPSRCPATH) clean; \
	fi


