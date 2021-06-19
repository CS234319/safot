#ifndef COLORS_H
#define COLORS_H

#include "layout.h"
#include "Handle.h"
#include "Word.h"
#includ


Type Cons: Handle {
  Cons(Short h): Handle(h) {}
  auto car(Short h) const { s1() = h; return *this; }
  auto cdr(Short h) const { s2() = h; return *this; }
  auto car() const { return s1(); }
  auto cdr() const { return s2(); } 
};


Type Pristine: Handle {
  static Short count;
  Pristine(Short h): Handle(h) {}
  auto prev(Short h) const { 
    Expect(!marked(h));
    s1() = mark(h); 
    return *this;
  }
  auto next(Short h) const { 
    Expect(!marked(h));
    s2() = mark(h); 
    return *this;
  }
  auto prev() const { 
    Expect(marked(s1()));
    return mark(s1()); 
  }
  auto next() const { 
    Expect(marked(s2()));
    return mark(s2()); 
  }
};

static struct {
  auto clean(Short &h) {
    if (marked(h)) h = mark(h);
    return *this;
  }
  auto stain(Short &h){
    if (!marked(h)) h = mark(h);
    return *this;
  }
  inline auto cons(Short h) { 
    Expect(h >= $P_f$ && h <= $P_t$)
    Promise(Handle(h).cons());
    clean(P[h].s1).clean(P[h].s2);
    return Cons(h);
  } 
  inline auto Pristine(Short h) { 
    Expect(h >= $P_f$ && h <= $P_t$)
    Promise(Handle(h).Pristine());
    stain(P[h].s1).stain(P[h].s2);
    return Pristine(h);
  } 
  inline auto item(Short h) { 
    Expect(h >= $P_f$ && h <= $P_t$)
    Promise(Handle(h).item()) 
    clean(P[h].s1).stain(P[h].s2);
    return Item(h);
  } 
} paint; 
#endif


