#import "chic.h"
#import "Pair.cc"

Type Item below
Type Pristine below

Occasionally(Knob, Pair,
  using Super::handle;
  Fill(Knob) from(nothing) below 
  Property(Short s1) below
  Property(Short s2) below       
  Property(Boolean ok) below
  Property(Boolean cons) below
  Property(Boolean item) below
  Property(Boolean pristine) below
  Property(Boolean weirdo) below
  Property(Boolean x) below

  Selfer(s1(Short));
  Selfer(s2(Short));
)

#if Implementation 
#import "Word.cc"
#import "layout.h"

#import "Pair.cc"
#import "Item.cc"
#import "Pristine.cc"
#import "Short.h"

Property(Boolean Knob::ok)       is(x() || handle() >= $P_f$ and handle() <= $P_t$)
Property(Boolean Knob::x)        is(handle() == $P_x$)
Property(Short   Knob::s1)       is(P[handle()].s1)  
Property(Short   Knob::s2)       is(P[handle()].s2)  
Property(Boolean Knob::cons)     is(white(s1()) and white(s2()))
Property(Boolean Knob::item)     is(white(s1()) and black(s2()))
Property(Boolean Knob::pristine) is(black(s1()) and black(s2()))
Property(Boolean Knob::weirdo)   is(black(s1()) and white(s2()))

/*
Pair     Knob::Pair(S s1, S s2) const { return Pair().s1(s1).s2(s2); }
Item     Knob::Item()     const  { return  handle(); }
Pristine Knob::Pristine() const  { return  handle(); }
*/

Knob Knob::s1(Short  s) { P[handle()].s1 = s; return  *this; }
Knob Knob::s2(Short  s) { P[handle()].s2 = s; return  *this; }

#include "layout.h"

Filling(Knob) from(nothing)   by(Knob($P_x$)) 
int f() {
  int i;
  Knob h;
  Knob h1((short)i);
  Knob h2();
  Knob h3(0);
  Knob h4(h3);
  Knob h5((Short)h1);
  Knob h6((short)i);
}
#endif
