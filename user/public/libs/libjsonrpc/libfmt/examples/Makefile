SOURCES    = parse.c parse_generic.c \
		generate.c array_next.c data.c delete.c empty_strings.c \
		object_update.c
OBJECTS    = $(SOURCES:.c=.o)
BINARIES   = $(OBJECTS:.o=)
CC         = gcc
CFLAGS     = -Wall -fPIC -O2

JSMNSRC    = ../../jsmn
JSMNINC    = -I$(JSMNSRC)

FMTSRC     = ../../libfmt
FMTLIB     = -L$(FMTSRC) -lfmt
FMTINC     = -I$(FMTSRC)

INCLUDES   = -I../ $(FMTINC) $(JSMNINC)
LDFLAGS    = $(FMTLIB)

all: $(BINARIES)

$(BINARIES): $(OBJECTS)
	$(CC) $(@:=.o) -o $@ $(LDFLAGS)

clean:
	rm -f $(OBJECTS)
	rm -f $(OBJECTS:.o=)

.c.o:
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@
