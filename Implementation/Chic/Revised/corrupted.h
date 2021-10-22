#import "layout.h"

#import "heap.cc"
#import "accounting.cc"

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
      expecting(
          accounting.pairs >= 0, 
          accounting.pairs  <= $P_n$, 
          accounting.reuse  >= 0,
          accounting.reuse  >= 0, 
          accounting.miss >= 0, 
          accounting.pairs != 0 || accounting.reuse ==0, 
          accounting.pairs != 0 || accounting.miss ==0
      )
      short n = 0; 
      for (auto h = $P_f$; h <= $P_t$; ++h) { 
        let c = Pair(h);
        if (!c.ok()) 
          continue;
        ++n;
      }
      expecting(n == accounting.pairs)
      return false;
    } catch(...) {
      return true;
    }
  }
  Boolean pristines() {
    try {
      expecting(accounting.unused >= 0, accounting.unused <= $P_n$)
      short n = 0; 
      for (auto h = $P_f$; h <= $P_t$; ++h) { 
        let p = Prisitine.hande;
        if (!p.ok()) 
          continue;
        ++n;
        expecting(
            n <= accounting.unused, 
            Pristine(p.next()).x() || Pristine(p.next()).ok(), 
            Pristine(p.prev()).x() || Pristine(p.prev()).ok()
        )
      }
      expecting(n == accounting.unused, n, accounting.unused);
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
        if (!i.ok()) continue;
        ++n;
        expecting(
            Item(i.rest()).x() || Item(i.rest()).ok() 
            n <= accounting.items
        )
        if (!Item(i.rest()).x())  
          expecting(Item(i.rest()).ok());
      }
      return false;;
    } catch(...) {
      return true;
    }
  }
  private:
} corrupted;
