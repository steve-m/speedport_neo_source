
CUR_PATH = $(shell pwd)

CFLAGS += -Os -Wall -s -fPIC
CFLAGS += -I$(CUR_PATH)/include 
CFLAGS += -I$(SHARED_APPSPATH)/include -I$(SHARED_APPSPATH)/include/sal

LIBSAL_TARGET = libsal.so

LIBSAL_OBJS += wan.o ntp.o arp.o route.o system_info.o update_time.o dhcp6.o ipv6.o
LIBSAL_OBJS += login.o
LIBSAL_OBJS += storage.o 
LIBSAL_OBJS += temp.o lan.o 
LIBSAL_OBJS += wifi.o 


all: $(LIBSAL_TARGET)

$(LIBSAL_TARGET) : $(LIBSAL_OBJS)
	$(CC) $(CFLAGS) -Os -s -shared -fPIC $(LDFLAGS) -o $@ -Wl,-soname,$@ $(LIBSAL_OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<
		
install :
	cp -f $(LIBSAL_TARGET) $(INSTALLDIR)/lib
	
clean:
	rm -rf $(LIBSAL_TARGET) $(LIBSAL_OBJS)

