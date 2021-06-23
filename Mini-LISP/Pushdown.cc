#include "Pushdown.h"
#include "Short.h"

Pushdown::~Pushdown() { clear(); }

Property(Boolean Pushdown::empty) { 
  Keep(top.ok());
  return top.x(); 
} 

Pushdown& Pushdown::push(Short s) { 
  Expect(white(s));
  Keep(top.ok());
  Promise(!top.x());
  Promise(top.head() == s);
  ++size, top = fresh(s, top.inner()); 
  return *this; 
}

Pushdown& Pushdown::push(Short s1,Short s2) { return push(s2).push(s1); }
Pushdown& Pushdown::push(Short s1,Short s2, Short s3) { return push(s3).push(s1, s2); }
Pushdown& Pushdown::push(Short s1,Short s2, Short s3, Short s4) { return push(s4).push(s1, s2, s3); }
Pushdown& Pushdown::push(Short s1,Short s2, Short s3, Short s4, Short h5) { return push(h5).push(s1, s2, s3, s4); }

Short Pushdown::pop() {
  Expect(!empty());
  let $ = top.head();
  let old = top;
  top = top.rest();
  free(old);
  --size;
  return $;
}

Pushdown& Pushdown::clear() {
  while (!empty()) 
    pop();
  return *this;
}

Short Pushdown::peep() const {
  Expect(!empty());
  return top.head();
}

Short Pushdown::peep(Short depth) const {
  Expect(!empty());
  Expect(depth <= size);
  Expect(depth >= 0);
  Expect(!top.x());
  for (auto i = top; ; i = i.rest(), --depth) {
    Expect(i.ok());
    Expect(!i.x());
    if (depth == 0)
      return i.head();
  }
}

void Pushdown::poke(Short depth, Short value) {
  Expect(!empty());
  Expect(depth < size);
  Expect(depth >= 0);
  for (auto i = top; ; i = i.rest(), --depth) {
    Expect(i.ok());
    Expect(!i.x());
    if (depth == 0) {
      i.head(value);
      return;
    }
  }
}


#include "Pristine.h"
#include "Test.h"

TEST(Pushdown, Empty) {
  Pushdown p;
  EXPECT_TT(p.empty());
}

TEST(Pushdown, 1Push) {
  Pushdown p;
  p.push(3);
  EXPECT_FF(p.empty());
  EXPECT_EQ(3,p.pop());
  EXPECT_TT(p.empty());
}

TEST(Pushdown, 2Push) {
  Pushdown p;
  p.push(3);
  p.push(2);
  EXPECT_EQ(2,p.pop());
  EXPECT_EQ(3,p.pop());
  EXPECT_TT(p.empty());
}

TEST(Pushdown, 2Push0) {
  Pushdown p;
  p.push(3).push(2);
  EXPECT_EQ(2,p.pop());
  EXPECT_EQ(3,p.pop());
  EXPECT_TT(p.empty());
}

TEST(Pushdown, 2Push2) {
  Pushdown p;
  p.push(2,3);
  EXPECT_EQ(2,p.pop());
  EXPECT_EQ(3,p.pop());
  EXPECT_TT(p.empty());
}

TEST(Pushdown, Push3) {
  Pushdown p;
  p.push(1,2,3);
  EXPECT_EQ(1,p.pop());
  EXPECT_EQ(2,p.pop());
  EXPECT_EQ(3,p.pop());
  EXPECT_TT(p.empty());
}

TEST(Pushdown, Peep0) {
  Pushdown p;
  p.push(13);
  EXPECT_EQ(13,p.peep());
}

TEST(Pushdown, 0Peep0) {
  Pushdown p;
  p.push(13).push(12);
  EXPECT_EQ(12,p.peep(0));
}

TEST(Pushdown, 3Size) {
  Pushdown p;
  EXPECT_EQ(p.push(1,2,3).size, 3);
}

TEST(Pushdown, 3Peep) {
  Pushdown p;
  p.push(1,2,3);
  EXPECT_EQ(1,p.peep());
  EXPECT_EQ(1,p.peep(0));
  EXPECT_EQ(2,p.peep(1));
  EXPECT_EQ(3,p.peep(2));
  EXPECT_EQ(1,p.pop());
  EXPECT_EQ(2,p.pop());
  EXPECT_EQ(3,p.pop());
  EXPECT_TT(p.empty());
}

TEST(Pushdown, Push4) {
  Pushdown p;
  p.push(1,2,3,4);
  EXPECT_EQ(1,p.pop());
  EXPECT_EQ(2,p.pop());
  EXPECT_EQ(3,p.pop());
  EXPECT_EQ(4,p.pop());
  EXPECT_TT(p.empty());
}

TEST(Pushdown, Clear) {
  Pushdown p;
  EXPECT_TT(p.empty());
  p.push(1,2,3,4);
  EXPECT_FF(p.empty());
  p.clear(); 
  EXPECT_TT(p.empty());
  p.clear(); 
  EXPECT_TT(p.empty());
}

TEST(Pushdown, TopZero) {
  Pushdown p;
  EXPECT_TT(p.empty());
  EXPECT_TT(p.top.x());
  p.push(3);
  EXPECT_FF(p.top.x());
  p.clear(); 
  EXPECT_TT(p.top.x());
} 

TEST(Pushdown, Size) {
  Pushdown p;
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
  EXPECT_EQ(p.size,2);
  p.pop();
  EXPECT_EQ(p.size,1);
  p.pop();
  EXPECT_EQ(p.size,0);
} 


TEST(Pushdown, PushPush) {
  Pushdown p;
  p.push(3);
  EXPECT_FF(p.empty());
  p.push(2);
  EXPECT_FF(p.empty());
  EXPECT_EQ(2,p.pop());
  EXPECT_EQ(3,p.pop());
  EXPECT_TT(p.empty());
}

TEST(Pushdown, Destructor) {
  heapify();
  {
    Pushdown p;
    p.push(1,2,3,4,5);
    EXPECT_EQ(Item::count, 5);
  }
  EXPECT_EQ(Item::count, 0);
}

