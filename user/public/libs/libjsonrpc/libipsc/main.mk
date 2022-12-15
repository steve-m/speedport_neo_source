NAME    = libipsc
SOURCES = $(NAME).c priv.c
HEADERS = $(NAME).h priv.h
OBJECTS = $(SOURCES:.c=.o)
SHARED  = $(NAME).so
STATIC  = $(NAME).a


default: all
all: $(SOURCES) $(SHARED) $(STATIC)

.c.o: $(HEADERS)
	$(CC) -c $(CFLAGS) $< -o $@

$(SHARED): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -shared -o $@

$(STATIC): $(OBJECTS)
	$(AR) -rcv $@ $(OBJECTS)
	$(RANLIB) $(STATIC)

install:
	cp -f $(SHARED) $(INSTALLDIR)/lib

clean:
	rm -f *.o
	rm -f $(SHARED)
	rm -f $(STATIC)


.PHONY: default all $(SHARED) $(STATIC) clean
