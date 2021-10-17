#import "Handle.h"
Type Sx: private Handle { // An S-expression represented by its handle
  using Handle::handle;
  typedef Sx Self;
  Construct(Sx) ()               by(Sx((Short) 0))
  Construct(Sx) (Short s)        by(Handle(s))
  Construct(Sx) (Handle h)       by(Sx(h.handle()))

  Sx(const Sx& s1,const Sx  &s2); 
  Sx(const Text t);      

  Property(Boolean atom);
  Property(Sx car);
  Property(Sx cdr);
  Property(Boolean null);
  Property(Type Pair Pair); 
};
