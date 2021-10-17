#import "CHIC"
#import "Knob.h"
Type Item: private Knob {
  using Knob::x;
  Construct(Item) from(nohing) by(Knob())
  Construct(Item) from(Short s) by(Knob(s))
  Property(Item rest) below
  Property(Short head) below
  Property(Boolean ok);
  Item head(Short s);
  Item rest(Short s);
}; 
#import "Short.h"

#if Implementation
Item::Item(): Knob() {}
Property(Item Item::rest) Is(Item(flip(s2())))
Property(Short Item::head) Is(s1())
Item Item::head(Short s) { s1(s);       return *this; }
Item Item::rest(Short s) { s2(flip(s)); return *this; }
Property(Boolean Item::ok) Is(x() || white(s1())  && black(s2()))
#endif
