#include "chic.h"
#include "heap.h"

#include "Short.h"
#include "Word.h"
#include "Pair.h"

#include "layout.h"

Pristine heap = heapify(); 

Knob crude() {
  if (heap.x())
    throw EXHAUSTED; 
  Expect(!heap.x(),heap);
  Expect(heap.prev().x());
  Pristine::count--;
  let old = heap;
  heap = heap.next();
  if (!heap.x())
    heap.prev($P_x$);
  return old.handle(); 
}

Item fresh(Short s1, Short s2) {
  Expect(white(s1));
  Expect(white(s2));
  Expect(s2 == $P_x$ || s2 >= $P_f$ && s2 <= $P_t$);
  if (heap.x()) throw __LINE__; 
  Item::count++;
  return crude().Item().head(s1).rest(s2);
}

static Item fresh(Word w) { 
  return fresh(w.s1,w.s2); 
}

static Pair require(Word w, Short s) {
  Expect(Pair::ok(w));
  Expect(s != $P_x$);
  Expect(s >= $P_f$);
  Expect(s <= $P_t$);
  if (P[s].l == w.l) {
    Pair::reuse++;
    return s; 
  };
  Pair::count++;
  if (!Pristine(s).ok()) {
    Pair::miss++;
    return crude().Pair().car(w.s1).cdr(w.s2);
  }
  Expect(Pristine(s).ok());
  Promise(Pair::ok(P[s]));
  Pristine::count--;
  auto prev = Pristine(s).prev(), next = Pristine(s).next();
  if (!prev.x()) prev.next(next); 
  if (!next.x()) next.prev(prev); 
  if (heap.handle() == s) heap = next ;
  P[s] = w;
  return Pair(s);
}

Pair require(Word w) {
  return require(w, w.hash());
}
  
Pristine heapify() {
  for (Short s = $P_f$ + 1; s <= $P_t$ - 1; ++s) 
    Pristine(s).prev(Pristine(s-1)).next(Pristine(s+1));
  Pristine($P_f$).prev(Pristine()).next(Pristine($P_f$ +1));
  Pristine($P_t$).next(Pristine()).prev(Pristine($P_t$ -1));
  Pristine::count = $P_n$;
  Pair::count = 0;
  Pair::reuse = 0;
  Pair::miss = 0;
  Item::count = 0;
  return heap = Pristine($P_f$);
}

void prepend(Pristine p) {
  p.prev($P_x$).next(heap); 
  if (!heap.x())
    heap.prev(p);
  heap = p;
  Pristine::count++;
}

void free(Item i) {
  Expect(i.ok());
  Expect(Knob(i.handle()).item());
  prepend(Knob(i.handle()).Pristine());
  Item::count--;
}

Pair require(Sx car, Sx cdr) { return require(Word(car.handle(),cdr.handle())); }

#include "mark.h"

void mark(Sx s) {
 auto k = Knob(s.handle()); 
 k.s1(flip(k.s1())); 
}

void visit(Pair c);

void visit(Sx s) {
  if (white(s.handle()) && !s.atom()) {
    auto car = s.car();
    auto cdr = s.cdr();
    mark(s);
    visit(car);
    visit(cdr);
  } 
}

void preserve(Sx c) { 
  visit(c);
  for (auto s = $P_f$; s <= $P_t$; ++s) {
    if (Knob(s).pair()) {
      prepend(Pristine(s));
    } else if (Knob(s).weirdo()) { 
      mark(s); 
      Surely(Knob(s).pair());
    }
  }
}
