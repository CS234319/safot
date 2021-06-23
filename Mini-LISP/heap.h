#ifndef HEAP_H
#define HEAP_H
#include "chic.h"
#include "Item.h"
#include "Sx.h"
extern Pristine heapify();
extern Pristine heap;
extern Cons require(Sx, Sx); 
extern Item fresh(Short, Short); 
extern void free(Item i); 
#endif
