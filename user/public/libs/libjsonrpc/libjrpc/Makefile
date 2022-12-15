LDFLAGS += -L$(TARGETDIR)/lib -lfmt -lipsc

OPENSSL_DIR = $(PUBLIC_APPSPATH)/libs/openssl-$(OPENSSL_VER)
JSONRPC_DIR = $(PUBLIC_APPSPATH)/libs/libjsonrpc

CFLAGS +=  -D__SC_BUILD__
CFLAGS +=  -I$(JSONRPC_DIR)/libipsc/
CFLAGS +=  -I$(JSONRPC_DIR)/libfmt/
CFLAGS +=  -I$(JSONRPC_DIR)/libjsmn/
CFLAGS +=  -I$(OPENSSL_DIR)/include
CFLAGS +=  -fPIC -fno-builtin-memcmp
include main.mk
