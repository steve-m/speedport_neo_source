SUBLIBDIRS =


SUBLIBDIRS += libjsmn
SUBLIBDIRS += libfmt
SUBLIBDIRS += libipsc
SUBLIBDIRS += libjrpc

all:    libjsonrpc

libjsonrpc::
	@for i in ${SUBLIBDIRS} ;  do                                                    \
            echo "-----------------------------------------------------------------"; \
            echo -e "\033[;34m                         $$i                 \033[;0m"; \
            echo "-----------------------------------------------------------------"; \
            make -C $$i || exit 1 ;                                                   \
            make -C $$i install || exit 1 ;                                           \
	done

install:
		
clean:	
	@for i in $(SUBLIBDIRS) ; do $(MAKE) -C $$i clean || exit 1; done

