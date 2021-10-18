#import "chic.h"
#import "Pair.cc"
#import "S.h"
#import "Item.h"
#import "Pristine.h"

Module heap {
  extern Pair request(S, S); 
  extern Item fresh(Short, Short); 
  extern Unit free(Item); 
  extern const Pristine& heap;
  extern Pristine reset();
  extern Unit gobble(Pair);
}

#if Implementation

#import "Pristine.h"
#import "Pair.cc"
Module heap {
  Knob crude(); 
}



#import "Short.h"
#import "Word.cc"
#import "Pair.cc"

#import "layout.h"
#import "accounting.h"

Service {
  auto empty() { return first.x(); } 
  Knob pop() {
    not first.x() or panic();  
    Surely(first.prev().x());
    accounting.pop();
    let old = first;
    first = first.next();
    if (!first.x()) first.prev($P_x$);
    return old.handle(); 
  }
  Unit push(Pristine p) {
    accounting.push();
    p.prev($P_x$).next(first); 
    if (!first.x()) first.prev(p);
    first = p;
  }
  Unit pick(Pristine p) {
    Surely(p.ok());
    accounting.pick();
    auto prev = p.prev(), next = p.next();
    if (!prev.x()) prev.next(next); 
    if (!next.x()) next.prev(prev); 
    if (first.handle() == p.handle()) first = next ;
  }
  Unit init() {
    for (Short s = $P_f$ + 1; s <= $P_t$ - 1; ++s) 
      Pristine(s).prev(Pristine(s-1)).next(Pristine(s+1));
    Pristine($P_f$).prev(Pristine()).next(Pristine($P_f$ +1));
    Pristine($P_t$).next(Pristine()).prev(Pristine($P_t$ -1));
    accounting.init($P_n$);
    first = Pristine($P_f$);
  }
  Pristine first;
  private:
    Unit panic() { 
      extern S EXHAUSTED;
      throw EXHAUSTED; 
    }
} $H$;

const Pristine& heap = $H$.first; 

Item fresh(Short s1, Short s2) { 
  Expect(white(s1));
  Expect(white(s2));
  Expect(s2 == $P_x$ || s2 >= $P_f$ && s2 <= $P_t$);
  if ($H$.empty()) throw __LINE__; 
  ++accounting.items;
  return $H$.pop().Item().head(s1).rest(s2);
}

Unit free(Item i) {
  Expect(i.ok());
  $H$.push(Pristine(i.handle())) | --accounting.items;
}
 
#define Count(label,signature,value) (accounting.label() , value)  
static inline auto reuse(Short s) { accounting.reuse(); return Pair(s);  }
static inline auto hit(Word w, Short s) {  
  accounting.hit();
  $H$.pick(Pristine(s)); 
  P[s].l = w.l; 
  return Pair(s);
}

static inline auto miss(Word w) {  
  accounting.miss(); return $H$.pop().Pair(w.s1,w.s2); 
}

static Pair request(Word w, Short s) {
  Expect(Pair::ok(w));
  Expect(s != $P_x$);
  Expect(s >= $P_f$);
  Expect(s <= $P_t$);
  return P[s].l == w.l ? reuse(s) : (++accounting.pairs,Pristine(s).ok()) ? hit(w,s) : miss(w);
}

extern Pristine reset() {
  $H$.init();
  accounting.init($P_n$);
}

static struct {
  Boolean Pristine(Short s) { return ::Pristine(s).ok(); }
} bad;

static Pair request(Word w) {
  return  request(w, w.hash());
}
  
Unit collect(Pair p) { accounting.collect(); 
  Expect(p.ok());
  $H$.push(Pristine(p.handle())) | --accounting.pairs;
}


Module heap {
  Pair request(S car, S cdr) is(request(Word(car.handle(),cdr.handle()))) 
}
#endif
