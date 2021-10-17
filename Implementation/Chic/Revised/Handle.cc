#import "CHIC"
#import "Word.h"
Type Handle { // A handle of an S-Expression
  property(handle) is(capsule)
  Representation(Short capsule) 
  Construct(Handle) from(Short s) by(capsule(s)) 

  Property(Boolean ok) below
  Property(Word& cons) below
  Property(Text text) below 
};

#if Implementation 
#import "layout.h"
Property(Boolean Handle::ok)   is(capsule >= $X_f$ && capsule <= $X_t$)
Property(Word& Handle::cons)   is(P[capsule])
Property(Text Handle::text)    is(A + capsule) 
#endif
