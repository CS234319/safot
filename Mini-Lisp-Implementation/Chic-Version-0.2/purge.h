#import "chic.h"
#import "S.cc"
#import "Pair.cc"
#import "layout.h"
Service {
 Unit all() is(sweep())
 Unit preserving(S s)  is((mark(s), sweep()))
 Capsule(
    Unit mark(S s) 
      is(s.atom() or mark(Pair(s))) 
    Unit mark(Pair p) 
      is(p.seen() or do(mark(S(p.s1())) | mark(S(p.s2())), p.visit()))
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
