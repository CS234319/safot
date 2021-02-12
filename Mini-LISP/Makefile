PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

OBJS = mini-lisp.o stack-trace.o

ifndef BUILD_MODE
BUILD_MODE = debug
endif

CFLAGS += -Iinclude 
LDFLAGS += -L. 
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

all: mini-lisp

mini-lisp:	$(OBJS) 
	$(CXX) $(LDFLAGS) -o $@ $^ 

test: test.o tokenizer-test.o
	$(CXX) $(LDFLAGS) -o $@ $^ -lgtest -lpthread


%.o:	$(PROJECT_ROOT)%.cpp
	$(CXX) -c $(CFLAGS) $(CXXFLAGS) $(CPPFLAGS) -o $@ $<

%.o:	$(PROJECT_ROOT)%.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

clean:
		rm -fr $(OBJS) mini-lisp test *.o *~ *.backup
