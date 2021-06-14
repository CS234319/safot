#include "store.h"

static Half init();
static Half next = init();

static Half mark(Half h); 
static void mark(Pair &p);

#define DIE die(__LINE__) 

bool inline die(int t) {
  throw t;
}
#include "colors.h"

Half free($S_X$ s) {
  auto const h = s.handle;
  is.red(next) || DIE;
  is.black(h) || DIE;
  paint.red(h);
  is.red(h) || DIE;
  set.red(h).next(next); 
  set.red(h).prev($P_x$); 
  set.red(next).prev(h);
  return next = h;
}

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
    paint.red(h);
  return next = $P_f$;
}


static $S_X$ make(Pair p) {
  assume.red.prev(next) == $P_x$ || DIE; 
  auto h = next;
  next = assume.red.next(next);
  assume.red.prev(next) == h || DIE;
  set.red(next).prev($P_x$);  
  P[h] = p;

  is.white(h)  || DIE;
  assume.white.car(h) == p.car || DIE; 
  assume.white.cdr(h) == p.cdr || DIE; 
  p.cons == P[h].cons ||  DIE;
  return h;
}

static $S_X$ require(Pair p) {
  const Half h = $P_f$ + (p.cons ^ (p.cons << 7) ^ (p.cons >> 3)) % $P_n$;
  if (P[h].cons == p.cons) 
    return h;
  if (h == next || isnt.red(h))
    return make(p);
  const Half prev = assume.red.prev(h), next = assume.red.next(h);
  P[h] = p;
  if (prev != $P_x$) set.red(prev).next(next);
  if (next != $P_x$) set.red(next).prev(prev); 
  is.white(h)  || DIE;
  p.cons == P[h].cons || DIE;
  return h;
}

$S_X$ make(Half car, Half cdr) { return make(Pair(car,cdr)); }
$S_X$ require(Half car, Half cdr) { return require(Pair(car,cdr)); }

#include <stdio.h>

Half length() {
  Half result = 0;
  for (Half h = next; h != $P_x$; h = assume.red.next(h)) // printf("%d ", h), 
      ++result;
  return result;
}

#undef min
#undef max
#undef data
#undef function
#undef Type

int valid() {
  Half length = 0;
  for (Half h = next, h2 = h ; h != $P_x$; h = assume.red.next(h)) { 
    ++length;
    if (isnt.red(h)) return length; 
    if (h2 != $P_x$) h2 = assume.red.next(h2);
    if (h2 != $P_x$) h2 = assume.red.next(h2);
    if (h == h2) return -length; 
  } 
  return 0;
}

#include "gtest/gtest.h"
TEST(Colors,is) { 
  init();
  auto s = make(12,14);
  auto h = s.handle;
  EXPECT_TRUE(is.white(h));
  EXPECT_FALSE(is.red(h));
  EXPECT_FALSE(is.black(h));
  EXPECT_FALSE(isnt.white(h));
  EXPECT_TRUE(isnt.red(h));
  EXPECT_TRUE(isnt.black(h));
  paint.red(h);
  EXPECT_FALSE(is.white(h));
  EXPECT_TRUE(is.red(h));
  EXPECT_FALSE(is.black(h));
  EXPECT_TRUE(isnt.white(h));
  EXPECT_FALSE(isnt.red(h));
  EXPECT_FALSE(isnt.black(h));
  paint.black(h);
  EXPECT_FALSE(is.white(h));
  EXPECT_FALSE(is.red(h));
  EXPECT_TRUE(is.black(h));
  EXPECT_TRUE(isnt.white(h));
  EXPECT_TRUE(isnt.red(h));
  EXPECT_FALSE(isnt.black(h));
}

TEST(Words, Init) { 
  init();
  EXPECT_NE(next, $P_x$);
  EXPECT_EQ(next, 1);
  EXPECT_EQ(next, $P_f$);
  EXPECT_EQ(assume.red.next(1), 2);
  EXPECT_EQ(assume.red.prev(1), 0);
  EXPECT_EQ(assume.red.next(2), 3);
  EXPECT_EQ(assume.red.prev(2), 1);
  EXPECT_EQ(assume.red.prev($P_t$), $P_t$-1);
  EXPECT_EQ(assume.red.next($P_t$), $P_x$);
  EXPECT_EQ(length(), $P_n$);
}

TEST(Words, MakeLength1) { 
  init();
  EXPECT_EQ(valid(),0);
  EXPECT_EQ(next,1);
  auto s1 = make(2,3);
  EXPECT_EQ(next,2);
  EXPECT_EQ(s1.handle,1);
  EXPECT_EQ(P[s1.handle].car,2);
  EXPECT_EQ(P[s1.handle].cdr,3);
  EXPECT_EQ(valid(),0);
  EXPECT_EQ(length(), $P_n$-1);
}

TEST(Words, MakeLength2) { 
  init();
  EXPECT_EQ(valid(),0);
  EXPECT_EQ(next,1);
  auto s1 = make(2,3);
  EXPECT_EQ(next,2);
  EXPECT_EQ(s1.handle,1);
  EXPECT_EQ(P[s1.handle].car,2);
  EXPECT_EQ(P[s1.handle].cdr,3);
  EXPECT_EQ(valid(),0);
  EXPECT_EQ(length(), $P_n$-1);
  auto s2 = make(4,5);
  EXPECT_EQ(next,3);
  EXPECT_EQ(s2.handle,2);
  EXPECT_EQ(P[s2.handle].car,4);
  EXPECT_EQ(P[s2.handle].cdr,5);
  EXPECT_EQ(valid(),0);
  EXPECT_EQ(length(), $P_n$-2);
  auto s3 = make(6,7);
  EXPECT_EQ(next,4);
  EXPECT_EQ(s3.handle,3);
  EXPECT_EQ(P[s3.handle].car,6);
  EXPECT_EQ(P[s3.handle].cdr,7);
  EXPECT_EQ(valid(),0);
  EXPECT_EQ(length(), $P_n$-3);
}

TEST(Words, RequireLength2) { 
  init();
  EXPECT_EQ(valid(),0);
  EXPECT_EQ(next,1);
  auto s1 = require(2,3);
  EXPECT_EQ(next,1);
  EXPECT_NE(s1.handle,1);
  EXPECT_EQ(P[s1.handle].car,2);
  EXPECT_EQ(P[s1.handle].cdr,3);
  EXPECT_EQ(valid(),0);
  EXPECT_EQ(length(), $P_n$-1);
  auto s2 = require(4,5);
  EXPECT_EQ(P[s2.handle].car,4);
  EXPECT_EQ(P[s2.handle].cdr,5);
  EXPECT_EQ(valid(),0);
  EXPECT_EQ(next,1);
  EXPECT_EQ(length(), $P_n$-2);
  auto s3 = require(6,7);
  EXPECT_EQ(next,1);
  EXPECT_EQ(P[s3.handle].car,6);
  EXPECT_EQ(P[s3.handle].cdr,7);
  EXPECT_EQ(valid(),0);
  EXPECT_EQ(length(), $P_n$-3);
}

TEST(Words, MakeLength3) { 
  init();
  auto s1 = make(2,3);
  auto s2 = make(4,5);
  auto s3 = make(6,7);
  free(s1);
  EXPECT_EQ(next, 1);
}


TEST(Words, Reuse) { 
  init();
  EXPECT_EQ(valid(),0);
  auto s1 = require(0,0);
  EXPECT_EQ(valid(),0);
  auto s2 = require(2,3);
  EXPECT_EQ(valid(),0);
  auto s3 = require(3,2);
  EXPECT_EQ(valid(),0);
  auto s4 = require(2,3);
  EXPECT_EQ(valid(),0);
  auto s5 = require(0,0);
  EXPECT_EQ(valid(),0);
  auto s6 = require(3,2);
  EXPECT_EQ(valid(),0);
  EXPECT_EQ(s1.handle, s5.handle);
  EXPECT_EQ(s2.handle, s4.handle);
  EXPECT_EQ(s3.handle, s6.handle);
  EXPECT_EQ(length(), $P_n$-3);
  EXPECT_FALSE(is.red(s1.handle));
  EXPECT_TRUE(is.red(s1.handle));
  EXPECT_EQ(valid(),0);
  free(s2);
  EXPECT_TRUE(is.red(s1.handle));
  EXPECT_EQ(valid(),0);
  EXPECT_FALSE(is.red(s3.handle));
  EXPECT_FALSE(is.red(s6.handle));
  free(s3);
  EXPECT_TRUE(is.red(s6.handle));
  EXPECT_TRUE(is.red(s3.handle));
  EXPECT_EQ(valid(),0);
  free(s3);
  free(s5);
  free(s4);
  EXPECT_TRUE(is.red(s1.handle));
  EXPECT_TRUE(is.red(s2.handle));
  EXPECT_TRUE(is.red(s3.handle));
  EXPECT_EQ(valid(),0);
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
  EXPECT_GT(mark($A_t$-1), $P_t$);   
  EXPECT_GT(mark($A_f$+1), $P_t$);   
  EXPECT_EQ(mark(mark($A_f$)), $A_f$);
  EXPECT_EQ(mark(mark($A_t$)), $A_t$);
  EXPECT_EQ(mark(mark(($A_f$ + $A_t$)/2)),($A_f$ + $A_t$)/2);
  EXPECT_EQ(mark(mark($A_f$ + 1)),$A_f$ + 1 );
  EXPECT_EQ(mark(mark($A_t$ + 1)), $A_t$ + 1);
}

TEST(Marking, MarkingIsMarked) { 
  init();
  for (Half h = $X_f$; h <= $X_t$; ++h)
    EXPECT_TRUE(is.red(h));
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
  EXPECT_EQ(mark(mark($P_f$ - 1)),$P_f$ + 1 );
  EXPECT_EQ(mark(mark($P_f$ + 1)), $P_f$ + 1);
  EXPECT_EQ(mark(mark($P_t$ - 1)),$P_t$ + 1 );
  EXPECT_EQ(mark(mark($P_t$ + 1)), $P_t$ + 1);
}

TEST(Marking, Atoms1) { 
  EXPECT_GT(mark($A_f$), $X_t$);   
  EXPECT_LT(mark($A_t$), $A_f$);
  EXPECT_GT(mark(($A_t$ + $A_t$)/2), $X_t$);
  EXPECT_GT(mark($A_t$-1), $X_t$);   
  EXPECT_GT(mark($A_f$+1), $X_t$);   
  EXPECT_EQ(mark(mark($A_f$)),$A_f$);
  EXPECT_EQ(mark(mark($A_t$)),$A_t$);
  EXPECT_EQ(mark(mark(($A_t$ + $A_t$)/2)),($A_f$ + $A_t$)/2);
  EXPECT_EQ(mark(mark($A_f$ - 1)), $A_f$ - 1 );
  EXPECT_EQ(mark(mark($A_t$ - 1)), $A_t$ - 1);
  EXPECT_EQ(mark(mark($A_f$ + 1)), $A_f$ + 1 );
  EXPECT_EQ(mark(mark($A_t$ + 1)), $A_t$ - 1);
}

