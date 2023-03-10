### Generated automatically from Makefile.org by Configure.

##
## Makefile for OpenSSL
##

#
# Set our CommEngine directory (by splitting the pwd into two words
# at /userspace and taking the first word only).
# Then include the common defines under CommEngine.
#
CURR_DIR := $(shell pwd)
BUILD_DIR:=$(subst /userspace, /userspace,$(CURR_DIR))
BUILD_DIR:=$(word 1, $(BUILD_DIR))
TARGETS_DIR = $(BUILD_DIR)/targets

include $(BUILD_DIR)/make.common

VERSION=0.9.7f
MAJOR=0
MINOR=9.7
SHLIB_VERSION_NUMBER=0.9.7
SHLIB_VERSION_HISTORY=
SHLIB_MAJOR=0
SHLIB_MINOR=9.7
SHLIB_EXT=.so.$(SHLIB_MAJOR).$(SHLIB_MINOR)
PLATFORM=linux-mips

OPTIONS = no-krb5 no-hw shared no-bf no-cast no_md2 no-md4 no-mdc2 no-ripemd no-rc2 no-krb5 no_dsa no_ec 
ifeq ($(strip $(BUILD_HTTPD_SSL)),)
OPTIONS += no_engine no_ocsp
endif
ifneq ($(strip $(BENCHMARKS_SMP)),y)
OPTIONS += no-threads no-zlib no_speed
endif

CONFIGURE_ARGS=no-krb5 no-hw shared linux-mips
SHLIB_TARGET=linux-shared

# HERE indicates where this Makefile lives.  This can be used to indicate
# where sub-Makefiles are expected to be.  Currently has very limited usage,
# and should probably not be bothered with at all.
HERE=.

# INSTALL_PREFIX is for package builders so that they can configure
# for, say, /usr/ and yet have everything installed to /tmp/somedir/usr/.
# Normally it is left empty.
INSTALL_PREFIX=
INSTALLTOP=/usr/local/ssl

# Do not edit this manually. Use Configure --openssldir=DIR do change this!
OPENSSLDIR=/usr/local/ssl

# NO_IDEA - Define to build without the IDEA algorithm
# NO_RC4  - Define to build without the RC4 algorithm
# NO_RC2  - Define to build without the RC2 algorithm
# THREADS - Define when building with threads, you will probably also need any
#           system defines as well, i.e. _REENTERANT for Solaris 2.[34]
# TERMIO  - Define the termio terminal subsystem, needed if sgtty is missing.
# TERMIOS - Define the termios terminal subsystem, Silicon Graphics.
# LONGCRYPT - Define to use HPUX 10.x's long password modification to crypt(3).
# DEVRANDOM - Give this the value of the 'random device' if your OS supports
#           one.  32 bytes will be read from this when the random
#           number generator is initalised.
# SSL_FORBID_ENULL - define if you want the server to be not able to use the
#           NULL encryption ciphers.
#
# LOCK_DEBUG - turns on lots of lock debug output :-)
# REF_CHECK - turn on some xyz_free() assertions.
# REF_PRINT - prints some stuff on structure free.
# CRYPTO_MDEBUG - turns on my 'memory leak' detecting stuff
# MFUNC - Make all Malloc/Free/Realloc calls call
#       CRYPTO_malloc/CRYPTO_free/CRYPTO_realloc which can be setup to
#       call application defined callbacks via CRYPTO_set_mem_functions()
# MD5_ASM needs to be defined to use the x86 assembler for MD5
# SHA1_ASM needs to be defined to use the x86 assembler for SHA1
# RMD160_ASM needs to be defined to use the x86 assembler for RIPEMD160
# Do not define B_ENDIAN or L_ENDIAN if 'unsigned long' == 8.  It must
# equal 4.
# PKCS1_CHECK - pkcs1 tests.

#CC= cc
#CFLAG= -DL_ENDIAN -DTERMIO -O3 -fomit-frame-pointer -m486 -Wall -Wuninitialized -DSHA1_ASM -DMD5_ASM -DRMD160_ASM
#CFLAG= -DOPENSSL_NO_KRB5 -O

CFLAG= -fPIC -DOPENSSL_THREADS -D_REENTRANT -DDSO_DLFCN -DHAVE_DLFCN_H -DOPENSSL_NO_KRB5 -DOPENSSL_NO_HW -Os -fomit-frame-pointer -Wall

# ARCH_ENDIAN is defined in make.comon.  Assign Endianess according to the ARCH_ENDIAN (little or big).
ifeq ($(strip $(ARCH_ENDIAN)),little)
CFLAG += -DL_ENDIAN
else
CFLAG += -DB_ENDIAN
endif

CFLAG+= -DOPENSSL_NO_IDEA  -DOPENSSL_NO_BF -DOPENSSL_NO_CAST -DOPENSSL_NO_MD2 -DOPENSSL_NO_MD4 -DOPENSSL_NO_RIPEMD -DOPENSSL_NO_MDC2 -DOPENSSL_NO_RC2 -DOPENSSL_NO_DSA -DOPENSSL_NO_EC 
CFLAG += $(BRCM_WERROR_CFLAGS)
ifeq ($(strip $(BUILD_HTTPD_SSL)),)
CFLAG+= -DOPENSSL_NO_ENGINE -DOPENSSL_NO_OCSP
CFLAG+= -DOPENSSL_NO_RC5 -DOPENSSL_NO_ERR -DOPENSSL_NO_SSL2 
ifeq ($(strip $(BUILD_TR69C_SSL)),)
CFLAG+= -DOPENSSL_NO_RC4
endif
endif
ifneq ($(strip $(BENCHMARKS_SMP)),y)
CFLAG+= -DOPENSSL_NO_SPEED
endif


#CONFIG_MIPS_BRCM: mwang: really should put this in LDFLAGS, but the app/Makefile does not have LDFLAG
CFLAG += -Wl,-rpath, -L$(INSTALL_DIR)/lib -L$(INSTALL_DIR)/lib/public
#CFLAG += -Werror -Wfatal-errors
CFLAG += -I$(TOOLCHAIN)/include -Wl,-L$(TOOLCHAIN)/lib -Wl,-L$(TOOLCHAIN_TOP)/lib

DEPFLAG= 
PEX_LIBS= 

ifeq ($(strip $(DESKTOP_LINUX)),y)
EX_LIBS= -ldl
else
ifneq ($(strip $(LEGACY_TOOLCHAIN)),y)
EX_LIBS= -ldl -L$(HOSTUSRLIBDIR) -L$(USRGCCLIBDIR) -lgcc_s
else
EX_LIBS= -ldl
endif
endif


EXE_EXT= 
ARFLAGS= 
AR=ar $(ARFLAGS) r
#RANLIB= /usr/bin/ranlib
PERL= /usr/bin/perl
TAR= tar
TARFLAGS= --no-recursion
#MAKEDEPPROG=makedepend
MAKEDEPPROG=gcc

# We let the C compiler driver to take care of .s files. This is done in
# order to be excused from maintaining a separate set of architecture
# dependent assembler flags. E.g. if you throw -mcpu=ultrasparc at SPARC
# gcc, then the driver will automatically translate it to -xarch=v8plus
# and pass it down to assembler.
AS=$(CC) -c
ASFLAG=$(CFLAG)

# Set BN_ASM to bn_asm.o if you want to use the C version
BN_ASM= bn_asm.o
#BN_ASM= bn_asm.o
#BN_ASM= asm/bn86-elf.o	# elf, linux-elf
#BN_ASM= asm/bn86-sol.o # solaris
#BN_ASM= asm/bn86-out.o # a.out, FreeBSD
#BN_ASM= asm/bn86bsdi.o # bsdi
#BN_ASM= asm/alpha.o    # DEC Alpha
#BN_ASM= asm/pa-risc2.o # HP-UX PA-RISC
#BN_ASM= asm/r3000.o    # SGI MIPS cpu
#BN_ASM= asm/sparc.o    # Sun solaris/SunOS
#BN_ASM= asm/bn-win32.o # Windows 95/NT
#BN_ASM= asm/x86w16.o   # 16 bit code for Windows 3.1/DOS
#BN_ASM= asm/x86w32.o   # 32 bit code for Windows 3.1

# For x86 assembler: Set PROCESSOR to 386 if you want to support
# the 80386.
PROCESSOR= 

# Set DES_ENC to des_enc.o if you want to use the C version
#There are 4 x86 assember options.
FIPS_DES_ENC= 
DES_ENC= des_enc.o fcrypt_b.o
#DES_ENC= des_enc.o fcrypt_b.o          # C
#DES_ENC= asm/dx86-elf.o asm/yx86-elf.o # elf
#DES_ENC= asm/dx86-sol.o asm/yx86-sol.o # solaris
#DES_ENC= asm/dx86-out.o asm/yx86-out.o # a.out, FreeBSD
#DES_ENC= asm/dx86bsdi.o asm/yx86bsdi.o # bsdi

# Set BF_ENC to bf_enc.o if you want to use the C version
#There are 4 x86 assember options.
BF_ENC= bf_enc.o
#BF_ENC= bf_enc.o
#BF_ENC= asm/bx86-elf.o # elf
#BF_ENC= asm/bx86-sol.o # solaris
#BF_ENC= asm/bx86-out.o # a.out, FreeBSD
#BF_ENC= asm/bx86bsdi.o # bsdi

# Set CAST_ENC to c_enc.o if you want to use the C version
#There are 4 x86 assember options.
CAST_ENC= c_enc.o
#CAST_ENC= c_enc.o
#CAST_ENC= asm/cx86-elf.o # elf
#CAST_ENC= asm/cx86-sol.o # solaris
#CAST_ENC= asm/cx86-out.o # a.out, FreeBSD
#CAST_ENC= asm/cx86bsdi.o # bsdi

# Set RC4_ENC to rc4_enc.o if you want to use the C version
#There are 4 x86 assember options.
RC4_ENC= rc4_enc.o
#RC4_ENC= rc4_enc.o
#RC4_ENC= asm/rx86-elf.o # elf
#RC4_ENC= asm/rx86-sol.o # solaris
#RC4_ENC= asm/rx86-out.o # a.out, FreeBSD
#RC4_ENC= asm/rx86bsdi.o # bsdi

# Set RC5_ENC to rc5_enc.o if you want to use the C version
#There are 4 x86 assember options.
RC5_ENC= rc5_enc.o
#RC5_ENC= rc5_enc.o
#RC5_ENC= asm/r586-elf.o # elf
#RC5_ENC= asm/r586-sol.o # solaris
#RC5_ENC= asm/r586-out.o # a.out, FreeBSD
#RC5_ENC= asm/r586bsdi.o # bsdi

# Also need MD5_ASM defined
MD5_ASM_OBJ= 
#MD5_ASM_OBJ= asm/mx86-elf.o        # elf
#MD5_ASM_OBJ= asm/mx86-sol.o        # solaris
#MD5_ASM_OBJ= asm/mx86-out.o        # a.out, FreeBSD
#MD5_ASM_OBJ= asm/mx86bsdi.o        # bsdi

# Also need SHA1_ASM defined
SHA1_ASM_OBJ= 
FIPS_SHA1_ASM_OBJ= 
#SHA1_ASM_OBJ= asm/sx86-elf.o       # elf
#SHA1_ASM_OBJ= asm/sx86-sol.o       # solaris
#SHA1_ASM_OBJ= asm/sx86-out.o       # a.out, FreeBSD
#SHA1_ASM_OBJ= asm/sx86bsdi.o       # bsdi

# Also need RMD160_ASM defined
RMD160_ASM_OBJ= 
#RMD160_ASM_OBJ= asm/rm86-elf.o       # elf
#RMD160_ASM_OBJ= asm/rm86-sol.o       # solaris
#RMD160_ASM_OBJ= asm/rm86-out.o       # a.out, FreeBSD
#RMD160_ASM_OBJ= asm/rm86bsdi.o       # bsdi

# KRB5 stuff
KRB5_INCLUDES=
LIBKRB5=

# When we're prepared to use shared libraries in the programs we link here
# we might set SHLIB_MARK to '$(SHARED_LIBS)'.
SHLIB_MARK=

DIRS=   crypto fips ssl $(SHLIB_MARK) sigs apps tools
SHLIBDIRS= crypto ssl

# dirs in crypto to build
SDIRS=  objects \
	md5 sha hmac \
	des dh\
	bn rsa dso \
	buffer stack rand err \
	evp asn1 pem x509 lhash bio txt_db x509v3 conf pkcs7 pkcs12 comp ui 

# if BUILD_TR69C_SSL is enabled then add rc4
ifneq ($(strip $(BUILD_TR69C_SSL)),)
SDIRS+= rc4
endif

ifneq ($(strip $(BUILD_HTTPD_SSL)),)
# if BUILD_TR69C_SSL is disabled then add rc4 when BUILD_HTTPD_SSL is enabled
ifeq ($(strip $(BUILD_TR69C_SSL)),)
SDIRS+= rc4
endif
SDIRS+= rc5 engine aes ocsp
endif

/* brcm: aes used by other modules */
#ifneq ($(strip $(BUILD_IPSEC_TOOLS)),)
SDIRS+= aes
#endif

# ocsp  
FDIRS=	sha1 rand des rsa dh
#
# tests to perform.  "alltests" is a special word indicating that all tests
# should be performed.
TESTS = alltests

MAKEFILE= Makefile

MANDIR=$(OPENSSLDIR)/man
MAN1=1
MAN3=3
MANSUFFIX=
SHELL=/bin/sh

TOP=    .
ONEDIRS=out tmp
EDIRS=  times doc bugs util include certs ms shlib mt demos perl sf dep VMS
WDIRS=  windows
LIBS=   libcrypto.a libssl.a
SIGS=	libcrypto.a.sha1
SHARED_CRYPTO=libcrypto$(SHLIB_EXT)
SHARED_SSL=libssl$(SHLIB_EXT)
SHARED_LIBS= $(SHARED_CRYPTO) $(SHARED_SSL)
SHARED_LIBS_LINK_EXTS=.so.$(SHLIB_MAJOR) .so
SHARED_LDFLAGS=

GENERAL=        Makefile
BASENAME=       openssl
NAME=           $(BASENAME)-$(VERSION)
TARFILE=        $(NAME).tar
WTARFILE=       $(NAME)-win.tar
EXHEADER=       e_os2.h
HEADER=         e_os.h

# When we're prepared to use shared libraries in the programs we link here
# we might remove 'clean-shared' from the targets to perform at this stage

all: Makefile sub_all openssl.pc

dynamic: all install

sigs:	$(SIGS)
libcrypto.a.sha1: libcrypto.a
	@if egrep 'define OPENSSL_FIPS' $(TOP)/include/openssl/opensslconf.h > /dev/null; then \
		$(RANLIB) libcrypto.a; \
		fips/sha1/fips_standalone_sha1 libcrypto.a > libcrypto.a.sha1; \
	fi

sub_all:
	@for i in $(DIRS); \
	do \
	if [ -d "$$i" ]; then \
		(cd $$i && echo "making all in $$i..." && \
		$(MAKE) CC='${CC}' PLATFORM='${PLATFORM}' CFLAG='${CFLAG}' AS='${AS}' ASFLAG='${ASFLAG}' SDIRS='$(SDIRS)' FDIRS='$(FDIRS)' INSTALLTOP='${INSTALLTOP}' PEX_LIBS='${PEX_LIBS}' EX_LIBS='${EX_LIBS}' BN_ASM='${BN_ASM}' DES_ENC='${DES_ENC}' FIPS_DES_ENC='${FIPS_DES_ENC}' BF_ENC='${BF_ENC}' CAST_ENC='${CAST_ENC}' RC4_ENC='${RC4_ENC}' RC5_ENC='${RC5_ENC}' SHA1_ASM_OBJ='${SHA1_ASM_OBJ}' FIPS_SHA1_ASM_OBJ='${FIPS_SHA1_ASM_OBJ}' MD5_ASM_OBJ='${MD5_ASM_OBJ}' RMD160_ASM_OBJ='${RMD160_ASM_OBJ}' AR='${AR}' PROCESSOR='${PROCESSOR}' PERL='${PERL}' RANLIB='${RANLIB}' KRB5_INCLUDES='${KRB5_INCLUDES}' LIBKRB5='${LIBKRB5}' EXE_EXT='${EXE_EXT}' SHARED_LIBS='${SHARED_LIBS}' SHLIB_EXT='${SHLIB_EXT}' SHLIB_TARGET='${SHLIB_TARGET}' all ) || exit 1; \
	else \
		$(MAKE) $$i; \
	fi; \
	done;

sub_target:
	@for i in $(DIRS); \
	do \
	if [ -d "$$i" ]; then \
		(cd $$i && echo "making $(TARGET) in $$i..." && \
		$(MAKE) CC='${CC}' PLATFORM='${PLATFORM}' CFLAG='${CFLAG}' AS='${AS}' ASFLAG='${ASFLAG}' SDIRS='$(SDIRS)' FDIRS='$(FDIRS)' INSTALLTOP='${INSTALLTOP}' PEX_LIBS='${PEX_LIBS}' EX_LIBS='${EX_LIBS}' BN_ASM='${BN_ASM}' DES_ENC='${DES_ENC}' FIPS_DES_ENC='${FIPS_DES_ENC}' BF_ENC='${BF_ENC}' CAST_ENC='${CAST_ENC}' RC4_ENC='${RC4_ENC}' RC5_ENC='${RC5_ENC}' SHA1_ASM_OBJ='${SHA1_ASM_OBJ}' FIPS_SHA1_ASM_OBJ='${FIPS_SHA1_ASM_OBJ}' MD5_ASM_OBJ='${MD5_ASM_OBJ}' RMD160_ASM_OBJ='${RMD160_ASM_OBJ}' AR='${AR}' PROCESSOR='${PROCESSOR}' PERL='${PERL}' RANLIB='${RANLIB}' KRB5_INCLUDES='${KRB5_INCLUDES}' LIBKRB5='${LIBKRB5}' EXE_EXT='${EXE_EXT}' SHARED_LIBS='${SHARED_LIBS}' SHLIB_EXT='${SHLIB_EXT}' SHLIB_TARGET='${SHLIB_TARGET}' TARGET='$(TARGET)' sub_target ) || exit 1; \
	else \
		$(MAKE) $$i; \
	fi; \
	done;

libcrypto$(SHLIB_EXT): libcrypto.a
	@if [ "$(SHLIB_TARGET)" != "" ]; then \
		$(MAKE) SHLIBDIRS=crypto build-shared; \
	else \
		echo "There's no support for shared libraries on this platform" >&2; \
	fi

libssl$(SHLIB_EXT): libcrypto$(SHLIB_EXT) libssl.a
	@if [ "$(SHLIB_TARGET)" != "" ]; then \
		$(MAKE) SHLIBDIRS=ssl SHLIBDEPS='-lcrypto' build-shared; \
	else \
		echo "There's no support for shared libraries on this platform" >&2; \
	fi

clean-shared:
	@for i in $(SHLIBDIRS); do \
		if [ -n "$(SHARED_LIBS_LINK_EXTS)" ]; then \
			tmp="$(SHARED_LIBS_LINK_EXTS)"; \
			for j in $${tmp:-x}; do \
				( set -x; rm -f lib$$i$$j ); \
			done; \
		fi; \
		( set -x; rm -f lib$$i$(SHLIB_EXT) ); \
		if [ "$(PLATFORM)" = "Cygwin" ]; then \
			( set -x; rm -f cyg$$i-$(SHLIB_VERSION_NUMBER)$(SHLIB_EXT) lib$$i$(SHLIB_EXT).a ); \
		fi; \
	done

link-shared: do_$(SHLIB_TARGET)
	@if [ -n "$(SHARED_LIBS_LINK_EXTS)" ]; then \
		tmp="$(SHARED_LIBS_LINK_EXTS)"; \
		for i in $(SHLIBDIRS); do \
			prev=lib$$i$(SHLIB_EXT); \
			for j in $${tmp:-x}; do \
				( set -x; \
				rm -f lib$$i$$j; ln -s $$prev lib$$i$$j ); \
				prev=lib$$i$$j; \
			done; \
		done; \
	fi

build-shared: clean-shared do_$(SHLIB_TARGET) link-shared

do_bsd-gcc-shared: do_gnu-shared
do_linux-shared: do_gnu-shared
do_gnu-shared: clean-shared
	libs='-L. -L${LIBDIR} ${SHLIBDEPS}'; for i in ${SHLIBDIRS}; do \
	if [ "${SHLIBDIRS}" = "ssl" -a -n "$(LIBKRB5)" ]; then \
		libs="$(LIBKRB5) $$libs"; \
	fi; \
	( set -x; ${LD} ${SHARED_LDFLAGS} \
		-shared -o lib$$i.so.${SHLIB_MAJOR}.${SHLIB_MINOR} \
		-soname=lib$$i.so.${SHLIB_MAJOR}.${SHLIB_MINOR} \
		-Bsymbolic \
		--whole-archive lib$$i.a \
		--no-whole-archive $$libs ${EX_LIBS} -lc ) || exit 1; \
	libs="-l$$i $$libs"; \
	done

DETECT_GNU_LD=(${CC} -Wl,-V /dev/null 2>&1 | grep '^GNU ld' )>/dev/null

# For Darwin AKA Mac OS/X (dyld)
do_darwin-shared: 
	libs='-L. ${SHLIBDEPS}'; for i in ${SHLIBDIRS}; do \
	if [ "${SHLIBDIRS}" = "ssl" -a -n "$(LIBKRB5)" ]; then \
		libs="$(LIBKRB5) $$libs"; \
	fi; \
	( set -x; ${CC} --verbose -dynamiclib -o lib$$i${SHLIB_EXT} \
		lib$$i.a $$libs -all_load -current_version ${SHLIB_MAJOR}.${SHLIB_MINOR} \
		-compatibility_version ${SHLIB_MAJOR}.`echo ${SHLIB_MINOR} | cut -d. -f1` \
		-install_name ${INSTALLTOP}/lib/lib$$i${SHLIB_EXT} ) || exit 1; \
	libs="-l`basename $$i${SHLIB_EXT} .dylib` $$libs"; \
	echo "" ; \
	done

do_cygwin-shared:
	libs='-L. ${SHLIBDEPS}'; for i in ${SHLIBDIRS}; do \
	if [ "${SHLIBDIRS}" = "ssl" -a -n "$(LIBKRB5)" ]; then \
		libs="$(LIBKRB5) $$libs"; \
	fi; \
	shlib=cyg$${i}-$(SHLIB_VERSION_NUMBER).dll; \
	[ "$(PLATFORM)" = "mingw" ] && shlib=$${i}eay32.dll; \
	[ -f apps/$$shlib ] && rm apps/$$shlib; \
	[ -f test/$$shlib ] && rm test/$$shlib; \
	base=;  [ $$i = "crypto" ] && base=-Wl,--image-base,0xFE00000; \
	( set -x; ${CC} ${SHARED_LDFLAGS} \
		-shared $$base -o $$shlib \
		-Wl,-Bsymbolic \
		-Wl,--whole-archive lib$$i.a \
		-Wl,--out-implib,lib$$i.dll.a \
		-Wl,--no-whole-archive $$libs ${EX_LIBS} ) || exit 1; \
	cp -p $$shlib apps/; cp -p $$shlib test/; \
	libs="-l$$i $$libs"; \
	done

# This assumes that GNU utilities are *not* used
do_alpha-osf1-shared:
	if ${DETECT_GNU_LD}; then \
		$(MAKE) do_gnu-shared; \
	else \
		libs='-L. ${SHLIBDEPS}'; for i in ${SHLIBDIRS}; do \
		if [ "${SHLIBDIRS}" = "ssl" -a -n "$(LIBKRB5)" ]; then \
			libs="$(LIBKRB5) $$libs"; \
		fi; \
		( set -x; ${CC} ${SHARED_LDFLAGS} \
			-shared -o lib$$i.so \
			-set_version "${SHLIB_VERSION_HISTORY}${SHLIB_VERSION_NUMBER}" \
			-all lib$$i.a -none $$libs ${EX_LIBS} -lc ) || exit 1; \
		libs="-l$$i $$libs"; \
		done; \
	fi

# This assumes that GNU utilities are *not* used
# The difference between alpha-osf1-shared and tru64-shared is the `-msym'
# option passed to the linker.
do_tru64-shared:
	if ${DETECT_GNU_LD}; then \
		$(MAKE) do_gnu-shared; \
	else \
		libs='-L. ${SHLIBDEPS}'; for i in ${SHLIBDIRS}; do \
		if [ "${SHLIBDIRS}" = "ssl" -a -n "$(LIBKRB5)" ]; then \
			libs="$(LIBKRB5) $$libs"; \
		fi; \
		( set -x; ${CC} ${SHARED_LDFLAGS} \
			-shared -msym -o lib$$i.so \
			-set_version "${SHLIB_VERSION_HISTORY}${SHLIB_VERSION_NUMBER}" \
			-all lib$$i.a -none $$libs ${EX_LIBS} -lc ) || exit 1; \
		libs="-l$$i $$libs"; \
		done; \
	fi

# This assumes that GNU utilities are *not* used
# The difference between tru64-shared and tru64-shared-rpath is the
# -rpath ${INSTALLTOP}/lib passed to the linker.
do_tru64-shared-rpath:
	if ${DETECT_GNU_LD}; then \
		$(MAKE) do_gnu-shared; \
	else \
		libs='-L. ${SHLIBDEPS}'; for i in ${SHLIBDIRS}; do \
		if [ "${SHLIBDIRS}" = "ssl" -a -n "$(LIBKRB5)" ]; then \
			libs="$(LIBKRB5) $$libs"; \
		fi; \
		( set -x; ${CC} ${SHARED_LDFLAGS} \
			-shared -msym -o lib$$i.so \
			-rpath  ${INSTALLTOP}/lib \
			-set_version "${SHLIB_VERSION_HISTORY}${SHLIB_VERSION_NUMBER}" \
			-all lib$$i.a -none $$libs ${EX_LIBS} -lc ) || exit 1; \
		libs="-l$$i $$libs"; \
		done; \
	fi


# This assumes that GNU utilities are *not* used
do_solaris-shared:
	if ${DETECT_GNU_LD}; then \
		$(MAKE) do_gnu-shared; \
	else \
		libs='-L. ${SHLIBDEPS}'; for i in ${SHLIBDIRS}; do \
		if [ "${SHLIBDIRS}" = "ssl" -a -n "$(LIBKRB5)" ]; then \
			libs="$(LIBKRB5) $$libs"; \
		fi; \
		( PATH=/usr/ccs/bin:$$PATH ; export PATH; \
		  MINUSZ='-z '; \
		  (${CC} -v 2>&1 | grep gcc) > /dev/null && MINUSZ='-Wl,-z,'; \
		  set -x; ${CC} ${SHARED_LDFLAGS} -G -dy -z text \
			-o lib$$i.so.${SHLIB_MAJOR}.${SHLIB_MINOR} \
			-h lib$$i.so.${SHLIB_MAJOR}.${SHLIB_MINOR} \
			-Wl,-Bsymbolic \
			$${MINUSZ}allextract lib$$i.a $${MINUSZ}defaultextract \
			$$libs ${EX_LIBS} -lc ) || exit 1; \
		libs="-l$$i $$libs"; \
		done; \
	fi

# OpenServer 5 native compilers used
do_svr3-shared:
	if ${DETECT_GNU_LD}; then \
		$(MAKE) do_gnu-shared; \
	else \
		libs='-L. ${SHLIBDEPS}'; for i in ${SHLIBDIRS}; do \
		if [ "${SHLIBDIRS}" = "ssl" -a -n "$(LIBKRB5)" ]; then \
			libs="$(LIBKRB5) $$libs"; \
		fi; \
		( PATH=/usr/ccs/bin:$$PATH ; export PATH; \
		  find . -name "*.o" -print > allobjs ; \
		  OBJS= ; export OBJS ; \
		  for obj in `ar t lib$$i.a` ; do \
		    OBJS="$${OBJS} `grep /$$obj allobjs`" ; \
		  done ; \
		  set -x; ${CC} ${SHARED_LDFLAGS} \
			-G -o lib$$i.so.${SHLIB_MAJOR}.${SHLIB_MINOR} \
			-h lib$$i.so.${SHLIB_MAJOR}.${SHLIB_MINOR} \
			$${OBJS} $$libs ${EX_LIBS} ) || exit 1; \
		libs="-l$$i $$libs"; \
		done; \
	fi

# UnixWare 7 and OpenUNIX 8 native compilers used
do_svr5-shared:
	if ${DETECT_GNU_LD}; then \
		$(MAKE) do_gnu-shared; \
	else \
		libs='-L. ${SHLIBDEPS}'; for i in ${SHLIBDIRS}; do \
		if [ "${SHLIBDIRS}" = "ssl" -a -n "$(LIBKRB5)" ]; then \
			libs="$(LIBKRB5) $$libs"; \
		fi; \
		( PATH=/usr/ccs/bin:$$PATH ; export PATH; \
		  SHARE_FLAG='-G'; \
		  (${CC} -v 2>&1 | grep gcc) > /dev/null && SHARE_FLAG='-shared'; \
		  find . -name "*.o" -print > allobjs ; \
		  OBJS= ; export OBJS ; \
		  for obj in `ar t lib$$i.a` ; do \
		    OBJS="$${OBJS} `grep /$$obj allobjs`" ; \
		  done ; \
		  set -x; LD_LIBRARY_PATH=.:$$LD_LIBRARY_PATH \
			${CC} ${SHARED_LDFLAGS} \
			$${SHARE_FLAG} -o lib$$i.so.${SHLIB_MAJOR}.${SHLIB_MINOR} \
			-h lib$$i.so.${SHLIB_MAJOR}.${SHLIB_MINOR} \
			$${OBJS} $$libs ${EX_LIBS} ) || exit 1; \
		libs="-l$$i $$libs"; \
		done; \
	fi

# This assumes that GNU utilities are *not* used
do_irix-shared:
	if ${DETECT_GNU_LD}; then \
		$(MAKE) do_gnu-shared; \
	else \
		libs='-L. ${SHLIBDEPS}'; for i in ${SHLIBDIRS}; do \
		if [ "${SHLIBDIRS}" = "ssl" -a -n "$(LIBKRB5)" ]; then \
			libs="$(LIBKRB5) $$libs"; \
		fi; \
		( WHOLELIB="-all lib$$i.a -none"; \
		  (${CC} -v 2>&1 | grep gcc) > /dev/null && WHOLELIB="-Wl,-all,lib$$i.a,-none"; \
		  set -x; ${CC} ${SHARED_LDFLAGS} \
			-shared -o lib$$i.so.${SHLIB_MAJOR}.${SHLIB_MINOR} \
			-Wl,-soname,lib$$i.so.${SHLIB_MAJOR}.${SHLIB_MINOR} \
			$${WHOLELIB} $$libs ${EX_LIBS} -lc) || exit 1; \
		libs="-l$$i $$libs"; \
		done; \
	fi

# This assumes that GNU utilities are *not* used
# HP-UX includes the full pathname of libs we depend on, so we would get
# ./libcrypto (with ./ as path information) compiled into libssl, hence
# we omit the SHLIBDEPS. Applications must be linked with -lssl -lcrypto
# anyway.
# The object modules are loaded from lib$i.a using the undocumented -Fl
# option.
#
# WARNING: Until DSO is fixed to support a search path, we support SHLIB_PATH
#          by temporarily specifying "+s"!
#
do_hpux-shared:
	for i in ${SHLIBDIRS}; do \
	if [ "${SHLIBDIRS}" = "ssl" -a -n "$(LIBKRB5)" ]; then \
		libs="$(LIBKRB5) $$libs"; \
	fi; \
	if expr $(PLATFORM) : '.*ia64' > /dev/null; then \
		shlib=lib$$i.so.${SHLIB_MAJOR}.${SHLIB_MINOR}; \
	else \
		shlib=lib$$i.sl.${SHLIB_MAJOR}.${SHLIB_MINOR}; \
	fi; \
	[ -f $$shlib ] && rm -f $$shlib; \
	( set -x; /usr/ccs/bin/ld ${SHARED_LDFLAGS} \
		+vnocompatwarnings \
		-b -z +s \
		-o $$shlib +h $$shlib \
		-Fl lib$$i.a -ldld -lc ) || exit 1; \
	chmod a=rx $$shlib; \
	done

# This assumes that GNU utilities are *not* used
# HP-UX includes the full pathname of libs we depend on, so we would get
# ./libcrypto (with ./ as path information) compiled into libssl, hence
# we omit the SHLIBDEPS. Applications must be linked with -lssl -lcrypto
# anyway.
#
# HP-UX in 64bit mode has "+s" enabled by default; it will search for
# shared libraries along LD_LIBRARY_PATH _and_ SHLIB_PATH.
#
do_hpux64-shared:
	for i in ${SHLIBDIRS}; do \
	if [ "${SHLIBDIRS}" = "ssl" -a -n "$(LIBKRB5)" ]; then \
		libs="$(LIBKRB5) $$libs"; \
	fi; \
	if expr $(PLATFORM) : '.*ia64' > /dev/null; then \
		shlib=lib$$i.so.${SHLIB_MAJOR}.${SHLIB_MINOR}; \
	else \
		shlib=lib$$i.sl.${SHLIB_MAJOR}.${SHLIB_MINOR}; \
	fi; \
	[ -f $$shlib ] && rm -f $$shlib; \
	( set -x; /usr/ccs/bin/ld ${SHARED_LDFLAGS} \
		-b -z \
		-o $$shlib +h $$shlib \
		+forceload lib$$i.a -ldl -lc ) || exit 1; \
	chmod a=rx $$shlib; \
	done

# The following method is said to work on all platforms.  Tests will
# determine if that's how it's gong to be used.
# This assumes that for all but GNU systems, GNU utilities are *not* used.
# ALLSYMSFLAGS would be:
#  GNU systems: --whole-archive
#  Tru64 Unix:  -all
#  Solaris:     -z allextract
#  Irix:        -all
#  HP/UX-32bit: -Fl
#  HP/UX-64bit: +forceload
#  AIX:		-bnogc
# SHAREDFLAGS would be:
#  GNU systems: -shared -Wl,-soname=lib$$i.so.${SHLIB_MAJOR}.${SHLIB_MINOR}
#  Tru64 Unix:  -shared \
#		-set_version "${SHLIB_VERSION_HISTORY}${SHLIB_VERSION_NUMBER}"
#  Solaris:     -G -h lib$$i.so.${SHLIB_MAJOR}.${SHLIB_MINOR}
#  Irix:        -shared -Wl,-soname,lib$$i.so.${SHLIB_MAJOR}.${SHLIB_MINOR}
#  HP/UX-32bit: +vnocompatwarnings -b -z +s \
#		+h lib$$i.sl.${SHLIB_MAJOR}.${SHLIB_MINOR}
#  HP/UX-64bit: -b -z +h lib$$i.sl.${SHLIB_MAJOR}.${SHLIB_MINOR}
#  AIX:		-G -bE:lib$$i.exp -bM:SRE
# SHAREDCMD would be:
#  GNU systems: $(CC)
#  Tru64 Unix:  $(CC)
#  Solaris:     $(CC)
#  Irix:        $(CC)
#  HP/UX-32bit: /usr/ccs/bin/ld
#  HP/UX-64bit: /usr/ccs/bin/ld
#  AIX:		$(CC)
ALLSYMSFLAG=-bnogc
SHAREDFLAGS=${SHARED_LDFLAGS} -G -bE:lib$$i.exp -bM:SRE
SHAREDCMD=$(CC)
do_aix-shared:
	libs='-L. ${SHLIBDEPS}'; for i in ${SHLIBDIRS}; do \
	if [ "${SHLIBDIRS}" = "ssl" -a -n "$(LIBKRB5)" ]; then \
		libs="$(LIBKRB5) $$libs"; \
	fi; \
	( set -x; \
	  OBJECT_MODE=`expr x${SHARED_LDFLAGS} : 'x\-[a-z]\([0-9]*\)'`; \
	  OBJECT_MODE=$${OBJECT_MODE:-32}; export OBJECT_MODE; \
	  ld -r -o lib$$i.o $(ALLSYMSFLAG) lib$$i.a && \
	  ( nm -Pg lib$$i.o | grep ' [BD] ' | cut -f1 -d' ' > lib$$i.exp; \
	    $(SHAREDCMD) $(SHAREDFLAGS) \
		-o lib$$i.so.${SHLIB_MAJOR}.${SHLIB_MINOR} lib$$i.o \
		$$libs ${EX_LIBS} ) ) \
	|| exit 1; \
	libs="-l$$i $$libs"; \
	done

do_reliantunix-shared:
	libs='-L. ${SHLIBDEPS}'; for i in ${SHLIBDIRS}; do \
	if [ "${SHLIBDIRS}" = "ssl" -a -n "$(LIBKRB5)" ]; then \
		libs="$(LIBKRB5) $$libs"; \
	fi; \
	tmpdir=/tmp/openssl.$$$$ ; rm -rf $$tmpdir ; \
	( set -x; \
	  ( Opwd=`pwd` ; mkdir $$tmpdir || exit 1; \
	    cd $$tmpdir || exit 1 ; ar x $$Opwd/lib$$i.a ; \
	    ${CC} -G -o lib$$i.so.${SHLIB_MAJOR}.${SHLIB_MINOR} *.o \
	  ) || exit 1; \
	  cp $$tmpdir/lib$$i.so.${SHLIB_MAJOR}.${SHLIB_MINOR} . ; \
	) || exit 1; \
	rm -rf $$tmpdir ; \
	libs="-l$$i $$libs"; \
	done

openssl.pc: Makefile
	@ ( echo 'prefix=$(INSTALLTOP)'; \
	    echo 'exec_prefix=$${prefix}'; \
	    echo 'libdir=$${exec_prefix}/lib'; \
	    echo 'includedir=$${prefix}/include'; \
	    echo ''; \
	    echo 'Name: OpenSSL'; \
	    echo 'Description: Secure Sockets Layer and cryptography libraries and tools'; \
	    echo 'Version: '$(VERSION); \
	    echo 'Requires: '; \
	    echo 'Libs: -L$${libdir} -lssl -lcrypto $(LIBKRB5) $(EX_LIBS)'; \
	    echo 'Cflags: -I$${includedir} $(KRB5_INCLUDES)' ) > openssl.pc

#Makefile: Makefile.org
#	@echo "Makefile is older than Makefile.org."
#	@echo "Reconfigure the source tree (via './config' or 'perl Configure'), please."
#	@false
Makefile: 

libclean:
	rm -f *.map *.so *.so.* engines/*.so *.a */lib */*/lib
	rm -f $(INSTALL_DIR)/lib/libssl.so*
	rm -f $(INSTALL_DIR)/lib/libcrypto.so*
	rm -f $(INSTALL_DIR)/bin/openssl

#
# clean and distclean will do the "make clean" plus deleting all the files that we have not modified for brcm.
# We will get all those files from the tarball anyways.
#

clean distclean: libclean
	if [ ! -f Makefile.org ]; then \
		echo Untarring original source...; \
		(tar xkfj $(LIB_DIRS)/openssl.tar.bz2 -C $(LIB_DIRS) 2> /dev/null || true); \
	fi
	rm -f shlib/*.o *.o core a.out fluff rehash.time testlog make.log cctest cctest.c
	@for i in $(DIRS) ;\
	do \
	if [ -d "$$i" ]; then \
		(cd $$i && echo "making clean in $$i..." && \
		$(MAKE) EXE_EXT='${EXE_EXT}' SDIRS='${SDIRS}' clean ) || exit 1; \
		rm -f $(LIBS); \
	fi; \
	done;
	rm -f openssl.pc
	rm -f speed.* .pure
	rm -f $(TARFILE)
	@for i in $(ONEDIRS) ;\
	do \
	rm -fr $$i/*; \
	done

	rm -rf bugs certs CHANGES* config demos doc e_os* FAQ
	rm -rf include INSTALL* install.com LICENSE MacOS Makefile.org makevms.com
	rm -rf ms NEWS openssl.* os2 perl PROBLEMS README* shlib test times
	rm -rf tools util VMS
	-find apps -type f -a ! \( -name progs.h -o -name s_socket.c \) -exec rm -f {} \;
	rm -f apps/md4.c
	rm -rf apps/demoCA apps/set
	-find crypto -type f -a ! \( -name opensslconf.h -o -name err_all.c \) -exec rm -f {} \;
	-find crypto -depth -type d -a ! \( -name crypto -o -name err \) -exec rmdir {} \;
	-find fips -type f -a ! -name fips_aesavs.c -exec rm -f {} \;
	rm -rf fips/rand fips/des fips/rsa fips/dh fips/sha1 fips/dsa
	-find ssl -type f -a ! -name s23_meth.c -exec rm -f {} \;


makefile.one: files
	$(PERL) util/mk1mf.pl >makefile.one; \
	sh util/do_ms.sh

files:
	$(PERL) $(TOP)/util/files.pl Makefile > $(TOP)/MINFO
	@for i in $(DIRS) ;\
	do \
	if [ -d "$$i" ]; then \
		(cd $$i && echo "making 'files' in $$i..." && \
		$(MAKE) SDIRS='${SDIRS}' PERL='${PERL}' files ) || exit 1; \
	fi; \
	done;

links:
	@$(PERL) $(TOP)/util/mkdir-p.pl include/openssl
	@$(PERL) $(TOP)/util/mklink.pl include/openssl $(EXHEADER)
	@for i in $(DIRS); do \
	if [ -d "$$i" ]; then \
		(cd $$i && echo "making links in $$i..." && \
		$(MAKE) CC='${CC}' PLATFORM='${PLATFORM}' CFLAG='${CFLAG}' SDIRS='$(SDIRS)' INSTALLTOP='${INSTALLTOP}' PEX_LIBS='${PEX_LIBS}' EX_LIBS='${EX_LIBS}' BN_ASM='${BN_ASM}' DES_ENC='${DES_ENC}' FIPS_DES_ENC='${FIPS_DES_ENC}' BF_ENC='${BF_ENC}' CAST_ENC='${CAST_ENC}' RC4_ENC='${RC4_ENC}' RC5_ENC='${RC5_ENC}' SHA1_ASM_OBJ='${SHA1_ASM_OBJ}' FIPS_SHA1_ASM_OBJ='${FIPS_SHA1_ASM_OBJ}' MD5_ASM_OBJ='${MD5_ASM_OBJ}' RMD160_ASM_OBJ='${RMD160_ASM_OBJ}' AR='${AR}' PERL='${PERL}' KRB5_INCLUDES='${KRB5_INCLUDES}' LIBKRB5='${LIBKRB5}' links ) || exit 1; \
	fi; \
	done;

gentests:
	@(cd test && echo "generating dummy tests (if needed)..." && \
	$(MAKE) CC='${CC}' PLATFORM='${PLATFORM}' CFLAG='${CFLAG}' SDIRS='$(SDIRS)' INSTALLTOP='${INSTALLTOP}' PEX_LIBS='${PEX_LIBS}' EX_LIBS='${EX_LIBS}' BN_ASM='${BN_ASM}' DES_ENC='${DES_ENC}' FIPS_DES_ENC='${FIPS_DES_ENC}' BF_ENC='${BF_ENC}' CAST_ENC='${CAST_ENC}' RC4_ENC='${RC4_ENC}' RC5_ENC='${RC5_ENC}' SHA1_ASM_OBJ='${SHA1_ASM_OBJ}' FIPS_SHA1_ASM_OBJ='${FIPS_SHA1_ASM_OBJ}' MD5_ASM_OBJ='${MD5_ASM_OBJ}' RMD160_ASM_OBJ='${RMD160_ASM_OBJ}' AR='${AR}' PROCESSOR='${PROCESSOR}' PERL='${PERL}' RANLIB='${RANLIB}' TESTS='${TESTS}' KRB5_INCLUDES='${KRB5_INCLUDES}' LIBKRB5='${LIBKRB5}' EXE_EXT='${EXE_EXT}' SHARED_LIBS='${SHARED_LIBS}' SHLIB_EXT='${SHLIB_EXT}' SHLIB_TARGET='${SHLIB_TARGET}' TESTS='${TESTS}' OPENSSL_DEBUG_MEMORY=on generate );

dclean:
	rm -f *.bak
	@for i in $(DIRS) ;\
	do \
	if [ -d "$$i" ]; then \
		(cd $$i && echo "making dclean in $$i..." && \
		$(MAKE) SDIRS='${SDIRS}' PERL='${PERL}' dclean ) || exit 1; \
	fi; \
	done;

rehash: rehash.time
rehash.time: certs
	@(OPENSSL="`pwd`/util/opensslwrap.sh"; \
	  OPENSSL_DEBUG_MEMORY=on; \
	  export OPENSSL OPENSSL_DEBUG_MEMORY; \
	  $(PERL) tools/c_rehash certs)
	touch rehash.time

test:   tests

tests: rehash
	@(cd test && echo "testing..." && \
	$(MAKE) CC='${CC}' PLATFORM='${PLATFORM}' CFLAG='${CFLAG}' SDIRS='$(SDIRS)' INSTALLTOP='${INSTALLTOP}' PEX_LIBS='${PEX_LIBS}' EX_LIBS='${EX_LIBS}' BN_ASM='${BN_ASM}' DES_ENC='${DES_ENC}' FIPS_DES_ENC='${FIPS_DES_ENC}' BF_ENC='${BF_ENC}' CAST_ENC='${CAST_ENC}' RC4_ENC='${RC4_ENC}' RC5_ENC='${RC5_ENC}' SHA1_ASM_OBJ='${SHA1_ASM_OBJ}' FIPS_SHA1_ASM_OBJ='${FIPS_SHA1_ASM_OBJ}' MD5_ASM_OBJ='${MD5_ASM_OBJ}' RMD160_ASM_OBJ='${RMD160_ASM_OBJ}' AR='${AR}' PROCESSOR='${PROCESSOR}' PERL='${PERL}' RANLIB='${RANLIB}' TESTS='${TESTS}' KRB5_INCLUDES='${KRB5_INCLUDES}' LIBKRB5='${LIBKRB5}' EXE_EXT='${EXE_EXT}' SHARED_LIBS='${SHARED_LIBS}' SHLIB_EXT='${SHLIB_EXT}' SHLIB_TARGET='${SHLIB_TARGET}' TESTS='${TESTS}' OPENSSL_DEBUG_MEMORY=on tests );
	util/shlib_wrap.sh apps/openssl version -a

report:
	@$(PERL) util/selftest.pl

depend:
	@for i in $(DIRS) ;\
	do \
	if [ -d "$$i" ]; then \
		(cd $$i && echo "making dependencies $$i..." && \
		$(MAKE) SDIRS='${SDIRS}' CFLAG='${CFLAG}' DEPFLAG='${DEPFLAG}' MAKEDEPPROG='${MAKEDEPPROG}' KRB5_INCLUDES='${KRB5_INCLUDES}' PERL='${PERL}' depend ) || exit 1; \
	fi; \
	done;

lint:
	@for i in $(DIRS) ;\
	do \
	if [ -d "$$i" ]; then \
		(cd $$i && echo "making lint $$i..." && \
		$(MAKE) SDIRS='${SDIRS}' lint ) || exit 1; \
	fi; \
	done;

tags:
	rm -f TAGS
	find . -name '[^.]*.[ch]' | xargs etags -a

errors:
	$(PERL) util/mkerr.pl -recurse -write
	(cd crypto/engine; $(MAKE) PERL=$(PERL) errors)

stacks:
	$(PERL) util/mkstack.pl -write

util/libeay.num::
	$(PERL) util/mkdef.pl crypto update

util/ssleay.num::
	$(PERL) util/mkdef.pl ssl update

crypto/objects/obj_dat.h: crypto/objects/obj_dat.pl crypto/objects/obj_mac.h
	$(PERL) crypto/objects/obj_dat.pl crypto/objects/obj_mac.h crypto/objects/obj_dat.h
crypto/objects/obj_mac.h: crypto/objects/objects.pl crypto/objects/objects.txt crypto/objects/obj_mac.num
	$(PERL) crypto/objects/objects.pl crypto/objects/objects.txt crypto/objects/obj_mac.num crypto/objects/obj_mac.h

apps/openssl-vms.cnf: apps/openssl.cnf
	$(PERL) VMS/VMSify-conf.pl < apps/openssl.cnf > apps/openssl-vms.cnf

TABLE: Configure
	(echo 'Output of `Configure TABLE'"':"; \
	$(PERL) Configure TABLE) > TABLE

update: depend errors stacks util/libeay.num util/ssleay.num crypto/objects/obj_dat.h apps/openssl-vms.cnf TABLE

# Build distribution tar-file. As the list of files returned by "find" is
# pretty long, on several platforms a "too many arguments" error or similar
# would occur. Therefore the list of files is temporarily stored into a file
# and read directly, requiring GNU-Tar. Call "make TAR=gtar dist" if the normal
# tar does not support the --files-from option.
tar:
	find . -type d -print | xargs chmod 755
	find . -type f -print | xargs chmod a+r
	find . -type f -perm -0100 -print | xargs chmod a+x
	find * \! -path CVS/\* \! -path \*/CVS/\* \! -name CVS \! -name .cvsignore \! -name STATUS \! -name TABLE | sort > ../$(TARFILE).list; \
	$(TAR) $(TARFLAGS) --files-from ../$(TARFILE).list -cvf - | \
	tardy --user_number=0  --user_name=openssl \
	      --group_number=0 --group_name=openssl \
	      --prefix=openssl-$(VERSION) - |\
	gzip --best >../$(TARFILE).gz; \
	rm -f ../$(TARFILE).list; \
	ls -l ../$(TARFILE).gz

tar-snap:
	@$(TAR) $(TARFLAGS) -cvf - \
		`find * \! -path CVS/\* \! -path \*/CVS/\* \! -name CVS \! -name .cvsignore \! -name STATUS \! -name TABLE \! -name '*.o' \! -name '*.a' \! -name '*.so' \! -name '*.so.*'  \! -name 'openssl' \! -name '*test' \! -name '.#*' \! -name '*~' | sort` |\
	tardy --user_number=0  --user_name=openssl \
	      --group_number=0 --group_name=openssl \
	      --prefix=openssl-$(VERSION) - > ../$(TARFILE);\
	ls -l ../$(TARFILE)

dist:   
	$(PERL) Configure dist
	@$(MAKE) dist_pem_h
	@$(MAKE) SDIRS='${SDIRS}' clean
	@$(MAKE) TAR='${TAR}' TARFLAGS='${TARFLAGS}' tar

dist_pem_h:
	(cd crypto/pem; $(MAKE) CC='${CC}' SDIRS='${SDIRS}' CFLAG='${CFLAG}' pem.h; $(MAKE) clean)

#install: all install_docs install_sw

### if ipsec is enabled, include openssl application
ifeq ($(strip $(BUILD_IPSEC_TOOLS)),)
ifeq ($(strip $(BUILD_CERT)),)
# if ipsec and cert are both disabled then install libs only
install: install_libs
else
# if cert is enabled then install app and libs
install: install_app install_libs
endif
else
# if ipsec is enabled then install app and libs
install: install_app install_libs
endif

install_app:
	mkdir -p $(INSTALL_DIR)/bin
	install -m 755 apps/openssl $(INSTALL_DIR)/bin

# Install openssl libs in standard place of /lib instead of /public/lib because
# busybox WGET_HTTPS needs it.  During system bootup, init (which is actually
# busybox) does not know to look in /public/lib.  But header files still 
# follow our build conventions and are installed in $(BCM_FSBUILD_DIR)/public/include/openssl 
install_libs:
	mkdir -p $(INSTALL_DIR)/lib
	install -m 755 libssl.so.0.9.7 $(INSTALL_DIR)/lib
	(cd $(INSTALL_DIR)/lib; rm -f libssl.so; ln -s libssl.so.0.9.7 libssl.so)
	install -m 755 libcrypto.so.0.9.7 $(INSTALL_DIR)/lib
	(cd $(INSTALL_DIR)/lib; rm -f libcrypto.so; ln -s libcrypto.so.0.9.7 libcrypto.so)
	mkdir -p $(BCM_FSBUILD_DIR)/lib
	install -m 755 libssl.so.0.9.7 $(BCM_FSBUILD_DIR)/lib
	(cd $(BCM_FSBUILD_DIR)/lib; rm -f libssl.so; ln -s libssl.so.0.9.7 libssl.so)
	install -m 755 libcrypto.so.0.9.7 $(BCM_FSBUILD_DIR)/lib
	(cd $(BCM_FSBUILD_DIR)/lib; rm -f libcrypto.so; ln -s libcrypto.so.0.9.7 libcrypto.so)
	mkdir -p $(BCM_FSBUILD_DIR)/public/include/openssl
	install -m 755 include/openssl/* $(BCM_FSBUILD_DIR)/public/include/openssl
	
install_sw:
	@$(PERL) $(TOP)/util/mkdir-p.pl $(INSTALL_PREFIX)$(INSTALLTOP)/bin \
		$(INSTALL_PREFIX)$(INSTALLTOP)/lib \
		$(INSTALL_PREFIX)$(INSTALLTOP)/lib/pkgconfig \
		$(INSTALL_PREFIX)$(INSTALLTOP)/include/openssl \
		$(INSTALL_PREFIX)$(OPENSSLDIR)/misc \
		$(INSTALL_PREFIX)$(OPENSSLDIR)/certs \
		$(INSTALL_PREFIX)$(OPENSSLDIR)/private
	@headerlist="$(EXHEADER)"; for i in $$headerlist ;\
	do \
	(cp $$i $(INSTALL_PREFIX)$(INSTALLTOP)/include/openssl/$$i; \
	chmod 644 $(INSTALL_PREFIX)$(INSTALLTOP)/include/openssl/$$i ); \
	done;
	@for i in $(DIRS) ;\
	do \
	if [ -d "$$i" ]; then \
		(cd $$i; echo "installing $$i..."; \
		$(MAKE) CC='${CC}' CFLAG='${CFLAG}' INSTALL_PREFIX='${INSTALL_PREFIX}' INSTALLTOP='${INSTALLTOP}' OPENSSLDIR='${OPENSSLDIR}' EX_LIBS='${EX_LIBS}' SDIRS='${SDIRS}' RANLIB='${RANLIB}' EXE_EXT='${EXE_EXT}' install ); \
	fi; \
	done
	@for i in $(LIBS) ;\
	do \
		if [ -f "$$i" ]; then \
		(       echo installing $$i; \
			cp $$i $(INSTALL_PREFIX)$(INSTALLTOP)/lib/$$i.new; \
			if egrep 'define OPENSSL_FIPS' $(TOP)/include/openssl/opensslconf.h > /dev/null; then \
				: ; \
			else \
				$(RANLIB) $(INSTALL_PREFIX)$(INSTALLTOP)/lib/$$i.new; \
			fi; \
			chmod 644 $(INSTALL_PREFIX)$(INSTALLTOP)/lib/$$i.new; \
			mv -f $(INSTALL_PREFIX)$(INSTALLTOP)/lib/$$i.new $(INSTALL_PREFIX)$(INSTALLTOP)/lib/$$i ); \
		fi; \
	done;
	@if [ -n "$(SHARED_LIBS)" ]; then \
		tmp="$(SHARED_LIBS)"; \
		for i in $${tmp:-x}; \
		do \
			if [ -f "$$i" -o -f "$$i.a" ]; then \
			(       echo installing $$i; \
				if [ "$(PLATFORM)" != "Cygwin" ]; then \
					cp $$i $(INSTALL_PREFIX)$(INSTALLTOP)/lib/$$i.new; \
					chmod 555 $(INSTALL_PREFIX)$(INSTALLTOP)/lib/$$i.new; \
					mv -f $(INSTALL_PREFIX)$(INSTALLTOP)/lib/$$i.new $(INSTALL_PREFIX)$(INSTALLTOP)/lib/$$i; \
				else \
					c=`echo $$i | sed 's/^lib\(.*\)\.dll/cyg\1-$(SHLIB_VERSION_NUMBER).dll/'`; \
					cp $$c $(INSTALL_PREFIX)$(INSTALLTOP)/bin/$$c.new; \
					chmod 755 $(INSTALL_PREFIX)$(INSTALLTOP)/bin/$$c.new; \
					mv -f $(INSTALL_PREFIX)$(INSTALLTOP)/bin/$$c.new $(INSTALL_PREFIX)$(INSTALLTOP)/bin/$$c; \
					cp $$i.a $(INSTALL_PREFIX)$(INSTALLTOP)/lib/$$i.a.new; \
					chmod 644 $(INSTALL_PREFIX)$(INSTALLTOP)/lib/$$i.a.new; \
					mv -f $(INSTALL_PREFIX)$(INSTALLTOP)/lib/$$i.a.new $(INSTALL_PREFIX)$(INSTALLTOP)/lib/$$i.a; \
				fi ); \
			fi; \
		done; \
		(	here="`pwd`"; \
			cd $(INSTALL_PREFIX)$(INSTALLTOP)/lib; \
			set $(MAKE); \
			$$1 -f $$here/Makefile link-shared ); \
		if [ "$(INSTALLTOP)" != "/usr" ]; then \
			echo 'OpenSSL shared libraries have been installed in:'; \
			echo '  $(INSTALLTOP)'; \
			echo ''; \
			sed -e '1,/^$$/d' doc/openssl-shared.txt; \
		fi; \
	fi
	@for i in $(SIGS) ;\
	do \
		if [ -f "$$i" ]; then \
		(       echo installing $$i; \
			cp $$i $(INSTALL_PREFIX)$(INSTALLTOP)/lib/$$i.new; \
			chmod 644 $(INSTALL_PREFIX)$(INSTALLTOP)/lib/$$i.new; \
			mv -f $(INSTALL_PREFIX)$(INSTALLTOP)/lib/$$i.new $(INSTALL_PREFIX)$(INSTALLTOP)/lib/$$i ); \
		fi; \
	done;
	cp openssl.pc $(INSTALL_PREFIX)$(INSTALLTOP)/lib/pkgconfig
	chmod 644 $(INSTALL_PREFIX)$(INSTALLTOP)/lib/pkgconfig/openssl.pc

install_docs:
	@$(PERL) $(TOP)/util/mkdir-p.pl \
		$(INSTALL_PREFIX)$(MANDIR)/man1 \
		$(INSTALL_PREFIX)$(MANDIR)/man3 \
		$(INSTALL_PREFIX)$(MANDIR)/man5 \
		$(INSTALL_PREFIX)$(MANDIR)/man7
	@pod2man="`cd util; ./pod2mantest $(PERL)`"; \
	here="`pwd`"; \
	filecase=; \
	if [ "$(PLATFORM)" = "DJGPP" -o "$(PLATFORM)" = "Cygwin" -o "$(PLATFORM)" = "mingw" ]; then \
		filecase=-i; \
	fi; \
	for i in doc/apps/*.pod; do \
		fn=`basename $$i .pod`; \
		if [ "$$fn" = "config" ]; then sec=5; else sec=1; fi; \
		echo "installing man$$sec/$$fn.$${sec}$(MANSUFFIX)"; \
		(cd `$(PERL) util/dirname.pl $$i`; \
		sh -c "$$pod2man \
			--section=$$sec --center=OpenSSL \
			--release=$(VERSION) `basename $$i`") \
			>  $(INSTALL_PREFIX)$(MANDIR)/man$$sec/$$fn.$${sec}$(MANSUFFIX); \
		$(PERL) util/extract-names.pl < $$i | \
			grep -v $$filecase "^$$fn\$$" | \
			grep -v "[	]" | \
			(cd $(INSTALL_PREFIX)$(MANDIR)/man$$sec/; \
			 while read n; do \
				$$here/util/point.sh $$fn.$${sec}$(MANSUFFIX) "$$n".$${sec}$(MANSUFFIX); \
			 done); \
	done; \
	for i in doc/crypto/*.pod doc/ssl/*.pod; do \
		fn=`basename $$i .pod`; \
		if [ "$$fn" = "des_modes" ]; then sec=7; else sec=3; fi; \
		echo "installing man$$sec/$$fn.$${sec}$(MANSUFFIX)"; \
		(cd `$(PERL) util/dirname.pl $$i`; \
		sh -c "$$pod2man \
			--section=$$sec --center=OpenSSL \
			--release=$(VERSION) `basename $$i`") \
			>  $(INSTALL_PREFIX)$(MANDIR)/man$$sec/$$fn.$${sec}$(MANSUFFIX); \
		$(PERL) util/extract-names.pl < $$i | \
			grep -v $$filecase "^$$fn\$$" | \
			grep -v "[	]" | \
			(cd $(INSTALL_PREFIX)$(MANDIR)/man$$sec/; \
			 while read n; do \
				$$here/util/point.sh $$fn.$${sec}$(MANSUFFIX) "$$n".$${sec}$(MANSUFFIX); \
			 done); \
	done

# DO NOT DELETE THIS LINE -- make depend depends on it.
