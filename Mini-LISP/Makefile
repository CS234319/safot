OBJS = mini-lisp.o stack-trace.o main.o tokenizer.o parser.o
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
-include $(SRC:%.c=%.d)

all: mini-lisp test

mini-lisp:	$(OBJS) 
	$(CXX) $(LDFLAGS) -o $@ $^ 

test: test.o tokenizer-test.o parser-test.o
	$(CXX) $(LDFLAGS) -o $@ $^ -lgtest -lpthread

%.o: %.cc %$(DEPDIR)/%.d | $(DEPDIR)
	$(CXX) -MD -MP -c $(CFLAGS) $(CXXFLAGS) $(CPPFLAGS) -o $@ $<

%.o: %.c %$(DEPDIR)/%.d | $(DEPDIR)
	$(CXX) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

clean:
		rm -fr $(OBJS) mini-lisp test *.o *~ *.backup

