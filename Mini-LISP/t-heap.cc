#include "heap.h"

#include "text.h"
#include "Pushdown.h"
#include "Pristine.h"
#include "Short.h"
#include "Cons.h"
#include "Sx.h"

#include "stdio.h"

Short length() {
  Short result = 0;
  for (auto h = heap; !h.x();  h = h.next()) 
      ++result;
  return result;
}

static struct {
  Boolean something() Is(uncounted() || excess() || asymmetric() || cyclic() || weirdos() || pristines() || items() || pairs()); 
  Boolean uncounted() Is(length() > Pristine::count); 
  Boolean excess()   Is(length() < Pristine::count); 
  Boolean cyclic() {
    if (!heap.x())
      for (auto h = heap, h2 = heap.next(); !h2.x(); h = h.next()) { 
        if (h.inner() == h2.inner()) 
          return true;
        if (!h2.x()) h2 = h2.next();
        if (!h2.x()) h2 = h2.next();
      }
    return false;
  }
  Boolean weirdos() {
    for (auto h = $P_f$; h <= $P_t$; ++h) 
      if (Knob(h).weirdo()) 
        return true;
    return false;
  }  
  Boolean asymmetric() {
    for (auto p = heap; !p.x(); p = p.next()) { 
      if (!p.prev().x() && p.prev().next().inner() != p.inner()) 
        return true;
      if (!p.next().x() && p.next().prev().inner() != p.inner()) 
        return true;
    }
    return false;
  }
  Boolean pairs() {
    try {
      Expect(Cons::count >= 0);
      Expect(Cons::count  <= $P_n$);
      Expect(Cons::reuse  >= 0);
      Expect(Cons::reuse  >= 0);
      Expect(Cons::miss  >= 0);
      Expect(Cons::count != 0 || Cons::reuse ==0)
      Expect(Cons::count != 0 || Cons::miss ==0)
      short n = 0; 
      for (auto h = $P_f$; h <= $P_t$; ++h) { 
        let c = Cons(h);
        if (!c.ok()) 
          continue;
        ++n;
      }
      Expect(n == Cons::count);
      return false;
    } catch(...) {
      return true;
    }
  }
  Boolean pristines() {
    try {
      Expect(Pristine::count >= 0);
      Expect(Pristine::count <= $P_n$);
      short n = 0; 
      for (auto h = $P_f$; h <= $P_t$; ++h) { 
        let p = Pristine(h);
        if (!p.ok()) 
          continue;
        ++n;
        Expect(n <= Pristine::count);
        Expect (Pristine(p.next()).x() || Pristine(p.next()).ok());
        Expect (Pristine(p.prev()).x() || Pristine(p.prev()).ok());
        if (!Pristine(p.next()).x())  
          Expect(Pristine(p.next()).ok());
        if (!Pristine(p.prev()).x())  
          Expect(Pristine(p.prev()).ok());
      }
      Expect(n == Pristine::count, n, Pristine::count);
      return false;
    } catch(...) {
      return true;
    }
  }
  Boolean items() {
    try {
      Short  n = 0; 
      for (auto h = $P_f$; h <= $P_t$; ++h) { 
        let i = Item(h);
        if (!i.ok()) 
          continue;
        ++n;
        Expect(Item(i.rest()).x() || Item(i.rest()).ok());
        Expect(n <= Item::count);
        if (!Item(i.rest()).x())  
          Expect(Item(i.rest()).ok());
      }
      return false;;
    } catch(...) {
      return true;
    }
  }
} corrupted;

#include "Test.h"
#include "mark.h"

TEST(Mark, exists) {
  heapify();
  auto s = require(2,3);
  mark(s);
}

TEST(Mark, correct) {
  heapify();
  auto s = require(2,3);
  auto k = Knob(s.inner());
  mark(s);
  EXPECT_TT(k.weirdo());
}

TEST(Mark, flip) {
  heapify();
  auto c = require(2,3);
  Short before = Knob(c.inner()).s1();
  mark(c);
  Short after = Knob(c.inner()).s1();
  EXPECT_EQ(before, flip(after)); 
  EXPECT_EQ(after, flip(before)); 
}

TEST(Mark, undo) {
  heapify();
  auto s = require(2,3);
  auto k = Knob(s.inner());
  EXPECT_TT(k.cons());
  mark(s);
  mark(s);
  EXPECT_FF(k.weirdo());
  EXPECT_TT(k.cons());
}

TEST(Mark, special) {
  heapify();
  auto s = require(2,3);
  auto k = Knob(s.inner());
  EXPECT_TT(k.cons());
  mark(s);
  EXPECT_FF(k.Cons().ok());
  EXPECT_FF(k.Item().ok());
  EXPECT_FF(k.Pristine().ok());
}

TEST(Mark, weird) {
  heapify();
  auto s = require(2,3);
  mark(s);
  EXPECT_FF(s.ok());
}

TEST(Preserve, exists) {
  heapify();
  auto s = require(2,3);
  preserve(s);
}

TEST(Preserve, singletonKeep) {
  heapify();
  auto dead = require(-3,-2);
  auto live = require(-2,-3);
  EXPECT_TT(live.ok());
  preserve(live);
  EXPECT_TT(live.ok());
}

TEST(Preserve, singletonKill) {
  heapify();
  auto dead = require(-3,-2);
  auto live = require(-2,-3);
  EXPECT_TT(dead.ok());
  preserve(live);
  EXPECT_FF(dead.ok());
}

TEST(Preserve, singletonPristine) {
  heapify();
  auto dead = require(-3,-2);
  auto live = require(-2,-3);
  EXPECT_TT(dead.ok());
  preserve(live);
  EXPECT_TT(Knob(dead.inner()).Pristine().ok());
}

TEST(Preserve, singletonConnected) {
  heapify();
  auto dead = require(-3,-2);
  auto live = require(-2,-3);
  preserve(live);
  EXPECT_EQ(Pristine::count, $P_n$-1);
}

TEST(Preserve, singletonCount) {
  heapify();
  auto dead = require(-3,-2);
  auto live = require(-2,-3);
  preserve(live);
  EXPECT_EQ(Pristine::count, $P_n$-1);
}

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
  EXPECT_EQ(Pristine($P_f$).next().inner(), $P_f$+1); 
}

TEST(Heapify, entryLast) { 
  heapify();
  EXPECT_TT(Pristine($P_t$).next().x()); 
  EXPECT_FF(Pristine($P_t$).prev().x()); 
  EXPECT_EQ(Pristine($P_t$).prev().inner(), $P_t$-1); 
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

  EXPECT_EQ(p.inner(), 5);
  EXPECT_EQ(p.prev().inner(), 4);
  EXPECT_EQ(p.next().inner(), 6);
  EXPECT_TT(p.ok());
}

TEST(Heapify, entryBetween) { 
  heapify();
  for (Short s = $P_f$ + 1; s < $P_t$; ++s) {
    EXPECT_EQ(Pristine(s).prev().inner(), s-1) << s; 
    EXPECT_EQ(Pristine(s).next().inner(), s+1) << s; 
  }
}

TEST(Heapify, prefix) { 
  heapify();
  EXPECT_EQ(heap.inner(), $P_f$);
  EXPECT_EQ(heap.inner(), $P_f$);
  EXPECT_EQ(Pristine($P_f$).next().inner(), 2);
  EXPECT_ZZ(Pristine($P_f$).prev().inner());
  EXPECT_EQ(Pristine(2).next().inner(), 3);
  EXPECT_EQ(Pristine(2).prev().inner(), $P_f$);
  EXPECT_EQ(Pristine($P_t$).prev().inner(), $P_t$-1);
  EXPECT_EQ(Pristine($P_t$).next().inner(), $P_x$);
}

TEST(Heapify, counters) { 
  heapify();
  EXPECT_ZZ(Cons::count);
  EXPECT_ZZ(Cons::miss);
  EXPECT_ZZ(Cons::reuse);
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
  Item f = fresh(15,$P_x$);
  EXPECT_TT(f.ok());
  EXPECT_EQ(f.inner(), 1);
  EXPECT_EQ(heap.inner(), 2);
  EXPECT_EQ(f.head(), 15);
  EXPECT_EQ(f.rest().inner(), $P_x$);
  EXPECT_TT(f.ok());
  EXPECT_FF(Cons(f.inner()).ok());
  EXPECT_FF(Pristine(f.inner()).ok());
}

TEST(Counters, AllocateFree) { 
  heapify();
  auto f = fresh(15,(21));
  EXPECT_EQ(Pristine::count, $P_n$ -1);
  free(f);
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
    EXPECT_EQ(heap.inner(), 1);
    EXPECT_EQ(length(), $P_n$ - 2);
    EXPECT_EQ(length(), Pristine::count);

    free(s3);
    EXPECT_EQ(heap.inner(), 3);
    EXPECT_EQ(length(), $P_n$ - 1);
    EXPECT_EQ(length(), Pristine::count);

    free(s2);
    EXPECT_EQ(heap.inner(), 2);
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

TEST(Require, cons) { 
  try {
    heapify();
    Cons h = require(Sx(0xDE),Sx(0xAD));
    EXPECT_TT(h.ok());
  } catch(int e) {
    ADD_FAILURE() << "Died at line " << e;
  }
}

TEST(Require, correct) { 
  try {
    heapify();
    Short h = require(Sx(0xDE),Sx(0xAD)).inner();
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
  EXPECT_EQ(heap.inner(),1);
  auto s1 = require(2,3);
  EXPECT_EQ(heap.inner(),1);
  EXPECT_NE(s1.inner(),1);
  EXPECT_EQ(P[s1.inner()].s1,2);
  EXPECT_EQ(P[s1.inner()].s2,3);
  EXPECT_FF(corrupted.asymmetric());
  EXPECT_EQ(length(), $P_n$-1);
  EXPECT_EQ(length(), Pristine::count);
  auto s2 = require(4,5);
  EXPECT_EQ(s2.car().inner(),4);
  EXPECT_EQ(s2.cdr().inner(),5);
  EXPECT_FF(corrupted.asymmetric());
  EXPECT_EQ(heap.inner(),1);
  EXPECT_EQ(length(), $P_n$-2);
  EXPECT_EQ(length(), Pristine::count);
  auto s3 = require(6,7);
  EXPECT_EQ(heap.inner(),1);
  EXPECT_EQ(s3.car().inner(),6);
  EXPECT_EQ(P[s3.inner()].s2,7);
  EXPECT_EQ(P[s3.inner()].s2,s3.cdr().inner());
}

TEST(Require, Scenario) { 
  heapify();
  EXPECT_FF(corrupted.asymmetric());
  EXPECT_EQ(heap.inner(),1);
  auto s1 = require(2,3);
  EXPECT_EQ(heap.inner(),1);
  EXPECT_EQ(s1.inner(),Word(2,3).hash());
  EXPECT_EQ(P[s1.inner()].s1,2);
  EXPECT_EQ(P[s1.inner()].s2,3);
  EXPECT_FF(corrupted.asymmetric());
  EXPECT_EQ(length(), $P_n$-1);
  EXPECT_EQ(length(), Pristine::count);
  auto s2 = require(4,5);
  EXPECT_EQ(s2.inner(),Word(4,5).hash());
  EXPECT_EQ(heap.inner(),1);
  EXPECT_EQ(P[s2.inner()].s1,4);
  EXPECT_EQ(P[s2.inner()].s2,5);
  EXPECT_FF(corrupted.asymmetric());
  EXPECT_EQ(length(), $P_n$-2);
  EXPECT_EQ(length(), Pristine::count);
  auto s3 = require(6,7);
  EXPECT_EQ(s3.inner(),Word(6,7).hash());
  EXPECT_EQ(P[s3.inner()].s1,6);
  EXPECT_EQ(P[s3.inner()].s2,7);
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
  EXPECT_EQ(s1.inner(), P[s1.inner()].hash());
  EXPECT_FF(corrupted.asymmetric());
  EXPECT_EQ(length(), $P_n$-1);
  EXPECT_EQ(length(), Pristine::count);

  auto s2 = require(2,3);
  EXPECT_TT(s2.ok());
  EXPECT_EQ(s2.inner(),P[s2.inner()].hash());
  EXPECT_FF(corrupted.asymmetric());
  EXPECT_EQ(length(), $P_n$-2);
  EXPECT_EQ(length(), Pristine::count);

  auto s3 = require(3,2);
  EXPECT_EQ(s3.inner(), P[s3.inner()].hash());
  EXPECT_TT(s3.ok());
  EXPECT_FF(corrupted.asymmetric());
  EXPECT_EQ(length(), $P_n$-3);
  EXPECT_EQ(length(), Pristine::count);

  auto s4 = require(2,3);
  EXPECT_TT(s4.ok());
  EXPECT_EQ(s4.inner(), P[s4.inner()].hash());
  EXPECT_FF(corrupted.asymmetric());
  EXPECT_EQ(length(), $P_n$-3);
  EXPECT_EQ(length(), Pristine::count);

  auto s5 = require(3,3);
  EXPECT_TT(s5.ok());
  EXPECT_EQ(s5.inner(), P[s5.inner()].hash());
  EXPECT_EQ(length(), $P_n$-3);
  EXPECT_EQ(length(), Pristine::count);
  EXPECT_FF(corrupted.asymmetric());

  auto s6 = require(3,2);
  EXPECT_TT(s6.ok());
  EXPECT_EQ(s6.inner(), P[s6.inner()].hash());
  EXPECT_EQ(length(), Pristine::count);
  EXPECT_EQ(length(), $P_n$-3);
  EXPECT_FF(corrupted.asymmetric());

  EXPECT_EQ(s1.inner(), s5.inner());
  EXPECT_EQ(s2.inner(), s4.inner());
  EXPECT_EQ(s3.inner(), s6.inner());

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
  EXPECT_EQ(i.rest().inner(),  $P_x$);
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
    EXPECT_EQ(i.inner(), s - $P_f$ + 1);
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
  EXPECT_ZZ(Cons::count);
  EXPECT_ZZ(Cons::miss);
  EXPECT_ZZ(Cons::reuse);
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
      Cons c(require(i,j).inner());
      ++n;
      EXPECT_TT(c.ok());
      EXPECT_EQ(i, c.car().inner());
      EXPECT_EQ(j, c.cdr().inner());
      EXPECT_EQ(n, Cons::count) << n;
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
      int d = P[c.inner()].hash() % 10;
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
  EXPECT_EQ(Cons::count, 1);
  EXPECT_ZZ(Cons::miss);
  EXPECT_ZZ(Cons::reuse);
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
  EXPECT_EQ(Cons::count, 2*N*N);
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
  EXPECT_EQ(heap.inner(),1);
  auto s1 = crude().inner();
  EXPECT_EQ(heap.inner(),2);
  EXPECT_EQ(s1,1);
  EXPECT_FF(corrupted.asymmetric());
  EXPECT_EQ(length(), $P_n$-1);
  EXPECT_EQ(length(), Pristine::count);
}

TEST(Crude, almostExhausted) { 
  heapify();
  for (auto i = 1; i < $P_n$; ++i)
    crude().inner();
  EXPECT_FF(heap.x());
  EXPECT_EQ(Pristine::count, 1);
}

TEST(Crude, exhausted) { 
  heapify();
  EXPECT_EQ(Pristine::count, $P_n$); 
  for (auto i = 1; i <= $P_n$; ++i) {
    auto const f = crude().inner();
    EXPECT_EQ(i, f - $P_f$ + 1);
    EXPECT_EQ(Pristine::count, $P_n$ - i); 
    EXPECT_ZZ(Item::count); // This black box test corrupts the heap,
  }
  EXPECT_TT(heap.x());
  EXPECT_ZZ(Pristine::count);
}

TEST(Crude, last) { 
  heapify();
  for (auto i = 1; i < $P_n$; ++i)
    crude().inner();
  crude();
}

TEST(Crude, lastCorrect) { 
  heapify();
  for (auto i = 1; i < $P_n$; ++i)
    crude().inner();
  crude();
  EXPECT_TT(heap.x());
  EXPECT_ZZ(Pristine::count);
}
