#include "Handle.h"
#include "layout.h"
#include "Short.h"

Is::Is(Short h): Handle(h) {}
Is::Is(Handle s): Handle(s) {}
Short Is::s1() const { return P[self].s1; }
Short Is::s2() const { return P[self].s2; }
Short& Is::s1() { return P[self].s1; }
Short& Is::s2() { return P[self].s2; }
Is Is::s1(Short h) { P[self].s1 = h; return *this;}
Is Is::s2(Short h) { P[self].s2 = h; return *this;}
bool Is::cons() const { !marked(s1()) && !marked(s2()); } 
bool Is::Pristine() const { marked(s1()) && marked(s2()); } 
bool Is::item() const { !marked(s1()) && marked(s2()); } 
