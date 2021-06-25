#ifndef HEAP_H
#define HEAP_H
#include "chic.h"
#include "Sx.h"
#include "Item.h"
#include "Pristine.h"
#include "Cons.h"
extern Pristine heapify();
extern Pristine heap;
extern Cons require(Sx, Sx); 
extern Item fresh(Short, Short); 
extern void free(Item); 
extern void preserve(Cons); 
#endif
