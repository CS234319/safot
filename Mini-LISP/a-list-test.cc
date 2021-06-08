#include <iostream>
#include "gtest/gtest.h"
#include "a-list.h"
#include "test.h"

// Mark here every exceptions that was tested; 
// Add test that all exceptions were checked.
// Add tests that error strings are meaningful; consult with Yossi on how

/**
 * Tests of mini-lisp basics; should be renamed one day
 */

#define EXPECT_STRUE(e) EXPECT_TRUE(e.t())
#define EXPECT_SFALSE(e) EXPECT_TRUE(e.null())

TEST(Lookup, T) {
  EXPECT_STRUE(lookup("T"));
  EXPECT_TRUE(lookup("T").eq(S::T));
}

TEST(Lookup, NIL) {
  EXPECT_SFALSE(lookup("NIL"));
  EXPECT_FALSE(lookup("NIL").t());
  EXPECT_TRUE(lookup("NIL").eq("NIL"));
  EXPECT_TRUE(lookup("NIL").null());
}

TEST(Lookup, FailurBarBaz) {
  EXPECT_EXCEPTION(lookup("bar baz"),S("bar baz"), S::MISSING);
}

TEST(Lookup, FailureFooBarBaz) {
  EXPECT_EXCEPTION(lookup("foo" "bar" "baz"), S("foo" "bar" "baz"), S::MISSING);
  EXPECT_EXCEPTION(lookup("Y"), S("Y"), S::MISSING);
}

TEST(Lookup, Failure) {
  EXPECT_EXCEPTION(lookup(UNIQUE), S(UNIQUE), S::MISSING);
  EXPECT_EXCEPTION(lookup("Y"), S("Y"), S::MISSING);
}

TEST(Lookup, SetGoodLookup) {
  set("X","Y");
  EXPECT_STRUE(lookup("X"));
}


TEST(Lookup, TeaAndCofee) {
  set("coffee","tea");
  EXPECT_EQ(lookup("coffee"), S("tea"));
  EXPECT_EXCEPTION(lookup("tea"),S("tea"), S::MISSING);
  set("tea","coffee");
  EXPECT_STRUE(lookup("tea"));
  EXPECT_STRUE(lookup("coffee"));
  EXPECT_EQ(lookup("tea"), S("coffee"));
}
