#include "Pair.h"

#include "Short.h"
#include "layout.h"
// Properties:
Property(Word& Pair::p) Is(P[handle()])
Property(Boolean  Pair::ok) Is(white(car().handle()) && white(cdr().handle()))
Property(Sx  Pair::car) Is(p().s1)
Property(Sx  Pair::cdr) Is(p().s2)

Pair::Pair(Short s): Sx(s) {}
Pair Pair::car(Sx s) { p().s1 = s.handle(); return *this; }
Pair Pair::cdr(Sx s) { p().s2 = s.handle(); return *this; }
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
  EXPECT_EQ(P[c1.handle()].hash(), Word(13,13).hash());
  Word w = hash13();
  auto c2 = require(w.s1, w.s2);
  auto h1 = c1.handle(), h2 = c2.handle();
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
