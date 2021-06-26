#include "Pair.h"
#include "Short.h"
#include "layout.h" // Do we need all this; Just P and A!

// Properties:
Property(Word& Pair::p) Is(P[handle()])
Property(Boolean Pair::ok)      Is(white(car().handle()) && white(cdr().handle()))
Property(Boolean Pair::seen)    Is(black(car().handle()))
Property(Boolean Pair::foreign) Is(black(cdr().handle()))
Property(Sx  Pair::car) Is(p().s1)
Property(Sx  Pair::cdr) Is(p().s2)

Pair::Pair(Short s): Sx(s) {}
Pair Pair::car(Sx s) { p().s1 = s.handle(); return *this; }
Pair Pair::cdr(Sx s) { p().s2 = s.handle(); return *this; }

Boolean Pair::ok(Word w) { return white(w.s1) && white(w.s2); } 

Pair Pair::visit()  { 
  Expect(not seen()); 
  Promise(black(car().handle()));
  Promise(seen()); 
  return car(flip(car().handle())); 
} 

Pair Pair::unvisit() { 
  Expect(seen()); 
  Promise(not seen()); 
  return car(flip(car().handle())); 
} 

Short Pair::count = 0; // Accounting elsewhere please
Integer Pair::reuse = 0;
Integer Pair::miss = 0;
