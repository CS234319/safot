#include "Pair.h"

#include "Sx.h"
#include "Short.h"

// Properties:
Property(Sx  Pair::car) Is(Sx(s1()))
Property(Sx  Pair::cdr) Is(Sx(s2()))
Property(Boolean  Pair::ok) Is(white(s1()) && white(s2()))

Pair::Pair(Short s): Knob(s) {}
Pair Pair::car(Sx s) { s1(s.inner()); return *this; }
Pair Pair::cdr(Sx s) { s2(s.inner()); return *this; }
Boolean Pair::ok(Word w) { return white(w.s1) && white(w.s2); } 

Short Pair::count = 0;
Integer Pair::reuse = 0;
Integer Pair::miss = 0;
#include "layout.h"
#include "heap.h"
#include "Pristine.h"
#include "Word.h"

#include "Test.h" 

Word hash13() {
  auto const h = Word(13,13).hash();
  for (int i = 1; ; ++i) {
    Word w;
    w.l = i;
    if (w.hash() == h)
      return w;
  }
}

TEST(Pair, Hash13) {
  Word w = hash13();
  EXPECT_NE(w.l, Word(13,13).l);
  EXPECT_NE(w.l, 13);
  EXPECT_NE(w.s1, 13);
  EXPECT_NE(w.s2, 13);
  EXPECT_TT(white(w.s1));
  EXPECT_TT(white(w.s2));
  EXPECT_EQ(w.hash(), Word(13,13).hash());
}

TEST(Pair, Hash13a) {
  heapify();
  auto c1 = require(13,13); 
  EXPECT_EQ(P[c1.inner()].hash(), Word(13,13).hash());
  Word w = hash13();
  auto c2 = require(w.s1, w.s2);
  auto h1 = c1.inner(), h2 = c2.inner();
  EXPECT_NE(h1, h2);
  EXPECT_EQ(P[h1].hash(), P[h2].hash());

  EXPECT_EQ(Pair::miss, 1);
  EXPECT_ZZ(Pair::reuse);
  EXPECT_EQ(Pair::count, 2);
}

TEST(Pair, count) {
  heapify();
  EXPECT_ZZ(Pair::count);
  for (int i = 0;  i <= 4; i++)  
    for (int j = 0;  j <= 4; j++) 
      require(i,j);
  EXPECT_EQ(Pair::count, 25);
}

TEST(Pair, reuse) {
  heapify();
  EXPECT_ZZ(Pair::reuse);
  for (int i = 0;  i <= 4; i++)  
    for (int j = 0;  j <= 4; j++) 
      require(i,j);
  EXPECT_ZZ(Pair::reuse);
  for (int i = 0;  i <= 4; i++)  
    for (int j = 0;  j <= 4; j++) 
      require(i,j);
  EXPECT_EQ(Pair::reuse, 25);
  for (int i = 0;  i <= 4; i++)  
    for (int j = 0;  j <= 4; j++) 
      require(i,j);
  EXPECT_EQ(Pair::reuse, 50);
}

TEST(Pair, Miss) {
  enum { N = 220 };
  heapify();
  EXPECT_ZZ(Pair::miss);
  int n = 0;
  for (int i = 0;  i < N; i++) { 
    for (int j = 0;  j < N; j++) {
      require(i,j);
      ++n;
      if (Pair::miss > 5) 
        break;
    }
    if (Pair::miss > 5) 
      break;
  }
  EXPECT_EQ(n,Pair::count);
  EXPECT_GT(n * n,$P_n$);
  EXPECT_LT(n,N * N / 2);
  EXPECT_GT(Pair::miss,0);
  EXPECT_EQ(Pair::miss,6);
  EXPECT_ZZ(Pair::reuse);
  EXPECT_EQ(Pair::count,n);
}
