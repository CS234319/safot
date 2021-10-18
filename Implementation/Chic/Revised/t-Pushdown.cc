#import "Pushdown.h"
#import "Pristine.h"
#import "heap.cc"
#import "accounting.h"

#import "Testee.h"

TEST(Pushdown, empty) {
  Pushdown p;
  EXPECT_TT(p.empty());
}

TEST(Pushdown, push) {
  reset();
  Pushdown p;
  p.clear().push(3);
  EXPECT_TT(!p.empty());
}

TEST(Pushdown, clear) {
  reset();
  Pushdown p;
  p.clear().push(3).push(7).push(19).pop();
  p.push(21).pop(); 
  p.push(23);
  p.clear();
  EXPECT_TT(p.empty());
}

TEST(Pushdown, pushPopEmpty) {
  reset();
  Pushdown p;
  p.push(3).pop();
  EXPECT_TT(p.empty());
}

TEST(Pushdown, correctPop1) {
  reset();
  Pushdown p;
  p.push(3);
  EXPECT_FF(p.empty());
  EXPECT_EQ(3,p.pop());
  EXPECT_TT(p.empty());
}

TEST(Pushdown, correctPop2) {
  reset();
  Pushdown p;
  p.push(3);
  p.push(2);
  EXPECT_EQ(2,p.pop());
  EXPECT_EQ(3,p.pop());
  EXPECT_TT(p.empty());
}

TEST(Item, 1Count) {
  reset();
  Pushdown p;
  EXPECT_TT(p.top.x());
  EXPECT_TT(p.empty());
  int before = accounting.items;
  EXPECT_GE(before,0);
  p.push(3);
  EXPECT_GE(accounting.items,1);
  EXPECT_EQ(accounting.items, before + 1);
}

TEST(Pushdown, 2Push0) {
  reset();
  Pushdown p;
  p.push(3).push(2);
  EXPECT_EQ(2,p.pop());
  EXPECT_EQ(3,p.pop());
  EXPECT_TT(p.empty());
}

TEST(Pushdown, 2Push2) {
  reset();
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
  reset();
  Pushdown p;
  p.push(13);
  EXPECT_EQ(13,p.peep());
}

TEST(Pushdown, 0Peep0) {
  reset();
  Pushdown p;
  p.push(13).push(12);
  EXPECT_EQ(12,p.peep(0));
}

TEST(Pushdown, size) {
  reset();
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
  reset();
  Pushdown p;
  p.push(1,2,3,4);
  EXPECT_EQ(1,p.pop());
  EXPECT_EQ(2,p.pop());
  EXPECT_EQ(3,p.pop());
  EXPECT_EQ(4,p.pop());
  EXPECT_TT(p.empty());
}

TEST(Pushdown, Clear) {
  reset();
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
  reset();
  Pushdown p;
  EXPECT_TT(p.empty());
  EXPECT_TT(p.top.x());
  p.push(3);
  EXPECT_FF(p.top.x());
  p.clear(); 
  EXPECT_TT(p.top.x());
} 

TEST(Pushdown, Size) {
  reset();
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
  reset();
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
  reset();
  {
    Pushdown p;
    p.push(1,2,3,4,5);
    EXPECT_EQ(accounting.items, 5);
  }
  EXPECT_EQ(accounting.items, 0);
}
