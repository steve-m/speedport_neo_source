
AM_CFLAGS = -D_GNU_SOURCE -Wall -Werror -O2 -pipe -fno-stack-protector \
-I$(top_builddir)/../coova/bstring \
-I$(top_builddir)/../coova/src \
-I$(top_builddir)/../chillout

LDADD = \
$(top_builddir)/../coova/src/libchilli.la \
$(top_builddir)/../coova/bstring/libbstring.la \
$(top_builddir)/../chillout/libchillout.la

chillout_la_SOURCES = chillout-mod.c
chillout_la_LDFLAGS = -module -avoid-version
chillout_la_LIBADD = $(LDADD)
pkglib_LTLIBRARIES = chillout.la
pkglibdir = $(libdir)/coova-chilli
