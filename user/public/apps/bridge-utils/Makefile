BRCTLPATH=bridge-utils-1.2

all:    
	make brctl_build
	
brctl_build:
	if test -e ./$(BRCTLPATH)/Makefile; then \
		$(MAKE) -C ./$(BRCTLPATH); \
	else \
		cd ./$(BRCTLPATH); \
    	./configure --host=mips-linux; \
		$(MAKE); \
	fi
	cp ./$(BRCTLPATH)/brctl/brctl $(INSTALL_ROOT)/usr/sbin
	
brctl_clean:
	if test -e ./$(BRCTLPATH)/Makefile; then \
		$(MAKE) -C ./$(BRCTLPATH) clean; \
#		$(RM) -rf ./$(BRCTLPATH)/Makefile; \
	fi

install:

clean:	
	make brctl_clean

