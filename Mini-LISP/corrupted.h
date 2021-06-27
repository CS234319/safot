#ifndef CORRUPTED_H
#define CORRUPTED_H
#include "heap.h"

#include "accounting.h"

inline Short length() {
  Short result = 0;
  for (auto h = heap; !h.x();  h = h.next()) 
      ++result;
  return result;
}


static struct {
  Boolean something() Is(uncounted() || excess() || asymmetric() || cyclic() || weirdos() || pristines() || items() || pairs()); 
  Boolean uncounted() Is(length() > accounting.unused); 
  Boolean excess()   Is(length() < accounting.unused); 
  Boolean cyclic() {
    if (!heap.x())
      for (auto h = heap, h2 = heap.next(); !h2.x(); h = h.next()) { 
        if (h.handle() == h2.handle()) 
          return true;
        if (!h2.x()) h2 = h2.next();
        if (!h2.x()) h2 = h2.next();
      }
    return false;
  }
  Boolean weirdos() {
    for (auto h = $P_f$; h <= $P_t$; ++h) 
      if (Knob(h).weirdo()) 
        return true;
    return false;
  }  
  Boolean asymmetric() {
    for (auto p = heap; !p.x(); p = p.next()) { 
      if (!p.prev().x() && p.prev().next().handle() != p.handle()) 
        return true;
      if (!p.next().x() && p.next().prev().handle() != p.handle()) 
        return true;
    }
    return false;
  }
  Boolean pairs() {
    try {
      Expect(accounting.pairs >= 0);
      Expect(accounting.pairs  <= $P_n$);
      Expect(accounting.reused  >= 0);
      Expect(accounting.reused  >= 0);
      Expect(accounting.missed >= 0);
      Expect(accounting.pairs != 0 || accounting.reused ==0)
      Expect(accounting.pairs != 0 || accounting.missed ==0)
      short n = 0; 
      for (auto h = $P_f$; h <= $P_t$; ++h) { 
        let c = Pair(h);
        if (!c.ok()) 
          continue;
        ++n;
      }
      Expect(n == accounting.pairs);
      return false;
    } catch(...) {
      return true;
    }
  }
  Boolean pristines() {
    try {
      Expect(accounting.unused >= 0);
      Expect(accounting.unused <= $P_n$);
      short n = 0; 
      for (auto h = $P_f$; h <= $P_t$; ++h) { 
        let p = Pristine(h);
        if (!p.ok()) 
          continue;
        ++n;
        Expect(n <= accounting.unused);
        Expect (Pristine(p.next()).x() || Pristine(p.next()).ok());
        Expect (Pristine(p.prev()).x() || Pristine(p.prev()).ok());
        if (!Pristine(p.next()).x())  
          Expect(Pristine(p.next()).ok());
        if (!Pristine(p.prev()).x())  
          Expect(Pristine(p.prev()).ok());
      }
      Expect(n == accounting.unused, n, accounting.unused);
      return false;
    } catch(...) {
      return true;
    }
  }
  Boolean items() {
    try {
      Short  n = 0; 
      for (auto h = $P_f$; h <= $P_t$; ++h) { 
        let i = Item(h);
        if (!i.ok()) 
          continue;
        ++n;
        Expect(Item(i.rest()).x() || Item(i.rest()).ok());
        Expect(n <= accounting.items);
        if (!Item(i.rest()).x())  
          Expect(Item(i.rest()).ok());
      }
      return false;;
    } catch(...) {
      return true;
    }
  }
  private:
} corrupted;
#endif


