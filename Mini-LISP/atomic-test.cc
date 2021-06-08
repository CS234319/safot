#include <iostream>
#include "gtest/gtest.h"
#include "eval.h"

// Mark here every exceptions that was tested; 
// Add test that all exceptions were checked.
// Add tests that error strings are meaningful; consult with Yossi on how

/**
 * Tests of mini-lisp basics; should be renamed one day
 */
TEST(Atomic,EQ) {
  S t("T");
  S n("NIL");
  EXPECT_EQ(S::NIL.handle,0);
  EXPECT_EQ(S::NIL.handle,n.handle);
  EXPECT_EQ(S::T.handle,-2);
  EXPECT_EQ(t.handle, -2);
  EXPECT_FALSE(S::NIL.eq(S::T));
  EXPECT_FALSE(S::T.eq(S::NIL));
  EXPECT_TRUE(S("aBC").eq(S("AbC")));
  EXPECT_TRUE(S("ABC").eq(S("ABC")));
  EXPECT_TRUE(S("nIl").eq(S::NIL));
  EXPECT_TRUE(S("NIL").eq(S("nil")));
  EXPECT_TRUE(S::NIL.eq(S("nil")));
  EXPECT_TRUE(S::NIL.eq(S("NIL")));
  EXPECT_TRUE(S::NIL.eq(S::NIL));
  EXPECT_TRUE(S::T.eq(S::T));
  EXPECT_TRUE(S::T.eq("T"));
  EXPECT_TRUE(S::T.eq(S("T")));
}
