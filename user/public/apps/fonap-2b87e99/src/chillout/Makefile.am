
chilloutincludedir = $(includedir)/chillout
chilloutinclude_HEADERS = chillout.h

lib_LTLIBRARIES = libchillout.la
sbin_PROGRAMS = chilloutd chillout-client
# chillout-client

libchillout_la_SOURCES = chillout.c log.c poption.c

AM_CFLAGS = -Wall -fno-builtin -fno-strict-aliasing -O2 -fomit-frame-pointer -funroll-loops -pipe \
 -DDEFPIDFILE='"$(localstatedir)/run/chillout.pid"'

chilloutd_SOURCES= chilloutd.c

LDADD = libchillout.la -ldaemon

chillout_client_SOURCES= chillout-client.c

