all: test services
services: tags .depend 
.PHONY: all services clean wc gvim list

CFLAGS += -w -std=gnu2x -fmax-errors=10

PRIMITIVES=Short Word
SERVICES=accounting heap text layout 
TYPES=Handle Id Item Knob Pair Pristine S 
READ=Pushdown lexer LL parser 
TESTERS=t-heap t-misc t-purge t-Pushdown t-accounting t-lexer t-parser

CORE            := $(PRIMITIVES) $(SERVICES) $(TYPES) $(READ)  
TEST            := $(CORE) $(TESTERS)
MODULES         := $(PRIMITIVES) $(SERVICE) $(TYPES) $(TEST)

SOURCES         := $(addsuffix .cc,$(MODULES)) 
HEADERS         := $(sort $(filter %.h,$(shell cat .depend 2> /dev/null)))

test: $(addsuffix .o,$(TEST))
	$(CXX) $(LDFLAGS) -o $@ $^ -lgtest -lpthread 

%.o: %.cc                                      # Compiling individual C++ files into ob
	$(CXX) $(CFLAGS) $(CPPFLAGS) -c $<

.depend: $(SOURCES)  $(HEADERS)
	@$(CXX) -w -MM $^ > "$@"

include .depend

tags: $(SOURCES) $(HEADERS)
	@ctags $(SOURCES) > $@

list:
	@echo "HEADERS        = " $(HEADERS)
	@echo "SOURCES        = " $(SOURCES)

gvim: 
	@gvim $(SOURCES) $(HEADERS) Makefile -c make -c cwindow

wc: 
	@wc -l $(SOURCES) $(HEADERS) Makefile | sort -n 

clean:
		rm -rf $(TARGETS) $(OBJECTS) *.o *.d *~ *.backup memory *.back *.aux *.log delme* diff .depend test
