#import "chic.h"
#import "Pair.cc"

Type Item below
Type Pristine below

  // An S-expression represented by its Knob

Occasionally(Knob, Pair,
  using Super::handle;
  Constructor(Knob) from(Short s) by(Super(s)) 
  Construct(Knob) from(Handle h) by(Super(h))
  Property(Short s1) below
  Property(Short s2) below       
  Property(Boolean ok) below
  Property(Boolean pair) below
  Property(Boolean item) below
  Property(Boolean pristine) below
  Property(Boolean weirdo) below
  Property(Boolean x) below

  // Type Pair     Pair(S, S) const;
  // Type Item     Item()       const;
  // Type Pristine Pristine()   const;
  // Mutators:
  Selfer(s1(Short));
  Selfer(s2(Short));
)

#if Implementation 
#import "Word.cc"
#import "layout.h"

#import "Pair.cc"
#import "Item.h"
#import "Pristine.h"
#import "Short.h"

Property(Boolean Knob::ok)       is(x() || handle() >= $P_f$ and handle() <= $P_t$)
Property(Boolean Knob::x)        is(handle() == $P_x$)
Property(Short   Knob::s1)       is(P[handle()].s1)  
Property(Short   Knob::s2)       is(P[handle()].s2)  
Property(Boolean Knob::pair)     is(white(s1()) and white(s2()))
Property(Boolean Knob::pristine) is(black(s1()) and black(s2()))
Property(Boolean Knob::item)     is(white(s1()) and black(s2()))
Property(Boolean Knob::weirdo)   is(black(s1()) and white(s2()))
Knob::Knob()     by(Self($P_x$)) 

Knob Knob::s1(Short  s) { P[handle()].s1 = s; return  *this; }
Knob Knob::s2(Short  s) { P[handle()].s2 = s; return  *this; }

// Properties:
Pair     Knob::Pair(S s1, S s2) const { return Pair().s1(s1).s2(s2); }
Item     Knob::Item()     const  { return  Pair().handle(); }
Pristine Knob::Pristine() const  { return  Pair().handle(); }
#endif
