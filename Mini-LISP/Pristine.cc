#include "Pristine.h"
#include "Short.h"
#include "layout.h"

Short Pristine::count = 0;

Pristine::Pristine(): Pristine($P_x$) {}
Pristine::Pristine(Short s): Knob(s) {}

bool Pristine::ok() const { return x() || marked(s1()) && marked(s2()); }

Pristine Pristine::prev(Pristine p) { 
  let s = p.inner();
  Expect(!marked(s));
  Expect(!x());
  s1(mark(s)); 
  return *this;
}

Pristine Pristine::next(Pristine p) { 
  let s = p.inner();
  Expect(!marked(s));
  Expect(!x());
  s2(mark(s)); 
  return *this;
}

Pristine Pristine::prev() const { 
  Expect(marked(s1()));
  Expect(!x());
  return mark(s1()); 
}

Pristine Pristine::next() const { 
  Expect(marked(s2()));
  Expect(!x());
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

extern Short error();

TEST(Pristine, 1Count) {
  Pushdown p;
  EXPECT_TRUE(p.top.x());
  EXPECT_TRUE(p.empty());
  EXPECT_GE(Pristine::count,10);
  int before = Pristine::count;
  p.push(3);
  EXPECT_EQ(Pristine::count, before - 1);
  EXPECT_EQ(error(),0);
}

TEST(Pristine, RequireCons) {
  EXPECT_EQ(error(),0);
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
  EXPECT_TRUE(p.top.x());
  EXPECT_EQ(error(),0);
}

TEST(Pristine, nRequireCons) {
  EXPECT_EQ(error(),0);
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
  EXPECT_TRUE(p.top.x());
  EXPECT_EQ(error(),0);
}

TEST(Pristine, nPushPop) {
  EXPECT_EQ(error(),0);
  heapify();
  Pushdown p;
  int before = Pristine::count;
  for (int i = 0, n = 0;  i < 16; i++)  
    for (int j = 0;  j < 16; j++) {
      require(i,j);
      ++n;
      p.push(i+j);
      ++n;
      EXPECT_EQ(error(),0);
    }
  EXPECT_EQ(before - Pristine::count, 512);
  for (int i = 0;  i < 16; i++)  
    for (int j = 0;  j < 16; j++) 
      p.pop();
  EXPECT_TRUE(p.top.x());
  EXPECT_EQ(error(),0);
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
  EXPECT_EQ(error(),0);
}

TEST(Pristine, 1RequireCons) {
  EXPECT_EQ(error(),0);
  heapify();
  int before = Pristine::count;
  EXPECT_EQ(Pristine::count, before);
  require(12,13);
  EXPECT_NE(Pristine::count, before);
  EXPECT_EQ(Pristine::count, before -1);
  EXPECT_EQ(error(),0);
}


TEST(Pristine, RequireBoth) {
  EXPECT_EQ(error(),0);
  heapify();
  Pushdown p;
  EXPECT_TRUE(p.top.x());
  EXPECT_TRUE(p.empty());
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
  EXPECT_TRUE(p.empty());
  EXPECT_TRUE(p.top.x());
  EXPECT_EQ(error(),0);
}
