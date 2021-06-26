#include "chic.h"
#include "heap.h"

#include "Short.h"
#include "Word.h"
#include "Pair.h"

#include "layout.h"
#include "accounting.h"

static struct {
  Knob pop() {
    if (heap.x())
      throw EXHAUSTED; 
    Expect(heap.prev().x());
    accounting.use();
    let old = heap;
    heap = heap.next();
    if (!heap.x())
      heap.prev($P_x$);
    return old.handle(); 
  }
  Unit push(Pristine p) {
   accounting.unuse();
   p.prev($P_x$).next(heap); 
   if (!heap.x()) heap.prev(p);
   heap = p;
  }
  Pristine heapify() {
    for (Short s = $P_f$ + 1; s <= $P_t$ - 1; ++s) 
      Pristine(s).prev(Pristine(s-1)).next(Pristine(s+1));
    Pristine($P_f$).prev(Pristine()).next(Pristine($P_f$ +1));
    Pristine($P_t$).next(Pristine()).prev(Pristine($P_t$ -1));
    accounting.init($P_n$);
    inner.available = $P_n$;
    accounting.allocated = 0;
    Pair::reuse = 0;
    Pair::miss = 0;
    accounting.itemized = 0;
    return heap = Pristine($P_f$);
    }
    } heap;

Item fresh(Short s1, Short s2) {
  Expect(white(s1));
  Expect(white(s2));
  Expect(s2 == $P_x$ || s2 >= $P_f$ && s2 <= $P_t$);
  if (heap.x()) throw __LINE__; 
  accounting.itemized++;
  return pop().Item().head(s1).rest(s2);
}

static Item fresh(Word w) { 
  return fresh(w.s1,w.s2); 
}

static Pair request(Word w, Short s) {
  Expect(Pair::ok(w));
  Expect(s != $P_x$);
  Expect(s >= $P_f$);
  Expect(s <= $P_t$);
  if (P[s].l == w.l) {
    Pair::reuse++;
    return s; 
  };
  accounting.allocated++;
  if (!Pristine(s).ok()) {
    Pair::miss++;
    return pop().Pair().car(w.s1).cdr(w.s2);
  }
  Expect(Pristine(s).ok());
  Promise(Pair::ok(P[s]));
  accounting.available--;
  auto prev = Pristine(s).prev(), next = Pristine(s).next();
  if (!prev.x()) prev.next(next); 
  if (!next.x()) next.prev(prev); 
  if (heap.handle() == s) heap = next ;
  P[s] = w;
  return Pair(s);
}

Pair request(Word w) {
  return request(w, w.hash());
}
  
Unit gobble(Pair p) {
  Expect(p.ok());
  push(Pristine(p.handle())) | accounting.allocated--;
}

Unit free(Item i) {
  Expect(i.ok());
  push(Pristine(i.handle())) | accounting.itemized--;
}

Pair request(Sx car, Sx cdr) { return request(Word(car.handle(),cdr.handle())); }
