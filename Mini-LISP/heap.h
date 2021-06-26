#ifndef HEAP_H
#define HEAP_H
#include "chic.h"
#include "Sx.h"
#include "Item.h"
extern Pair require(Sx, Sx); 
extern Item fresh(Short, Short); 
extern Unit free(Item); 

#include "Pristine.h"
#include "Pair.h"
extern Pristine heapify();
extern Pristine heap;
extern Unit gobble(Pair);
Knob crude(); 
#endif
