#include "Purge.h"
#include "heap.h"
#include "corrupted.h"
#include "Short.h"

#include "Test.h"

TEST(Sx, Pair) {
  Sx s(13);
  Pair p = s.Pair();
  EXPECT_EQ(p.handle(), s.handle());
}

TEST(Visit, exists) {
  heapify();
  auto s = require(2,3);
  s.visit();
}

TEST(Visit, repertoire) {
  heapify();
  Pair p = require(-2,-3);
  p.visit();
  p.unvisit();
  p.seen();
}

TEST(Visit, exists2) {
  heapify();
  require(2,3).visit();
}

TEST(Visit, seen) {
  heapify();
  Pair p = require(5,6);
  EXPECT_FF(p.seen());
  EXPECT_TT(p.visit().seen());
  EXPECT_TT(!p.unvisit().seen());
}

TEST(Visit, distinct) {
  heapify();
  auto x = require(2,3);
  Word w = P[x.handle()];
  x.visit();
  EXPECT_NE(w.l,P[x.handle()].l);
}

TEST(Visit, unseen) {
  auto x = require(2,3);
  Word w = P[x.handle()];
  EXPECT_FF(x.visit().unvisit().seen());
}

TEST(Visit, reversible) {
  heapify();
  auto x = require(2,3);
  Word w = P[x.handle()];
  EXPECT_FF(x.visit().unvisit().seen());
  EXPECT_EQ(w.l,P[x.handle()].l);
}


TEST(Visit, flip) {
  heapify();
  auto p = require(2,3);
  Short before = p.car().handle();
  p.visit(); 
  Short after = p.car().handle();
  EXPECT_EQ(before, flip(after)); 
  EXPECT_EQ(after, flip(before)); 
}

TEST(Visit, ok) {
  heapify();
  Pair p = require(2,3);
  EXPECT_TT(p.ok());
  EXPECT_TT(not p.visit().ok());
  EXPECT_TT(p.unvisit().ok());
}

TEST(Visit, special) {
  Pair p = require(2,3);
  EXPECT_TT(p.ok());
  p.visit();
  EXPECT_FF(p.ok());
  EXPECT_FF(Item(p.handle()).ok());
  EXPECT_FF(Pristine(p.handle()).ok());
}

TEST(Preserve, exists) {
  heapify();
  auto s = require(-2,-3);
  purge.preserving(s);
  EXPECT_FF(corrupted.something());
}

TEST(Preserve, mess) {
  heapify();
  try { // Do not dare in real life!
    purge.preserving(require(2,3)); // Use a raw S-Expression.
    EXPECT_FF(corrupted.something()); // The heap may be corrupted, or an exception
  } catch(...) {
    EXPECT_TT(true); // Something bad should happen' we don't know which 
  }
}

TEST(Preserve, singleton) {
  heapify();
  auto dead = require(-3,-2);
  auto live = require(-2,-3);
  EXPECT_TT(live.ok());
  purge.preserving(live);
  EXPECT_FF(corrupted.something());
}

TEST(Preserve, singletonKill) {
  heapify();
  auto dead = require(-3,-2);
  auto live = require(-2,-3);
  EXPECT_TT(dead.ok());
  purge.preserving(live);
  EXPECT_FF(dead.ok());
}

TEST(Preserve, singletonPristine) {
  heapify();
  auto dead = require(-3,-2);
  auto live = require(-2,-3);
  EXPECT_TT(dead.ok());
  purge.preserving(live);
  EXPECT_TT(Knob(dead.handle()).Pristine().ok());
}

TEST(Preserve, singletonPrepended) {
  heapify();
  auto dead = require(-3,-2);
  auto live = require(-2,-3);
  purge.preserving(live);
  EXPECT_EQ(dead.handle(), heap.handle());
}

TEST(Preserve, singletonCount) {
  heapify();
  auto dead = require(-3,-2);
  auto live = require(-2,-3);
  purge.preserving(live);
  EXPECT_EQ(Pristine::count, $P_n$-1);
}

TEST(Preserve, pairCount) {
  heapify();
  auto dead1 = require(-3,-2);
  auto dead2 = require(-5,-2);
  auto dead3 = require(dead2,dead1);
  auto live = require(-2,-3);
  EXPECT_FF(corrupted.something());
  EXPECT_EQ(Pair::count,4);
  purge.preserving(live);
  EXPECT_EQ(Pair::count,1);
  EXPECT_EQ(Pristine::count, $P_n$-1);
}

TEST(Preserve, tripleCount) {
  heapify();
  auto dead1 = require(-3,-2);
  auto dead2 = require(-5,-2);
  auto live = require(-2,-3);
  purge.preserving(live);
  EXPECT_EQ(Pristine::count, $P_n$-1);
}

TEST(Preserve, live2) {
  heapify();
  auto dead1 = require(-3,-2);
  auto dead2 = require(-5,-2);
  auto live1 = require(-2,-3);
  auto live2 = require(live1.handle(),-4);
  purge.preserving(live2);
  EXPECT_EQ($P_n$ - Pristine::count, 2);
  EXPECT_FF(corrupted.something());
}

TEST(Preserve, live5) {
  heapify();
  auto d1 = require(-3,-2).handle();
  auto l1 = require(-2,-3).handle();
  auto d2 = require(d1,d1).handle();
  auto l2 = require(l1,-4).handle();
  auto d3 = require(d1,d2).handle();

  auto live1 = require(-2,-3);
  auto live2 = require(live1.handle(),-4);
  auto live3 = require(live2.handle(),-5);
  auto live4 = require(live3,-6);
  auto live5 = require(live4,-6);

  auto l3 = require(l2,-5).handle();
  auto d4 = require(d3,d2).handle();
  auto l4 = require(l2,l3).handle();
  auto d5 = require(d4,d3).handle();
  auto l5 = require(l4,l4).handle();

  purge.preserving(live5);
  EXPECT_EQ($P_n$ - Pristine::count, 5);
  EXPECT_FF(corrupted.something());
}

TEST(Preserve, live7) {
  heapify();
  auto live1 = require(-2,-3);
  auto live2 = require(-3,-4);
  auto live3 = require(-8,-6);
  auto live4 = require(-6,-4);

  auto live5 = require(live1,live2);
  auto live6 = require(live3,live4);
  auto live7 = require(live5,live5);
  EXPECT_TT(live1.ok());
  EXPECT_TT(live2.ok());
  EXPECT_TT(live3.ok());
  EXPECT_TT(live4.ok());
  EXPECT_TT(live5.ok());
  EXPECT_TT(live6.ok());
  EXPECT_TT(live7.ok());
  EXPECT_EQ($P_n$ - Pristine::count, 7);
  purge.preserving(live7);
  EXPECT_TT(live1.ok());
  EXPECT_TT(live2.ok());
  EXPECT_TT(live3.ok());
  EXPECT_TT(live4.ok());
  EXPECT_TT(live5.ok());
  EXPECT_TT(live6.ok());
  EXPECT_TT(live7.ok());
  EXPECT_EQ($P_n$ - Pristine::count, 7);
}

TEST(Sx, Pair1) {
  Sx s(13);
  Pair p = s.Pair();
  EXPECT_EQ(p.handle(), s.handle());
}

TEST(Preserve, live15) {
  heapify();
  auto live1 = require(-1,-3);
  auto live2 = require(-2,-4);
  auto live3 = require(-3,-6);
  auto live4 = require(-4,-4);
  auto live5 = require(-5,-1);
  auto live6 = require(-6,-7);
  auto live7 = require(-7,-5);
  auto live8 = require(-8,-2);

  auto live09 = require(live1,live2);
  auto live10 = require(live3,live4);
  auto live11 = require(live5,live6);
  auto live12 = require(live7,live8);

  auto live13 = require(live09,live10);
  auto live14 = require(live11,live12);

  auto live15 = require(live13,live14);

  EXPECT_EQ($P_n$ - Pristine::count, 15);
  purge.preserving(live7);
  EXPECT_EQ($P_n$ - Pristine::count, 15);
  EXPECT_FF(corrupted.something());
}

TEST(Preserve, live31) {
  heapify();
  auto live1 = require(-1,-3);
  auto live2 = require(-2,-4);
  auto live3 = require(-3,-6);
  auto live4 = require(-4,-4);
  auto live5 = require(-5,-1);
  auto live6 = require(-6,-7);
  auto live7 = require(-7,-5);
  auto live8 = require(-8,-2);

  auto live09 = require(live1,live2);
  auto live10 = require(live3,live4);
  auto live11 = require(live5,live6);
  auto live12 = require(live7,live8);

  auto live13 = require(live09,live10);
  auto live14 = require(live11,live12);

  auto live15 = require(live13,live14);

  auto love1 = require(-11,-23);
  auto love2 = require(-21,-24);
  auto love3 = require(-31,-26);
  auto love4 = require(-41,-24);
  auto love5 = require(-51,-21);
  auto love6 = require(-61,-27);
  auto love7 = require(-71,-25);
  auto love8 = require(-81,-22);

  auto love09 = require(love1,love2);
  auto love10 = require(love3,love4);
  auto love11 = require(love5,love6);
  auto love12 = require(love7,love8);

  auto love13 = require(love09,love10);
  auto love14 = require(love11,love12);

  auto love15 = require(love13,love14);

  auto leave = require(love15,live15);

  EXPECT_EQ($P_n$ - Pristine::count, 31);
  purge.preserving(live7);
  EXPECT_EQ($P_n$ - Pristine::count, 31);
  EXPECT_FF(corrupted.something());
}


TEST(Preserve, DAG) {
  heapify();
  auto dead1 = require(-3,-2);
  auto live1 = require(-2,-3);
  auto dead2 = require(-5,-2);
  auto live2 = require(live1.handle(),-4);
  auto dead3 = require(dead1,dead2);
  auto live3 = require(live2.handle(),-5);
  auto dead4 = require(dead3,dead2);
  auto dead5 = require(dead4,dead4);
  auto live4 = require(live2,live3);
  EXPECT_EQ($P_n$ - Pristine::count, 9);
  purge.preserving(live4);
  EXPECT_EQ($P_n$ - Pristine::count, 5);
}


