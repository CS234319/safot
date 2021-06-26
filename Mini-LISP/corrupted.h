#ifndef CORRUPTED_H
#define CORRUPTED_H
#include "heap.h"

inline Short length() {
  Short result = 0;
  for (auto h = heap; !h.x();  h = h.next()) 
      ++result;
  return result;
}


static struct {
  Boolean something() Is(uncounted() || excess() || asymmetric() || cyclic() || weirdos() || pristines() || items() || pairs()); 
  Boolean uncounted() Is(length() > Pristine::count); 
  Boolean excess()   Is(length() < Pristine::count); 
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
      Expect(Pair::count >= 0);
      Expect(Pair::count  <= $P_n$);
      Expect(Pair::reuse  >= 0);
      Expect(Pair::reuse  >= 0);
      Expect(Pair::miss  >= 0);
      Expect(Pair::count != 0 || Pair::reuse ==0)
      Expect(Pair::count != 0 || Pair::miss ==0)
      short n = 0; 
      for (auto h = $P_f$; h <= $P_t$; ++h) { 
        let c = Pair(h);
        if (!c.ok()) 
          continue;
        ++n;
      }
      Expect(n == Pair::count);
      return false;
    } catch(...) {
      return true;
    }
  }
  Boolean pristines() {
    try {
      Expect(Pristine::count >= 0);
      Expect(Pristine::count <= $P_n$);
      short n = 0; 
      for (auto h = $P_f$; h <= $P_t$; ++h) { 
        let p = Pristine(h);
        if (!p.ok()) 
          continue;
        ++n;
        Expect(n <= Pristine::count);
        Expect (Pristine(p.next()).x() || Pristine(p.next()).ok());
        Expect (Pristine(p.prev()).x() || Pristine(p.prev()).ok());
        if (!Pristine(p.next()).x())  
          Expect(Pristine(p.next()).ok());
        if (!Pristine(p.prev()).x())  
          Expect(Pristine(p.prev()).ok());
      }
      Expect(n == Pristine::count, n, Pristine::count);
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
        Expect(n <= Item::count);
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


