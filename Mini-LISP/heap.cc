#include "chic.h"
#include "heap.h"

#include "Short.h"
#include "Word.h"
#include "Cons.h"

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
  return old.inner(); 
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

static Cons require(Word w, Short s) {
  Expect(Cons::ok(w));
  Expect(s != $P_x$);
  Expect(s >= $P_f$);
  Expect(s <= $P_t$);
  if (P[s].l == w.l) {
    Cons::reuse++;
    return s; 
  };
  Cons::count++;
  if (!Pristine(s).ok()) {
    Cons::miss++;
    return crude().Cons().car(w.s1).cdr(w.s2);
  }
  Expect(Pristine(s).ok());
  Promise(Cons::ok(P[s]));
  Pristine::count--;
  auto prev = Pristine(s).prev(), next = Pristine(s).next();
  if (!prev.x()) prev.next(next); 
  if (!next.x()) next.prev(prev); 
  if (heap.inner() == s) heap = next ;
  P[s] = w;
  return Cons(s);
}

Cons require(Word w) {
  return require(w, w.hash());
}
  
Pristine heapify() {
  for (Short s = $P_f$ + 1; s <= $P_t$ - 1; ++s) 
    Pristine(s).prev(Pristine(s-1)).next(Pristine(s+1));
  Pristine($P_f$).prev(Pristine()).next(Pristine($P_f$ +1));
  Pristine($P_t$).next(Pristine()).prev(Pristine($P_t$ -1));
  Pristine::count = $P_n$;
  Cons::count = 0;
  Cons::reuse = 0;
  Cons::miss = 0;
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
  Expect(Knob(i.inner()).item());
  prepend(Knob(i.inner()).Pristine());
  Item::count--;
}

Cons require(Sx car, Sx cdr) { return require(Word(car.inner(),cdr.inner())); }

#include "mark.h"
void mark(Cons c) {
 auto k = Knob(c.inner()); 
 k.s1(flip(k.s1())); 
}

void visit(Cons c);
void visit(Sx s) {
  if (white(s.inner()) && !s.atom())
    visit(Cons(s.inner()));
}

void visit(Cons c) {
  Expect(c.ok());
  mark(c);
  visit(c.car());
  visit(c.cdr());
}

void preserve(Cons c) { 
  visit(c);
  for (auto s = $P_f$; s <= $P_t$; ++s) {
    if (Knob(s).cons()) {
      prepend(Pristine(s));
    } else if (Knob(s).weirdo()) { 
      mark(s); 
      Surely(Knob(s).cons());
    }
  }
}


