#import "CHIC"

#import "Handle.h"

Occasionally(Pair, Handle,
  Property(Boolean unseen) below
  Property(Boolean seen) below
  Property(Boolean ok) below // Consolidate variadic macro
  Constructor(Pair) from(Short) below
  Property(Boolean x) below // Change someday to nil

  Property(Boolean foreign) below


  Selfer(visit()) below // Consolidate variadic macro
  Selfer(leave()) below 

  static Boolean ok(Word) below
  protected:
    Selfer(s1(S)) below 
    Selfer(s2(S)) below 
    property(s1) is(p().s1)
    property(s2) is(p().s2)
    Property(Word& p) below
)
#if Implementation
#import "Short.h"
#import "layout.h" // Do we need all this; Just P and A!
#import "accounting.h"

// Properties:
Property(Boolean Pair::ok)      is(white(s1()) && white(s2()))
Property(Boolean Pair::seen)    {Expect(white(s2())) is(black(s1())) }
Property(Boolean Pair::foreign) is(black(s2()))

Pair::Pair(Short s): Super(s) {}

Boolean Pair::ok(Word w) is(white(w.s1) && white(w.s2))

Pair Pair::visit()  { accounting.visit();
  Expect(not seen()); 
  Promise(black(s1()));
  Promise(seen()); 
  return s1(flip(s1())); 
} 

Pair Pair::leave() { accounting.leave();
  Expect(seen()); 
  Promise(not seen()); 
  return s1(flip(s1())); 
} 
// Pair::Pair(): Pair($P_x$) {} 
#endif
