#include "heap.h"

#include "text.h"
#include "Pushdown.h"
#include "Pristine.h"
#include "Short.h"
#include "Pair.h"
#include "Sx.h"

#include "corrupted.h"

#include "stdio.h"

#include "Test.h"
#include "mark.h"


TEST(Heapify, exists) { 
  heapify();
}

TEST(Heapify, head) { 
  heapify();
  EXPECT_FF(heap.x());
}

TEST(Heapify, allPristine) { 
  heapify();
  for (Short s = $P_f$; s <= $P_t$; ++s)
    ASSERT_TRUE(Pristine(s).ok()) << s;
}

TEST(Heapify, entryFirst) { 
  heapify();
  EXPECT_TT(Pristine($P_f$).prev().x()); 
  EXPECT_FF(Pristine($P_f$).next().x()); 
  EXPECT_EQ(Pristine($P_f$).next().handle(), $P_f$+1); 
}

TEST(Heapify, entryLast) { 
  heapify();
  EXPECT_TT(Pristine($P_t$).next().x()); 
  EXPECT_FF(Pristine($P_t$).prev().x()); 
  EXPECT_EQ(Pristine($P_t$).prev().handle(), $P_t$-1); 
}

TEST(Heapify, entry5) { 
  const Short s = 5;
  auto p = Pristine(s);
  EXPECT_FF(p.x());
  Pristine(s).prev(Pristine(s-1)).next(Pristine(s+1));
  auto k = Knob(s);
  EXPECT_TT(black(k.s1()));
  EXPECT_TT(black(k.s2()));
  EXPECT_EQ(flip(k.s1()), s-1);
  EXPECT_EQ(flip(k.s2()), s + 1);

  EXPECT_EQ(p.handle(), 5);
  EXPECT_EQ(p.prev().handle(), 4);
  EXPECT_EQ(p.next().handle(), 6);
  EXPECT_TT(p.ok());
}

TEST(Heapify, entryBetween) { 
  heapify();
  for (Short s = $P_f$ + 1; s < $P_t$; ++s) {
    EXPECT_EQ(Pristine(s).prev().handle(), s-1) << s; 
    EXPECT_EQ(Pristine(s).next().handle(), s+1) << s; 
  }
}

TEST(Heapify, prefix) { 
  heapify();
  EXPECT_EQ(heap.handle(), $P_f$);
  EXPECT_EQ(heap.handle(), $P_f$);
  EXPECT_EQ(Pristine($P_f$).next().handle(), 2);
  EXPECT_ZZ(Pristine($P_f$).prev().handle());
  EXPECT_EQ(Pristine(2).next().handle(), 3);
  EXPECT_EQ(Pristine(2).prev().handle(), $P_f$);
  EXPECT_EQ(Pristine($P_t$).prev().handle(), $P_t$-1);
  EXPECT_EQ(Pristine($P_t$).next().handle(), $P_x$);
}

TEST(Heapify, counters) { 
  heapify();
  EXPECT_ZZ(Pair::count);
  EXPECT_ZZ(Pair::miss);
  EXPECT_ZZ(Pair::reuse);
  EXPECT_ZZ(Item::count);
  EXPECT_EQ(Pristine::count, $P_n$);
}

TEST(Heapify, pristines) { 
  heapify();
  EXPECT_FF(corrupted.pristines());
}

TEST(Heapify, items) { 
  heapify();
  EXPECT_FF(corrupted.items());
}

TEST(Heapify, pairs) { 
  heapify();
  EXPECT_FF(corrupted.pairs());
}

TEST(Heapify, symmetric) { 
  heapify();
  EXPECT_FF(corrupted.asymmetric());
}

TEST(Heapify, acyclic) { 
  heapify();
  EXPECT_FF(corrupted.cyclic());
}

TEST(Heapify, weirdos) { 
  heapify();
  EXPECT_FF(corrupted.weirdos());
}

TEST(Heapify, valid) { 
  heapify();
  EXPECT_FF(corrupted.something());
}

TEST(Item, 3Count) {
  Pushdown p;
  p.clear();
  EXPECT_TT(p.top.x());
  EXPECT_TT(p.empty());
  EXPECT_GE(Item::count,0);
  int before = Item::count;
  p.push(3);
  EXPECT_EQ(Item::count, before + 1);
  p.push(2);
  EXPECT_EQ(Item::count, before + 2);
  EXPECT_EQ(2,p.pop());
  EXPECT_EQ(Item::count, before + 1);
  EXPECT_EQ(3,p.pop());
  EXPECT_EQ(Item::count, before);
  EXPECT_TT(p.empty());
  EXPECT_TT(p.top.x());
}
TEST(Corruption, makeCyclic) { 
  try {
    heapify();
    EXPECT_FF(corrupted.cyclic());
    Pristine($P_t$-3).next(($P_f$ + $P_t$)/2);
    EXPECT_TT(corrupted.cyclic());
  } catch(int e) {
    ADD_FAILURE() << "Died at line " << e;
  }
}

TEST(Corruption, ofPrev) { 
  try {
    heapify();
    Pristine($P_t$).prev(($P_f$ + $P_t$)/2);
    EXPECT_TT(corrupted.asymmetric());
  } catch(int e) {
    ADD_FAILURE() << "Died at line " << e;
  }
}

TEST(Corruption, ofNext) { 
  try {
    heapify();
    Pristine(Word(13,17).hash()).next(Word(17,13).hash());
    EXPECT_TT(corrupted.asymmetric());
  } catch(int e) {
    ADD_FAILURE() << "Died at line " << e;
  }
}

TEST(Corruption, selfLoop) { 
  try {
    heapify();
    Pristine(Word(13,17).hash()).next(Word(13,17).hash());
    EXPECT_TT(corrupted.cyclic());
  } catch(int e) {
    ADD_FAILURE() << "Died at line " << e;
  }
}

TEST(Fresh, exists) { 
  heapify();
  fresh(15,21);
}

TEST(Fresh, uncorrupting) {
  heapify();
  fresh(15,$P_x$);
  EXPECT_FF(corrupted.something());
}

TEST(Fresh, correct) { 
  heapify();
  Item i = fresh(15,$P_x$);
  EXPECT_TT(i.ok());
  EXPECT_EQ(i.handle(), 1);
  EXPECT_EQ(heap.handle(), 2);
  EXPECT_EQ(i.head(), 15);
  EXPECT_EQ(i.rest().handle(), $P_x$);
  EXPECT_TT(i.ok());
  EXPECT_FF(Pair(i.handle()).ok());
  EXPECT_FF(Pristine(i.handle()).ok());
}

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

TEST(Pair, require) {
  heapify();
  auto d1 = require(-3,-2).handle();
  auto l1 = require(-2,-3).handle();
  auto d2 = require(d1,d1).handle();
  auto l2 = require(l1,-4).handle();
  auto d3 = require(d1,d2).handle();
  auto l3 = require(l2,-5).handle();
  auto d4 = require(d3,d2).handle();
  auto l4 = require(l2,l3).handle();
  auto d5 = require(d4,d3).handle();
  auto l5 = require(l4,l4).handle();

#define XE6(y1,y2,y3,y4,y5,y6) NE4(y1,y2,y3,y4,y5)  XE5(y2,y3,y4,y5,y6)
#define XE5(y1,y2,y3,y4,y5)    NE4(y1,y2,y3,y4,y5)  XE4(y2,y3,y4,y5)
#define XE4(y1,y2,y3,y4)       NE3(y1,y2,y3,y4)     XE3(y2,y3,y4)
#define XE3(y1,y2,y3)          NE2(y1,y2,y3)        XE2(y2,y3)
#define XE2(y1,y2)             NE1(y1,y2)           XE1(y2)
#define XE1(y1)                NE0(y1)              XE0()
#define XE0()                  NE0()                


#define NE5(x,y1,y2,y3,y4,y5) NE(x,y1)NE4(x,y2,y3,y4,y5); 
#define NE4(x,y1,y2,y3,y4)    NE(x,y1)NE3(x,y2,y3,y4) 
#define NE3(x,y1,y2,y3)       NE(x,y1)NE2(x,y2,y3)
#define NE2(x,y1,y2)          NE(x,y1)NE1(x,y2)
#define NE1(x,y1)             NE(x,y1)NE0(x)
#define NE0(x)

#define NE(x,y)               EXPECT_NE(x,y);

  XE5(d1,d2,d3,d4,d5);
  XE5(l1,l2,l3,l4,l5);
  XE6(l1,d1,d2,d3,d4,d5);
  XE6(d1,l1,l2,l3,l4,l5);
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

TEST(Counters, freshFree) { 
  heapify();
  auto i = fresh(15,21);
  EXPECT_EQ(Pristine::count, $P_n$ -1);
  free(i);
  EXPECT_EQ(Pristine::count, $P_n$);
}

TEST(Fresh, 3) { 
  try {
    auto const s1 = fresh(2,3);
    auto const s2 = fresh(4,5);
    auto const s3 = fresh(6,7);
    free(s2);
    free(s1);
    free(s3);
  } catch(int e) {
    ADD_FAILURE() << "Died at line " << e;
  }
}

TEST(Fresh, Length) { 
  try {
    heapify();
    EXPECT_EQ(length(), $P_n$);
    EXPECT_EQ(length(), Pristine::count);

    auto const s1 = fresh(2,3);
    EXPECT_EQ(length(), $P_n$ - 1);
    EXPECT_EQ(length(), Pristine::count);

    auto const s2 = fresh(4,5);
    EXPECT_EQ(length(), $P_n$ - 2);
    EXPECT_EQ(length(), Pristine::count);

    auto const s3 = fresh(6,7);
    EXPECT_EQ(length(), $P_n$ - 3);
    EXPECT_EQ(length(), Pristine::count);

    free(s1);
    EXPECT_EQ(heap.handle(), 1);
    EXPECT_EQ(length(), $P_n$ - 2);
    EXPECT_EQ(length(), Pristine::count);

    free(s3);
    EXPECT_EQ(heap.handle(), 3);
    EXPECT_EQ(length(), $P_n$ - 1);
    EXPECT_EQ(length(), Pristine::count);

    free(s2);
    EXPECT_EQ(heap.handle(), 2);
    EXPECT_EQ(length(), $P_n$);
    EXPECT_EQ(length(), Pristine::count);
  } catch(int e) {
    ADD_FAILURE() << "Died at line " << e;
  }
}

TEST(Require, exists) { 
  try {
    heapify();
    require(Sx(0xDE),Sx(0xAD));
  } catch(int e) {
    ADD_FAILURE() << "Died at line " << e;
  }
}

TEST(Require, pair) { 
  try {
    heapify();
    Pair h = require(Sx(0xDE),Sx(0xAD));
    EXPECT_TT(h.ok());
  } catch(int e) {
    ADD_FAILURE() << "Died at line " << e;
  }
}

TEST(Require, correct) { 
  try {
    heapify();
    Short h = require(Sx(0xDE),Sx(0xAD)).handle();
    EXPECT_EQ(P[h].s1, 0xDE);
    EXPECT_EQ(P[h].s2, 0xAD);
  } catch(int e) {
    ADD_FAILURE() << "Died at line " << e;
  }
}

TEST(Require, 3) { 
  try {
    heapify();
    auto s1 = require(2,3);
    auto s2 = require(4,5);
    auto s3 = require(6,7);
  } catch(int e) {
    ADD_FAILURE() << "Died at line " << e;
  }
}

TEST(Require, correct3) { 
  heapify();
  EXPECT_FF(corrupted.asymmetric());
  EXPECT_EQ(heap.handle(),1);
  auto s1 = require(2,3);
  EXPECT_EQ(heap.handle(),1);
  EXPECT_NE(s1.handle(),1);
  EXPECT_EQ(P[s1.handle()].s1,2);
  EXPECT_EQ(P[s1.handle()].s2,3);
  EXPECT_FF(corrupted.asymmetric());
  EXPECT_EQ(length(), $P_n$-1);
  EXPECT_EQ(length(), Pristine::count);
  auto s2 = require(4,5);
  EXPECT_EQ(s2.car().handle(),4);
  EXPECT_EQ(s2.cdr().handle(),5);
  EXPECT_FF(corrupted.asymmetric());
  EXPECT_EQ(heap.handle(),1);
  EXPECT_EQ(length(), $P_n$-2);
  EXPECT_EQ(length(), Pristine::count);
  auto s3 = require(6,7);
  EXPECT_EQ(heap.handle(),1);
  EXPECT_EQ(s3.car().handle(),6);
  EXPECT_EQ(P[s3.handle()].s2,7);
  EXPECT_EQ(P[s3.handle()].s2,s3.cdr().handle());
}

TEST(Require, Scenario) { 
  heapify();
  EXPECT_FF(corrupted.asymmetric());
  EXPECT_EQ(heap.handle(),1);
  auto s1 = require(2,3);
  EXPECT_EQ(heap.handle(),1);
  EXPECT_EQ(s1.handle(),Word(2,3).hash());
  EXPECT_EQ(P[s1.handle()].s1,2);
  EXPECT_EQ(P[s1.handle()].s2,3);
  EXPECT_FF(corrupted.asymmetric());
  EXPECT_EQ(length(), $P_n$-1);
  EXPECT_EQ(length(), Pristine::count);
  auto s2 = require(4,5);
  EXPECT_EQ(s2.handle(),Word(4,5).hash());
  EXPECT_EQ(heap.handle(),1);
  EXPECT_EQ(P[s2.handle()].s1,4);
  EXPECT_EQ(P[s2.handle()].s2,5);
  EXPECT_FF(corrupted.asymmetric());
  EXPECT_EQ(length(), $P_n$-2);
  EXPECT_EQ(length(), Pristine::count);
  auto s3 = require(6,7);
  EXPECT_EQ(s3.handle(),Word(6,7).hash());
  EXPECT_EQ(P[s3.handle()].s1,6);
  EXPECT_EQ(P[s3.handle()].s2,7);
  EXPECT_FF(corrupted.asymmetric());
  EXPECT_EQ(length(), $P_n$-3);
  EXPECT_EQ(length(), Pristine::count);
}

TEST(Words, Reuse) { 
  heapify();
  EXPECT_FF(corrupted.asymmetric());
  EXPECT_EQ(length(), $P_n$);
  EXPECT_EQ(length(), Pristine::count);

  auto s1 = require(3,3);
  EXPECT_TT(s1.ok());
  EXPECT_EQ(s1.handle(), P[s1.handle()].hash());
  EXPECT_FF(corrupted.asymmetric());
  EXPECT_EQ(length(), $P_n$-1);
  EXPECT_EQ(length(), Pristine::count);

  auto s2 = require(2,3);
  EXPECT_TT(s2.ok());
  EXPECT_EQ(s2.handle(),P[s2.handle()].hash());
  EXPECT_FF(corrupted.asymmetric());
  EXPECT_EQ(length(), $P_n$-2);
  EXPECT_EQ(length(), Pristine::count);

  auto s3 = require(3,2);
  EXPECT_EQ(s3.handle(), P[s3.handle()].hash());
  EXPECT_TT(s3.ok());
  EXPECT_FF(corrupted.asymmetric());
  EXPECT_EQ(length(), $P_n$-3);
  EXPECT_EQ(length(), Pristine::count);

  auto s4 = require(2,3);
  EXPECT_TT(s4.ok());
  EXPECT_EQ(s4.handle(), P[s4.handle()].hash());
  EXPECT_FF(corrupted.asymmetric());
  EXPECT_EQ(length(), $P_n$-3);
  EXPECT_EQ(length(), Pristine::count);

  auto s5 = require(3,3);
  EXPECT_TT(s5.ok());
  EXPECT_EQ(s5.handle(), P[s5.handle()].hash());
  EXPECT_EQ(length(), $P_n$-3);
  EXPECT_EQ(length(), Pristine::count);
  EXPECT_FF(corrupted.asymmetric());

  auto s6 = require(3,2);
  EXPECT_TT(s6.ok());
  EXPECT_EQ(s6.handle(), P[s6.handle()].hash());
  EXPECT_EQ(length(), Pristine::count);
  EXPECT_EQ(length(), $P_n$-3);
  EXPECT_FF(corrupted.asymmetric());

  EXPECT_EQ(s1.handle(), s5.handle());
  EXPECT_EQ(s2.handle(), s4.handle());
  EXPECT_EQ(s3.handle(), s6.handle());

  EXPECT_FF(corrupted.pristines());
  EXPECT_FF(corrupted.items());
  EXPECT_FF(corrupted.pairs());
}

void mess(Pushdown &p) {
  static Word seed(23,41);
  seed.l = seed.hash();
  if (seed.l % 3 == 0)
    if (!p.empty())
      p.pop();
  seed.l = seed.hash();
  if (seed.l % 11 > 5)
    p.push(seed.hash());
}

TEST(Exhaust, Almost) { 
  heapify();
  EXPECT_EQ(Pristine::count, $P_n$); 
  for (auto s = 1 ; s < $P_n$; ++s)
    Item i = fresh(s, $P_x$);
  EXPECT_FF(heap.x());
  EXPECT_EQ(Pristine::count, 1);
  EXPECT_EQ(Item::count, $P_n$ - 1);
  EXPECT_FF(corrupted.pristines());
  EXPECT_FF(corrupted.items());
  EXPECT_FF(corrupted.pairs());
}

TEST(Exhaust, LateItemCorrect) { 
  heapify();
  for (auto s = 1 ; s < $P_n$; ++s)
    Item i = fresh(s, $P_x$);
  Item i = fresh(-2, $P_x$); 
  EXPECT_EQ(i.head(), -2);
  EXPECT_EQ(i.rest().handle(),  $P_x$);
}

TEST(Exhaust, LastItem) { 
  heapify();
  for (auto s = 1 ; s < $P_n$; ++s)
    Item i = fresh(s, $P_x$);
  Item i = fresh(-2, $P_x$); 
  EXPECT_FF(corrupted.pristines());
  EXPECT_FF(corrupted.items());
  EXPECT_FF(corrupted.pairs());
  EXPECT_FF(corrupted.something());
}

TEST(Exhaust, items) { 
  heapify();
  EXPECT_FF(corrupted.something());
  EXPECT_EQ(Pristine::count, $P_n$); 
  for (auto s = 1 ; s <= $P_n$; ++s) {
    Item i = fresh(s, $P_x$);
    EXPECT_EQ(i.handle(), s - $P_f$ + 1);
    EXPECT_EQ(Item::count + Pristine::count, $P_n$); 
    EXPECT_EQ(Pristine::count, $P_n$ - s); 
    EXPECT_EQ(Item::count, s); 
  }
  EXPECT_TT(heap.x());
  EXPECT_ZZ(Pristine::count);
  EXPECT_FF(corrupted.items());
  EXPECT_FF(corrupted.pristines());
}

TEST(Exhaust, andRestore) { 
  heapify();
  Pushdown p;
  EXPECT_EQ(Pristine::count, $P_n$); 
  for (auto s = 1 ; s <= $P_n$; ++s) 
    p.push(s);
  for (auto s = $P_n$ ; s >= 1; --s) 
    EXPECT_EQ(s, p.pop()) << s;
  EXPECT_ZZ(Pair::count);
  EXPECT_ZZ(Pair::miss);
  EXPECT_ZZ(Pair::reuse);
  EXPECT_ZZ(Item::count);
  EXPECT_EQ(Pristine::count, $P_n$);
  EXPECT_FF(corrupted.cyclic());
  EXPECT_FF(corrupted.weirdos()); 
  EXPECT_FF(corrupted.pristines());
  EXPECT_FF(corrupted.items());
  EXPECT_FF(corrupted.pairs());
  EXPECT_FF(corrupted.something());
}

TEST(Churn, Pushdown) { 
  heapify();
  for (int i = 0; i < 200 ; i++) { 
    {
      Pushdown p[103];
      for (int j = 0;  j < i; j++) 
        mess(p[Word(i,j).hash() % 10]); 
    }
    EXPECT_FF(corrupted.items());
    EXPECT_EQ(0, Item::count);
  }
  EXPECT_FF(corrupted.pristines());
  EXPECT_FF(corrupted.items());
  EXPECT_FF(corrupted.pairs());
}  

TEST(Churn, Require) { 
  heapify();
  int n = 0;
  for (Short i = 0;  ; i++) { 
    for (Short j = 0;  i <= j; j++) {
      Pair c(require(i,j).handle());
      ++n;
      EXPECT_TT(c.ok());
      EXPECT_EQ(i, c.car().handle());
      EXPECT_EQ(j, c.cdr().handle());
      EXPECT_EQ(n, Pair::count) << n;
      if (n > 25000)
        goto done;
    }
    EXPECT_FF(corrupted.pristines());
  }
done:
  EXPECT_FF(corrupted.pristines());
}  

TEST(Churn, Both) { 
  heapify();
  for (int i = 0, n = 0;  ; i++) { 
    Pushdown p[10];
    for (int j = 0; j <= i; ++j, ++n) {
      if (heap.x()) goto done;
      auto const c = require(i,j);
      if (heap.x()) goto done;
      int d = P[c.handle()].hash() % 10;
      mess(p[d]);
    }
  }
  done:
    EXPECT_ZZ(Item::count);
    EXPECT_FF(corrupted.something());
}

TEST(Counting, items) {
  Pushdown p;
  EXPECT_TT(p.top.x());
  EXPECT_TT(p.empty());
  int before = Item::count;
  EXPECT_GE(before,0);
  p.push(3);
  EXPECT_GE(Item::count,1);
  EXPECT_EQ(Item::count, before + 1);
}

TEST(Counting, pairs) {
  heapify();
  auto const before = Pristine::count;
  require(13,14);
  EXPECT_NE(Pristine::count, before);
  EXPECT_EQ(Pristine::count, before - 1);
  EXPECT_EQ(Pristine::count, $P_n$ - 1);
  EXPECT_EQ(Pair::count, 1);
  EXPECT_ZZ(Pair::miss);
  EXPECT_ZZ(Pair::reuse);
  EXPECT_FF(corrupted.something());
}

TEST(Counting, itemsPristines2) {
  heapify();
  Pushdown p;
  EXPECT_TT(p.top.x());
  EXPECT_TT(p.empty());
  EXPECT_GE(Pristine::count,10);
  int before = Pristine::count;
  p.push(3);
  EXPECT_EQ(Pristine::count, before - 1);
  EXPECT_FF(corrupted.something());
}

TEST(Pristine, itemsPristines3) {
  EXPECT_FF(corrupted.asymmetric());
  heapify();
  Pushdown p;
  p.push(3,2,1);
  EXPECT_FF(corrupted.asymmetric());
  require(12,13);
  EXPECT_FF(corrupted.asymmetric());
  require(12,13);
  EXPECT_FF(corrupted.asymmetric());
  p.pop();
  EXPECT_FF(corrupted.asymmetric());
}

TEST(Pristine, itemsPristines4) {
  heapify();
  EXPECT_FF(corrupted.something());
  Pushdown p;
  int before = Pristine::count;
  p.push(3,2,1);
  EXPECT_EQ(Pristine::count, before - 3);
  EXPECT_EQ(Pristine::count, before - 3);
  require(12,13);
  EXPECT_EQ(Pristine::count, before - 4);
  require(12,13);
  EXPECT_EQ(Pristine::count, before - 4);
  EXPECT_EQ(3,p.pop());
  EXPECT_EQ(2,p.pop());
  EXPECT_EQ(1,p.pop());
  EXPECT_EQ(Pristine::count, before - 1);
  EXPECT_ZZ(p.size);
  EXPECT_TT(p.top.x());
  EXPECT_FF(corrupted.something());
}

TEST(Pristine, RequireConsN) {
  heapify();
  EXPECT_FF(corrupted.something());
  Pushdown p;
  int before = Pristine::count;
  p.push(3,2,1);
  EXPECT_EQ(Pristine::count, before - 3);
  EXPECT_EQ(Pristine::count, before - 3);
  for (int i = 0;  i <= 4; i++)  
    for (int j = 0;  j <= 4; j++) 
      require(i,j);
  EXPECT_EQ(Pristine::count, before - 28);
  EXPECT_EQ(3,p.pop());
  EXPECT_EQ(2,p.pop());
  EXPECT_EQ(1,p.pop());
  EXPECT_EQ(Pristine::count, before - 25);
  EXPECT_ZZ(p.size);
  EXPECT_TT(p.top.x());
  EXPECT_FF(corrupted.something());
}

TEST(Exercise, PushRequirePopRequire) {
  enum {N = 16};
  EXPECT_FF(corrupted.something());
  heapify();
  Pushdown p;
  int before = Pristine::count;
  for (int i = 0, n = 0;  i < 16; i++)  
    for (int j = 0;  j < 16; j++) {
      require(i,j);
      ++n;
      p.push(i+j);
      ++n;
    }
  EXPECT_FF(corrupted.something());
  EXPECT_EQ(before - Pristine::count, 2 * N * N);
  for (int i = 0;  i < 16; i++)  
    for (int j = 0;  j < 16; j++) {
      require(i+50, j+100);
      p.pop();
      require(i, j);
    }
  EXPECT_TT(p.top.x());
  EXPECT_FF(corrupted.something());
  EXPECT_EQ(Pair::count, 2*N*N);
  EXPECT_EQ(Pristine::count, $P_n$ - 2 * N *N); 
}

TEST(Pristine, RequireAtom) {
  Pushdown p;
  heapify();
  int before = Pristine::count;
  p.push(3,2,1);
  require("ABC");
  EXPECT_EQ(Pristine::count, before - 3);
  require("ABC");
  require("CDE");
  EXPECT_EQ(Pristine::count, before - 3);
  EXPECT_EQ(3,p.pop());
  EXPECT_EQ(2,p.pop());
  EXPECT_EQ(1,p.pop());
  EXPECT_EQ(Pristine::count, before);
}

TEST(Pristine, 1RequireAtom) {
  int before = Pristine::count;
  EXPECT_EQ(Pristine::count, before);
  require("Foo Bar");
  EXPECT_NE(Pristine::count, before -1);
  EXPECT_EQ(Pristine::count, before);
  EXPECT_FF(corrupted.something());
}

TEST(Pristine, RequireBoth) {
  EXPECT_FF(corrupted.something());
  heapify();
  Pushdown p;
  EXPECT_TT(p.top.x());
  EXPECT_TT(p.empty());
  int before = Pristine::count;
  EXPECT_GE(before,2);
  p.push(3);
  EXPECT_EQ(Pristine::count, before -1);
  p.push(2);
  EXPECT_EQ(Pristine::count, before -2);
  require("ABC");
  EXPECT_EQ(Pristine::count, before -2);
  require("CDE");
  EXPECT_EQ(Pristine::count, before -2);
  require("ABC");
  EXPECT_EQ(Pristine::count, before -2);
  require("CDE");
  EXPECT_EQ(Pristine::count, before -2);
  require(12,13);
  EXPECT_EQ(Pristine::count, before -3);
  require(12,13);
  EXPECT_EQ(Pristine::count, before -3);
  EXPECT_EQ(2,p.pop());
  EXPECT_EQ(Pristine::count, before -2);
  EXPECT_EQ(3,p.pop());
  EXPECT_EQ(Pristine::count, before -1);
  EXPECT_TT(p.empty());
  EXPECT_TT(p.top.x());
  EXPECT_FF(corrupted.something());
}

extern Knob crude();
TEST(Crude, 1) { 
  heapify();
  EXPECT_FF(corrupted.asymmetric());
  EXPECT_EQ(heap.handle(),1);
  auto s1 = crude().handle();
  EXPECT_EQ(heap.handle(),2);
  EXPECT_EQ(s1,1);
  EXPECT_FF(corrupted.asymmetric());
  EXPECT_EQ(length(), $P_n$-1);
  EXPECT_EQ(length(), Pristine::count);
}

TEST(Crude, almostExhausted) { 
  heapify();
  for (auto i = 1; i < $P_n$; ++i)
    crude().handle();
  EXPECT_FF(heap.x());
  EXPECT_EQ(Pristine::count, 1);
}

TEST(Crude, exhausted) { 
  heapify();
  EXPECT_EQ(Pristine::count, $P_n$); 
  for (auto i = 1; i <= $P_n$; ++i) {
    auto const s = crude().handle();
    EXPECT_EQ(i, s);
    EXPECT_EQ(Pristine::count, $P_n$ - i); 
    EXPECT_ZZ(Item::count); // This black box test corrupts the heap,
  }
  EXPECT_TT(heap.x());
  EXPECT_ZZ(Pristine::count);
}

TEST(Crude, last) { 
  heapify();
  for (auto i = 1; i < $P_n$; ++i)
    crude().handle();
  crude();
}

TEST(Crude, lastCorrect) { 
  heapify();
  for (auto i = 1; i < $P_n$; ++i)
    crude().handle();
  crude();
  EXPECT_TT(heap.x());
  EXPECT_ZZ(Pristine::count);
}
