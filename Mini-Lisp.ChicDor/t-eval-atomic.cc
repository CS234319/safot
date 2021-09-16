#include <iostream>
#include "gtest/gtest.h"
#include "test.h"

extern bool atomic(S);

TEST(AtomicFunctionsList, AfterSet) {
  EXPECT_TRUE(atomic("car"));
  EXPECT_TRUE(atomic("cdr"));
  EXPECT_TRUE(atomic("cons"));
  EXPECT_TRUE(atomic("NULL"));

  EXPECT_FALSE(atomic("NIL"));
  EXPECT_FALSE(atomic("T"));
  EXPECT_FALSE(atomic("X"));
  EXPECT_FALSE(atomic(""));
}


