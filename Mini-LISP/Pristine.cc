#include "Pristine.h"
#include "Short.h"
#include "layout.h"

Short Pristine::count = 0;

Pristine::Pristine(): Pristine($P_x$) {}
Pristine::Pristine(Short s): Knob(s) {}

Boolean Pristine::ok() const { 
  if (x()) 
    return true;
  if (!marked(s1()) || !marked(s2()))
      return false;
  const Short p = prev().inner(), n = next().inner();
  if (p != $P_x$) {
    Surely(0, *this,x(), p, n); 
    Surely(0, prev(), next(), prev().inner(), next().inner()); 
    Expect(p >= $P_f$,p); 
    Expect(p <= $P_t$,p); 
    return false;
  }
  if (n != $P_x$) {
    Expect(n >= $P_f$,n); 
    Expect(n <= $P_t$,n); 
    return false;
  }
  return true;
}

Pristine Pristine::prev(Pristine p) { 
  Expect(!x());
  let s = p.inner();
  Expect(!marked(s));
  s1(mark(s)); 
  return *this;
}

Pristine Pristine::next(Pristine p) { 
  Expect(!x());
  let s = p.inner();
  Expect(!marked(s));
  s2(mark(s)); 
  return *this;
}

Pristine Pristine::prev() const { 
  Expect(!x());
  Expect(marked(s1()));
  return mark(s1()); 
}

Pristine Pristine::next() const { 
  Expect(!x());
  Expect(marked(s2()));
  return mark(s2()); 
}

#include "Pushdown.h"
#include "text.h"
#include "Cons.h"

#define UNCHIC
#include "chic.h" 
#undef function
#include <string.h>
#include <gtest/gtest.h>


TEST(Pristine, 1Count) {
  Pushdown p;
  EXPECT_TT(p.top.x());
  EXPECT_TT(p.empty());
  EXPECT_GE(Pristine::count,10);
  int before = Pristine::count;
  p.push(3);
  EXPECT_EQ(Pristine::count, before - 1);
  EXPECT_TT(Pristine::valid());
}

TEST(Pristine, RequireCons) {
  heapify();
  EXPECT_TT(Pristine::valid());
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
  EXPECT_EQ(p.size,0);
  EXPECT_TT(p.top.x());
  EXPECT_TT(Pristine::valid());
}

TEST(Pristine, nRequireCons) {
  EXPECT_TT(Pristine::valid());
  heapify();
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
  EXPECT_EQ(p.size,0);
  EXPECT_TT(p.top.x());
  EXPECT_TT(Pristine::valid());
}

TEST(Pristine, nPushPop) {
  EXPECT_TT(Pristine::valid());
  heapify();
  Pushdown p;
  int before = Pristine::count;
  for (int i = 0, n = 0;  i < 16; i++)  
    for (int j = 0;  j < 16; j++) {
      require(i,j);
      ++n;
      p.push(i+j);
      ++n;
  EXPECT_TT(Pristine::valid());
    }
  EXPECT_EQ(before - Pristine::count, 512);
  for (int i = 0;  i < 16; i++)  
    for (int j = 0;  j < 16; j++) 
      p.pop();
  EXPECT_TT(p.top.x());
  EXPECT_TT(Pristine::valid());
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
  EXPECT_TT(Pristine::valid());
}

TEST(Pristine, 1RequireCons) {
  EXPECT_TT(Pristine::valid());
  heapify();
  int before = Pristine::count;
  EXPECT_EQ(Pristine::count, before);
  require(12,13);
  EXPECT_NE(Pristine::count, before);
  EXPECT_EQ(Pristine::count, before -1);
  EXPECT_TT(Pristine::valid());
}

TEST(Pristine, RequireBoth) {
  EXPECT_TT(Pristine::valid());
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
  EXPECT_TT(Pristine::valid());

}
