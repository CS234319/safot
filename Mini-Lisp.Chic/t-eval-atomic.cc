#include <iostream>
#include "gtest/gtest.h"
#include "test.h"

auto atom(S s) { return s.atom(); }

TEST(AtomicFunctionsList, AfterSet) {
  EXPECT_TRUE(atom("car"));
  EXPECT_TRUE(atom("cdr"));
  EXPECT_TRUE(atom("cons"));
  EXPECT_TRUE(atom("NULL"));
  EXPECT_TRUE(atom("NIL"));
  EXPECT_TRUE(atom("X"));
  EXPECT_TRUE(atom(""));
}
