#import  <string.h>
#import  <gtest/gtest.h>
#import  "stack.h"
#import  "test.h"

using namespace Stack;

struct stack:Test{
  stack() {
    Stack::reset();
  }
  ~stack() {
    Stack::reset();
  }
};

TEST_F(stack, Empty) {
  EXPECT_TRUE(empty());
}

TEST_F(stack, Push) {
  EXPECT_TRUE(empty());
  push(3);
  EXPECT_FALSE(empty());
  EXPECT_EQ(3,pop());
  EXPECT_TRUE(empty());
}

TEST_F(stack, Push2) {
  EXPECT_TRUE(empty());
  push(2,3);
  EXPECT_EQ(2,pop());
  EXPECT_EQ(3,pop());
  EXPECT_TRUE(empty());
}

TEST_F(stack, Push3) {
  push(1,2,3);
  EXPECT_EQ(1,pop());
  EXPECT_EQ(2,pop());
  EXPECT_EQ(3,pop());
  EXPECT_TRUE(empty());
}

TEST_F(stack, Peep) {
  push(1,2,3);
  EXPECT_EQ(1,peep());
  EXPECT_EQ(1,peep(0));
  EXPECT_EQ(2,peep(1));
  EXPECT_EQ(3,peep(2));
  EXPECT_EQ(1,pop());
  EXPECT_EQ(2,pop());
  EXPECT_EQ(3,pop());
  EXPECT_TRUE(empty());
}


TEST_F(stack, Push4) {
  push(1,2,3,4);
  EXPECT_EQ(1,pop());
  EXPECT_EQ(2,pop());
  EXPECT_EQ(3,pop());
  EXPECT_EQ(4,pop());
  EXPECT_TRUE(empty());
}

TEST_F(stack, reset) {
  EXPECT_TRUE(empty());
  Stack::push(1,2,3,4);
  EXPECT_FALSE(empty());
  Stack::reset(); 
  EXPECT_TRUE(empty());
  Stack::reset(); 
  EXPECT_TRUE(empty());
}

TEST_F(stack, TopZero) {
  EXPECT_TRUE(empty());
  EXPECT_TRUE(top == 0);
  push(3);
  EXPECT_FALSE(top == 0);
  Stack::reset(); 
  EXPECT_TRUE(top == 0);
} 

TEST_F(stack, PushPush) {
  push(3);
  EXPECT_FALSE(empty());
  push(2);
  EXPECT_FALSE(empty());
  EXPECT_EQ(2,pop());
  EXPECT_EQ(3,pop());
  EXPECT_TRUE(empty());
}

TEST_F(stack, Remaining) {
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
