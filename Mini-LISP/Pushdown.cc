#include "Pushdown.h"

bool Pushdown::empty() { return top.x(); } 

Pushdown Pushdown::push(Short data) { 
  ++size, top = fresh(data, top.rest()); 
  return *this; 
}

Pushdown Pushdown::push(Short h1,Short h2) { return push(h2).push(h1); }
Pushdown Pushdown::push(Short h1,Short h2, Short h3) { return push(h3).push(h1, h2); }
Pushdown Pushdown::push(Short h1,Short h2, Short h3, Short h4) { return push(h4).push(h1, h2, h3); }
Pushdown Pushdown::push(Short h1,Short h2, Short h3, Short h4, Short h5) { return push(h5).push(h1, h2, h3, h4); }

Short Pushdown::pop() {
  Expect(!empty());
  let $ = top.head();
  let old = top;
  top = top.rest();
  free(old);
  --size;
  return $;
}

Pushdown Pushdown::clear() {
  while (!empty()) 
    pop();
  return *this;
}

Short Pushdown::peep() {
  Expect(!empty());
  return top.head();
}

Short Pushdown::peep(Short depth) {
  Expect(!empty());
  Expect(depth < size);
  Expect(depth >= 0);
  for (auto i = top; --depth; i = i.rest())
    if (depth == 0)
      return i.head();
}

void Pushdown::poke(Short depth, Short value) {
  Expect(!empty());
  Expect(depth < size);
  Expect(depth >= 0);
  for (auto i = top; --depth; i = i.rest())
    if (depth == 0) {
      i.head(value);
      return;
    }
}


#include "Pristine.h"
#define UNCHIC
#include "chic.h" 
#include <string.h>
#include <gtest/gtest.h>

Pushdown p;

TEST(Pushdown, Empty) {
  EXPECT_TRUE(p.empty());
}

TEST(Pushdown, Push) {
  p.push(3);
  EXPECT_FALSE(p.empty());
  EXPECT_EQ(3,p.pop());
  EXPECT_TRUE(p.empty());
}

TEST(Pushdown, Push2) {
  p.push(2,3);
  EXPECT_EQ(2,p.pop());
  EXPECT_EQ(3,p.pop());
  EXPECT_TRUE(p.empty());
}

TEST(Pushdown, Push3) {
  p.push(1,2,3);
  EXPECT_EQ(1,p.pop());
  EXPECT_EQ(2,p.pop());
  EXPECT_EQ(3,p.pop());
  EXPECT_TRUE(p.empty());
}

TEST(Pushdown, Peep) {
  p.push(1,2,3);
  EXPECT_EQ(1,p.peep());
  EXPECT_EQ(1,p.peep(0));
  EXPECT_EQ(2,p.peep(1));
  EXPECT_EQ(3,p.peep(2));
  EXPECT_EQ(1,p.pop());
  EXPECT_EQ(2,p.pop());
  EXPECT_EQ(3,p.pop());
  EXPECT_TRUE(p.empty());
}


TEST(Pushdown, Push4) {
  p.push(1,2,3,4);
  EXPECT_EQ(1,p.pop());
  EXPECT_EQ(2,p.pop());
  EXPECT_EQ(3,p.pop());
  EXPECT_EQ(4,p.pop());
  EXPECT_TRUE(p.empty());
}

TEST(Pushdown, Clear) {
  EXPECT_TRUE(p.empty());
  p.push(1,2,3,4);
  EXPECT_FALSE(p.empty());
  p.clear(); 
  EXPECT_TRUE(p.empty());
  p.clear(); 
  EXPECT_TRUE(p.empty());
}

TEST(Pushdown, TopZero) {
  EXPECT_TRUE(p.empty());
  EXPECT_TRUE(p.top.x());
  p.push(3);
  EXPECT_FALSE(p.top.x());
  p.clear(); 
  EXPECT_TRUE(p.top.x());
} 

TEST(Pushdown, Size) {
  p.clear();
  EXPECT_EQ(p.size,0);
  p.push(__LINE__);
  EXPECT_EQ(p.size,1);
  p.push(__LINE__);
  EXPECT_EQ(p.size,2);
  p.push(__LINE__);
  EXPECT_EQ(p.size,3);
  p.pop();
  EXPECT_EQ(p.size,2);
  p.push(__LINE__);
  EXPECT_EQ(p.size,3);
  p.pop();
  EXPECT_EQ(p.size,1);
  p.pop();
  EXPECT_EQ(p.size,0);
} 


TEST(Pushdown, PushPush) {
  p.push(3);
  EXPECT_FALSE(p.empty());
  p.push(2);
  EXPECT_FALSE(p.empty());
  EXPECT_EQ(2,p.pop());
  EXPECT_EQ(3,p.pop());
  EXPECT_TRUE(p.empty());
}

TEST(Item, Count) {
  EXPECT_TRUE(p.top.x());
  EXPECT_TRUE(p.empty());
  int before = Item::count;
  EXPECT_GE(before,2);
  p.push(3);
  EXPECT_EQ(Pristine::count, before - 1);
  p.push(2);
  EXPECT_EQ(Item::count, before - 2);
  EXPECT_EQ(2,p.pop());
  EXPECT_EQ(Item::count, before - 1);
  EXPECT_EQ(3,p.pop());
  EXPECT_EQ(Item::count, before);
  EXPECT_TRUE(p.empty());
  EXPECT_TRUE(p.top.x());
}
