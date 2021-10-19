#import "chic.h"
Type Word { 
  Representation (
    perspective(Long l)        
    perspective(Short s1, s2)      
  ) 
  Initialize(Word) from(nothing) by(Word(0)) 
  Initialize(Word) from(Short s1prime, Short s2prime) by(s1(s1prime),s2(s2prime))
  Initialize(Word) from(Long lprime) by(l(lprime))
  Property(Short hash) below
};
#if Implementation
#import "layout.h"
Property(Short Word::hash) is($P_f$ + (unsigned)(l * 31 + 17) % $P_n$)
#endif
