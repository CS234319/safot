#import "layout.h"
Word::Word(Short s1_, Short s2_): s1(s1_), s2(s2_) {}
Word::Word() {}
Property(Short Word::hash) Is($P_f$ + (unsigned)(l * 31 + 17) % $P_n$);
