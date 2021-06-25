#include "Knob.h"

#include "Word.h"
#include "layout.h"

#include "Pair.h"
#include "Item.h"
#include "Pristine.h"
#include "Short.h"

Property(Boolean Knob::ok)       Is(x() || handle() >= $P_f$ && handle() <= $P_t$)
Property(Boolean Knob::x)        Is(handle() == $P_x$)
Property(Short   Knob::s1)       Is(P[handle()].s1)  
Property(Short   Knob::s2)       Is(P[handle()].s2)  
Property(Boolean Knob::pair)     Is(white(s1()) && white(s2()))
Property(Boolean Knob::pristine) Is(black(s1()) && black(s2()))
Property(Boolean Knob::item)     Is(white(s1()) && black(s2()))
Property(Boolean Knob::weirdo)   Is(black(s1()) && white(s2()))
Knob::Knob(): Knob($P_x$) {} 
Knob::Knob(Short s): Super(s) {}

Knob Knob::s1(Short  s) { P[handle()].s1 = s; return  *this; }
Knob Knob::s2(Short  s) { P[handle()].s2 = s; return  *this; }

// Properties:
Pair     Knob::Pair()     const  { return  handle(); }
Item     Knob::Item()     const  { return  handle(); }
Pristine Knob::Pristine() const  { return  handle(); }
