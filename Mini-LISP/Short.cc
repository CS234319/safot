#include "Short.h"
#include "layout.h"

#include <iostream>
extern Short flip(Short s)    { return s + (1 << 15); } 
extern Boolean black(Short s) { return s < $X_f$ || s > $X_t$ + 1; } 
extern Boolean white(Short s) { return !black(s); } 

extern void stain(Short &s) {
  Promise(black(s));
  if (white(s)) s = flip(s);
}

extern void cleanse(Short &s) {
  Promise(white(s));
  if (black(s)) s = flip(s);
}
#include <stdio.h>
#include "Pristine.h"
#undef Type
#undef function

#include "gtest/gtest.h"

TEST(Stain, Short) {
  Short s = 12;
  EXPECT_EQ(12,s);
  EXPECT_NE(12,flip(s));
  EXPECT_FF(black(12));
  EXPECT_FF(black(12));
  stain(s);
  EXPECT_NE(12,s);
  EXPECT_TT(black(s));
  cleanse(s);
  EXPECT_EQ(12,s);
}

TEST(Stain, Word) {
  P[4].s1 = 3;
  P[4].s2 = 2;
  EXPECT_FF(Pristine(4).ok());
  EXPECT_FF(black(Knob(4).s1()));
  stain(P[4].s1); 
  EXPECT_TT(black(Knob(4).s1()));
  EXPECT_FF(Pristine(4).ok());
  stain(P[4].s2); 
  EXPECT_TT(Pristine(4).ok());
}

TEST(Marking, Distinct) { 
  for (auto s = -32768; s != 32767; ++s)
    EXPECT_NE(s, flip(s)) << s;
}

TEST(Marking, Pairs) { 
  EXPECT_LT(flip($P_f$), $A_f$);   
  EXPECT_LT(flip($P_t$), $A_f$);   
  EXPECT_LT(flip(($P_f$ + $P_t$)/2), $A_f$);   
  EXPECT_LT(flip($P_f$-1), $A_f$);   
  EXPECT_LT(flip($P_f$+1), $A_f$);   
  EXPECT_EQ(flip(flip($P_f$)), $P_f$);
  EXPECT_EQ(flip(flip($P_t$)), $P_t$);
  EXPECT_EQ(flip(flip(($P_f$ + $P_t$)/2)),($P_f$ + $P_t$)/2);
  EXPECT_EQ(flip(flip($P_t$ + 1)),$P_t$ + 1 );
  EXPECT_EQ(flip(flip($P_t$ + 1)), $P_t$ + 1);
}

TEST(Marking, Atoms) { 
  EXPECT_GT(flip($A_f$), $A_t$);   
  EXPECT_LT(flip($A_t$),0);
  EXPECT_GT(flip(($A_f$ + $A_t$)/2), $P_t$);   
  EXPECT_GT(flip($A_t$ - 1), $P_t$);   
  EXPECT_GT(flip($A_f$ - 1), $P_t$);   
  EXPECT_EQ(flip(flip($A_f$)), $A_f$);
  EXPECT_EQ(flip(flip($A_f$ + 1)),$A_f$ + 1 );
  EXPECT_EQ(flip(flip($A_t$ + 1)), $A_t$ + 1);
  EXPECT_EQ(flip(flip($A_t$)), $A_t$);
  EXPECT_EQ(flip(flip(($A_f$ + $A_t$)/2)),($A_f$ + $A_t$)/2);
}

TEST(Marking, Bounds) { 
  EXPECT_LT(flip($P_f$), $P_f$);   
  EXPECT_LT(flip($P_t$), $P_t$);   
  EXPECT_LT(flip(($P_f$ + $P_t$)/2), $A_f$);
  EXPECT_LT(flip($P_f$-1), $X_f$);
  EXPECT_LT(flip($P_f$+1), $X_f$);   
  EXPECT_EQ(flip(flip($P_f$)), $P_f$);
  EXPECT_EQ(flip(flip($P_t$)), $P_t$);
  EXPECT_EQ(flip(flip(($P_f$ + $P_t$)/2)),($P_f$ + $P_t$)/2);
  EXPECT_EQ(flip(flip($P_f$ - 1)),$P_f$ - 1 );
  EXPECT_EQ(flip(flip($P_f$ + 1)), $P_f$ + 1);
  EXPECT_EQ(flip(flip($P_t$ - 1)),$P_t$ - 1 );
  EXPECT_EQ(flip(flip($P_t$ + 1)), $P_t$ + 1);
}

TEST(Marking, Atoms1) { 
  EXPECT_GT(flip($A_f$), $X_t$);   
  EXPECT_LT(flip($A_t$), $A_f$);
  EXPECT_GT(flip(($A_f$ + $A_t$)/2), $X_t$);
  EXPECT_GT(flip($A_t$-1), $X_t$);   
  EXPECT_GT(flip($A_f$+1), $X_t$);   
  EXPECT_EQ(flip(flip($A_f$)),$A_f$);
  EXPECT_EQ(flip(flip($A_t$)),$A_t$);
  EXPECT_EQ(flip(flip(($A_f$ + $A_t$)/2)),($A_f$ + $A_t$)/2);
  EXPECT_EQ(flip(flip($A_f$ - 1)), $A_f$ - 1 );
  EXPECT_EQ(flip(flip($A_t$ - 1)), $A_t$ - 1);
  EXPECT_EQ(flip(flip($A_f$ + 1)), $A_f$ + 1 );
  EXPECT_EQ(flip(flip($A_t$ + 1)), $A_t$ + 1);
}
