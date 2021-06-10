OBJS = \
	atomic.o \
		a-list.o \
		eval.o \
	  io.o \
		pairs.o \
		parser.o \
		stack.o  \
		strings.o \
		tokenizer.o \

TEST_OBJS = \
	$(OBJS) \
		dump.o \
		io.o \
		stack-trace.o \
		test-a-list.o  \
		test-apply.o \
		test-ast.o \
		test-atomic.cc \
		test-basics.o \
		test-eval-cond.o \
		test-evaluate-primitive.o \
		test-eval-atomic.cc \
		test-main.o \
		test-pairs.o \
		test-parser.o \
		test-stack.o \
		test-strings.o \
		test-tokenizer.o \

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

dump.cc: dump.h

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

