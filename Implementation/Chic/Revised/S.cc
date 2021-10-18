#import "chic.h"
#import "Handle.cc"
Occasionally(S, Handle, 
  Construct(S) from(Short s) by(Super(s))
  Constructor(S) from(S,S) below 
  Constructor(S) from(Text) below

  property(atom) is(handle() <= 0) 
  property(compound) is(not atom())
  property(null) is(handle() == 0);
  property(t) is(not null()) 

  Query(eq) with(S s) is(atom() and capsule == s.handle()) 

  Property(Text text) below 
  Property(Word &word) below 
  Property(S car) below
  Property(S cdr) below
)

#if Implementation 
#import "layout.h"

Property(Word& S::word)  is(P[capsule])
Property(Text S::text)   is(A + capsule) 
Property(S S::car)  is(word().s1) 
Property(S S::cdr)  is(word().s2) 

#import "heap.cc"
namespace heap {
  extern S request(S, S); 
}
Construct(S::S) from(S s1, S s2) by(S(heap::request(s1, s2))) 


Construct(S::S) from(Text t) by(S(text::request(t))) 
#endif
