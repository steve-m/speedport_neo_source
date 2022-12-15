
SUBDIRS =

SUBDIRS += dynip-3.00
SUBDIRS += ez-ipupdate-3.0.11b8
SUBDIRS += inadyn
SUBDIRS += noip-2.1.9-1

all:
	make applications

applications::

	@for i in ${SUBDIRS} ;  do                                                    \
            echo "-----------------------------------------------------------------"; \
            echo -e "\033[;34m                         $$i                 \033[;0m"; \
            echo "-----------------------------------------------------------------"; \
            make -C $$i || exit 1 ;                     \
            make -C $$i install || exit 1 ;                                      \
	done

install:

clean:
	@for i in $(SUBDIRS) ; do $(MAKE) -C $$i clean || exit 1; done

