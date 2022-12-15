#################################################################
#								#
# DO NOT MAKE ANY CHANGES TO 'Makefile', use 'Makefile.X' 	#
# instead!							#
#								#
#################################################################
CFLAGS=%cflags%
LIBS=%libs%
MANPATH=%manpath%
OSTYPE=-DDYNIP_OSTYPE=%ostype%
BINDIR=%bindir%
CFGDIR=%cfgdir%
CFGDIRDEF=-DCFGDIR=\"%cfgdir%\"

all: 	dynipclient dynipadmin

dynipclient.o: dynipclient.c dynipclient.h dynipgbl.h
	cc -O ${CFLAGS} ${CFGDIRDEF} -c dynipclient.c

dynipclient: dynipclient.o prof.o opt.o log.o
	cc -o dynipclient dynipclient.o prof.o opt.o log.o ${LIBS}
	strip dynipclient

dynipadmin.o: dynipadmin.c dynipadmin.h prof.h dynipgbl.h opt.c opt.h
	cc -O ${OSTYPE} ${CFLAGS} ${CFGDIRDEF} -c dynipadmin.c

dynipadmin: dynipadmin.o prof.o opt.o
	cc -o dynipadmin dynipadmin.o opt.o prof.o ${LIBS}
	strip dynipadmin

prof.o: prof.c prof.h
	cc -O -c prof.c

opt.o: opt.c opt.h
	cc -O -c opt.c

log.o: log.c log.h
	cc -O -c log.c

# Copy the MAN pages for the dynipclient and dynipadmin program.
# Must run with ROOT in order to save in the man directory
man:	
	cp ./dynipclient.1 ${MANPATH}/.
	cp ./dynipadmin.1  ${MANPATH}/.
	chmod 444 ${MANPATH}/dynipclient.1
	chmod 444 ${MANPATH}/dynipadmin.1

# copy files to the local binaries directory
install: 
	cp ./dynipadmin ${BINDIR}/.
	cp ./dynipclient ${BINDIR}/.
	cp ./dynip.cfg ${CFGDIR}/.
	cp ./dynip.dom ${CFGDIR}/.

# perform cleanup
clean:
	rm -f *.o
