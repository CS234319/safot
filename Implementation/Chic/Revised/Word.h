#import "CHIC"
Type Word { // The different perspectives of a word.
  Representation {
    perspective(Long l)        
    perspective(Short s1, s2)      
  };
  Construct(Word) from(nothing) by(Word(0)) 
  Construct(Word) from(Short s1prime, Short s2prime) by(s1(s1prime),s2(s2prime))
  Construct(Word) from(Long lprime) by(l(lprime))
  Property(Short hash) below
};
