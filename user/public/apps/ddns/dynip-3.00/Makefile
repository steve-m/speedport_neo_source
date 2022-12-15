#################################################################
#								#
# DO NOT MAKE ANY CHANGES TO 'Makefile', use 'Makefile.X' 	#
# instead!							#
#								#
#################################################################
CFLAGS += -Os -s -Wall -I$(KERNEL_DIR)/include -L$(PRIVATE_APPSPATH)/libs/libcrash -lcrash -I$(PRIVATE_APPSPATH)/include
CFLAGS += -DLINUX
MANPATH=$(INSTALL_ROOT)/etc
OSTYPE=-DDYNIP_OSTYPE=6
BINDIR=$(INSTALL_ROOT)/usr/sbin
CFGDIR=$(INSTALL_ROOT)/etc
CFGDIRDEF=-DCFGDIR=\"/tmp\"

all: 	dynipclient dynipadmin

dynipclient.o: dynipclient.c dynipclient.h dynipgbl.h
	$(CC) ${CFLAGS} ${CFGDIRDEF} -c dynipclient.c

dynipclient: dynipclient.o prof.o opt.o log.o
	$(CC) -o dynipclient dynipclient.o prof.o opt.o log.o 
	$(STRIP) dynipclient

dynipadmin.o: dynipadmin.c dynipadmin.h prof.h dynipgbl.h opt.c opt.h log.h
	$(CC) ${OSTYPE} ${CFLAGS} ${CFGDIRDEF} -c dynipadmin.c

dynipadmin: dynipadmin.o prof.o opt.o log.o
	$(CC) -o dynipadmin dynipadmin.o prof.o opt.o log.o 
	$(STRIP) dynipadmin

prof.o: prof.c prof.h
	$(CC) ${CFLAGS} -c prof.c

opt.o: opt.c opt.h
	$(CC) ${CFLAGS} -c opt.c

log.o: log.c log.h
	$(CC) ${CFLAGS} -c log.c

# Copy the MAN pages for the dynipclient and dynipadmin program.
# Must run with ROOT in order to save in the man directory
man:	
	cp ./dynipclient.1 ${MANPATH}/.
	cp ./dynipadmin.1  ${MANPATH}/.
	chmod 444 ${MANPATH}/dynipclient.1
	chmod 444 ${MANPATH}/dynipadmin.1

# copy files to the local binaries directory
install: 
	install -D dynipadmin $(INSTALL_ROOT)/usr/sbin/dynipadmin
	install -D dynipclient $(INSTALL_ROOT)/usr/sbin/dynipclient
	install -D dynip.cfg $(INSTALL_ROOT)/usr/etc/dynip.cfg
	install -D dynip.dom $(INSTALL_ROOT)/usr/etc/dynip.dom

# perform cleanup
clean:
	rm -f *.o dynipclient dynipadmin
