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
static Pushdown p;

#define UNCHIC
#include "chic.h" 
#undef function
#include <string.h>
#include <gtest/gtest.h>


TEST(Pristine, 1Count) {
  heapify();
  p.clear();
  EXPECT_TRUE(p.top.x());
  EXPECT_TRUE(p.empty());
  EXPECT_GE(Pristine::count,10);
  int before = Pristine::count;
  p.push(3);
  EXPECT_EQ(Pristine::count, before - 1);
}
 
TEST(Pristine, 3Count) {
  p.clear();
  EXPECT_TRUE(p.top.x());
  EXPECT_TRUE(p.empty());
  int before = Pristine::count;
  EXPECT_GE(before,2);
  p.push(3);
  EXPECT_EQ(Pristine::count, before - 1);
  p.push(2);
  EXPECT_EQ(Pristine::count, before - 2);
  require("ABC");
  EXPECT_EQ(Pristine::count, before - 2);
  require(12,13);
  EXPECT_EQ(Pristine::count, before - 3);
  EXPECT_EQ(2,p.pop());
  EXPECT_EQ(Pristine::count, before - 2);
  EXPECT_EQ(3,p.pop());
  EXPECT_EQ(Pristine::count, before - 1);
  EXPECT_TRUE(p.empty());
  EXPECT_TRUE(p.top.x());
}
