SOURCES    = libfmt.c ezjson.c fmt_tests.c fmt_priv.c dump.c load.c open_l.c csiphash.c macro_helpers.c
HEADERS    = libfmt.h ezjson.h fmt_priv.h
OBJECTS    = $(SOURCES:.c=.o)
LIBNAME    = libfmt
SHARED     = .so
STATIC     = .a

ifndef RANLIB
	RANLIB = ranlib
endif

default: all
all: $(SOURCES) $(LIBNAME)$(SHARED) $(LIBNAME)$(STATIC)

$(LIBNAME)$(SHARED): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -shared -o $@

$(LIBNAME)$(STATIC): $(OBJECTS) $(JSMNOBJ)
	$(AR) -rcv $@ $(OBJECTS) $(JSMNOBJ)
	$(RANLIB) $(LIBNAME)$(STATIC)

install :
	cp -f $(LIBNAME)$(SHARED) $(INSTALLDIR)/lib

clean:
	rm -f *.o
	rm -f $(LIBNAME)$(SHARED)
	rm -f $(LIBNAME)$(STATIC)

.c.o: $(HEADERS)
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@


.PHONY: default all $(LIBNAME)$(SHARED) $(LIBNAME)$(STATIC)
