#import "Handle.h"
Type S: private Handle { // An S-expression represented by its handle
  using Handle::handle;
  typedef S Self;
  Construct(S) ()               by(S((Short) 0))
  Construct(S) (Short s)        by(Handle(s))
  Construct(S) (Handle h)       by(S(h.handle()))
  Constructor(S) (const S& s1,const S  &s2) below 
  Constructor(S) (const Text t) below     

  Property(Boolean atom) Is(handle() <= 0) 
  Property(Boolean null) Is(handle() == 0);
  Property(Boolean t) Is(not null()) 
  Property(Boolean eq(S other)) Is(handle() == other.handle() and atom()) 
  Property(Type Pair Pair); 
  Property(S car);
  Property(S cdr);
};
