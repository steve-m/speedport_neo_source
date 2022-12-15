
AM_CFLAGS = -D_GNU_SOURCE -Wall -Werror -O2 -pipe -fno-stack-protector \
-I$(top_builddir)/../coova/bstring \
-I$(top_builddir)/../coova/src 

LDADD = \
$(top_builddir)/../coova/src/libchilli.la \
$(top_builddir)/../coova/bstring/libbstring.la 

sbin_PROGRAMS = fonctl

fonctl_SOURCES = fon-api.c
fon_api_la_SOURCES = fon-api-mod.c
fon_api_la_LDFLAGS = -module -avoid-version
fon_api_la_LIBADD = $(LDADD)
pkglib_LTLIBRARIES = fon-api.la
pkglibdir = $(libdir)/coova-chilli
