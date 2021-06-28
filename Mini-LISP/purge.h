#ifndef PURGE_H
#define PURGE_H
#define do(...) ((__VA_ARGS__),0); 
#include "Pair.h"
#include "layout.h"
struct {
 Unit preserving(Sx s)  Is(mark(s), sweep())
private:
  Unit mark(Sx s) 
    Is(s.atom() or mark(s.Pair())) 
  Unit mark(Pair p) 
    Is(p.seen() or do(mark(p.car()) | mark(p.cdr()), p.visit()))
  Unit sweep() {
    for (auto s = $P_f$; s <= $P_t$; ++s) 
      consider(Pair(s)); 
  }
  Unit consider(Pair p) {
    extern Unit collect(Pair);
    p.foreign() or (p.seen() ? (p.unvisit(),0) : collect(p));
  }
} purge;
#endif
