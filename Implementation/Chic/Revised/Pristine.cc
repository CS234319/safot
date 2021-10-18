#import "chic.h"
#import "Knob.h"
Occasionally(Pristine, Knob, 
  // Decomposition
  // using Knob::handle;
  using Knob::x;
  //using Knob::Item, Knob::Pair;
  Construct(Pristine) from(Short s) by(Super(s)) 
  Property(Pristine prev);
  Property(Pristine next);
  Property(Boolean ok);

  Pristine& prev(Pristine); 
  Pristine& next(Pristine); 
)
#if Implementation
#import "Pristine.h"
#import "Short.h"
#import "layout.h"

// Pristine::Pristine(): Pristine($P_x$) {}
// Pristine::Pristine(Short s): Knob(s) {}

Property(Pristine Pristine::prev) { 
  Expect(!x());
  Expect(black(s1()));
  Is(flip(s1())); 
}

Property(Pristine Pristine::next) { 
  Expect(!x());
  Expect(black(s2()));
  Is(flip(s2())); 
}

Property(Boolean Pristine::ok) { 
  if (x()) return true;
  if (white(s1()) || white(s2())) return false;
  let p = prev().handle(), n = next().handle();
  if (p != $P_x$) {
    Expect(p >= $P_f$,p); 
    Expect(p <= $P_t$,p); 
    if (p < $P_f$) return false;
    if (p > $P_t$) return false;
  }
  if (n != $P_x$) {
    Expect(n >= $P_f$,n); 
    Expect(n <= $P_t$,n); 
    if (n < $P_f$) return false;
    if (n > $P_t$) return false;
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
#endif
