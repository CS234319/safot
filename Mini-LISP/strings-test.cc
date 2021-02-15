#include <iostream>
#include "gtest/gtest.h"
#include "strings.cc"
#include "test.h"

 
TEST(Strings, Representation) {
  using namespace Strings;
  EXPECT_EQ(nil, buffer + sizeof(data.buffer));
  EXPECT_EQ(nil - buffer, sizeof(data.buffer));
  EXPECT_EQ(nil, pool);
}

