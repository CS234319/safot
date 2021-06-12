#include "store.h"

static Half init();
static Half next = init();

static Half flip(Half h); 
static bool red(Half h); 
static void flip(Pair &p);
static bool red(Pair p); 


static Half init() {
  for (Half h = $P_f$  + 1; h < $P_t$; ++h) {
    P[h].prev = h - 1;
    P[h].next = h + 1;
  }
  P[$P_f$].prev = $P_x$;
  P[$P_f$].next = $P_f$  + 1;
  P[$P_t$].prev = $P_t$ - 1;
  P[$P_t$].next = $P_x$;
  for (Half h = $P_f$; h <= $P_t$; ++h) 
    flip(P[h]);
  return $P_f$;
}

static Half make(Pair p) {
  const Half h = $P_f$ + (p.cons ^ (p.cons << 7) ^ (p.cons >> 3)) % $P_n$;
  if (P[h].cons == p.cons) 
    return h;
  if (h == next || !red(P[h])) {
    flip(P[next]);
    next = P[next].next;
    flip(P[next]);
    P[h] = p;
    return h;
  }
  flip(P[h]);
  const Half prev = P[h].prev, next = P[h].next;
  if (prev != $P_x$) {
    flip(P[prev]);
    P[prev].next = next; 
    flip(P[prev]);
  }
  if (next != $P_x$) {
    flip(P[next]);
    P[next].prev = prev; 
    flip(P[next]);
  }
  return h;
}

S make(Half car, Half cdr) {
  return make(Pair(car,cdr));
}

int remaining;

void free(Half h) {
  P[h].next = next; 
  P[h].prev = $P_x$; 
  flip(P[next]);
  P[next].prev = h;
  remaining++; 
  next = h;
}

Half flip(Half h)  { return h + (1 << 15); } 
bool red(Half h)   { return h < $X_f$ || h > $X_t$; } 
void flip(Pair &p) { p.car = flip(p.car); }
bool red(Pair p)   { return red(p.car);  }

#undef min
#undef max
#undef data
#undef function
#undef Type

#include "gtest/gtest.h"

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
  EXPECT_GT(flip($A_t$-1), $P_t$);   
  EXPECT_GT(flip($A_f$+1), $P_t$);   
  EXPECT_EQ(flip(flip($A_f$)), $A_f$);
  EXPECT_EQ(flip(flip($A_t$)), $A_t$);
  EXPECT_EQ(flip(flip(($A_f$ + $A_t$)/2)),($A_f$ + $A_t$)/2);
  EXPECT_EQ(flip(flip($A_f$ + 1)),$A_f$ + 1 );
  EXPECT_EQ(flip(flip($A_t$ + 1)), $A_t$ + 1);
}

TEST(Marking, MarkingIsMarked) { 
  for (Half h = $X_f$; h <= $X_t$; ++h)
    EXPECT_TRUE(red(flip(h)));
}


