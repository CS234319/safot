#include <string.h>
#include <gtest/gtest.h>
#include "stack.h"
#include "test.h"

using namespace Stack;
TEST(Stack, Empty) {
  EXPECT_T(empty());
}

TEST(Stack, Push) {
  push(3);
  EXPECT_F(empty());
  EXPECT_EQ(3,pop());
  EXPECT_T(empty());
}

TEST(Stack, Push2) {
  push(2,3);
  EXPECT_EQ(2,pop());
  EXPECT_EQ(3,pop());
  EXPECT_T(empty());
}

TEST(Stack, Push3) {
  push(1,2,3);
  EXPECT_EQ(1,pop());
  EXPECT_EQ(2,pop());
  EXPECT_EQ(3,pop());
  EXPECT_T(empty());
}

TEST(Stack, Peep) {
  push(1,2,3);
  EXPECT_EQ(1,peep());
  EXPECT_EQ(1,peep(0));
  EXPECT_EQ(2,peep(1));
  EXPECT_EQ(3,peep(2));
  EXPECT_EQ(1,pop());
  EXPECT_EQ(2,pop());
  EXPECT_EQ(3,pop());
  EXPECT_T(empty());
}


TEST(Stack, Push4) {
  push(1,2,3,4);
  EXPECT_EQ(1,pop());
  EXPECT_EQ(2,pop());
  EXPECT_EQ(3,pop());
  EXPECT_EQ(4,pop());
  EXPECT_T(empty());
}

TEST(Stack, Clear) {
  EXPECT_T(empty());
  push(1,2,3,4);
  EXPECT_F(empty());
  clear(); 
  EXPECT_T(empty());
  clear(); 
  EXPECT_T(empty());
}

TEST(Stack, TopZero) {
  EXPECT_T(empty());
  EXPECT_T(top == 0);
  push(3);
  EXPECT_F(top == 0);
  clear(); 
  EXPECT_T(top == 0);
} 



TEST(Stack, PushPush) {
  push(3);
  EXPECT_F(empty());
  push(2);
  EXPECT_F(empty());
  EXPECT_EQ(2,pop());
  EXPECT_EQ(3,pop());
  EXPECT_T(empty());
}

TEST(Stack, Remaining) {
  EXPECT_EQ(0, top);
  EXPECT_T(empty());
  int before = Pairs::to_go();
  EXPECT_GE(before,2);
  push(3);
  EXPECT_EQ(Pairs::to_go(), before - 1);
  push(2);
  EXPECT_EQ(Pairs::to_go(), before - 2);
  EXPECT_EQ(2,pop());
  EXPECT_EQ(Pairs::to_go(), before - 1);
  EXPECT_EQ(3,pop());
  EXPECT_EQ(Pairs::to_go(), before);
  EXPECT_T(empty());
  EXPECT_EQ(0, top);
}
