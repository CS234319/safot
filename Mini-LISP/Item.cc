#include "Item.h"
#include "Short.h"
Item::Item(): Knob() {}
Item::Item(Short s): Knob(s) {}
Item Item::head(Short s) { s1(s);       return *this; }
Item Item::rest(Short s) { s2(flip(s)); return *this; }
Property(Item Item::rest) Is(Item(flip(s2())))
Property(Short Item::head) Is(s1())
Property(Boolean Item::ok) Is(x() || white(s1())  && black(s2()))
Short accounting.itemized = 0;
