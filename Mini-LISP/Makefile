OBJS = mini-lisp.o strings.o pairs.o stack-trace.o main.o tokenizer.o parser.o stack.o
SRCS = $(wildcard *.c) $(wildcard *.cc) 

ifndef BUILD_MODE
	BUILD_MODE = run
endif

ifeq ($(BUILD_MODE),debug)
	CFLAGS += -g
else ifeq ($(BUILD_MODE),run)
	CFLAGS += -O2
else ifeq ($(BUILD_MODE),linuxtools)
	CFLAGS += -g -pg -fprofile-arcs -ftest-coverage
	LDFLAGS += -pg -fprofile-arcs -ftest-coverage
else
    $(error Build mode $(BUILD_MODE) not supported by this Makefile)
endif

CFLAGS += -MD -MP 

all: mini-lisp test

stack-test.cc: stack.cc

parser-test.cc: parser.cc

%.o: %.cc
	$(CXX) $(CFLAGS) $(CPPFLAGS) -c $<

%.o: %.c
	$(CXX) $(CFLAGS)  -c $<

mini-lisp:	$(OBJS) 
	$(CXX) $(LDFLAGS) -o $@ $^ 

test: test-main.o test.o tokenizer-test.o strings-test.o pairs-test.o parser-test.o stack-test.o stack-trace.o
	$(CXX) $(LDFLAGS) -o $@ $^ -lgtest -lpthread

-include $(SRC:%.c=%.d)

clean:
		rm -fr $(OBJS) mini-lisp test *.o *.d *~ *.backup 

