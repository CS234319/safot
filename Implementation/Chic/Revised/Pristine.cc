#import "chic.h"
#import "Knob.cc"
Occasionally(Pristine, Knob, 
  using Knob::x;
  Fill(Pristine) from(Short s) by(Super(s)) 
  Property(Pristine prev) below
  Property(Pristine next) below
  Property(Boolean ok) below

  Pristine& prev(Pristine) below 
  Pristine& next(Pristine) below 
)
#if Implementation
#import "Pristine.cc"
#import "Short.h"
#import "layout.h"

// Pristine::Pristine(): Pristine($P_x$) {}
// Pristine::Pristine(Short s): Knob(s) {}

Property(Pristine Pristine::prev) { 
  expecting(not x(), black(s1()))
  is(Pristine(flip(s1()))) 
}

Property(Pristine Pristine::next) { 
  expecting(not x(), black(s2()))
  is(Pristine(flip(s2()))) 
}

Property(Boolean Pristine::ok) { 
  if (x()) return true;
  if (white(s1()) || white(s2())) return false;
  let p = prev().handle(), n = next().handle();
  if (p != $P_x$) {
    expecting(p >= $P_f$,  p <= $P_t$) 
    if (p < $P_f$) return false;
    if (p > $P_t$) return false;
  }
  if (n != $P_x$) {
    expecting(n >= $P_f$,  n <= $P_t$) 
    if (n < $P_f$) return false;
    if (n > $P_t$) return false;
  }
  return true;
}

Pristine& Pristine::prev(Pristine p) { 
  expecting(not x())
  let s = p.handle();
  expecting(white(s))
  s1(flip(s)); 
  return *this;
}

Pristine& Pristine::next(Pristine p) { 
  expecting(not x())
  let s = p.handle();
  expecting(white(s))
  s2(flip(s)); 
  return *this;
}

int f() {
  int i;
  Pristine h;
  Pristine h1((short)i);
  Pristine h2();
  Pristine h3(0);
  Pristine h4(h3);
  Pristine h5((Short)h1);
  Pristine h6((short)i);

}
#endif
