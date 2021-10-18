#import "Handle.h"
Type S: public Handle { // An S-expression represented by its handle
  using Handle::handle;

  typedef S Self;
  Construct(S) from() by(S((Short) 0))
  Construct(S) from(Short s) by(Handle(s))
  Construct(S) from(Handle h) by(S(h.handle()))

  property(atom) is(handle() <= 0) 
  property(compound) is(not atom())
  property(null) is(handle() == 0);
  property(t) is(not null()) 
  Query(eq) with(S s) is(atom() and handle() == s.handle()) 

  Constructor(S) from(const S&,const S &) below 
  Constructor(S) from(const Text) below

  Property(Text text) below 
  Property(Type Pair Pair) below 
  Property(S car) below
  Property(S cdr) below
};
