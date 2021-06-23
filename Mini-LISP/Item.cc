#include "Item.h"

#include "Short.h"

static Short count;
Item::Item(): Knob() {}
Item::Item(Short s): Knob(s) {}
Item Item::head(Short s) { s1(s);       return *this; }
Item Item::rest(Short s) { s2(flip(s)); return *this; }
Short Item::head() const { return s1(); }
Item Item::rest() const { return Item(flip(s2())); } 
Boolean Item::ok() const { return x() || white(s1())  && black(s2()); }

#include "Pushdown.h"
static Pushdown p;
#include "Test.h"

TEST(Item, 1Push) {
  p.clear();
  p.push(3);
}

TEST(Item, 1Free) {
  p.clear();
  p.push(3);
  p.pop();
}

TEST(Item, 1Count) {
  p.clear();
  EXPECT_TT(p.top.x());
  EXPECT_TT(p.empty());
  int before = Item::count;
  EXPECT_GE(before,0);
  p.push(3);
  EXPECT_GE(Item::count,1);
  EXPECT_EQ(Item::count, before + 1);
}

TEST(Item, 3Count) {
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
