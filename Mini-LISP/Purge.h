#ifndef PURGE_H
#define PURGE_H

#define DO(x) DO x OD

#define DO (0,( 
#define OD  ),0) 

#include "Pair.h"
#include "layout.h"
struct {
  Unit preserving(Sx s) { 
    mark(s), sweep();
  }
private:
  Unit mark(Sx s) {
    s.atom() or mark(s.Pair());
  }
  Unit mark(Pair p) {
//    p.seen() or DO mark(p.car()) | mark(p.cdr()), p.visit() OD;
   if (p.seen()) return 0;
   mark(p.car());
   mark(p.cdr());
   p.visit();
  }
  Unit sweep() {
    for (auto s = $P_f$; s <= $P_t$; ++s) 
      consider(Pair(s)); 
  }
  Unit consider(Pair p) {
    extern Unit gobble(Pair);
    p.foreign() or (p.seen() ? (p.unvisit(),0) : gobble(p));
  }
} purge;
#endif
