#include "Cons.h"

#include "Short.h"

// Properties:
Property(Handle  Cons::car) Is(s1())
Property(Handle  Cons::cdr) Is(s2())
Property(Boolean  Cons::ok) Is(white(s1()) && white(s2()))

Cons::Cons(Short s): Knob(s) {}
Cons Cons::car(Short h) { s1(h); return *this; }
Cons Cons::cdr(Short h) { s2(h); return *this; }
Boolean Cons::ok(Word w) { return white(w.s1) && white(w.s2); } 

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

TEST(Cons, Hash13) {
  Word w = hash13();
  EXPECT_NE(w.l, Word(13,13).l);
  EXPECT_NE(w.l, 13);
  EXPECT_NE(w.s1, 13);
  EXPECT_NE(w.s2, 13);
  EXPECT_TT(white(w.s1));
  EXPECT_TT(white(w.s2));
  EXPECT_EQ(w.hash(), Word(13,13).hash());
}

TEST(Cons, Hash13a) {
  heapify();
  auto c1 = require(13,13); 
  EXPECT_EQ(P[c1.inner()].hash(), Word(13,13).hash());
  Word w = hash13();
  auto c2 = require(w.s1, w.s2);
  auto h1 = c1.inner(), h2 = c2.inner();
  EXPECT_NE(h1, h2);
  EXPECT_EQ(P[h1].hash(), P[h2].hash());

  EXPECT_EQ(Cons::miss, 1);
  EXPECT_ZZ(Cons::reuse);
  EXPECT_EQ(Cons::count, 2);
}


TEST(Cons, count) {
  heapify();
  EXPECT_ZZ(Cons::count);
  for (int i = 0;  i <= 4; i++)  
    for (int j = 0;  j <= 4; j++) 
      require(i,j);
  EXPECT_EQ(Cons::count, 25);
}

TEST(Cons, reuse) {
  heapify();
  EXPECT_ZZ(Cons::reuse);
  for (int i = 0;  i <= 4; i++)  
    for (int j = 0;  j <= 4; j++) 
      require(i,j);
  EXPECT_ZZ(Cons::reuse);
  for (int i = 0;  i <= 4; i++)  
    for (int j = 0;  j <= 4; j++) 
      require(i,j);
  EXPECT_EQ(Cons::reuse, 25);
  for (int i = 0;  i <= 4; i++)  
    for (int j = 0;  j <= 4; j++) 
      require(i,j);
  EXPECT_EQ(Cons::reuse, 50);
}

TEST(Cons, Miss) {
  enum { N = 220 };
  heapify();
  EXPECT_ZZ(Cons::miss);
  int n = 0;
  for (int i = 0;  i < N; i++) { 
    for (int j = 0;  j < N; j++) {
      require(i,j);
      ++n;
      if (Cons::miss > 5) 
        break;
    }
    if (Cons::miss > 5) 
      break;
  }
  EXPECT_EQ(n,Cons::count);
  EXPECT_GT(n * n,$P_n$);
  EXPECT_LT(n,N * N / 2);
  EXPECT_GT(Cons::miss,0);
  EXPECT_EQ(Cons::miss,6);
  EXPECT_ZZ(Cons::reuse);
  EXPECT_EQ(Cons::count,n);
}
