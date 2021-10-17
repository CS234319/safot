#import "Pair.h"
#import "layout.h"
Service {
 Unit all() Is(sweep())
 Unit preserving(S s)  Is(mark(s), sweep())
 Capsule(
    Unit mark(S s) 
      Is(s.atom() or mark(s.Pair())) 
    Unit mark(Pair p) 
      Is(p.seen() or do(mark(p.car()) | mark(p.cdr()), p.visit()))
    Unit sweep() {
      for (auto s = $P_f$; s <= $P_t$; ++s) 
        consider(Pair(s)); 
    }
    Unit consider(Pair p) {
      extern Unit collect(Pair);
      p.foreign() or (p.seen() ? (p.leave(),0) : collect(p));
    }
  )
} purge;
