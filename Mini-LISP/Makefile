OBJS = \
		read.o \
		strings.o \
		pairs.o \
		stack.o  \
		tokenizer.o \
		parser.o \
		fluentons.o \
		a-list.o \
		eval.o \
		out.o 

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
		t-error.o \
		t-defun.o \
		t-apply.o \
		t-eval.o \
		t-book.o \
		t-alist-global-local.o \

SRCS = $(wildcard *.c) $(wildcard *.cc) 

CFLAGS += -MD -MP -w -std=gnu2x


all: test mini-lisp 

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
		rm -fr $(OBJS) mini-lisp test store *.o *.d *~ *.backup memory *.back *.aux *.log delme*

