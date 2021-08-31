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

TEST(Lookup, T0) {
  CAREFULLY_EXPECT(EQ,lookup("T"),"T", << 2); 
}

TEST(Lookup, T) {
  EXPECT_STRUE(lookup("T"));
  EXPECT_TRUE(lookup("T").eq(T));
}

TEST(Lookup, NIL) {
  EXPECT_SFALSE(lookup("NIL"));
  EXPECT_FALSE(lookup("NIL").t());
  EXPECT_TRUE(lookup("NIL").eq("NIL"));
  EXPECT_TRUE(lookup("NIL").null());
}

TEST(Lookup, FailurBarBaz) {
  EXPECT_EXCEPTION(lookup("bar baz"),S("bar baz"), UNDEFINED);
}

TEST(Lookup, FailureFooBarBaz) {
  EXPECT_EXCEPTION(lookup("foo" "bar" "baz"), S("foo" "bar" "baz"), UNDEFINED);
  EXPECT_EXCEPTION(lookup("Y"), S("Y"), UNDEFINED);
}

TEST(Lookup, Failure) {
  EXPECT_EXCEPTION(lookup(UNIQUE), S(UNIQUE), UNDEFINED);
  EXPECT_EXCEPTION(lookup("Y"), S("Y"), UNDEFINED);
}

TEST(Lookup, SetGoodLookup) {
  set("X","Y");
  reset_set_counter();
  EXPECT_STRUE(lookup("X"));
}

TEST(Lookup, TeaAndCofee) {
  set("coffee","tea");
  reset_set_counter();
  EXPECT_EQ(lookup("coffee"), S("tea"));
  EXPECT_EXCEPTION(lookup("tea"),S("tea"), UNDEFINED);
  set("tea","coffee");
  reset_set_counter();
  EXPECT_STRUE(lookup("tea"));
  EXPECT_STRUE(lookup("coffee"));
  EXPECT_EQ(lookup("tea"), S("coffee"));
}


TEST(Lookup, Remove1) {
    S restored_alist = *alist();
    // Add 1 element to alist:
    push("A", "X");
    EXPECT_EQ(lookup("A"), S("X"));

    // Remove element from alist:
    remove_element("A");
    EXPECT_EXCEPTION(lookup("A"),S("A"), UNDEFINED);

    *alist() = restored_alist;
}

TEST(Lookup, Remove2) {
    S restored_alist = *alist();

    // Add 2 elements to alist:
    push("A", "X");
    push("B", "Y");
    EXPECT_EQ(lookup("A"), S("X"));
    EXPECT_EQ(lookup("B"), S("Y"));

    // Remove element from alist:
    remove_element("A");
    EXPECT_EXCEPTION(lookup("A"),S("A"), UNDEFINED);
    EXPECT_EQ(lookup("B"), S("Y"));

    *alist() = restored_alist;
}

TEST(Lookup, RemoveElements) {
    S restored_alist = *alist();

    // Add 2 elements to alist:
    push("A", "X");
    push("B", "Y");
    push("C", "Z");
    EXPECT_EQ(lookup("A"), S("X"));
    EXPECT_EQ(lookup("B"), S("Y"));
    EXPECT_EQ(lookup("C"), S("Z"));

    // Remove element from alist:
    S names = list(S("A"), S("B"));
    remove_elements(names);
    EXPECT_EXCEPTION(lookup("A"),S("A"), UNDEFINED);
    EXPECT_EXCEPTION(lookup("B"),S("B"), UNDEFINED);
    EXPECT_EQ(lookup("C"), S("Z"));

    *alist() = restored_alist;
}
