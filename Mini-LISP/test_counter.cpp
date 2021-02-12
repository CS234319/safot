#include <iostream>
using namespace std;
#include "gtest/gtest.h"
#include "mini-lisp.hh"

TEST(Atomic, List) {
  S l = list();  
  EXPECT_EQ(NIL,l);
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


