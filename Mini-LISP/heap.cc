#include "chic.h"
#include "heap.h"

#include "Short.h"
#include "Word.h"
#include "Cons.h"
#include "Pristine.h"

#include "layout.h"

Pristine heap; 

static Knob fresh() {
  if (heap.x())
    throw EXHAUSTED; 
  Expect(!heap.x(),heap);
  Expect(heap.prev().x());
  Pristine::count--;
  let old = heap;
  heap = heap.next();
  if (!heap.x())
    heap.prev($P_x$);
  return old.inner(); 
}

Item fresh(Short s1, Short s2) {
  Expect(white(s1));
  Expect(white(s2));
  Expect(s2 == $P_x$ || s2 >= $P_f$ && s2 <= $P_t$);
  if (heap.x()) throw __LINE__; 
  Item::count++;
  return fresh().Item().head(s1).rest(s2);
}

static Item fresh(Word w) { 
  return fresh(w.s1,w.s2); 
}

static Cons require(Word w, Short s) {
  Expect(Cons::ok(w));
  Expect(s != $P_x$);
  Expect(s >= $P_f$);
  Expect(s <= $P_t$);
  if (P[s].l == w.l) {
    Cons::reuse++;
    return s; 
  };
  Cons::count++;
  if (!Pristine(s).ok()) {
    Cons::miss++;
    return fresh().Cons().car(w.s1).cdr(w.s2);
  }
  Expect(Pristine(s).ok());
  Promise(Cons::ok(P[s]));
  Pristine::count--;
  auto prev = Pristine(s).prev(), next = Pristine(s).next();
  if (!prev.x()) prev.next(next); 
  if (!next.x()) next.prev(prev); 
  if (heap.inner() == s) heap = next ;
  P[s] = w;
  return Cons(s);
}

Cons require(Word w) {
  return require(w, w.hash());
}
  
Pristine heapify() {
  for (Short s = $P_f$ + 1; s <= $P_t$ - 1; ++s) 
    Pristine(s).prev(Pristine(s-1)).next(Pristine(s+1));
  Pristine($P_f$).prev(Pristine()).next(Pristine($P_f$ +1));
  Pristine($P_t$).next(Pristine()).prev(Pristine($P_t$ -1));
  Pristine::count = $P_n$;
  Cons::count = 0;
  Cons::reuse = 0;
  Cons::miss = 0;
  Item::count = 0;
  return heap = Pristine($P_f$);
}


void free(Item i) {
  Expect(i.ok());
  let h = i.inner();
  Expect(Knob(h).item());
  Pristine(h).prev($P_x$).next(heap); 
  if (!heap.x())
    heap.prev(Pristine(h));
  heap = h;
  Pristine::count++;
  Item::count--;
}

Cons require(Sx car, Sx cdr) { return require(Word(car.inner(),cdr.inner())); }

Short length() {
  Short result = 0;
  for (auto h = heap; !h.x();  h = h.next()) 
      ++result;
  return result;
}

Boolean asymmetric() {
  int n;
  for (auto p = heap; !p.x(); p = p.next(), ++n) { 
    if (!p.prev().x() && p.prev().next().inner() != p.inner()) 
      return true;
    if (!p.next().x() && p.next().prev().inner() != p.inner()) 
      return true;
  }
  return false;
}

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

Boolean weird() {
  for (auto h = $P_f$; h <= $P_t$; ++h) 
    if (Knob(h).weirdo()) 
      return true;
  return false;
}

Boolean Pristine::valid() {
  return !asymmetric() && !cyclic() && !weird() &&
    !Pristine::corrupted() && !Item::corrupted() && !Cons::corrupted(); 
}

Boolean Pristine::corrupted() {
  try {
    Expect(count >= 0);
    Expect(count  <= $P_n$);
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
    Expect(n == count, n, count);
    return false;
  } catch(...) {
    return true;
  }
}

Short Cons::count = 0;
Integer Cons::reuse = 0;
Integer Cons::miss = 0;

Boolean Cons::corrupted() {
  try {
    Expect(count >= 0);
    Expect(count  <= $P_n$);
    Expect(reuse  >= 0);
    Expect(reuse  >= 0);
    Expect(miss  >= 0);
    Expect(count != 0 || reuse ==0)
    Expect(count != 0 || miss ==0)

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

Short Item::count = 0;

Boolean Item::corrupted() {
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
      return false;;
    }
  } catch(...) {
    return true;
  }
}





#include "Pushdown.h"
#include <stdio.h>
#undef Type
#undef function

#include "gtest/gtest.h"

TEST(Heapify, 5) { 
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

TEST(Heapify, exists) { 
  try {
    heapify();
  } catch(int e) {
    ADD_FAILURE() << "Died at line " << e;
  }
}

TEST(Heapify, zeroes) { 
  try {
    heapify();
    EXPECT_EQ(Cons::count, 0);
    EXPECT_EQ(Cons::miss, 0);
    EXPECT_EQ(Cons::reuse, 0);
    EXPECT_EQ(Item::count, 0);
    EXPECT_EQ(Pristine::count, $P_n$);
  } catch(int e) {
    ADD_FAILURE() << "Died at line " << e;
  }
}

TEST(Heapify, FirstRequire) { 
  try {
    heapify();
    EXPECT_EQ(Cons::count, 0);
    EXPECT_EQ(Cons::miss, 0);
    EXPECT_EQ(Cons::reuse, 0);
    EXPECT_EQ(Item::count, 0);
    EXPECT_EQ(Pristine::count, $P_n$);

  } catch(int e) {
    ADD_FAILURE() << "Died at line " << e;
  }
}


TEST(Heapify, AllPristine) { 
  heapify();
  for (Short s = $P_f$; s <= $P_t$; ++s)
    ASSERT_TRUE(Pristine(s).ok()) << s;
}

TEST(Heapify, PristineCorrupted) { 
  try {
    heapify();
    for (Short s = $P_f$; s <= $P_t$; ++s)
      EXPECT_TT(Pristine(s).ok()) << s;
    EXPECT_FF(Pristine::corrupted());
  } catch(int e) {
    ADD_FAILURE() << "Died at line " << e;
  }
}

TEST(Heapify, ItemCorrupted) { 
  try {
    heapify();
    EXPECT_FF(Item::corrupted());
  } catch(int e) {
    ADD_FAILURE() << "Died at line " << e;
  }
}

TEST(Heapify, ConsCorrupted) { 
  try {
    heapify();
    EXPECT_FF(Cons::corrupted());
  } catch(int e) {
    ADD_FAILURE() << "Died at line " << e;
  }
}


TEST(Heapify, Symmetric) { 
  try {
    heapify();
    EXPECT_FF(asymmetric());
  } catch(int e) {
    ADD_FAILURE() << "Died at line " << e;
  }
}

TEST(Heapify, checkFirst) { 
  heapify();
  EXPECT_TT(Pristine($P_f$).prev().x()); 
  EXPECT_FF(Pristine($P_f$).next().x()); 
  EXPECT_EQ(Pristine($P_f$).next().inner(), $P_f$+1); 
}

TEST(Heapify, checkLast) { 
  heapify();
  EXPECT_TT(Pristine($P_t$).next().x()); 
  EXPECT_FF(Pristine($P_t$).prev().x()); 
  EXPECT_EQ(Pristine($P_t$).prev().inner(), $P_t$-1); 
}

TEST(Heapify, checkBetween) { 
  heapify();
  for (Short s = $P_f$ + 1; s < $P_t$; ++s) {
    EXPECT_EQ(Pristine(s).prev().inner(), s-1) << s; 
    EXPECT_EQ(Pristine(s).next().inner(), s+1) << s; 
  }
}

TEST(Heapify, Acyclic) { 
  heapify();
  EXPECT_EQ(Cons::count, 0);
  EXPECT_EQ(Cons::miss, 0);
  EXPECT_EQ(Cons::reuse, 0);
  EXPECT_EQ(Item::count, 0);
  EXPECT_EQ(Pristine::count, $P_n$);
  EXPECT_FF(Pristine::corrupted());
  EXPECT_FF(Item::corrupted());
  EXPECT_FF(Cons::corrupted());
  EXPECT_FF(asymmetric());
  for (Short s = $P_f$; s <= $P_t$; ++s)
    EXPECT_TT(Pristine(s).ok()) << s;
  EXPECT_TT(Pristine($P_f$).prev().x()); 
  EXPECT_FF(Pristine($P_f$).next().x()); 
  EXPECT_EQ(Pristine($P_f$).next().inner(), $P_f$+1); 
  EXPECT_TT(Pristine($P_t$).next().x()); 
  EXPECT_FF(Pristine($P_t$).prev().x()); 
  EXPECT_EQ(Pristine($P_t$).prev().inner(), $P_t$-1); 
  for (Short s = $P_f$ + 1; s < $P_t$; ++s) {
    EXPECT_EQ(Pristine(s).prev().inner(), s-1) << s; 
    EXPECT_EQ(Pristine(s).next().inner(), s+1) << s; 
  }
  EXPECT_FF(cyclic());
}

TEST(Heapify, Weirdos) { 
  heapify();
  EXPECT_FF(weird());
}

TEST(Heapify, valid) { 
  try {
    heapify();
    EXPECT_TT(Pristine::valid());
  } catch(int e) {
    ADD_FAILURE() << "Died at line " << e;
  }
}

TEST(Heapify, Pristine) { 
  heapify();
  EXPECT_FF(heap.x());
  EXPECT_EQ(heap.inner(), 1);
  EXPECT_EQ(heap.inner(), $P_f$);
  EXPECT_EQ(Pristine(1).next().inner(), 2);
  EXPECT_EQ(Pristine(1).prev().inner(), 0);
  EXPECT_EQ(Pristine(2).next().inner(), 3);
  EXPECT_EQ(Pristine(2).prev().inner(), 1);
  EXPECT_EQ(Pristine($P_t$).prev().inner(), $P_t$-1);
  EXPECT_EQ(Pristine($P_t$).next().inner(), $P_x$);

  EXPECT_FF(Pristine::corrupted());
  EXPECT_FF(Item::corrupted());
  EXPECT_FF(Cons::corrupted());
}


TEST(Corruption, makeCyclic) { 
  try {
    heapify();
    EXPECT_FF(cyclic());
    Pristine($P_t$-3).next(($P_f$ + $P_t$)/2);
    EXPECT_TT(cyclic());
  } catch(int e) {
    ADD_FAILURE() << "Died at line " << e;
  }
}

TEST(Corruption, ofPrev) { 
  try {
    heapify();
    Pristine($P_t$).prev(($P_f$ + $P_t$)/2);
    EXPECT_TT(asymmetric());
  } catch(int e) {
    ADD_FAILURE() << "Died at line " << e;
  }
}

TEST(Corruption, ofNext) { 
  try {
    heapify();
    Pristine(Word(13,17).hash()).next(Word(17,13).hash());
    EXPECT_TT(asymmetric());
  } catch(int e) {
    ADD_FAILURE() << "Died at line " << e;
  }
}

TEST(Heapify, CycleOfSize1) { 
  try {
    heapify();
    Pristine(Word(13,17).hash()).next(Word(13,17).hash());
    EXPECT_TT(cyclic());
  } catch(int e) {
    ADD_FAILURE() << "Died at line " << e;
  }
}


TEST(Fresh, exists) { 
  heapify();
  fresh(15,21);
}

TEST(Fresh, validItem) { 
  heapify();
  fresh(15,$P_x$);
  EXPECT_FF(Item::corrupted());
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

  EXPECT_FF(Pristine::corrupted());
  EXPECT_FF(Item::corrupted());
  EXPECT_FF(Cons::corrupted());
}

TEST(Fresh, Count) { 
  heapify();
  EXPECT_EQ(Pristine::count, $P_n$);
  auto f = fresh(15,(21));
  EXPECT_EQ(Pristine::count, $P_n$ -1);
  free(f);
  EXPECT_EQ(Pristine::count, $P_n$);
}


TEST(Fresh, 1) { 
  heapify();
  EXPECT_FF(asymmetric());
  EXPECT_EQ(heap.inner(),1);
  auto s1 = fresh().inner();
  EXPECT_EQ(heap.inner(),2);
  EXPECT_EQ(s1,1);
  EXPECT_FF(asymmetric());
  EXPECT_EQ(length(), $P_n$-1);
  EXPECT_EQ(length(), Pristine::count);
}

TEST(Fresh, 3) { 
  try {
    let s1 = fresh(2,3);
    let s2 = fresh(4,5);
    let s3 = fresh(6,7);
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

    let s1 = fresh(2,3);
    EXPECT_EQ(length(), $P_n$ - 1);
    EXPECT_EQ(length(), Pristine::count);

    let s2 = fresh(4,5);
    EXPECT_EQ(length(), $P_n$ - 2);
    EXPECT_EQ(length(), Pristine::count);

    let s3 = fresh(6,7);
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
  EXPECT_FF(asymmetric());
  EXPECT_EQ(heap.inner(),1);
  auto s1 = require(2,3);
  EXPECT_EQ(heap.inner(),1);
  EXPECT_NE(s1.inner(),1);
  EXPECT_EQ(P[s1.inner()].s1,2);
  EXPECT_EQ(P[s1.inner()].s2,3);
  EXPECT_FF(asymmetric());
  EXPECT_EQ(length(), $P_n$-1);
  EXPECT_EQ(length(), Pristine::count);
  auto s2 = require(4,5);
  EXPECT_EQ(s2.car().inner(),4);
  EXPECT_EQ(s2.cdr().inner(),5);
  EXPECT_FF(asymmetric());
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
  EXPECT_FF(asymmetric());
  EXPECT_EQ(heap.inner(),1);
  auto s1 = require(2,3);
  EXPECT_EQ(heap.inner(),1);
  EXPECT_EQ(s1.inner(),Word(2,3).hash());
  EXPECT_EQ(P[s1.inner()].s1,2);
  EXPECT_EQ(P[s1.inner()].s2,3);
  EXPECT_FF(asymmetric());
  EXPECT_EQ(length(), $P_n$-1);
  EXPECT_EQ(length(), Pristine::count);
  auto s2 = require(4,5);
  EXPECT_EQ(s2.inner(),Word(4,5).hash());
  EXPECT_EQ(heap.inner(),1);
  EXPECT_EQ(P[s2.inner()].s1,4);
  EXPECT_EQ(P[s2.inner()].s2,5);
  EXPECT_FF(asymmetric());
  EXPECT_EQ(length(), $P_n$-2);
  EXPECT_EQ(length(), Pristine::count);
  auto s3 = require(6,7);
  EXPECT_EQ(s3.inner(),Word(6,7).hash());
  EXPECT_EQ(P[s3.inner()].s1,6);
  EXPECT_EQ(P[s3.inner()].s2,7);
  EXPECT_FF(asymmetric());
  EXPECT_EQ(length(), $P_n$-3);
  EXPECT_EQ(length(), Pristine::count);
}

TEST(Words, Reuse) { 
  heapify();
  EXPECT_FF(asymmetric());
  EXPECT_EQ(length(), $P_n$);
  EXPECT_EQ(length(), Pristine::count);

  auto s1 = require(3,3);
  EXPECT_TT(s1.ok());
  EXPECT_EQ(s1.inner(), P[s1.inner()].hash());
  EXPECT_FF(asymmetric());
  EXPECT_EQ(length(), $P_n$-1);
  EXPECT_EQ(length(), Pristine::count);

  auto s2 = require(2,3);
  EXPECT_TT(s2.ok());
  EXPECT_EQ(s2.inner(),P[s2.inner()].hash());
  EXPECT_FF(asymmetric());
  EXPECT_EQ(length(), $P_n$-2);
  EXPECT_EQ(length(), Pristine::count);

  auto s3 = require(3,2);
  EXPECT_EQ(s3.inner(), P[s3.inner()].hash());
  EXPECT_TT(s3.ok());
  EXPECT_FF(asymmetric());
  EXPECT_EQ(length(), $P_n$-3);
  EXPECT_EQ(length(), Pristine::count);

  auto s4 = require(2,3);
  EXPECT_TT(s4.ok());
  EXPECT_EQ(s4.inner(), P[s4.inner()].hash());
  EXPECT_FF(asymmetric());
  EXPECT_EQ(length(), $P_n$-3);
  EXPECT_EQ(length(), Pristine::count);

  auto s5 = require(3,3);
  EXPECT_TT(s5.ok());
  EXPECT_EQ(s5.inner(), P[s5.inner()].hash());
  EXPECT_EQ(length(), $P_n$-3);
  EXPECT_EQ(length(), Pristine::count);
  EXPECT_FF(asymmetric());

  auto s6 = require(3,2);
  EXPECT_TT(s6.ok());
  EXPECT_EQ(s6.inner(), P[s6.inner()].hash());
  EXPECT_EQ(length(), Pristine::count);
  EXPECT_EQ(length(), $P_n$-3);
  EXPECT_FF(asymmetric());

  EXPECT_EQ(s1.inner(), s5.inner());
  EXPECT_EQ(s2.inner(), s4.inner());
  EXPECT_EQ(s3.inner(), s6.inner());

  EXPECT_FF(Pristine::corrupted());
  EXPECT_FF(Item::corrupted());
  EXPECT_FF(Cons::corrupted());
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


TEST(Fresh, VirginAlmostExhausted) { 
  heapify();
  for (auto i = 1; i < $P_n$; ++i)
    fresh().inner();
  EXPECT_FF(heap.x());
  EXPECT_EQ(Pristine::count, 1);
}

TEST(Fresh, VirginExhausted) { 
  heapify();
  EXPECT_EQ(Pristine::count, $P_n$); 
  for (auto i = 1; i <= $P_n$; ++i) {
    let f = fresh().inner();
    EXPECT_EQ(i, f - $P_f$ + 1);
    EXPECT_EQ(Pristine::count, $P_n$ - i); 
    EXPECT_EQ(Item::count, 0); // This black box test corrupts the heap,
  }
  EXPECT_TT(heap.x());
  EXPECT_EQ(Pristine::count, 0);
}


TEST(Fresh, VirginLastWorks) { 
  heapify();
  for (auto i = 1; i < $P_n$; ++i)
    fresh().inner();
  fresh();
}

TEST(Fresh, VirginLastCorrect) { 
  heapify();
  for (auto i = 1; i < $P_n$; ++i)
    fresh().inner();
  fresh();
  EXPECT_TT(heap.x());
  EXPECT_EQ(Pristine::count, 0);
}

TEST(Exhaust, Almost) { 
  heapify();
  EXPECT_EQ(Pristine::count, $P_n$); 
  for (auto s = 1 ; s < $P_n$; ++s)
    Item i = fresh(s, $P_x$);
  EXPECT_FF(heap.x());
  EXPECT_EQ(Pristine::count, 1);
  EXPECT_EQ(Item::count, $P_n$ - 1);
  EXPECT_FF(Pristine::corrupted());
  EXPECT_FF(Item::corrupted());
  EXPECT_FF(Cons::corrupted());
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
  EXPECT_FF(Pristine::corrupted());
  EXPECT_FF(Item::corrupted());
  EXPECT_FF(Cons::corrupted());
  EXPECT_TT(Pristine::valid());
}

TEST(Exhaust, Items) { 
  heapify();
  EXPECT_EQ(Pristine::count, $P_n$); 
  for (auto s = 1 ; s <= $P_n$; ++s) {
    Item i = fresh(s, $P_x$);
    EXPECT_EQ(i.inner(), s - $P_f$ + 1);
    EXPECT_EQ(Item::count + Pristine::count, $P_n$); 
    EXPECT_EQ(Pristine::count, $P_n$ - s); 
    EXPECT_EQ(Item::count, s); 
  }
  EXPECT_TT(heap.x());
  EXPECT_EQ(Pristine::count, 0);
  EXPECT_FF(Item::corrupted());
  EXPECT_FF(Pristine::corrupted());
}

TEST(Exhaust, Cycle) { 
  heapify();
  Pushdown p;
  EXPECT_EQ(Pristine::count, $P_n$); 
  for (auto s = 1 ; s <= $P_n$; ++s) 
    p.push(s);
  for (auto s = $P_n$ ; s >= 1; --s) 
    EXPECT_EQ(s, p.pop()) << s;
  EXPECT_EQ(Cons::count, 0);
  EXPECT_EQ(Cons::miss, 0);
  EXPECT_EQ(Cons::reuse, 0);
  EXPECT_EQ(Item::count, 0);
  EXPECT_EQ(Pristine::count, $P_n$);
  EXPECT_TT(Pristine::valid());
}

TEST(Churn, Pushdown) { 
  heapify();
  for (int i = 0; i < 200 ; i++) { 
    {
      Pushdown p[103];
      for (int j = 0;  j < i; j++) 
        mess(p[Word(i,j).hash() % 10]); 
    }
    EXPECT_FF(Item::corrupted());
    EXPECT_EQ(0, Item::count);
  }
  EXPECT_FF(Pristine::corrupted());
  EXPECT_FF(Item::corrupted());
  EXPECT_FF(Cons::corrupted());
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
    EXPECT_FF(Pristine::corrupted());
  }
done:
  EXPECT_FF(Pristine::corrupted());
}  


TEST(Churn, Both) { 
  heapify();
  for (int i = 0, n = 0;  ; i++) { 
    EXPECT_EQ(Item::count, 0);
    Pushdown p[10];
    for (int j = 0; j <= i; ++j, ++n) {
      if (heap.x()) goto done;
      auto const c = require(i,j);
      if (heap.x()) goto done;
      int d = P[c.inner()].hash() % 10;
      mess(p[d]);
    }
    if (n > 8000) {
      EXPECT_GT(Pristine::count, 0);
      EXPECT_FF(asymmetric());
      EXPECT_FF(Pristine::corrupted());
      EXPECT_FF(Item::corrupted());
      EXPECT_FF(Cons::corrupted());
     }
  }
  done:
    EXPECT_EQ(Item::count, 0);
    EXPECT_FF(asymmetric());
}
