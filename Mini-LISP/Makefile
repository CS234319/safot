OBJS = \
		strings.o \
		pairs.o \
		stack.o  \
		tokenizer.o \
		parser.o \
		fluentons.o \
		a-list.o \
		eval.o \

TEST_OBJS = \
	$(OBJS) \
		dump.o \
		io.o \
		stack-trace.o \
		t-fluentons.cc \
		t-a-list.o  \
		t-apply.o \
		t-ast.o \
		t-basics.o \
		t-eval-cond.o \
		t-evaluate-primitive.o \
		t-eval-atomic.cc \
		t-main.o \
		t-pairs.o \
		t-parser.o \
		t-stack.o \
		t-strings.o \
		t-tokenizer.o \

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

store:
all: test mini-lisp store 

store: layout.o cons.o characters.o
	$(CXX) $(LDFLAGS) -o $@ $^ -lgtest -lpthread

test: $(TEST_OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ -lgtest -lpthread

mini-lisp: 00.o	$(OBJS) 
	$(CXX) $(LDFLAGS) -o $@ $^ 


%.o: %.cc
	$(CXX) $(CFLAGS) $(CPPFLAGS) -c $<

%.o: %.c
	$(CXX) $(CFLAGS)  -c $<

# -include $(SRC:%.c=%.d)

clean:
		rm -fr $(OBJS) mini-lisp test store *.o *.d *~ *.backup memory *.back *.aux *.log

