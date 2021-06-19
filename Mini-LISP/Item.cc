#include "Item.h"

#include "Short.h"

Short Item::count = 0;
static Short count;
Item::Item(Short s): Knob(s) {}
Item Item::head(Short s) { s1(s);       return *this; }
Item Item::rest(Short s) { s2(mark(s)); return *this; }
Short Item::head() const { return s1(); }

Short Item::rest() const { return mark(s2()); } 
