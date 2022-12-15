
SUBDIRS =

SUBDIRS += shared/libs
#SUBDIRS += private/libs
SUBDIRS += public/libs
#SUBDIRS += private/apps
SUBDIRS += public/apps
SUBDIRS += public/apps/lush_conntrackf
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

