SUBDIR = $(shell pwd)

OBJS = flush_conntrack.ko
	
obj-m:= flush_conntrack.o

all:
	make -C $(KERNEL_DIR) SUBDIRS=$(SUBDIR) modules CROSS_COMPILE=$(CROSS_COMPILE)

install:
	cp $(OBJS) $(INSTALL_ROOT)/lib/modules

clean:
	rm -rf .*.cmd *.o *.mod.c *.ko .tmp_versions *.order *.symvers 


.PHONY: all install clean
