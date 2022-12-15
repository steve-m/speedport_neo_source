TARGET_PATH=libdaemon-0.14

BUILDIR:=$(shell pwd)/build

all:
	make libdaemon_build

libdaemon_prepare:
	if test -d ./$(TARGET_PATH); then \
		echo $(TARGET_PATH) existing; \
	else \
		tar -zxvf $(TARGET_PATH).tar.gz; \
	fi

libdaemon_build: libdaemon_prepare
	-mkdir -p $(BUILDIR);
	if test -e ./$(TARGET_PATH)/Makefile; then \
		make -C ./$(TARGET_PATH); \
	else \
		cd ./$(TARGET_PATH); \
		echo "ac_cv_func_setpgrp_void=yes" > config.cache; \
		./configure --host=mips-linux --target=mips-linux \
		--config-cache \
		--prefix=/tmp \
		--exec-prefix=/usr/ \
		CC=${CROSS_COMPILE}gcc \
		AR=${CROSS_COMPILE}ar \
		AS=${CROSS_COMPILE}as \
		LD=${CROSS_COMPILE}ld \
		STRIP=${CROSS_COMPILE}strip \
		RANLIB=${CROSS_COMPILE}ranlib; \
		make; \
	fi
	make -C ./$(TARGET_PATH) DESTDIR=$(BUILDIR) install

clean:
	if test -e ./$(TARGET_PATH)/Makefile; then \
		make -C ./$(TARGET_PATH) clean; \
		rm -rf ./$(TARGET_PATH)/Makefile; \
	fi
	rm -rf $(TARGET_PATH);
	rm -rf $(BUILDIR);

install:
	cp -af $(BUILDIR)/usr/lib/libdaemon.so.* $(INSTALL_ROOT)/usr/lib/

