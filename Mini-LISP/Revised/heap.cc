#include "chic.h"
#include "heap.h"

#include "Short.h"
#include "Word.h"
#include "Pair.h"

#include "layout.h"
#include "accounting.h"

static struct {
  auto empty() { return top.x(); } 
  Knob pop() {
    not top.x() or panic();  
    Surely(top.prev().x());
    accounting.pop();
    let old = top;
    top = top.next();
    if (!top.x()) top.prev($P_x$);
    return old.handle(); 
  }
  Unit push(Pristine p) {
    accounting.push();
    p.prev($P_x$).next(top); 
    if (!top.x()) top.prev(p);
    top = p;
  }
  Unit pick(Pristine p) {
    Surely(p.ok());
    accounting.pick();
    auto prev = p.prev(), next = p.next();
    if (!prev.x()) prev.next(next); 
    if (!next.x()) next.prev(prev); 
    if (top.handle() == p.handle()) top = next ;
  }
  Unit init() {
    for (Short s = $P_f$ + 1; s <= $P_t$ - 1; ++s) 
      Pristine(s).prev(Pristine(s-1)).next(Pristine(s+1));
    Pristine($P_f$).prev(Pristine()).next(Pristine($P_f$ +1));
    Pristine($P_t$).next(Pristine()).prev(Pristine($P_t$ -1));
    accounting.init($P_n$);
    top = Pristine($P_f$);
  }
  Pristine top;
  private:
    Unit panic() { throw EXHAUSTED; }
} stack;

const Pristine& heap = stack.top; 

Item fresh(Short s1, Short s2) { 
  Expect(white(s1));
  Expect(white(s2));
  Expect(s2 == $P_x$ || s2 >= $P_f$ && s2 <= $P_t$);
  if (stack.empty()) throw __LINE__; 
  ++accounting.items;
  return stack.pop().Item().head(s1).rest(s2);
}

Unit free(Item i) {
  Expect(i.ok());
  stack.push(Pristine(i.handle())) | --accounting.items;
}
 
#define Count(label,signature,value) (accounting.label() , value)  
static inline auto reuse(Short s) { accounting.reuse(); return Pair(s);  }
static inline auto hit(Word w, Short s) {  
  accounting.hit();
  stack.pick(Pristine(s)); 
  P[s].l = w.l; 
  return Pair(s);
}

static inline auto miss(Word w) {  
  accounting.miss(); return stack.pop().Pair(w.s1,w.s2); 
}

static Pair request(Word w, Short s) {
  Expect(Pair::ok(w));
  Expect(s != $P_x$);
  Expect(s >= $P_f$);
  Expect(s <= $P_t$);
  return P[s].l == w.l ? reuse(s) : (++accounting.pairs,Pristine(s).ok()) ? hit(w,s) : miss(w);
}

extern Pristine heapify() {
  stack.init();
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
  stack.push(Pristine(p.handle())) | --accounting.pairs;
}


Pair request(Sx car, Sx cdr) { 
  return request(Word(car.handle(),cdr.handle())); 
}
