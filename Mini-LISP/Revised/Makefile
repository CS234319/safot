store:

# CFLAGS += -MD -MP -w -std=gnu2x
#
CFLAGS += -w -std=gnu2x

PRIMITIVES=Short.o Word.o
SERVICES=accounting.o heap.o text.o layout.o 
TYPES=Handle.o Id.o Item.o Knob.o Pair.o Parser.o Pristine.o Pushdown.o Sx.o Tokenizer.o 
PRODUCTION=$(PRIMITIVES) $(SERVICES) $(TYPES)
TEST=t-heap.o t-misc.o t-purge.o t-Pushdown.o t-accounting.o 
OBJECTS=$(PRODUCTION) $(TEST)

store: $(OBJECTS) 
	$(CXX) $(LDFLAGS) -o $@ $^ -lgtest -lpthread

FOUND=Mak* chic*.h $(wildcard *.c) $(wildcard *.cc) $(wildcard *.h) 

accounting.o: accounting.h

FILES=chic.h $(OBJECTS:.o=.cc) $(OBJECTS:.o=.h) 

list:
	@echo $(FILES)

gvim: 
	@gvim $(FILES) Makefile -c make

wc: 
	wc -l chic.h $(FILES) Makefile | sort -n 


%.o: %.cc
	$(CXX) $(CFLAGS) $(CPPFLAGS) -c $<

clean:
		rm -rf store $(OBJECTS) *.o *.d *~ *.backup memory *.back *.aux *.log delme*

