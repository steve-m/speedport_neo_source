#######################################
ifndef BUILDPATH
export TOPDIR=$(shell pwd)/../../../..
export BUILDPATH = $(TOPDIR)/build/F1

include $(BUILDPATH)/rules.mk
endif
######################################

CFLAGS += -Os  -Wall -s -I$(PRIVATE_APPSPATH)/include -I$(SHARED_APPSPATH)/include -fPIC #-Werror

all: libscutil.so

OBJS=scutil.o lock.o

libscutil.so : $(OBJS)
	$(CC) -Os -s -shared -fPIC -o $@ -Wl,-soname,$@ $^
	
%.o : %.c
	$(CC) $(CFLAGS) -c $^ -o $@

install :
	cp -f *.so $(INSTALLDIR)/lib

clean:
	rm -rf *~ *.o *.so

