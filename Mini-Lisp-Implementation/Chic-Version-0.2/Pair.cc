#import "chic.h"
#import "Handle.cc"
#import "Word.cc"

Occasionally(Pair, Handle,
  Feature(s1) is(word().s1)
  Feature(s2) is(word().s2)

  Property(Word &word) below

  Property(Boolean unseen) below
  Property(Boolean seen) below
  Property(Boolean ok) below // Consolidate variadic macro
  Property(Boolean x) below // Change someday to nil
  Property(Boolean foreign) below
  Selfer(visit()) below // Consolidate variadic macro
  Selfer(leave()) below 

  static Boolean ok(Word) below
  Selfer(s1(Short)) below 
  Selfer(s2(Short)) below 
  Selfer(w(Word)) below
)

#if Implementation
#import "layout.h" // Do we need all this; Just P and A!
#import "accounting.cc"
#import "Short.h"

// Properties:
Property(Boolean Pair::ok)      is(white(s1()) && white(s2()))
Property(Boolean Pair::seen)    {expecting(white(s2())) is(black(s1())) }
Property(Boolean Pair::foreign) is(black(s2()))


Property(Word& Pair::word)  is(P[_])
Boolean Pair::ok(Word w) is(white(w.s1) && white(w.s2))

Pair Pair::visit()  { accounting.visit();
  expecting(not seen()); 
  promising(black(s1()), seen()); 
  return s1(flip(s1())); 
} 

Pair Pair::leave() { accounting.leave();
  expecting(seen()); 
  promising(not seen()); 
  return s1(flip(s1())); 
} 
// Pair::Pair(): Pair($P_x$) {} 
#endif
