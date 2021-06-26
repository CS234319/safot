#include "Pristine.h"
#include "Short.h"
#include "layout.h"

Pristine::Pristine(): Pristine($P_x$) {}
Pristine::Pristine(Short s): Knob(s) {}

Property(Pristine Pristine::prev) { 
  Expect(!x());
  Expect(black(s1()));
  return flip(s1()); 
}

Property(Pristine Pristine::next) { 
  Expect(!x());
  Expect(black(s2()));
  return flip(s2()); 
}

Property(Boolean Pristine::ok) { 
  if (x()) 
    return true;
  if (white(s1()) || white(s2()))
      return false;
  let p = prev().handle(), n = next().handle();
  if (p != $P_x$) {
    Expect(p >= $P_f$,p); 
    Expect(p <= $P_t$,p); 
    if (p < $P_f$) 
      return false;
    if (p > $P_t$) 
      return false;
  }
  if (n != $P_x$) {
    Expect(n >= $P_f$,n); 
    Expect(n <= $P_t$,n); 
    if (n < $P_f$) 
      return false;
    if (n > $P_t$) 
      return false;
  }
  return true;
}

Pristine& Pristine::prev(Pristine p) { 
  Expect(!x());
  let s = p.handle();
  Expect(white(s));
  s1(flip(s)); 
  return *this;
}

Pristine& Pristine::next(Pristine p) { 
  Expect(!x());
  let s = p.handle();
  Expect(white(s));
  s2(flip(s)); 
  return *this;
}
