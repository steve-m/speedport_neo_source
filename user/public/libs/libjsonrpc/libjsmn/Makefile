# You can put your build options here
-include config.mk


CFLAGS += -Os -Wall -s -fPIC

LIBJSMN_TARGET = libjsmn.so

LIBJSMN_OBJS = jsmn.o

all: $(LIBJSMN_TARGET)
	
$(LIBJSMN_TARGET) : $(LIBJSMN_OBJS)
	$(CC) -Os -s -shared -fPIC $(CFLAGS) $(LDFLAGS) -o $@ -Wl,-soname,$@ $(LIBJSMN_OBJS)

install :
	cp -f $(LIBJSMN_TARGET) $(INSTALLDIR)/lib
	
clean: 
	rm -rf $(LIBJSMN_TARGET) $(LIBJSMN_OBJS)
