#ifndef HEAP_H
#define HEAP_H
#include "chic.h"
#include "Sx.h"
#include "Item.h"
#include "Pristine.h"
#include "Pair.h"
extern Pristine heapify();
extern Pristine heap;
extern Pair require(Sx, Sx); 
extern Item fresh(Short, Short); 
extern void free(Item); 
extern void preserve(Pair); 
#endif
