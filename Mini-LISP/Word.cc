#include "layout.h"

Word::Word(Short s1_, Short s2_): s1(s1_), s2(s2_) {}
Word::Word() {}
Short Word::hash() const { return $P_f$ + (l * 31 + 17) % $P_n$; }
