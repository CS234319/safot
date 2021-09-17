#import  <iostream>
#import  "gtest/gtest.h"
#import  "S.h"
#import  "test.h"

namespace Pairs {
extern H allocate(); 
/* Sanity of free/allocate; someday: deal with exhausted memory */
TEST(Pairs, Representation) {
  using namespace Pairs;
  H before = Pairs::to_go();
  H h = Pairs::allocate();
  EXPECT_EQ(Pairs::to_go(), before - 1);
  Pairs::free(h);
  H h1 = Pairs::allocate();
  EXPECT_EQ(h, h1);
  EXPECT_EQ(Pairs::to_go(), before - 1);
  Pairs::free(h);
  EXPECT_EQ(Pairs::to_go(), before);
}
}
