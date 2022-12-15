

all:
	@sed -i "/CONFIG_PREFIX=.*/d" ./busybox-1.17.2/config.sc
	@echo "CONFIG_PREFIX=\"$(INSTALL_ROOT)\"" >> ./busybox-1.17.2/config.sc
	cd ./busybox-1.17.2 && cp config.sc .config && cd ..
	cd ./busybox-1.17.2 && touch .config 
	cd ./busybox-1.17.2 && touch .config.old
	cd ./busybox-1.17.2 && make


install:
	cd ./busybox-1.17.2 && make install


clean:
	cd ./busybox-1.17.2 && make clean



