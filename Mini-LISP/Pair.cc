#include "Pair.h"

#include "Short.h"
#include "layout.h"
// Properties:
Property(Word& Pair::p) Is(P[handle()])
Property(Boolean  Pair::ok) Is(white(car().handle()) && white(cdr().handle()))
Property(Sx  Pair::car) Is(p().s1)
Property(Sx  Pair::cdr) Is(p().s2)

Pair::Pair(Short s): Sx(s) {}
Pair Pair::car(Sx s) { p().s1 = s.handle(); return *this; }
Pair Pair::cdr(Sx s) { p().s2 = s.handle(); return *this; }
Boolean Pair::ok(Word w) { return white(w.s1) && white(w.s2); } 
Short Pair::count = 0;
Integer Pair::reuse = 0;
Integer Pair::miss = 0;
#include "layout.h"
#include "heap.h"
#include "Pristine.h"
#include "Word.h"

#include "Test.h" 


