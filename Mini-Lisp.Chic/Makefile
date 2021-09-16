default: m t list services test Makefile

00.o: $(MAKEFILE_LIST)
t-main.o: $(MAKEFILE_LIST)

services: tags depend 

.PHONY: default services clean depend wc gvim

MODULES   := $(sort $(MINI-LISP) $(TEST))
SOURCES   := $(addsuffix .cc,$(MODULES)) 
HEADERS 	:= $(sort $(filter %.h,$(shell cat .depend)))


MINI-LISP = 00 dump $(REPL)  
TESTER    = t-main dump $(TESTS) $(REPL)
REPL      = repl $(READ) $(EVALUATE) $(PRINT)
EVALUATE  = $(ENGINE) $(MACHINE) 

MACHINE  	=  fluentons S pairs strings
ENGINE    =  eval builtin a-list except
PRINT    	=  print recorder
READ      =  parser read stack tokenizer

TESTS = dump t-a-list t-alist-global-local t-apply t-ast t-basics t-book t-defun 
TESTS += t-error t-kernel t-eval t-eval-atomic t-eval-cond t-evaluate-primitive t-fluentons t-pairs 
TESTS += t-parser t-repl t-stack t-strings t-tokenizer

t: $(addsuffix .o,$(TESTER)) 
	$(CXX) $(LDFLAGS) -o $@ $^ -lgtest -lpthread # Link all objects

m: $(addsuffix .o,$(MINI-LISP)) 
	$(CXX) $(LDFLAGS) -o $@ $^ 

test: t
	./$^ --gtest_filter="*" 

list:
	@echo "ENGINE        = " $(ENGINE)
	@echo "MACHINE        = " $(ENGINE)
	@echo "EVALUATE       = " $(EVALUATE)
	@echo "READ           = " $(READ)
	@echo "PRINT          = " $(READ)
	@echo "REPL           = " $(REPL)
	@echo "TESTS          = " $(TEST)

#	@echo "TESTER         = " $(TESTERS)
#	@echo "MODULES        = " $(MODULES)
#	@echo "HEADERS        = " $(HEADERS)
#	@echo "SOURCES        = " $(SOURCES)


ifdef WORK_AROUND
CFLAGS += -DWORK_AROUND

endif

CFLAGS += -w -std=gnu2x -g

%.o: %.cc                                      # Compiling individual C++ files into ob
	$(CXX) $(CFLAGS) $(CPPFLAGS) -c $<

depend: .depend $(SOURCES) $(HEADERS)

.depend: $(SOURCES) $(wildcard *.h) 
	@$(CXX) -w -MM $^ > "$@"

include .depend

tags:   $(SOURCES)
	@ctags $(SOURCES) > $@

wc: 
	@wc -l $(addsuffix .cc,$(MINI-LISP)) | sort -n 
	@wc -l $(addsuffix .cc,$(TESTERS)) | sort -n 

gvim: 
	@gvim $(HEADERS) $(SOURCES) Makefile -c make

clean:
		rm -fr $(OBJS) ml tester *.o *~ .depend
