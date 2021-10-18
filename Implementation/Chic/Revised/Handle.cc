#import "chic.h"
#import "Word.cc"
Type Handle { // A handle of an S-Expression
  property(handle) is(capsule)
  Representation(Short capsule) 
  Construct(Handle) from(nothing) below 
  Construct(Handle) from(Short s) by(capsule(s)) 
  Construct(Handle) from(const Handle& h) by(capsule(h.capsule)) 

  Property(Boolean ok) below
  Property(Word& cons) below
  Property(Text text) below 
};

#if Implementation 
#import "layout.h"
Construct(Handle::Handle) from(nothing) by(Handle($X_x$))
Property(Boolean Handle::ok)  is(capsule >= $X_f$ and capsule <= $X_t$)
#endif
