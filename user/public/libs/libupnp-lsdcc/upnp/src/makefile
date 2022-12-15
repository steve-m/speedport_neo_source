###########################################################################
##
## Copyright (c) 2000-2003 Intel Corporation 
## All rights reserved. 
##
## Redistribution and use in source and binary forms, with or without 
## modification, are permitted provided that the following conditions are met: 
##
## * Redistributions of source code must retain the above copyright notice, 
## this list of conditions and the following disclaimer. 
## * Redistributions in binary form must reproduce the above copyright notice, 
## this list of conditions and the following disclaimer in the documentation 
## and/or other materials provided with the distribution. 
## * Neither name of Intel Corporation nor the names of its contributors 
## may be used to endorse or promote products derived from this software 
## without specific prior written permission.
## 
## THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
## ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
## LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR 
## A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL INTEL OR 
## CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
## EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
## PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
## PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY 
## OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
## NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
## SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
##
###########################################################################
ifdef TARGET
DIR_PATH=$(TARGET)
endif

ifeq ($(DEBUG),1)
TARGET_OUTPUT=../bin/debug/$(DIR_PATH)/libupnp_lsdcc.so
else
TARGET_OUTPUT=../bin/$(DIR_PATH)/libupnp_lsdcc.so
endif



ifndef JAVA_DIR
JAVA_DIR= /usr/java/jdk1.3
endif

SUBDIRS = ssdp soap genlib gena urlconfig api uuid
LIBS = -L$(INSTALLDIR)/lib
#ifeq ($(JNI),1)
#LIBS+= $(PRIVATE_APPSPATH)/libs/libixml/libixml.so
#SUBDIRS += jni
#endif

#ifeq ($(EFENCE),1)
#LIBS+= -lefence  
#endif

INCLUDES = -I inc -I ../inc -I inc/tools

#Add by Jeff Sun - Aug,11,2005 - for support nvram in upnp lib
#INCLUDES += -I ../../../nvram

C2FLAGS = -Wall $(DEFS) -shared -Wl,-soname,libupnp_lsdcc.so

ifeq ($(DEBUG),1)
DBG=DEBUG=1
LIBS += -L../bin/debug/$(DIR_PATH) -lthreadutil_lsdcc_dbg -lixml
LIBS += -lapcfg -lutility -lscnvram -lnvram -ldummy_nvram -lscfg -lmd5 -lmutex -lcrypt -lvoipuser 
LIBS += -lcal -lcml_api -lservicectrl -lrcl -lm -lsal -lswitch_api -ldns -ldualimage -lcron_api -liptv -lusb

LIBDEPS += ../bin/debug/$(DIR_PATH)/libthreadutil_lsdcc_dbg.so
OBJECT_DIR = lib/debug/$(DIR_PATH)/
else
DBG=
LIBS += -L../bin/$(DIR_PATH) -lthreadutil_lsdcc -lixml
LIBDEPS += ../bin/$(DIR_PATH)/libthreadutil_lsdcc.so
OBJECT_DIR = lib/$(DIR_PATH)/
endif

OBJECTS = $(OBJECT_DIR)api.o $(OBJECT_DIR)/ssdp.o $(OBJECT_DIR)/soap.o $(OBJECT_DIR)/uuid.o\
	$(OBJECT_DIR)/miniserverall.o $(OBJECT_DIR)/service_table.o \
	$(OBJECT_DIR)/uriall.o $(OBJECT_DIR)/client_table.o $(OBJECT_DIR)/utilall.o \
	$(OBJECT_DIR)/netall.o $(OBJECT_DIR)/httpall.o $(OBJECT_DIR)/urlconfigall.o \
	$(OBJECT_DIR)/gena.o

#Add by Jeff Sun - Aug,11,2005 - for support nvram in upnp lib
#OBJECTS += ../../../nvram/nvram.o

ifeq ($(JNI),1)
OBJECTS += lib/jniupnpall.o
endif

ifeq ($(STATIC),1)
all: $(LIBDEPS)
	@set -e; for i in $(SUBDIRS); do $(MAKE) -C $$i $(DBG); done
	$(AR) r ../bin/libupnp_lsdcc.a $(OBJECTS)
else
all: 
	@set -e; for i in $(SUBDIRS); do $(MAKE) -C $$i $(DBG); done
	$(CC) $(C2FLAGS) $(OBJECTS) -o $(TARGET_OUTPUT) $(LD_PATH) $(LIBS)
endif


clean:
	@set -e; for i in $(SUBDIRS); do $(MAKE) -C $$i clean; done

