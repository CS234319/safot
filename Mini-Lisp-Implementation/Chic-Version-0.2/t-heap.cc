#import "heap.cc"

#import "text.cc"
#import "Pushdown.cc"
#import "Pristine.cc"
#import "Short.h"
#import "Pair.cc"
#import "S.cc"

#import "corrupted.h"

#import "stdio.h"

#import "Testee.h"
#import "mark.h"

inline std::ostream& operator<<(std::ostream &os, Pristine p) {
  if (p.x())
    return  os << "Px";
  return os << "Pristine[" << p.prev().handle() << "." << p.next().handle()  << "]";
}

using namespace heap;
using heap::reset;

#define EXPECT_TT     EXPECT_TRUE
#define EXPECT_FF     EXPECT_FALSE
#define EXPECT_ZZ(Z)  EXPECT_EQ(0,Z)

TEST(Heapify, exists) { 
  heap::reset();
}

TEST(Heapify, head) { 
  heap::reset();
  heap::heap.x();
  EXPECT_FF(heap::heap.x());
}

TEST(Heapify, allPristine) { 
  heap::reset();
  for (Short s = $P_f$; s <= $P_t$; ++s)
    ASSERT_TRUE(Pristine(s).ok()) << s;
}

TEST(Heapify, entryFirst) { 
  heap::reset();
  EXPECT_TT(Pristine($P_f$).prev().x()); 
  EXPECT_FF(Pristine($P_f$).next().x()); 
  EXPECT_EQ(Pristine($P_f$).next().handle(), $P_f$+1); 
}

TEST(Heapify, entryLast) { 
  heap::reset();
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
  heap::reset();
  for (Short s = $P_f$ + 1; s < $P_t$; ++s) {
    EXPECT_EQ(Pristine(s).prev().handle(), s-1) << s; 
    EXPECT_EQ(Pristine(s).next().handle(), s+1) << s; 
  }
}

TEST(Heapify, prefix) { 
  heap::reset();
  EXPECT_EQ(heap::heap._, $P_f$);
  EXPECT_EQ(heap::heap, $P_f$);
  EXPECT_EQ(Pristine($P_f$).next().handle(), 2);
  EXPECT_ZZ(Pristine($P_f$).prev().handle());
  EXPECT_EQ(Pristine(2).next().handle(), 3);
  EXPECT_EQ(Pristine(2).prev().handle(), $P_f$);
  EXPECT_EQ(Pristine($P_t$).prev().handle(), $P_t$-1);
  EXPECT_EQ(Pristine($P_t$).next().handle(), $P_x$);
}

TEST(Heapify, counters) { 
  heap::reset();
  EXPECT_ZZ(accounting.used);
  EXPECT_ZZ(accounting.miss);
  EXPECT_ZZ(accounting.reuse);
  EXPECT_ZZ(accounting.items);
  EXPECT_EQ(accounting.unused, $P_n$);
}

TEST(Heapify, pristines) { 
  heap::reset();
  EXPECT_FF(corrupted.pristines());
}

TEST(Heapify, items) { 
  heap::reset();
  EXPECT_FF(corrupted.items());
}

TEST(Heapify, pairs) { 
  heap::reset();
  EXPECT_FF(corrupted.pairs());
}

TEST(Heapify, symmetric) { 
  heap::reset();
  EXPECT_FF(corrupted.asymmetric());
}

TEST(Heapify, acyclic) { 
  heap::reset();
  EXPECT_FF(corrupted.cyclic());
}

TEST(Heapify, weirdos) { 
  heap::reset();
  EXPECT_FF(corrupted.weirdos());
}

TEST(Heapify, valid) { 
  heap::reset();
  EXPECT_FF(corrupted.something());
}

TEST(Accounting, reset) { 
  heap::reset();
  EXPECT_ZZ(accounting.used);
  EXPECT_EQ(accounting.unused, $P_n$);
  EXPECT_ZZ(accounting.use); 
  EXPECT_ZZ(accounting.unuse); 
  EXPECT_ZZ(accounting.pairs); 
  EXPECT_ZZ(accounting.items); 
  EXPECT_ZZ(accounting.pairs); 
  EXPECT_ZZ(accounting.allocate); 
  EXPECT_ZZ(accounting.pop); 
  EXPECT_ZZ(accounting.pick); 
  EXPECT_ZZ(accounting.release); 
  EXPECT_ZZ(accounting.push); 
  EXPECT_ZZ(accounting.collect); 
  EXPECT_ZZ(accounting.live); 
  EXPECT_ZZ(accounting.visit); 
  EXPECT_ZZ(accounting.leave); 
  EXPECT_ZZ(accounting.request); 
  EXPECT_ZZ(accounting.reuse); 
  EXPECT_ZZ(accounting.provide); 
  EXPECT_ZZ(accounting.hit); 
  EXPECT_ZZ(accounting.miss); 
}

TEST(Accounting, Nesting) { 
  heap::reset();
  ++accounting.items;
  EXPECT_EQ(accounting.use, 1); 
  EXPECT_EQ(accounting.used, 1); 
  ++accounting.pairs;
  EXPECT_EQ(accounting.use, 2); 
  EXPECT_EQ(accounting.used, 2); 
}

TEST(Accounting, push) { 
  heap::reset();
  Pushdown p;
  p.push(3);
  EXPECT_EQ(accounting.use, 1); 
  EXPECT_EQ(accounting.used, 1);
  EXPECT_EQ(accounting.unuse, 0); 
  EXPECT_EQ(accounting.unused, $P_n$ - 1);
  EXPECT_EQ(accounting.pairs, 0); 
  EXPECT_EQ(accounting.items, 1); 
  EXPECT_EQ(accounting.allocate, 1); 
  EXPECT_EQ(accounting.pop, 1); 
  EXPECT_EQ(accounting.live, 1); 
  EXPECT_ZZ(accounting.visit); 
  EXPECT_ZZ(accounting.leave); 
  EXPECT_ZZ(accounting.pick); 
  EXPECT_ZZ(accounting.release); 
  EXPECT_ZZ(accounting.push); 
  EXPECT_ZZ(accounting.collect); 
  EXPECT_ZZ(accounting.request); 
  EXPECT_ZZ(accounting.reuse); 
  EXPECT_ZZ(accounting.provide); 
  EXPECT_ZZ(accounting.hit); 
  EXPECT_ZZ(accounting.miss); 
}

TEST(Accounting, request) {
  heap::reset();
  EXPECT_ZZ(accounting.used);
  for (int i = 0;  i <= 4; i++)  
    for (int j = 0;  j <= 4; j++) 
      request(S(i),S(j));
  EXPECT_EQ(accounting.used, 25);
}


TEST(Item, 3Count) {
  Pushdown p;
  p.clear();
  EXPECT_TT(p.top.x());
  EXPECT_TT(p.empty());
  EXPECT_GE(accounting.items,0);
  int before = accounting.items;
  p.push(3);
  EXPECT_EQ(accounting.items, before + 1);
  p.push(2);
  EXPECT_EQ(accounting.items, before + 2);
  EXPECT_EQ(2,p.pop());
  EXPECT_EQ(accounting.items, before + 1);
  EXPECT_EQ(3,p.pop());
  EXPECT_EQ(accounting.items, before);
  EXPECT_TT(p.empty());
  EXPECT_TT(p.top.x());
}

TEST(Corruption, makeCyclic) { 
  try {
    heap::reset();
    EXPECT_FF(corrupted.cyclic());
    Pristine($P_t$-3).next(Pristine(($P_f$ + $P_t$)/2));
    EXPECT_TT(corrupted.cyclic());
  } catch(int e) {
    ADD_FAILURE() << "Died at line " << e;
  }
}

TEST(Corruption, ofPrev) { 
  try {
    heap::reset();
    Pristine($P_t$).prev(Pristine(($P_f$ + $P_t$)/2));
    EXPECT_TT(corrupted.asymmetric());
  } catch(int e) {
    ADD_FAILURE() << "Died at line " << e;
  }
}

TEST(Corruption, ofNext) { 
  try {
    heap::reset();
    Pristine(Word(13,17).hash()).next(Pristine(Word(17,13).hash()));
    EXPECT_TT(corrupted.asymmetric());
  } catch(int e) {
    ADD_FAILURE() << "Died at line " << e;
  }
}

TEST(Corruption, selfLoop) { 
  try {
    heap::reset();
    Pristine(Word(13,17).hash()).next(Pristine(Word(13,17).hash()));
    EXPECT_TT(corrupted.cyclic());
  } catch(int e) {
    ADD_FAILURE() << "Died at line " << e;
  }
}

TEST(Fresh, exists) { 
  heap::reset();
  fresh(15,21);
}

TEST(Fresh, uncorrupting) {
  heap::reset();
  fresh(15,$P_x$);
  EXPECT_FF(corrupted.something());
}

TEST(Fresh, correct) { 
  heap::reset();
  Item i = fresh(15,$P_x$);
  EXPECT_TT(i.ok());
  EXPECT_EQ(i.handle(), 1);
  EXPECT_EQ(heap::heap.handle(), 2);
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

TEST(Pair, request) {
  heap::reset();
  S d1 = S(request(S(-3),S(-2)).handle());
  S l1 = S(request(S(-2),S(-3)).handle());
  S d2 = S(request(d1,d1).handle());
  S l2 = S(request(l1,S(-4)).handle());
  S d3 = S(request(d1,d2).handle());
  S l3 = S(request(l2,S(-5)).handle());
  S d4 = S(request(d3,d2).handle());
  S l4 = S(request(l2,l3).handle());
  S d5 = S(request(d4,d3).handle());
  S l5 = S(request(l4,l4).handle());

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
  heap::reset();
  auto c1 = S(request(S(13),S(13))); 
  EXPECT_EQ(P[c1.handle()].hash(), Word(13,13).hash());
  Word w = hash13();
  auto c2 = request(S(w.s1), S(w.s2));
  auto h1 = c1.handle(), h2 = c2.handle();
  EXPECT_NE(h1, h2);
  EXPECT_EQ(P[h1].hash(), P[h2].hash());

  EXPECT_EQ(accounting.miss, 1);
  EXPECT_ZZ(accounting.reuse);
  EXPECT_EQ(accounting.used, 2);
}

TEST(Pair, reuse) {
  heap::reset();
  EXPECT_ZZ(accounting.reuse);
  for (int i = 0;  i <= 4; i++)  
    for (int j = 0;  j <= 4; j++) 
      request(S(i),S(j));
  EXPECT_ZZ(accounting.reuse);
  for (int i = 0;  i <= 4; i++)  
    for (int j = 0;  j <= 4; j++) 
      request(S(i),S(j));
  EXPECT_EQ(accounting.reuse, 25);
  for (int i = 0;  i <= 4; i++)  
    for (int j = 0;  j <= 4; j++) 
      request(S(i),S(j));
  EXPECT_EQ(accounting.reuse, 50);
}

TEST(Pair, Miss) {
  enum { N = 220 };
  heap::reset();
  EXPECT_ZZ(accounting.miss);
  int n = 0;
  for (int i = 0;  i < N; i++) { 
    for (int j = 0;  j < N; j++) {
      request(S(i),S(j));
      ++n;
      if (accounting.miss > 5) 
        break;
    }
    if (accounting.miss > 5) 
      break;
  }
  EXPECT_EQ(n,accounting.used);
  EXPECT_GT(n * n,$P_n$);
  EXPECT_LT(n,N * N / 2);
  EXPECT_GT(accounting.miss,0);
  EXPECT_EQ(accounting.miss,6);
  EXPECT_ZZ(accounting.reuse);
  EXPECT_EQ(accounting.used,n);
}

TEST(Counters, freshFree) { 
  heap::reset();
  auto i = fresh(15,21);
  EXPECT_EQ(accounting.unused, $P_n$ -1);
  free(i);
  EXPECT_EQ(accounting.unused, $P_n$);
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
    heap::reset();
    EXPECT_EQ(length(), $P_n$);
    EXPECT_EQ(length(), accounting.unused);

    auto const s1 = fresh(2,3);
    EXPECT_EQ(length(), $P_n$ - 1);
    EXPECT_EQ(length(), accounting.unused);

    auto const s2 = fresh(4,5);
    EXPECT_EQ(length(), $P_n$ - 2);
    EXPECT_EQ(length(), accounting.unused);

    auto const s3 = fresh(6,7);
    EXPECT_EQ(length(), $P_n$ - 3);
    EXPECT_EQ(length(), accounting.unused);

    free(s1);
    EXPECT_EQ(heap::heap.handle(), 1);
    EXPECT_EQ(length(), $P_n$ - 2);
    EXPECT_EQ(length(), accounting.unused);

    free(s3);
    EXPECT_EQ(heap::heap.handle(), 3);
    EXPECT_EQ(length(), $P_n$ - 1);
    EXPECT_EQ(length(), accounting.unused);

    free(s2);
    EXPECT_EQ(heap::heap.handle(), 2);
    EXPECT_EQ(length(), $P_n$);
    EXPECT_EQ(length(), accounting.unused);
  } catch(int e) {
    ADD_FAILURE() << "Died at line " << e;
  }
}

TEST(request, exists) { 
  try {
    heap::reset();
    request(S(0xDE),S(0xAD));
  } catch(int e) {
    ADD_FAILURE() << "Died at line " << e;
  }
}

TEST(request, pair) { 
  try {
    heap::reset();
    Cons h = request(S(0xDE),S(0xAD));
    EXPECT_TT(h.ok());
  } catch(int e) {
    ADD_FAILURE() << "Died at line " << e;
  }
}

TEST(request, correct) { 
  try {
    heap::reset();
    Short h = request(S(0xDE),S(0xAD)).handle();
    EXPECT_EQ(P[h].s1, 0xDE);
    EXPECT_EQ(P[h].s2, 0xAD);
  } catch(int e) {
    ADD_FAILURE() << "Died at line " << e;
  }
}

TEST(request, 3) { 
  try {
    heap::reset();
    auto s1 = request(S(2),S(3));
    auto s2 = request(S(4),S(5));
    auto s3 = request(S(6),S(7));
  } catch(int e) {
    ADD_FAILURE() << "Died at line " << e;
  }
}

TEST(request, correct3) { 
  heap::reset();
  EXPECT_FF(corrupted.asymmetric());
  EXPECT_EQ(heap::heap.handle(),1);
  auto s1 = request(2,3);
  EXPECT_EQ(heap::heap.handle(),1);
  EXPECT_NE(s1.handle(),1);
  EXPECT_EQ(P[s1.handle()].s1,2);
  EXPECT_EQ(P[s1.handle()].s2,3);
  EXPECT_FF(corrupted.asymmetric());
  EXPECT_EQ(length(), $P_n$-1);
  EXPECT_EQ(length(), accounting.unused);
  auto s2 = request(4,5);
  EXPECT_EQ(s2.car().handle(),4);
  EXPECT_EQ(s2.cdr().handle(),5);
  EXPECT_FF(corrupted.asymmetric());
  EXPECT_EQ(heap::heap.handle(),1);
  EXPECT_EQ(length(), $P_n$-2);
  EXPECT_EQ(length(), accounting.unused);
  auto s3 = request(6,7);
  EXPECT_EQ(heap::heap.handle(),1);
  EXPECT_EQ(s3.car().handle(),6);
  EXPECT_EQ(P[s3.handle()].s2,7);
  EXPECT_EQ(P[s3.handle()].s2,s3.cdr().handle());
}

TEST(request, Scenario) { 
  heap::reset();
  EXPECT_FF(corrupted.asymmetric());
  EXPECT_EQ(heap::heap.handle(),1);
  auto s1 = request(2,3);
  EXPECT_EQ(heap::heap.handle(),1);
  EXPECT_EQ(s1.handle(),Word(2,3).hash());
  EXPECT_EQ(P[s1.handle()].s1,2);
  EXPECT_EQ(P[s1.handle()].s2,3);
  EXPECT_FF(corrupted.asymmetric());
  EXPECT_EQ(length(), $P_n$-1);
  EXPECT_EQ(length(), accounting.unused);
  auto s2 = request(4,5);
  EXPECT_EQ(s2.handle(),Word(4,5).hash());
  EXPECT_EQ(heap::heap.handle(),1);
  EXPECT_EQ(P[s2.handle()].s1,4);
  EXPECT_EQ(P[s2.handle()].s2,5);
  EXPECT_FF(corrupted.asymmetric());
  EXPECT_EQ(length(), $P_n$-2);
  EXPECT_EQ(length(), accounting.unused);
  auto s3 = request(6,7);
  EXPECT_EQ(s3.handle(),Word(6,7).hash());
  EXPECT_EQ(P[s3.handle()].s1,6);
  EXPECT_EQ(P[s3.handle()].s2,7);
  EXPECT_FF(corrupted.asymmetric());
  EXPECT_EQ(length(), $P_n$-3);
  EXPECT_EQ(length(), accounting.unused);
}

TEST(Words, reuse) { 
  heap::reset();
  EXPECT_FF(corrupted.asymmetric());
  EXPECT_EQ(length(), $P_n$);
  EXPECT_EQ(length(), accounting.unused);

  auto s1 = request(3,3);
  EXPECT_TT(s1.ok());
  EXPECT_EQ(s1.handle(), P[s1.handle()].hash());
  EXPECT_FF(corrupted.asymmetric());
  EXPECT_EQ(length(), $P_n$-1);
  EXPECT_EQ(length(), accounting.unused);

  auto s2 = request(2,3);
  EXPECT_TT(s2.ok());
  EXPECT_EQ(s2.handle(),P[s2.handle()].hash());
  EXPECT_FF(corrupted.asymmetric());
  EXPECT_EQ(length(), $P_n$-2);
  EXPECT_EQ(length(), accounting.unused);

  auto s3 = request(3,2);
  EXPECT_EQ(s3.handle(), P[s3.handle()].hash());
  EXPECT_TT(s3.ok());
  EXPECT_FF(corrupted.asymmetric());
  EXPECT_EQ(length(), $P_n$-3);
  EXPECT_EQ(length(), accounting.unused);

  auto s4 = request(2,3);
  EXPECT_TT(s4.ok());
  EXPECT_EQ(s4.handle(), P[s4.handle()].hash());
  EXPECT_FF(corrupted.asymmetric());
  EXPECT_EQ(length(), $P_n$-3);
  EXPECT_EQ(length(), accounting.unused);

  auto s5 = request(3,3);
  EXPECT_TT(s5.ok());
  EXPECT_EQ(s5.handle(), P[s5.handle()].hash());
  EXPECT_EQ(length(), $P_n$-3);
  EXPECT_EQ(length(), accounting.unused);
  EXPECT_FF(corrupted.asymmetric());

  auto s6 = request(3,2);
  EXPECT_TT(s6.ok());
  EXPECT_EQ(s6.handle(), P[s6.handle()].hash());
  EXPECT_EQ(length(), accounting.unused);
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
  heap::reset();
  EXPECT_EQ(accounting.unused, $P_n$); 
  for (auto s = 1 ; s < $P_n$; ++s)
    Item i = fresh(s, $P_x$);
  EXPECT_FF(heap.x());
  EXPECT_EQ(accounting.unused, 1);
  EXPECT_EQ(accounting.items, $P_n$ - 1);
  EXPECT_FF(corrupted.pristines());
  EXPECT_FF(corrupted.items());
  EXPECT_FF(corrupted.pairs());
}

TEST(Exhaust, LateItemCorrect) { 
  heap::reset();
  for (auto s = 1 ; s < $P_n$; ++s)
    Item i = fresh(s, $P_x$);
  Item i = fresh(-2, $P_x$); 
  EXPECT_EQ(i.head(), -2);
  EXPECT_EQ(i.rest().handle(),  $P_x$);
}

TEST(Exhaust, LastItem) { 
  heap::reset();
  for (auto s = 1 ; s < $P_n$; ++s)
    Item i = fresh(s, $P_x$);
  Item i = fresh(-2, $P_x$); 
  EXPECT_FF(corrupted.pristines());
  EXPECT_FF(corrupted.items());
  EXPECT_FF(corrupted.pairs());
  EXPECT_FF(corrupted.something());
}

TEST(Exhaust, items) { 
  heap::reset();
  EXPECT_FF(corrupted.something());
  EXPECT_EQ(accounting.unused, $P_n$); 
  for (auto s = 1 ; s <= $P_n$; ++s) {
    Item i = fresh(s, $P_x$);
    EXPECT_EQ(i.handle(), s - $P_f$ + 1);
    EXPECT_EQ(accounting.items + accounting.unused, $P_n$); 
    EXPECT_EQ(accounting.unused, $P_n$ - s); 
    EXPECT_EQ(accounting.items, s); 
  }
  EXPECT_TT(heap.x());
  EXPECT_ZZ(accounting.unused);
  EXPECT_FF(corrupted.items());
  EXPECT_FF(corrupted.pristines());
}

TEST(Exhaust, andRestore) { 
  heap::reset();
  Pushdown p;
  EXPECT_EQ(accounting.unused, $P_n$); 
  for (auto s = 1 ; s <= $P_n$; ++s) 
    p.push(s);
  for (auto s = $P_n$ ; s >= 1; --s) 
    EXPECT_EQ(s, p.pop()) << s;
  EXPECT_ZZ(accounting.used);
  EXPECT_ZZ(accounting.miss);
  EXPECT_ZZ(accounting.reuse);
  EXPECT_ZZ(accounting.items);
  EXPECT_EQ(accounting.unused, $P_n$);
  EXPECT_FF(corrupted.cyclic());
  EXPECT_FF(corrupted.weirdos()); 
  EXPECT_FF(corrupted.pristines());
  EXPECT_FF(corrupted.items());
  EXPECT_FF(corrupted.pairs());
  EXPECT_FF(corrupted.something());
}

TEST(Churn, Pushdown) { 
  heap::reset();
  for (int i = 0; i < 200 ; i++) { 
    {
      Pushdown p[103];
      for (int j = 0;  j < i; j++) 
        mess(p[Word(i,j).hash() % 10]); 
    }
    EXPECT_FF(corrupted.items());
    EXPECT_EQ(0, accounting.items);
  }
  EXPECT_FF(corrupted.pristines());
  EXPECT_FF(corrupted.items());
  EXPECT_FF(corrupted.pairs());
}  

TEST(Churn, request) { 
  heap::reset();
  int n = 0;
  for (Short i = 0;  ; i++) { 
    for (Short j = 0;  i <= j; j++) {
      Pair c(request(S(i),S(j)).handle());
      ++n;
      EXPECT_TT(c.ok());
      EXPECT_EQ(i, c.car().handle());
      EXPECT_EQ(j, c.cdr().handle());
      EXPECT_EQ(n, accounting.used) << n;
      if (n > 25000)
        goto done;
    }
    EXPECT_FF(corrupted.pristines());
  }
done:
  EXPECT_FF(corrupted.pristines());
}  

TEST(Churn, Both) { 
  heap::reset();
  for (int i = 0, n = 0;  ; i++) { 
    Pushdown p[10];
    for (int j = 0; j <= i; ++j, ++n) {
      if (heap.x()) goto done;
      auto const c = request(S(i),S(j));
      if (heap.x()) goto done;
      int d = P[c.handle()].hash() % 10;
      mess(p[d]);
    }
  }
  done:
    EXPECT_ZZ(accounting.items);
    EXPECT_FF(corrupted.something());
}

TEST(Counting, items) {
  Pushdown p;
  EXPECT_TT(p.top.x());
  EXPECT_TT(p.empty());
  int before = accounting.items;
  EXPECT_GE(before,0);
  p.push(3);
  EXPECT_GE(accounting.items,1);
  EXPECT_EQ(accounting.items, before + 1);
}

TEST(Counting, pairs) {
  heap::reset();
  const Integer before = accounting.unused;
  request(13,14);
  EXPECT_NE(accounting.unused, before);
  EXPECT_EQ(accounting.unused, before - 1);
  EXPECT_EQ(accounting.unused, $P_n$ - 1);
  EXPECT_EQ(accounting.used, 1);
  EXPECT_ZZ(accounting.miss);
  EXPECT_ZZ(accounting.reuse);
  EXPECT_FF(corrupted.something());
}

TEST(Counting, itemsPristines2) {
  heap::reset();
  Pushdown p;
  EXPECT_TT(p.top.x());
  EXPECT_TT(p.empty());
  EXPECT_GE(accounting.unused,10L);
  int before = accounting.unused;
  p.push(3);
  EXPECT_EQ(accounting.unused, before - 1);
  EXPECT_FF(corrupted.something());
}

TEST(Pristine, itemsPristines3) {
  EXPECT_FF(corrupted.asymmetric());
  heap::reset();
  Pushdown p;
  p.push(3,2,1);
  EXPECT_FF(corrupted.asymmetric());
  request(12,13);
  EXPECT_FF(corrupted.asymmetric());
  request(12,13);
  EXPECT_FF(corrupted.asymmetric());
  p.pop();
  EXPECT_FF(corrupted.asymmetric());
}

TEST(Pristine, itemsPristines4) {
  heap::reset();
  EXPECT_FF(corrupted.something());
  Pushdown p;
  int before = accounting.unused;
  p.push(3,2,1);
  EXPECT_EQ(accounting.unused, before - 3);
  EXPECT_EQ(accounting.unused, before - 3);
  request(12,13);
  EXPECT_EQ(accounting.unused, before - 4);
  request(12,13);
  EXPECT_EQ(accounting.unused, before - 4);
  EXPECT_EQ(3,p.pop());
  EXPECT_EQ(2,p.pop());
  EXPECT_EQ(1,p.pop());
  EXPECT_EQ(accounting.unused, before - 1);
  EXPECT_ZZ(p.size);
  EXPECT_TT(p.top.x());
  EXPECT_FF(corrupted.something());
}

TEST(Pristine, requestConsN) {
  heap::reset();
  EXPECT_FF(corrupted.something());
  Pushdown p;
  int before = accounting.unused;
  p.push(3,2,1);
  EXPECT_EQ(accounting.unused, before - 3);
  EXPECT_EQ(accounting.unused, before - 3);
  for (int i = 0;  i <= 4; i++)  
    for (int j = 0;  j <= 4; j++) 
      request(S(i),S(j));
  EXPECT_EQ(accounting.unused, before - 28);
  EXPECT_EQ(3,p.pop());
  EXPECT_EQ(2,p.pop());
  EXPECT_EQ(1,p.pop());
  EXPECT_EQ(accounting.unused, before - 25);
  EXPECT_ZZ(p.size);
  EXPECT_TT(p.top.x());
  EXPECT_FF(corrupted.something());
}

TEST(Exercise, PushrequestPoprequest) {
  enum {N = 16};
  EXPECT_FF(corrupted.something());
  heap::reset();
  Pushdown p;
  int before = accounting.unused;
  for (int i = 0, n = 0;  i < 16; i++)  
    for (int j = 0;  j < 16; j++) {
      request(S(i),S(j));
      ++n;
      p.push(i+j);
      ++n;
    }
  EXPECT_FF(corrupted.something());
  EXPECT_EQ(before - accounting.unused, 2 * N * N);
  for (int i = 0;  i < 16; i++)  
    for (int j = 0;  j < 16; j++) {
      request(i+50, j+100);
      p.pop();
      request(i, j);
    }
  EXPECT_TT(p.top.x());
  EXPECT_FF(corrupted.something());
  EXPECT_EQ(accounting.used, 2*N*N);
  EXPECT_EQ(accounting.unused, $P_n$ - 2 * N *N); 
}

TEST(Pristine, requestAtom) {
  Pushdown p;
  heap::reset();
  int before = accounting.unused;
  p.push(3,2,1);
  request("ABC");
  EXPECT_EQ(accounting.unused, before - 3);
  request("ABC");
  request("CDE");
  EXPECT_EQ(accounting.unused, before - 3);
  EXPECT_EQ(3,p.pop());
  EXPECT_EQ(2,p.pop());
  EXPECT_EQ(1,p.pop());
  EXPECT_EQ(accounting.unused, before);
}

TEST(Pristine, 1requestAtom) {
  int before = accounting.unused;
  EXPECT_EQ(accounting.unused, before);
  request("Foo Bar");
  EXPECT_NE(accounting.unused, before -1);
  EXPECT_EQ(accounting.unused, before);
  EXPECT_FF(corrupted.something());
}

TEST(Pristine, requestBoth) {
  EXPECT_FF(corrupted.something());
  heap::reset();
  Pushdown p;
  EXPECT_TT(p.top.x());
  EXPECT_TT(p.empty());
  int before = accounting.unused;
  EXPECT_GE(before,2);
  p.push(3);
  EXPECT_EQ(accounting.unused, before -1);
  p.push(2);
  EXPECT_EQ(accounting.unused, before -2);
  request("ABC");
  EXPECT_EQ(accounting.unused, before -2);
  request("CDE");
  EXPECT_EQ(accounting.unused, before -2);
  request("ABC");
  EXPECT_EQ(accounting.unused, before -2);
  request("CDE");
  EXPECT_EQ(accounting.unused, before -2);
  request(12,13);
  EXPECT_EQ(accounting.unused, before -3);
  request(12,13);
  EXPECT_EQ(accounting.unused, before -3);
  EXPECT_EQ(2,p.pop());
  EXPECT_EQ(accounting.unused, before -2);
  EXPECT_EQ(3,p.pop());
  EXPECT_EQ(accounting.unused, before -1);
  EXPECT_TT(p.empty());
  EXPECT_TT(p.top.x());
  EXPECT_FF(corrupted.something());
}
