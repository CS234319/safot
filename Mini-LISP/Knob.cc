#include "Knob.h"

#include "Word.h"
#include "layout.h"

#include "Cons.h"
#include "Item.h"
#include "Pristine.h"
#include "Short.h"

Knob::Knob(Short s): Inner(s) {}

bool   Knob::x()  const { return inner() == $P_x$; } 
Short  Knob::s1() const { return P[inner()].s1;  }
Short  Knob::s2() const { return P[inner()].s2;  }

Knob Knob::s1(Short  s) { P[inner()].s1 = s; return  *this; }
Knob Knob::s2(Short  s) { P[inner()].s2 = s; return  *this; }

Cons     Knob::Cons()     const  { return  inner(); }
Item     Knob::Item()     const  { return  inner(); }
Pristine Knob::Pristine() const  { return  inner(); }

bool     Knob::item()     const  { !marked(s1())  &&  marked(s2());   }
bool     Knob::pristine() const  { marked(s1())   &&  marked(s2());   }
bool     Knob::cons()     const  { !marked(s1())  &&  !marked(s2());  }

// Short Knob::mark(Short s)  { return s + (1 << 15); } 
// bool Knob::marked(Short s) { return s < $X_f$ || s > $X_t$ + 1; } 
