#import "purge.h"
#import "heap.cc"
#import "corrupted.h"
#import "accounting.cc"
#import "Short.h"

#import "Testee.h"


TEST(S, Pair) {
  reset();
  S s(13);
  Pair p = s.Pair();
  EXPECT_EQ(p.handle(), s.handle());
}

TEST(Collect, Singleton) {
  reset();
  auto s = request(-1,-2);
  purge.preserving(s);
  EXPECT_EQ(accounting.used, 1);
} 

TEST(Collect, ParentaToSingleton) {
  reset();
  auto s1 = request(-1,-2);
  auto s2 = request(s1, s1);
  purge.preserving(s1);
  EXPECT_EQ(accounting.used, 1);
}

TEST(Collect, ParentaToLeftSingleton) {
  reset();
  auto s0 = request(-1,-2);
  auto s1 = request(s0, s0);
  auto s2 = request(s1, s0);
  purge.preserving(s1);
  EXPECT_EQ(accounting.used, 2);
}

TEST(Collect, ParentaToRightSingleton) {
  reset();
  auto s0 = request(-1,-2);
  auto s1 = request(s0, s0);
  auto s2 = request(s1, s1);
  purge.preserving(s1);
  EXPECT_EQ(accounting.used, 2);
}

TEST(Collect, ParentaToBoth) {
  reset();
  auto s1 = request(-1,-2);
  auto s2 = request(-3,-4);
  auto s3 = request(s1, s2);
  auto s4 = request(s2, s3);
  auto s5 = request(s3, s4);
  purge.preserving(s5);
  EXPECT_EQ(accounting.used, 5);
  purge.preserving(s4);
  EXPECT_EQ(accounting.used, 4);
  purge.preserving(s3);
  EXPECT_EQ(accounting.used, 3);
  purge.preserving(s2);
  EXPECT_EQ(accounting.used, 1);
}


TEST(Visit, exists) {
  reset();
  auto s = request(2,3);
  s.visit();
}

TEST(Visit, repertoire) {
  reset();
  Pair p = request(-2,-3);
  p.visit();
  p.leave();
  p.seen();
}

TEST(Visit, exists2) {
  reset();
  request(2,3).visit();
}

TEST(Visit, seen) {
  reset();
  Pair p = request(5,6);
  EXPECT_FF(p.seen());
  EXPECT_TT(p.visit().seen());
  EXPECT_TT(!p.leave().seen());
}

TEST(Visit, distinct) {
  reset();
  auto x = request(2,3);
  Word w = P[x.handle()];
  x.visit();
  EXPECT_NE(w.l,P[x.handle()].l);
}

TEST(Visit, unseen) {
  auto x = request(2,3);
  Word w = P[x.handle()];
  EXPECT_FF(x.visit().leave().seen());
}

TEST(Visit, reversible) {
  reset();
  auto x = request(2,3);
  Word w = P[x.handle()];
  EXPECT_FF(x.visit().leave().seen());
  EXPECT_EQ(w.l,P[x.handle()].l);
}


TEST(Visit, flip) {
  reset();
  auto p = request(2,3);
  Short before = p.car().handle();
  p.visit(); 
  Short after = p.car().handle();
  EXPECT_EQ(before, flip(after)); 
  EXPECT_EQ(after, flip(before)); 
}

TEST(Visit, ok) {
  reset();
  Pair p = request(2,3);
  EXPECT_TT(p.ok());
  EXPECT_TT(not p.visit().ok());
  EXPECT_TT(p.leave().ok());
}

TEST(Visit, special) {
  Pair p = request(2,3);
  EXPECT_TT(p.ok());
  p.visit();
  EXPECT_FF(p.ok());
  EXPECT_FF(Item(p.handle()).ok());
  EXPECT_FF(Pristine(p.handle()).ok());
}

TEST(Purge, exists) {
  reset();
  auto s = request(-2,-3);
  purge.preserving(s);
  EXPECT_FF(corrupted.something());
}

TEST(Purge, mess) {
  reset();
  try { // Do not dare in real life!
    purge.preserving(request(2,3)); // Use a raw S-Expression.
    EXPECT_TT(corrupted.something()); // The heap may be corrupted, throw exception
  } catch(...) {
    EXPECT_TT(true); // Something bad should happen' we don't know which 
  }
}

TEST(Purge, singleton) {
  reset();
  auto dead = request(-3,-2);
  auto live = request(-2,-3);
  EXPECT_TT(live.ok());
  purge.preserving(live);
  EXPECT_FF(corrupted.something());
}

TEST(Purge, singletonKill) {
  reset();
  auto dead = request(-3,-2);
  auto live = request(-2,-3);
  EXPECT_TT(dead.ok());
  purge.preserving(live);
  EXPECT_FF(dead.ok());
}

TEST(Purge, singletonPristine) {
  reset();
  auto dead = request(-3,-2);
  auto live = request(-2,-3);
  EXPECT_TT(dead.ok());
  purge.preserving(live);
  EXPECT_TT(Knob(dead.handle()).Pristine().ok());
}

TEST(Purge, singletonPrepended) {
  reset();
  auto dead = request(-3,-2);
  auto live = request(-2,-3);
  purge.preserving(live);
  EXPECT_EQ(dead.handle(), heap.handle());
}

TEST(Purge, singletonCount) {
  reset();
  auto dead = request(-3,-2);
  auto live = request(-2,-3);
  EXPECT_EQ(accounting.used, 2);
  purge.preserving(live);
  EXPECT_EQ(accounting.used, 1);
  EXPECT_EQ(accounting.unused, $P_n$-1);
}

TEST(Purge, pairCount) {
  reset();
  auto dead1 = request(-3,-2);
  auto dead2 = request(-5,-2);
  auto dead3 = request(dead2,dead1);
  auto live = request(-2,-3);
  EXPECT_FF(corrupted.something());
  EXPECT_EQ(accounting.used,4);
  purge.preserving(live);
  EXPECT_EQ(accounting.used,1);
  EXPECT_EQ(accounting.unused, $P_n$-1);
}

TEST(Purge, tripleCount) {
  reset();
  auto dead1 = request(-3,-2);
  auto dead2 = request(-5,-2);
  auto live = request(-2,-3);
  purge.preserving(live);
  EXPECT_EQ(accounting.unused, $P_n$-1);
}

TEST(Purge, live2a) {
  reset();
  auto dead1 = request(-3,-2);
  auto dead2 = request(-5,-2);
  auto live1 = request(-2,-3);
  auto live2 = request(live1.handle(),-4);
  purge.preserving(live2);
  EXPECT_EQ(accounting.used, 2);
  EXPECT_FF(corrupted.something());
}

TEST(Purge, live2b) {
  reset();
  auto dead1 = request(-3,-2);
  auto dead2 = request(-5,-2);
  auto live1 = request(-2,-3);
  auto live2 = request(-4,live1.handle());
  purge.preserving(live2);
  EXPECT_EQ(accounting.used, 2);
  EXPECT_FF(corrupted.something());
}

TEST(Purge, live5) {
  reset();
  auto d1 = request(-3,-2).handle();
  auto l1 = request(-2,-3).handle();
  auto d2 = request(d1,d1).handle();
  auto l2 = request(l1,-4).handle();
  auto d3 = request(d1,d2).handle();

  auto live1 = request(-2,-3);
  auto live2 = request(live1.handle(),-4);
  auto live3 = request(live2.handle(),-5);
  auto live4 = request(live3,-6);
  auto live5 = request(live4,-6);

  auto l3 = request(l2,-5).handle();
  auto d4 = request(d3,d2).handle();
  auto l4 = request(l2,l3).handle();
  auto d5 = request(d4,d3).handle();
  auto l5 = request(l4,l4).handle();

  purge.preserving(live5);
  EXPECT_EQ(accounting.used, 5);
  EXPECT_FF(corrupted.something());
}

TEST(Purge, sanity_t2a) {
  reset();

  EXPECT_ZZ(accounting.allocate);
  EXPECT_ZZ(accounting.collect);
  EXPECT_ZZ(accounting.ccit);
  EXPECT_ZZ(accounting.items);
  EXPECT_ZZ(accounting.leave);
  EXPECT_ZZ(accounting.live);
  EXPECT_ZZ(accounting.miss);
  EXPECT_ZZ(accounting.pairs);
  EXPECT_ZZ(accounting.pick);
  EXPECT_ZZ(accounting.pop);
  EXPECT_ZZ(accounting.provide);
  EXPECT_ZZ(accounting.push);
  EXPECT_ZZ(accounting.release);
  EXPECT_ZZ(accounting.request);
  EXPECT_ZZ(accounting.reuse);
  EXPECT_ZZ(accounting.unuse);
  EXPECT_ZZ(accounting.use);
  EXPECT_ZZ(accounting.used);
  EXPECT_ZZ(accounting.visit);

  auto t1 = request(-2,-3);

  EXPECT_EQ(accounting.allocate, 1);
  EXPECT_EQ(accounting.ccit, 1);
  EXPECT_EQ(accounting.live, 1);
  EXPECT_EQ(accounting.pairs, 1);
  EXPECT_EQ(accounting.pick, 1);
  EXPECT_EQ(accounting.provide,1);
  EXPECT_EQ(accounting.request, 1);
  EXPECT_EQ(accounting.use, 1);
  EXPECT_EQ(accounting.used, 1);
  EXPECT_ZZ(accounting.collect);
  EXPECT_ZZ(accounting.items);
  EXPECT_ZZ(accounting.leave);
  EXPECT_ZZ(accounting.miss);
  EXPECT_ZZ(accounting.pop);
  EXPECT_ZZ(accounting.push);
  EXPECT_ZZ(accounting.release);
  EXPECT_ZZ(accounting.reuse);
  EXPECT_ZZ(accounting.unuse);
  EXPECT_ZZ(accounting.visit);

  request(-2,-3); // Repeat the previous request

  EXPECT_EQ(accounting.allocate, 1);
  EXPECT_EQ(accounting.ccit, 1);
  EXPECT_EQ(accounting.live, 1);
  EXPECT_EQ(accounting.pairs, 1);
  EXPECT_EQ(accounting.pick, 1);
  EXPECT_EQ(accounting.provide, 1);
  EXPECT_EQ(accounting.request, 2);
  EXPECT_EQ(accounting.reuse,1);
  EXPECT_EQ(accounting.use, 1);
  EXPECT_EQ(accounting.used, 1);
  EXPECT_ZZ(accounting.collect);
  EXPECT_ZZ(accounting.items);
  EXPECT_ZZ(accounting.leave);
  EXPECT_ZZ(accounting.miss);
  EXPECT_ZZ(accounting.pop);
  EXPECT_ZZ(accounting.push);
  EXPECT_ZZ(accounting.release);
  EXPECT_ZZ(accounting.unuse);
  EXPECT_ZZ(accounting.visit);

  auto t2 = request(t1.handle(),-4);

  EXPECT_EQ(accounting.allocate, 2);
  EXPECT_EQ(accounting.ccit, 2);
  EXPECT_EQ(accounting.live, 2);
  EXPECT_EQ(accounting.pairs, 2);
  EXPECT_EQ(accounting.pick, 2);
  EXPECT_EQ(accounting.provide, 2);
  EXPECT_EQ(accounting.request, 3);
  EXPECT_EQ(accounting.reuse,1);
  EXPECT_EQ(accounting.use, 2);
  EXPECT_EQ(accounting.used, 2);
  EXPECT_FF(corrupted.something());
  EXPECT_ZZ(accounting.collect);
  EXPECT_ZZ(accounting.items);
  EXPECT_ZZ(accounting.leave);
  EXPECT_ZZ(accounting.miss);
  EXPECT_ZZ(accounting.pop);
  EXPECT_ZZ(accounting.push);
  EXPECT_ZZ(accounting.release);
  EXPECT_ZZ(accounting.unuse);
  EXPECT_ZZ(accounting.visit);

  purge.preserving(t2);

  EXPECT_EQ(accounting.allocate, 2);
  EXPECT_EQ(accounting.ccit, 2);
  EXPECT_EQ(accounting.leave,2);
  EXPECT_EQ(accounting.live, 2);
  EXPECT_EQ(accounting.pairs, 2);
  EXPECT_EQ(accounting.pick, 2);
  EXPECT_EQ(accounting.provide, 2);
  EXPECT_EQ(accounting.request, 3);
  EXPECT_EQ(accounting.reuse,1);
  EXPECT_EQ(accounting.use, 2);
  EXPECT_EQ(accounting.used, 2);
  EXPECT_EQ(accounting.visit,2);
  EXPECT_ZZ(accounting.collect);
  EXPECT_ZZ(accounting.items);
  EXPECT_ZZ(accounting.miss);
  EXPECT_ZZ(accounting.pop);
  EXPECT_ZZ(accounting.push);
  EXPECT_ZZ(accounting.release);
  EXPECT_ZZ(accounting.unuse);

  purge.preserving(t2);

  EXPECT_EQ(accounting.allocate, 2);
  EXPECT_EQ(accounting.ccit, 2);
  EXPECT_EQ(accounting.leave,4);
  EXPECT_EQ(accounting.live, 2);
  EXPECT_EQ(accounting.pairs, 2);
  EXPECT_EQ(accounting.pick, 2);
  EXPECT_EQ(accounting.provide, 2);
  EXPECT_EQ(accounting.request, 3);
  EXPECT_EQ(accounting.reuse,1);
  EXPECT_EQ(accounting.use, 2);
  EXPECT_EQ(accounting.used, 2);
  EXPECT_EQ(accounting.visit,4);
  EXPECT_ZZ(accounting.collect);
  EXPECT_ZZ(accounting.items);
  EXPECT_ZZ(accounting.miss);
  EXPECT_ZZ(accounting.pop);
  EXPECT_ZZ(accounting.push);
  EXPECT_ZZ(accounting.release);
  EXPECT_ZZ(accounting.unuse);
}

TEST(Purge, t2b) {
  reset();
  auto t1 = request(-2,-3);
  auto t2 = request(-4,t1.handle());
  purge.preserving(t2);
  EXPECT_EQ(accounting.used, 2);
  EXPECT_FF(corrupted.something());
}

TEST(Purge, t5) {
  reset();
  auto l1 = request(-2,-3).handle();
  auto l2 = request(l1,-4).handle();
  auto t1 = request(-2,-3);
  auto t2 = request(t1.handle(),-4);
  auto t3 = request(t2.handle(),-5);
  auto t4 = request(t3,-6);
  auto t5 = request(t4,-6);
  auto l3 = request(l2,-5).handle();
  auto l4 = request(l2,l3).handle();
  auto l5 = request(l4,l4).handle();

  purge.preserving(t5);
  EXPECT_EQ(accounting.used, 5);
  EXPECT_FF(corrupted.something());
}


TEST(Purge, complete3) {
  reset();
  auto live1 = request(-2,-3);
  auto live2 = request(-3,-4);
  auto live3 = request(-8,-6);

  EXPECT_TT(live1.ok());
  EXPECT_TT(live2.ok());
  EXPECT_TT(live3.ok());
  purge.preserving(live3);
  EXPECT_FF(live1.ok());
  EXPECT_FF(live2.ok());
  EXPECT_TT(live3.ok());

  EXPECT_EQ(accounting.used, 1);
}


TEST(Purge, complete7) {
  reset();
  auto live1 = request(-2,-3);
  auto live2 = request(-3,-4);
  auto live3 = request(-8,-6);
  auto live4 = request(-6,-4);

  auto live5 = request(live1,live2);
  auto live6 = request(live3,live4);
  auto live7 = request(live5,live5);

  EXPECT_TT(live1.ok());
  EXPECT_TT(live2.ok());
  EXPECT_TT(live3.ok());
  EXPECT_TT(live4.ok());
  EXPECT_TT(live5.ok());
  EXPECT_TT(live6.ok());
  EXPECT_TT(live7.ok());
  EXPECT_EQ(accounting.used, 7);
  EXPECT_EQ(accounting.pick, 7);

  purge.preserving(live7);

  EXPECT_TT(live7.ok());
  EXPECT_TT(live5.ok());
  EXPECT_TT(live2.ok());
  EXPECT_TT(live1.ok());

  EXPECT_EQ(accounting.leave, 4);
  EXPECT_EQ(accounting.visit, 4);
  EXPECT_EQ(accounting.collect, 3);
  EXPECT_EQ(accounting.used, 4);
  EXPECT_EQ(accounting.release, 3);
  EXPECT_EQ(accounting.push, 3);
  EXPECT_EQ(accounting.pop, 0);

  EXPECT_FF(live3.ok());
  EXPECT_FF(live4.ok());
  EXPECT_FF(live6.ok());
}

TEST(S, Pair1) {
  S s(13);
  Pair p = s.Pair();
  EXPECT_EQ(p.handle(), s.handle());
}

TEST(Purge, complete15) {
  reset();
  auto live1 = request(-1,-10);
  auto live2 = request(-2,live1);
  auto live3 = request(-3,live2);
  auto live4 = request(-4,live3);
  auto live5 = request(-5,live4);
  auto live6 = request(-6,live5);
  auto live7 = request(-7,live6);

  auto dead08 = request(-8,-2);
  auto dead09 = request(live1,live2);
  auto dead10 = request(live3,live4);
  auto dead11 = request(live5,live6);
  auto dead12 = request(live7,dead08);

  auto dead13 = request(dead09,dead10);
  auto dead14 = request(dead11,dead12);

  auto dead15 = request(dead13,dead14);

  EXPECT_TT(dead15.ok());
  EXPECT_TT(live7.ok());

  EXPECT_EQ(accounting.used, 15);

  purge.preserving(live7);

  EXPECT_EQ(accounting.collect, 8);
  EXPECT_EQ(accounting.push, 8);
  EXPECT_EQ(accounting.live, 7);
  EXPECT_FF(dead15.ok());
  EXPECT_TT(live7.ok());
  EXPECT_EQ(accounting.used, 7);
  EXPECT_FF(corrupted.something());

  purge.all();

  EXPECT_EQ(accounting.collect, 15);
  EXPECT_EQ(accounting.push, 15);
  EXPECT_EQ(accounting.live, 0);
  EXPECT_FF(dead15.ok());
  EXPECT_FF(live7.ok());
  EXPECT_EQ(accounting.used, 0);
  EXPECT_FF(corrupted.something());

}


TEST(Purge, live31) {
  reset();
  auto live1 = request(-1,-3);
  auto live2 = request(-2,-4);
  auto live3 = request(-3,-6);
  auto live4 = request(-4,-4);
  auto live5 = request(-5,-1);
  auto live6 = request(-6,-7);
  auto live7 = request(-7,-5);
  auto live8 = request(-8,-2);

  auto live09 = request(live1,live2);
  auto live10 = request(live3,live4);
  auto live11 = request(live5,live6);
  auto live12 = request(live7,live8);

  auto live13 = request(live09,live10);
  auto live14 = request(live11,live12);

  auto live15 = request(live13,live14);

  auto love1 = request(-11,-23);
  auto love2 = request(-21,-24);
  auto love3 = request(-31,-26);
  auto love4 = request(-41,-24);
  auto love5 = request(-51,-21);
  auto love6 = request(-61,-27);
  auto love7 = request(-71,-25);
  auto love8 = request(-81,-22);

  auto love09 = request(love1,love2);
  auto love10 = request(love3,love4);
  auto love11 = request(love5,love6);
  auto love12 = request(love7,love8);

  auto love13 = request(love09,love10);
  auto love14 = request(love11,love12);

  auto love15 = request(love13,love14);

  auto leave = request(love15,live15);

  EXPECT_EQ(accounting.used, 31);
  EXPECT_EQ(accounting.live, 31);
  EXPECT_EQ(accounting.collect, 0);
  purge.preserving(live7);
  EXPECT_EQ(accounting.live, 1);
  EXPECT_EQ(accounting.collect, 30);
  EXPECT_EQ(accounting.used, 1);
  EXPECT_FF(corrupted.something());
}


TEST(Purge, DAG) {
  reset();
  auto live1 = request(-2,-3);
  auto live2 = request(live1.handle(),-4);
  auto live3 = request(live2.handle(),-5);
  auto live4 = request(live2,live3);
  auto dead1 = request(-3,-2);
  auto dead2 = request(-5,-2);
  auto dead3 = request(dead1,live2);
  auto dead4 = request(live4,request(5,5));
  auto dead5 = request(dead4,dead4);
  EXPECT_EQ(accounting.used, 10);
  purge.preserving(live4);
  EXPECT_EQ(accounting.used, 4);
  EXPECT_EQ(accounting.collect, 6);
}

auto trailLeft(auto n) {
  reset(); Pair p[n];
  p[0] = request(-2, -3);
  for (auto i = 1; i < n; i++) p[i] = request(p[i-1],request(-i, -i));
  for (auto i = 1; i < n; ++i) ASSERT_TT(p[i].ok()) << i; 
  purge.preserving(p[n-1]);
  for (auto i = 1; i > n; ++i) ASSERT_TT(p[i].ok()) << i;
}

TEST(Purge, trailLeft1) { trailLeft(1); }
TEST(Purge, trailLeft2) { trailLeft(2); }
TEST(Purge, trailLeft3) { trailLeft(3); }
TEST(Purge, trailLeft4) { trailLeft(4); }
TEST(Purge, trailLeft5) { trailLeft(5); }
TEST(Purge, trailLeft6) { trailLeft(6); }
TEST(Purge, trailLeft7) { trailLeft(7); }

auto trailRight(auto n) {
  reset(); Pair p[n];
  p[0] = request(-2, -3);
  for (auto i = 1; i < n; i++) p[i] = request(p[i-1],request(-i, -i));
  for (auto i = 1; i < n; ++i) ASSERT_TT(p[i].ok()) << i;
  purge.preserving(p[n-1]);
  for (auto i = 1; i > n; ++i) ASSERT_TT(p[i].ok()) << i;
}
TEST(Purge, traiRight1) { trailRight(1); }
TEST(Purge, traiRight2) { trailRight(2); }
TEST(Purge, traiRight3) { trailRight(3); }
TEST(Purge, traiRight4) { trailRight(4); }
TEST(Purge, traiRight5) { trailRight(5); }
TEST(Purge, traiRight6) { trailRight(6); }
TEST(Purge, traiRight7) { trailRight(7); }

auto fibonnaci(auto n) {
  reset(); Pair p[n];
  p[0] = request(-2, -3); p[1] = request(-5, -8);
  for (auto i = 2; i < n; i++) p[i] = request(p[i-2], p[i-1]);
  for (auto i = 1; i < n; ++i) ASSERT_TT(p[i].ok()) << i;
  purge.preserving(p[n-1]);
  for (auto i = 1; i > n; ++i) ASSERT_TT(p[i].ok()) << i;
}
TEST(Purge, Fibonnaci1) { fibonnaci(1); }
TEST(Purge, Fibonnaci2) { fibonnaci(2); }
TEST(Purge, Fibonnaci3) { fibonnaci(3); }
TEST(Purge, Fibonnaci4) { fibonnaci(4); }
TEST(Purge, Fibonnaci5) { fibonnaci(5); }
TEST(Purge, Fibonnaci6) { fibonnaci(6); }
