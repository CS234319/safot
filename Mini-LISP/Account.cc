#include "Account.h"
#include "Test.h"

TEST(Account, exists) {
  Account c;
}

TEST(Account, zero) {
  Account c;
  EXPECT_ZZ(c);
}

TEST(Account, increment) {
  Account c;
  EXPECT_EQ(c,0);
  ++c;
  EXPECT_EQ(c,1);
  ++++c;
  EXPECT_EQ(c,3);
 ++++++c; 
  EXPECT_EQ(c,6);
}

TEST(Account, clear) {
  Account c;
  ++++++c; 
  EXPECT_EQ(c,3);
  !c;
  EXPECT_EQ(c,0);
}

TEST(Account, decrement) {
  Account c;
  ++++++c; 
  EXPECT_EQ(c,3);
  --++--++--c; 
  EXPECT_EQ(c,2);
  --++--++--c; 
  EXPECT_EQ(c,1);
  --++--++--c; 
  EXPECT_EQ(c,0);
}

TEST(Account, priority) {
  Account c;
  EXPECT_EQ(c,0);
  !++++++c;
  EXPECT_EQ(c,0);
}

TEST(Account, kind) {
  Account c;
  Account c1 = c.kind(), c2 = c.kind(), c11 = c1.kind(), c111 = c11.kind();
  EXPECT_EQ(c,0);
  ++c1;
  EXPECT_EQ(c,1);
  EXPECT_EQ(c1,1);
  ++c2;
  EXPECT_EQ(c2,1);
  EXPECT_EQ(c,2);
  EXPECT_EQ(c1,1);
  EXPECT_EQ(c11,0);
  EXPECT_EQ(c111,0);
  ++c11;
  EXPECT_EQ(c,3);
  EXPECT_EQ(c1,2);
  EXPECT_EQ(c11,1);
  EXPECT_EQ(c111,0);
  --c11;
  EXPECT_EQ(c,2);
  EXPECT_EQ(c1,1);
  EXPECT_EQ(c11,0);
  EXPECT_EQ(c111,0);
  ++c11;
  EXPECT_EQ(c,3);
  EXPECT_EQ(c1,2);
  EXPECT_EQ(c11,1);
  EXPECT_EQ(c111,0);
  ++c111;
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
  ++c111; 
  EXPECT_EQ(c,1);
  EXPECT_EQ(c1,1);
  EXPECT_EQ(c11,1);
  EXPECT_EQ(c111,2);
  ++c111; 
  EXPECT_EQ(c,2);
  EXPECT_EQ(c1,2);
  EXPECT_EQ(c11,2);
  EXPECT_EQ(c111,3);
  --c11; 
  EXPECT_EQ(c,1);
  EXPECT_EQ(c1,1);
  EXPECT_EQ(c11,1);
  EXPECT_EQ(c111,3);

  !c111; 
  EXPECT_EQ(c,1);
  EXPECT_EQ(c1,1);
  EXPECT_EQ(c11,1);
  EXPECT_EQ(c111,0);
}
