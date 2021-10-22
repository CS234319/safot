#import "chic.h"
#import "Handle.cc"
// #import "Text.cc"

Occasionally(S, Handle, 
  using Super::handle;
  Fill(S) from(S s1, S s2) below // by (S(request(s1,s2))) 
  Fill(S) from(Text t) below // by(S(request(t))) 
  static S request(Text) below
  static S request(S, S) below

  Feature(atom) is(handle() <= 0) 
  Feature(compound) is(not atom())
  Feature(null) is(handle() == 0);
  Feature(t) is(not null()) 

  Query(eq) with(S s) is(atom() and inner == s.handle()) 

  Property(Text text) below 
  Property(Word &word) below 
  Property(S car) below
  Property(S cdr) below
)

#if Implementation 

#import "layout.h"
#import "Text.cc"
Property(Text S::text)   {
  Short inner = this->inner;
  char *a = A;
  char *a1 = A + inner;
  Text t(a1);
  return t;
}

#import "layout.h"
#import "Word.cc"
Property(Word& S::word)  is(P[inner])

Property(S S::car)  is(S(word().s1)) 
Property(S S::cdr)  is(S(word().s2)) 

#import "heap.cc"
#import "Pair.cc"
Filling(S) from(S s1, S s2) by(S(heap::request(s1, s2))) 

#import "text.cc"
Filling(S::S) from(Text t) by(S(text::request(t))) 

#endif
