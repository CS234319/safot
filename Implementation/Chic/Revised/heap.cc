#import "chic.h"
/**
Context	::=	Assertion
Assertion	::=	Expectation | Assertion
Handle	::=	Pair | S
Pair	  ::=	Knob
Knob	::=	Item | Pristine
S	::=	Cons | Id
*/ 
Type Pair below
Type Item below
Type Item below
Type Pristine below
Type Knob below
Type S below
Type Cons below


Module heap {
  Provides const Pristine& heap below
  Provides Item fresh(Short, Short) below 
  Provides Cons request(S, S) below 
  Provides Pristine reset() below
  Provides Unit free(Item) below 
  Provides Unit gobble(Pair) below
  Provides Knob crude() below 
}

// Handle -> {S -> {Cons, Id},  Pair -> Knob -> {Item,  Pristine,  } }


#if Implementation
#import "accounting.cc"
#import "Item.cc"
#import "Knob.cc"
#import "layout.h"
#import "Pair.cc"
#import "Pristine.cc"
#import "S.cc"
#import "Short.h"
#import "Word.cc"

Service {
  Pristine first;
  auto empty() { return first.x(); } 
  Knob pop() {
    expecting(not first.x(), first.prev().x());
    accounting.pop();
    let pop = first;
    first = first.next();
    if (not first.x()) first.prev(Pristine($P_x$));
    return pop; 
  }
  Unit push(Pristine p) {
    accounting.push();
    p.prev(Pristine($P_x$)).next(first); 
    if (!first.x()) first.prev(p);
    first = p;
  }
  Unit pick(Pristine p) {
    expecting(p.ok());
    accounting.pick();
    auto prev = p.prev(), next = p.next();
    if (!prev.x()) prev.next(next); 
    if (!next.x()) next.prev(prev); 
    if (first.handle() == p.handle()) first = next ;
  }
  Unit reset() {
    for (Short s = $P_f$ + 1; s <= $P_t$ - 1; ++s) 
      Pristine(s).prev(Pristine(s-1)).next(Pristine(s+1));
    Pristine($P_f$).prev(Pristine()).next(Pristine($P_f$ +1));
    Pristine($P_t$).next(Pristine()).prev(Pristine($P_t$ -1));
    accounting.reset($P_n$);
    first = Pristine($P_f$);
  }
  private:
    Unit panic() { 
      extern S EXHAUSTED;
      throw EXHAUSTED; 
    }
} $H$;

#include "Cons.cc"

static inline Cons reuse(Short s) { accounting.reuse(); is(Cons(s))  }

static inline Cons hit(Word w, Short s) {  
  accounting.hit();
  $H$.pick(Pristine(s)); 
  P[s].l = w.l; 
  return Cons(s);
}

static inline Cons miss(Word w) is (accounting.miss() then Cons($H$.pop().w(w)))

static Cons request(Word w, Short s) {
  expecting(Pair::ok(w), s != $P_x$, s >= $P_f$, s <= $P_t$)
  return P[s].l == w.l ? reuse(s) : (++accounting.pairs,Pristine(s).ok()) ? hit(w,s) : miss(w);
}

static Cons request(Word w) is(request(w, w.hash()))
  
Unit collect(Pair p) { accounting.collect(); 
  expecting(p.ok())
  $H$.push(Pristine(p.handle())) | --accounting.pairs;
}

Module heap {
  const Pristine& heap = $H$.first; 
  Pristine reset() {
    $H$.reset();
    accounting.reset($P_n$);
  }
  Item fresh(Short s1, Short s2) { 
    expecting(white(s1), white(s2), s2 == $P_x$ or s2 >= $P_f$ and s2 <= $P_t$)
    if ($H$.empty()) throw __LINE__; 
    ++accounting.items;
    return Item($H$.pop()).head(s1).rest(s2);
  }

  Cons request(S car, S cdr) is(request(Word(car.handle(),cdr.handle()))) 
  Unit free(Item i) {
    expecting(i.ok());
    $H$.push(Pristine(i.handle())) | --accounting.items;
  }
}

Service {
  Boolean Pristine(Short s) { return ::Pristine(s).ok(); }
} xxbad;

#endif
