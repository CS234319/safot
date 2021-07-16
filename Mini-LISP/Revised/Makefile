# CFLAGS += -MD -MP -w -std=gnu2x
#
CFLAGS += -w -std=gnu2x

PRIMITIVES=Short.o Word.o
SERVICES=accounting.o heap.o text.o layout.o 
LISP_TYPES=Handle.o Id.o Item.o Knob.o Pair.o Parser.o Pristine.o Sx.o 
OTHER_TYPES=Pushdown.o Tokenizer.o Parser.o 

TYPES=$(LISP_TYPES) $(OTHER_TYPES)
PRODUCTION=$(PRIMITIVES) $(SERVICES) $(TYPES)
TEST=t-heap.o t-misc.o t-purge.o t-Pushdown.o t-accounting.o 
OBJECTS=$(PRODUCTION) $(TEST)
SOURCES=$(OBJECTS:.o=.cc) 
TARGETS=test .depend

test: # main target

test: $(OBJECTS)  
	$(CXX) $(LDFLAGS) -o $@ $^ -lgtest -lpthread # Link all objects

%.o: %.cc                                      # Compiling individual C++ files into ob
	$(CXX) $(CFLAGS) $(CPPFLAGS) -c $<


FILES=chic.h $(SOURCES) $(OBJECTS:.o=.h) 

depend: .depend Makefile

.depend: $(SOURCES) $(wildcard *.h) 
	@$(CXX) -w -MM $^ > "$@"

include .depend

list:
	@echo $(FILES)

gvim: 
	@gvim $(FILES) Makefile -c make

wc: 
	wc -l chic.h $(FILES) Makefile | sort -n 

clean:
		rm -rf $(TARGETS) $(OBJECTS) *.o *.d *~ *.backup memory *.back *.aux *.log delme* diff
