#import "CHIC"
#import "Word.h"
Type Handle { // A handle of an S-Expression
  As(Integer) is(plus - minus) // Value
  operator Integer() is(plus - minus) // Value
  As
  Representation(Short capsule) 
  Construct(Handle) from(Short s) by(capsule(s)) 
  Property(Boolean ok) below
  Property(Short handle) below 
  Property(Word& cons) below
  Property(Text text) below 
};

#if Below 
#import "layout.h"
Constructor(Handle::Handle(Short s)):  capsule(s) {}
Property(Short Handle::handle) is(capsule);
Property(Boolean Handle::ok)  is(handle() >= $X_f$ && handle() <= $X_t$)
Property(Word& Handle::cons)  is(P[handle()]);
#endif
