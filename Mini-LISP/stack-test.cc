#include <string.h>
#include <gtest/gtest.h>
#include "stack.cc"
#include "parser.h"
#include "test.h"

using namespace Stack;
TEST(Stack, Empty) {
  EXPECT_TRUE(empty());
}

TEST(Stack, Push) {
  push(3);
  EXPECT_FALSE(empty());
  EXPECT_EQ(3,pop());
  EXPECT_TRUE(empty());
}

TEST(Stack, Push2) {
  push(2,3);
  EXPECT_EQ(2,pop());
  EXPECT_EQ(3,pop());
  EXPECT_TRUE(empty());
}

TEST(Stack, Push3) {
  push(1,2,3);
  EXPECT_EQ(1,pop());
  EXPECT_EQ(2,pop());
  EXPECT_EQ(3,pop());
  EXPECT_TRUE(empty());
}

TEST(Stack, Push4) {
  push(1,2,3);
  EXPECT_EQ(1,pop());
  EXPECT_EQ(2,pop());
  EXPECT_EQ(3,pop());
  EXPECT_TRUE(empty());
}



TEST(Stack, PushPush) {
  push(3);
  EXPECT_FALSE(empty());
  push(2);
  EXPECT_FALSE(empty());
  EXPECT_EQ(2,pop());
  EXPECT_EQ(3,pop());
  EXPECT_TRUE(empty());
}

TEST(Stack, Remaining) {
  EXPECT_EQ(0, top);
  EXPECT_TRUE(empty());
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
  EXPECT_TRUE(empty());
  EXPECT_EQ(0, top);
}
