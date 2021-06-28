#include "Accounter.h"

#include "Test.h"

TEST(Accounter, exists) {
  Accounter c;
}

TEST(Accounter, zero) {
  Accounter c;
  EXPECT_ZZ(c);
}

TEST(Accounter, increment) {
  Accounter c;
  EXPECT_EQ(c,0);
  ++c;
  EXPECT_EQ(c,1);
  --c;
  EXPECT_EQ(c,0);
}

TEST(Accounter, clear) {
  Accounter c;
  EXPECT_EQ(c,0);
  ++c;
  ++c;
  ++c;
  EXPECT_EQ(c,3);
  !c;
  EXPECT_EQ(c,0);
}

TEST(Accounter, priority) {
  Accounter c;
  - - + + +!c;
  EXPECT_EQ(c,1);
}

TEST(Accounter, crash) {
  Accounter c;
  --c;
  EXPECT_EQ(c,1);
}
