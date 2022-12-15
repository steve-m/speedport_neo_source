LIB  = libsrv.so
OBJS = libsrv.o patch.o musl_dn_expand.o
TOP_DIR = $(shell pwd)

CFLAGS += -I$(TOP_DIR)/include -I$(TOP_DIR)/include/arpa

all: install

clean: generic_clean uninstall
	rm -f *.o *.so example/libsrv.so*
	rm -f $(BUILD_DIR)/userspace/public/include/libsrv.h
	rm -f ./include/libsrv.h
	rm -f $(BCM_DIR)/libsrv.so

%.o.%.c:
	$(CC) $(CFLAGS) -c $^

libsrv.so: $(OBJS)
	$(CC) -shared -Iinclude -Wl,--whole-archive,-soname,$@ -o $@ $(OBJS) -lc -Wl,--no-whole-archive
# Remove -lresolv	
# uclibc libresolv is stub, don't link it just put the functions we need in patch.c
#	$(CC) -shared -Iinclude -o libsrv.so libsrv.c -lc -lresolv
ifeq ($(PRODUCT_TYPE), VD168)
install: $(LIB)
	install libsrv.h $(BUILD_DIR)/userspace/public/include
	install libsrv.h ./include
	@echo "VD168 Melinda libsrv Makefile Copy libsrv.so to $(BCM_DIR)..."
	install libsrv.so $(BCM_DIR)/
	@echo "VD168 Melinda libsrv Makefile Copy libsrv.so to $(BCM_DIR) done"


#	@echo "Melinda --- Copy libsrv.so to $(FS_DIR)/lib..."
#	cp -af $(BCM_DIR)/libsrv.so $(FS_DIR)/lib/
#	@echo "Melinda --- Create symbolic link to  $(FS_DIR)/lib/libsrv.so ..."
#	ln -sf libsrv.so   $(FS_DIR)/lib/libsrv.so.1
#	ln -sf libsrv.so.1 $(FS_DIR)/lib/libsrv.so.1.0
#	@echo "Melinda --- Create symbolic link to  $(FS_DIR)/lib/libsrv.so done"

#	install -d $(TARGETDIR)/lib
#	install libsrv.so $(TARGETDIR)/lib/
#	$(STRIP) $(TARGETDIR)/lib/libsrv.so
#	rm -f $(TARGETDIR)/lib/libsrv.so.1 $(TARGETDIR)/lib/libsrv.so.1.0
#	ln -s libsrv.so   $(TARGETDIR)/lib/libsrv.so.1
#	ln -s libsrv.so.1 $(TARGETDIR)/lib/libsrv.so.1.0


uninstall:
	@echo 'libsrv uninstall BCM_DIR=$(BCM_DIR)'
	@echo 'FS_DIR=$(FS_DIR)'
	rm -f $(INSTALL_DIR)/lib/public/$(LIB)
	rm -f $(BCM_DIR)/lib/libsrv.so*
	rm -f $(FS_DIR)/lib/libsrv.so*
else
ifeq ($(PRODUCT_TYPE), F1)
install: $(LIB)
	install libsrv.h $(BUILD_DIR)/userspace/public/include
	install libsrv.h ./include
	@echo "F1 Melinda libsrv Makefile Copy libsrv.so to $(INSTALLDIR)/lib/..."
	install libsrv.so $(BUILD_DIR)/bin/
	install libsrv.so $(INSTALLDIR)/lib/
	@echo "F1 Melinda libsrv Makefile Copy libsrv.so to $(INSTALLDIR)/lib/ done"


#	@echo "Melinda --- Copy libsrv.so to $(FS_DIR)/lib..."
#	cp -af $(BUILD_DIR)/userspace/public/libs/libsrv/libsrv.so $(FS_DIR)/lib/
#	@echo "Melinda --- Create symbolic link to  $(FS_DIR)/lib/libsrv.so ..."
#	ln -sf libsrv.so   $(FS_DIR)/lib/libsrv.so.1
#	ln -sf libsrv.so.1 $(FS_DIR)/lib/libsrv.so.1.0
#	@echo "Melinda --- Create symbolic link to  $(FS_DIR)/lib/libsrv.so done"

#	install -d $(TARGETDIR)/lib
#	install libsrv.so $(TARGETDIR)/lib/
#	$(STRIP) $(TARGETDIR)/lib/libsrv.so
#	rm -f $(TARGETDIR)/lib/libsrv.so.1 $(TARGETDIR)/lib/libsrv.so.1.0
#	ln -s libsrv.so   $(TARGETDIR)/lib/libsrv.so.1
#	ln -s libsrv.so.1 $(TARGETDIR)/lib/libsrv.so.1.0


uninstall:
	@echo 'libsrv uninstall BCM_DIR=$(BCM_DIR)'
	@echo 'FS_DIR=$(FS_DIR)'
	rm -f $(INSTALL_DIR)/lib/public/$(LIB)
	rm -f $(BUILD_DIR)/bin/libsrv.so*
	rm -f $(FS_DIR)/lib/libsrv.so*
else
ifeq ($(PRODUCT_TYPE), Entry2)
install: $(LIB)
	install libsrv.h $(BUILD_DIR)/userspace/public/include
	install libsrv.h ./include
	@echo "Entry2 libsrv Makefile Copy libsrv.so to $(INSTALLDIR)/lib/..."
	install libsrv.so $(BUILD_DIR)/bin/
	install libsrv.so $(INSTALLDIR)/lib/
	@echo "Entry2 libsrv Makefile Copy libsrv.so to $(INSTALLDIR)/lib/ done"

uninstall:
	@echo 'libsrv uninstall BCM_DIR=$(BCM_DIR)'
	@echo 'FS_DIR=$(FS_DIR)'
	rm -f $(INSTALL_DIR)/lib/public/$(LIB)
	rm -f $(BUILD_DIR)/bin/libsrv.so*
	rm -f $(FS_DIR)/lib/libsrv.so*
endif
endif
endif

include $(BUILD_DIR)/make.common
include $(BUILD_DIR)/sc.mak
