#import "chic.h"

#import "Knob.cc"
Occasionally(Item, Knob, 
  using Knob::x;
  Initialize(Item) from(Short s) by(Super(s))
  Property(Item rest) below
  Property(Short head) below
  Property(Boolean ok) below
  Item head(Short s) below
  Item rest(Short s) below
)
#import "Short.h"

#if Implementation
Item::Item(): Knob() {}
Property(Item Item::rest) Is(Item(flip(s2())))
Property(Short Item::head) Is(s1())
Item Item::head(Short s) { s1(s);       return *this; }
Item Item::rest(Short s) { s2(flip(s)); return *this; }
Property(Boolean Item::ok) Is(x() || white(s1())  && black(s2()))
#endif
