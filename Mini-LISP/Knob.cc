#include "Knob.h"

#include "Word.h"
#include "layout.h"

#include "Cons.h"
#include "Item.h"
#include "Pristine.h"
#include "Short.h"

Property(Boolean Knob::ok)       Is(x() || inner() >= $P_f$ && inner() <= $P_t$)
Property(Boolean Knob::x)        Is(inner() == $P_x$)
Property(Short   Knob::s1)       Is(P[inner()].s1)  
Property(Short   Knob::s2)       Is(P[inner()].s2)  
Property(Boolean Knob::cons)     Is(white(s1()) && white(s2()))
Property(Boolean Knob::pristine) Is(black(s1()) && black(s2()))
Property(Boolean Knob::item)     Is(white(s1()) && black(s2()))
Property(Boolean Knob::weirdo)   Is(black(s1()) && white(s2()))
Knob::Knob(): Knob($P_x$) {} 
Knob::Knob(Short s): Inner(s) {}

Knob Knob::s1(Short  s) { P[inner()].s1 = s; return  *this; }
Knob Knob::s2(Short  s) { P[inner()].s2 = s; return  *this; }

// Properties:
Cons     Knob::Cons()     const  { return  inner(); }
Item     Knob::Item()     const  { return  inner(); }
Pristine Knob::Pristine() const  { return  inner(); }
