CFLAGS += \
	-g3 \
	-Wall

TIMEOUT ?= 2

ifneq ($(wildcard /usr/bin/valgrind),)
	VG ?= yes
endif

ifeq ($(VG),yes)
	vgparams = -q \
	           --error-exitcode=13 \
	           --leak-check=$(VG) \
	           --leak-resolution=high \
	           --track-origins=yes
else
	vgparams = --error-exitcode=13 $(VG)
endif

ifneq ($(VG),no)
	vgcmd = valgrind $(vgparams)
endif

test_list    = $(addprefix test_,    $(TESTS))
testobjs     = $(addsuffix /test.o,  $(test_list))
testapps     = $(addsuffix /test,    $(test_list))
testresults  = $(addsuffix /result,  $(test_list))
testcores    = $(addsuffix /core,    $(test_list))
testvgcores  = $(addsuffix /vgcore.*,$(test_list))
testrun      = $(addsuffix /run,     $(test_list))

all: build run

build: $(testapps)

run: $(testrun)

$(testobjs): $(DEPENDENCIES)

.c.o:
	@echo Compiling $<
	@rm -f $@
	-@$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

test_%/test: test_%/test.o
	@echo "Linking  " $<
	@rm -f $@
	-@$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

define store_exit_code
	new_exit_code=$$? ; \
	if [ "$$exit_code" -eq "0" ] ; then \
		exit_code=$$new_exit_code ; fi
endef

define print_result
	case $$exit_code in \
		0   ) \
			/usr/bin/printf \
			    "\u2517 %40s\033[1;32mPASSED   \u2714\033[m \u251B\n" "" ;; \
		13  ) \
			/usr/bin/printf \
			    "\u2517 %40s\033[1;33mVALGRIND \u2718\033[m \u251B\n" "" ;; \
		124 ) \
			/usr/bin/printf \
			    "\u2517 %40s\033[1;33mTIMEOUT  \u2718\033[m \u251B\n" "" ;; \
		139 ) \
			/usr/bin/printf \
			    "\u2517 %40s\033[1;31mSEGFAULT \u2718\033[m \u251B\n" "" ;; \
		*   ) \
			/usr/bin/printf \
			    "\u2517 %40s\033[1;31mFAILURE  \u2718\033[m \u251B\n" "" ;; \
	esac
endef

define cmp_result
	diff -u expected result ; \
	$(store_exit_code)
endef

define exec_test
	ulimit -c unlimited; timeout $(TIMEOUT) $(vgcmd) ./test ; \
	$(store_exit_code)
endef

test_%/run:
	@/usr/bin/printf \
		"\u250F Running test:   \033[1m%-34s\033[m \u2513\n" \
		$(subst test_,,$(subst /run,,$@))
	@rm -f $(subst /run,/result,$@)
	-@( \
	   cd $(subst /run,,$@) ; \
	   exit_code=0 ; \
	   $(exec_test) ; \
	   $(cmp_result) ; \
	   $(print_result) \
	  )

clean:
	rm -f $(testobjs) \
	      $(testapps) \
	      $(testresults) \
	      $(testcores) \
	      $(testvgcores)

.PHONY: clean all build run
.PRECIOUS: $(testresults)
