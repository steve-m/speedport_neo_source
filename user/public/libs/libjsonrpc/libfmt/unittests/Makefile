TESTS = \
	array_next \
	simple_read \
	construct \
	quote_read \
	quote_write \
	substr_key \
	empty_string \
	root_array \
	pretty_dump \
	parser_reserve \
	object_add_del_simple \
	object_add_del \
	object_del \
	object_is \
	load_string \
	load_null_file \
	null \
	bool \
	copy \
	sizes \
	checksum \
	set \
	load_file_w_escape \
	load_file_w_null

TESTS += \
	ezjson/simple_read \
	ezjson/construct

PROJ = ../..

LDFLAGS += \
	-L$(PROJ)/libfmt -lfmt \
	-lrt -lpthread

CFLAGS += \
	-I$(PROJ)/libfmt \
	-I$(PROJ)/jsmn \

DEPENDENCIES = ../libfmt.a

include test.mk
