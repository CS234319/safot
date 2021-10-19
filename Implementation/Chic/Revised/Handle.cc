#import "chic.h"
#import "Word.cc"
#import "Text.cc"
Type Handle { // A handle of an S-Expression
  Feature(handle) is(capsule)
  Representation(Short capsule) 
  Initialize(Handle) from(nothing) below 
  Initialize(Handle) from(Short s) by(capsule(s)) 
  Initialize(Handle) from(const Handle& h) by(capsule(h.capsule)) 

  Property(Boolean ok) below
  Property(Word& cons) below
  Property(Text text) below 
};

#if Implementation 
#import "layout.h"
Initialize(Handle::Handle) from(nothing) by(Handle($X_x$))
Property(Boolean Handle::ok)  is(capsule >= $X_f$ and capsule <= $X_t$)
#endif
