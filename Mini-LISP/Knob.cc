#include "Knob.h"

#include "Word.h"
#include "layout.h"

#include "Cons.h"
#include "Item.h"
#include "Pristine.h"
#include "Short.h"

Knob::Knob(): Knob($P_x$) {} 
Knob::Knob(Short s): Inner(s) {}
Boolean   Knob::x()  const { return inner() == $P_x$; } 
Short  Knob::s1() const { return P[inner()].s1;  }
Short  Knob::s2() const { return P[inner()].s2;  }

Knob Knob::s1(Short  s) { P[inner()].s1 = s; return  *this; }
Knob Knob::s2(Short  s) { P[inner()].s2 = s; return  *this; }

Cons     Knob::Cons()     const  { return  inner(); }
Item     Knob::Item()     const  { return  inner(); }
Pristine Knob::Pristine() const  { return  inner(); }

Boolean     Knob::item()     const  { !marked(s1())  &&  marked(s2());   }
Boolean     Knob::pristine() const  { marked(s1())   &&  marked(s2());   }
Boolean     Knob::cons()     const  { !marked(s1())  &&  !marked(s2());  }

// Short Knob::mark(Short s)  { return s + (1 << 15); } 
// Boolean Knob::marked(Short s) { return s < $X_f$ || s > $X_t$ + 1; } 
