CFLAGS += -Os -s -Wall -Werror -fPIC
CFLAGS += -I$(SHARED_APPSPATH)/include

LIBCAL_TARGET = libscevt.so
LIBCAL_OBJS = sc_event_c.o

all: $(LIBCAL_TARGET) 

$(LIBCAL_TARGET): $(LIBCAL_OBJS)
	$(CC) -Os -s -shared -fPIC  -Wl,-soname,$@ -o $@ $(LIBCAL_OBJS)

install:
	cp -f $(LIBCAL_TARGET) $(INSTALLDIR)/lib

	
clean:
	rm -f $(LIBCAL_TARGET) $(LIBCAL_OBJS)
	
