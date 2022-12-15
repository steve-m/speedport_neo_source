
CFLAGS  += -Os -s -Wall -I$(SHARED_APPSPATH)/include -I$(KERNEL_DIR)/include


all: libscnvram.so install

libscnvram.so : sc_nvram.o 
	$(CC) -Os -s -shared -Wl,-soname,libscnvram.so -o libscnvram.so sc_nvram.o 


sc_nvram.o : sc_nvram.c
	$(CC) $(CFLAGS) -fPIC -g -c $^ -o $@

install:
	install -D libscnvram.so $(INSTALLDIR)/lib/libscnvram.so
	$(STRIP) $(INSTALLDIR)/lib/libscnvram.so
	
clean:
	rm -rf *~ *.o *.so
