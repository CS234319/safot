#import "layout.h"

#import "heap.cc"
#import "accounting.cc"
#import "Pristine.cc"
#import "Item.cc"

inline Short length() {
  Short result = 0;
  for (auto h = heap::first; not h.x();  h = h.next()) 
      ++result;
  return result;
}

static struct {
  Boolean something() is(uncounted() or excess() or asymmetric() or cyclic() or weirdos() or pristines() or items() or pairs()); 
  Boolean uncounted() is(length() > accounting.unused); 
  Boolean excess()   is(length() < accounting.unused); 
  Boolean cyclic() {
    if (!heap::first.x())
      for (auto h = heap::first, h2 = heap::first.next(); !h2.x(); h = h.next()) { 
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
    for (auto p = heap::first; !p.x(); p = p.next()) { 
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
          accounting.pairs != 0 or accounting.reuse ==0, 
          accounting.pairs != 0 or accounting.miss ==0
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
        let p = Pristine(h);
        if (not p.ok()) 
          continue;
        ++n;
        expecting(
            n <= accounting.unused, 
            Pristine(p.next()).x() or Pristine(p.next()).ok(), 
            Pristine(p.prev()).x() or Pristine(p.prev()).ok()
        )
      }
      expecting(n == accounting.unused)
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
            Item(i.rest()).x() or Item(i.rest()).ok(),
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
