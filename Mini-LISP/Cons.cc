#include "Cons.h"

#include "Short.h"

Cons::Cons(Short s): Knob(s) {}
Cons Cons::car(Short h) { s1(h); return *this; }
Cons Cons::cdr(Short h) { s2(h); return *this; }
Knob Cons::car() const { return s1(); }
Knob Cons::cdr() const { return s2(); } 
bool Cons::ok() const { return !marked(s1()) && !marked(s2()); }
bool Cons::ok(Word w) { return !marked(w.s1) && !marked(w.s2); } 
