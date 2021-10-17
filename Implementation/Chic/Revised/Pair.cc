#import "Pair.h"
#import "Short.h"
#import "layout.h" // Do we need all this; Just P and A!
#import "accounting.h"

// Properties:
Property(Word& Pair::p) Is(P[handle()])
Property(Boolean Pair::ok)      Is(white(s1()) && white(s2()))
Property(Boolean Pair::seen)    {Expect(white(s2())) Is(black(s1())) }
Property(Boolean Pair::foreign) Is(black(s2()))
Property(S Pair::car) Is(p().s1)
Property(S Pair::cdr) Is(p().s2)

Pair::Pair(Short s): S(s) {}
Pair Pair::car(S s) selfing(s1() = s.handle())
Pair Pair::cdr(S s) selfing(s2() = s.handle())

Boolean Pair::ok(Word w) Is(white(w.s1) && white(w.s2))

Pair Pair::visit()  { accounting.visit();
  Expect(not seen()); 
  Promise(black(s1()));
  Promise(seen()); 
  return car(flip(s1())); 
} 

Pair Pair::leave() { accounting.leave();
  Expect(seen()); 
  Promise(not seen()); 
  return car(flip(s1())); 
} 
Pair::Pair(): Pair($P_x$) {} 
