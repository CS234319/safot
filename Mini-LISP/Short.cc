#include "Short.h"
#include "layout.h"

#include <iostream>
extern Short mark(Short h)   { return h + (1 << 15); } 
extern bool marked(Short h) { return h < $X_f$ || h > $X_t$ + 1; } 

extern void stain(Short &s) {
  Promise(marked(s));
  if (!marked(s)) s = mark(s);
}

extern void cleanse(Short &s) {
  Promise(!marked(s));
  if (marked(s)) s = mark(s);
}
#include <stdio.h>
#include "Pristine.h"
#undef Type
#undef function

#include "gtest/gtest.h"

TEST(Stain, Short) {
  Short s = 12;
  EXPECT_EQ(12,s);
  EXPECT_NE(12,mark(s));
  EXPECT_FALSE(marked(12));
  EXPECT_FALSE(marked(12));
  stain(s);
  EXPECT_NE(12,s);
  EXPECT_TRUE(marked(s));
  cleanse(s);
  EXPECT_EQ(12,s);
}

TEST(Stain, Word) {
  P[4].s1 = 3;
  P[4].s2 = 2;
  EXPECT_FALSE(Pristine(4).ok());
  EXPECT_FALSE(marked(Knob(4).s1()));
  stain(P[4].s1); 
  EXPECT_TRUE(marked(Knob(4).s1()));
  EXPECT_FALSE(Pristine(4).ok());
  stain(P[4].s2); 
  EXPECT_TRUE(Pristine(4).ok());
}

TEST(Mark, Distinct) { 
  for (auto h = -32768; h != 32767; ++h)
    EXPECT_NE(h, mark(h)) << h;
}

TEST(Mark, Last) {
  EXPECT_FALSE(marked($P_t$ + 1));
}

TEST(Marking, Pairs) { 
  EXPECT_LT(mark($P_f$), $A_f$);   
  EXPECT_LT(mark($P_t$), $A_f$);   
  EXPECT_LT(mark(($P_f$ + $P_t$)/2), $A_f$);   
  EXPECT_LT(mark($P_f$-1), $A_f$);   
  EXPECT_LT(mark($P_f$+1), $A_f$);   
  EXPECT_EQ(mark(mark($P_f$)), $P_f$);
  EXPECT_EQ(mark(mark($P_t$)), $P_t$);
  EXPECT_EQ(mark(mark(($P_f$ + $P_t$)/2)),($P_f$ + $P_t$)/2);
  EXPECT_EQ(mark(mark($P_t$ + 1)),$P_t$ + 1 );
  EXPECT_EQ(mark(mark($P_t$ + 1)), $P_t$ + 1);
}

TEST(Marking, Atoms) { 
  EXPECT_GT(mark($A_f$), $A_t$);   
  EXPECT_LT(mark($A_t$),0);
  EXPECT_GT(mark(($A_f$ + $A_t$)/2), $P_t$);   
  EXPECT_GT(mark($A_t$ - 1), $P_t$);   
  EXPECT_GT(mark($A_f$ - 1), $P_t$);   
  EXPECT_EQ(mark(mark($A_f$)), $A_f$);
  EXPECT_EQ(mark(mark($A_f$ + 1)),$A_f$ + 1 );
  EXPECT_EQ(mark(mark($A_t$ + 1)), $A_t$ + 1);
  EXPECT_EQ(mark(mark($A_t$)), $A_t$);
  EXPECT_EQ(mark(mark(($A_f$ + $A_t$)/2)),($A_f$ + $A_t$)/2);
}

TEST(Marking, Bounds) { 
  EXPECT_LT(mark($P_f$), $P_f$);   
  EXPECT_LT(mark($P_t$), $P_t$);   
  EXPECT_LT(mark(($P_f$ + $P_t$)/2), $A_f$);
  EXPECT_LT(mark($P_f$-1), $X_f$);
  EXPECT_LT(mark($P_f$+1), $X_f$);   
  EXPECT_EQ(mark(mark($P_f$)), $P_f$);
  EXPECT_EQ(mark(mark($P_t$)), $P_t$);
  EXPECT_EQ(mark(mark(($P_f$ + $P_t$)/2)),($P_f$ + $P_t$)/2);
  EXPECT_EQ(mark(mark($P_f$ - 1)),$P_f$ - 1 );
  EXPECT_EQ(mark(mark($P_f$ + 1)), $P_f$ + 1);
  EXPECT_EQ(mark(mark($P_t$ - 1)),$P_t$ - 1 );
  EXPECT_EQ(mark(mark($P_t$ + 1)), $P_t$ + 1);
}

TEST(Marking, Atoms1) { 
  EXPECT_GT(mark($A_f$), $X_t$);   
  EXPECT_LT(mark($A_t$), $A_f$);
  EXPECT_GT(mark(($A_f$ + $A_t$)/2), $X_t$);
  EXPECT_GT(mark($A_t$-1), $X_t$);   
  EXPECT_GT(mark($A_f$+1), $X_t$);   
  EXPECT_EQ(mark(mark($A_f$)),$A_f$);
  EXPECT_EQ(mark(mark($A_t$)),$A_t$);
  EXPECT_EQ(mark(mark(($A_f$ + $A_t$)/2)),($A_f$ + $A_t$)/2);
  EXPECT_EQ(mark(mark($A_f$ - 1)), $A_f$ - 1 );
  EXPECT_EQ(mark(mark($A_t$ - 1)), $A_t$ - 1);
  EXPECT_EQ(mark(mark($A_f$ + 1)), $A_f$ + 1 );
  EXPECT_EQ(mark(mark($A_t$ + 1)), $A_t$ + 1);
}
