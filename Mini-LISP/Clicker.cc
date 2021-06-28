#include "Clicker.h"

#include "Test.h"

TEST(Clicker, exists) {
  Clicker c;
}

TEST(Clicker, zero) {
  Clicker c;
  EXPECT_ZZ(c);
}

TEST(Clicker, increment) {
  Clicker c;
  EXPECT_EQ(c,0);
  c();
  EXPECT_EQ(c,1);
  c()();
  EXPECT_EQ(c,3);
  c()()();
  EXPECT_EQ(c,6);
}

TEST(Clicker, clear) {
  Clicker c;
  EXPECT_EQ(c,0);
  c();
  c()();
  c()()();
  EXPECT_EQ(c,6);
  !c;
  EXPECT_EQ(c,0);
}

TEST(Clicker, priority) {
  Clicker c;
  EXPECT_EQ(c,0);
  !c()()();
  EXPECT_EQ(c,0);
}

TEST(Clicker, kind) {
  Clicker c;
  Clicker c1 = c.kind(), c2 = c.kind(), c11 = c1.kind(), c111 = c11.kind();
  EXPECT_EQ(c,0);
  c1();
  EXPECT_EQ(c,1);
  EXPECT_EQ(c1,1);
  c2();
  EXPECT_EQ(c2,1);
  EXPECT_EQ(c,2);
  EXPECT_EQ(c1,1);
  EXPECT_EQ(c11,0);
  EXPECT_EQ(c111,0);
  c11();
  EXPECT_EQ(c,3);
  EXPECT_EQ(c1,2);
  EXPECT_EQ(c11,1);
  EXPECT_EQ(c111,0);
  c111();
  EXPECT_EQ(c,4);
  EXPECT_EQ(c1,3);
  EXPECT_EQ(c11,2);
  EXPECT_EQ(c111,1);
  !c; 
  EXPECT_EQ(c,0);
  EXPECT_EQ(c1,3);
  EXPECT_EQ(c11,2);
  EXPECT_EQ(c111,1);
  !c1; 
  EXPECT_EQ(c,0);
  EXPECT_EQ(c1,0);
  EXPECT_EQ(c11,2);
  EXPECT_EQ(c111,1);
  !c11; 
  EXPECT_EQ(c,0);
  EXPECT_EQ(c1,0);
  EXPECT_EQ(c11,0);
  EXPECT_EQ(c111,1);
  !c111; 
  EXPECT_EQ(c,0);
  EXPECT_EQ(c1,0);
  EXPECT_EQ(c11,0);
  EXPECT_EQ(c111,0);
}
