all: test mini-lisp services
services: tags depend 

.PHONY: all services clean depend wc gvim

HEADERS := $(sort $(filter %.h,$(shell cat .depend)))
MODULES         := $(IMPLEMENTATION) $(TESTERS) $(REPL)  
TEST            := $(IMPLEMENTATION) $(TESTERS)
IMPLEMENTATION  := $(READ) $(ENGINE) $(MACHINE) 
SOURCES         := $(addsuffix .cc,$(MODULES)) 

REPL += 00
REPL += out 
REPL += read 
REPL += basics

ENGINE += eval
ENGINE += a-list
ENGINE += fluentons

READ += tokenizer
READ += stack
READ += parser

MACHINE += strings
MACHINE += pairs
MACHINE += dump

TESTERS += dump
TESTERS += t-fluentons
TESTERS += t-a-list
TESTERS += t-apply
TESTERS += t-ast
TESTERS += t-basics
TESTERS += t-eval-cond
TESTERS += t-evaluate-primitive
TESTERS += t-eval-atomic
TESTERS += t-main
TESTERS += t-pairs
TESTERS += t-parser
TESTERS += t-stack
TESTERS += t-strings
TESTERS += t-tokenizer
TESTERS += t-error
TESTERS += t-defun
TESTERS += t-apply
TESTERS += t-eval
TESTERS += t-book
TESTERS += t-alist-global-local

mini-lisp: $(addsuffix .o,$(MINI-LISP))

IMPLEMENTATION  := $(READ) $(ENGINE) $(MACHINE) 
MINI-LISP       := $(IMPLEMENTATION) $(REPL) 
TEST            := $(IMPLEMENTATION) $(TESTERS)
MODULES         := $(IMPLEMENTATION) $(TESTERS) $(REPL)  
SOURCES         := $(addsuffix .cc,$(MODULES)) 

test: $(addsuffix .o,$(TEST)) 
	$(CXX) $(LDFLAGS) -o $@ $^ -lgtest -lpthread # Link all objects

mini-lisp: $(addsuffix .o,$(MINI-LISP)) 
	$(CXX) $(LDFLAGS) -o $@ $^ 

list:
	@echo "HEADERS        = " $(HEADERS)
	@echo "SOURCES        = " $(SOURCES)
	@echo "MODULES        = " $(MODULES)
	@echo "MINI-LISP      = " $(MINI-LISP)
	@echo "IMPLEMENTATION = " $(IMPLEMENTATION)
	@echo "READ           = " $(READ)
	@echo "REPL           = " $(REPL)
	@echo "TEST           = " $(TEST)
	@echo "TESTERS        = " $(TESTERS)
	@echo "ENGINE         = " $(ENGINE)
	@echo "TESTERS        = " $(TESTERS)

CFLAGS += -MD -MP -w -std=gnu2x

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
	@gvim $(SOURCES) Makefile -c make

clean:
		rm -fr $(OBJS) mini-lisp test store *.o .depend



