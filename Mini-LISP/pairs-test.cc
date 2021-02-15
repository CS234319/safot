#include <iostream>
#include "gtest/gtest.h"
#include "pairs.cc"
#include "test.h"

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


