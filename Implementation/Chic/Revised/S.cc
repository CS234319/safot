#import "chic.h"
#import "Handle.cc"
Occasionally(S, Handle, 
  using Super::handle;
  template<typename T> S(T t) by (Super(t))
  Fill(S) from(S,S) below 
  Fill(S) from(Text) below

  Feature(atom) is(handle() <= 0) 
  Feature(compound) is(not atom())
  Feature(null) is(handle() == 0);
  Feature(t) is(not null()) 

  Query(eq) with(S s) is(atom() and matter == s.handle()) 

  Property(Text text) below 
  Property(Word &word) below 
  Property(S car) below
  Property(S cdr) below
)

#if Implementation 
#import "layout.h"

Property(Word& S::word)  is(P[matter])
Property(Text S::text)   is(A + matter) 
Property(S S::car)  is(word().s1) 
Property(S S::cdr)  is(word().s2) 

#import "heap.cc"
#import "text.cc"
Fill(S::S) from(S s1, S s2) by(S(heap::request(s1, s2))) 
Fill(S::S) from(Text t) by(S(text::request(t))) 
#endif
