OBJS = atomic.o a-list.o eval.o dump.o strings.o pairs.o stack-trace.o tokenizer.o parser.o stack.o io.o 
TEST_OBJS =test.o  $(OBJS) tokenizer-test.o ast-test.o atomic-test.cc basics-test.o a-list-test.o  stack-test.o strings-test.o pairs-test.o parser-test.o apply-test.o evaluate-primitive-test.o cond-evaluation-test.o stack-trace.o dump.o io.o
SRCS = $(wildcard *.c) $(wildcard *.cc) 

ifndef BUILD_MODE
	BUILD_MODE = debug
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

CFLAGS += -MD -MP -w

all: mini-lisp test

stack-test.cc: stack.cc

dump.cc: dump.h

parser-test.cc: parser.cc

tokenizer-test.cc: tokenizer.cc

%.o: %.cc
	$(CXX) $(CFLAGS) $(CPPFLAGS) -c $<

%.o: %.c
	$(CXX) $(CFLAGS)  -c $<

mini-lisp: mini-lisp.o	$(OBJS) 
	$(CXX) $(LDFLAGS) -o $@ $^ 

test: $(TEST_OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ -lgtest -lpthread

store: store.o
	$(CXX) $(LDFLAGS) -o $@ $^ -lgtest -lpthread


# -include $(SRC:%.c=%.d)

clean:
		rm -fr $(OBJS) mini-lisp test store *.o *.d *~ *.backup memory *.back *.aux *.log

