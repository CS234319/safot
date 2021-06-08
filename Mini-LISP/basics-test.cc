#include <iostream>
#include "gtest/gtest.h"
#include "basics.h"
#include "test.h"

// Mark here every exceptions that was tested; 
// Add test that all exceptions were checked.
// Add tests that error strings are meaningful; consult with Yossi on how

/**
 * Tests of mini-lisp basics; should be renamed one day
 */

TEST(AtomicFunctionsList, AfterSet) {
  EXPECT_TRUE(atomic("car"));
  EXPECT_TRUE(atomic("cdr"));
  EXPECT_TRUE(atomic("cons"));
  EXPECT_FALSE(atomic("NIL"));
  EXPECT_FALSE(atomic("T"));
  EXPECT_FALSE(atomic("X"));
  EXPECT_FALSE(atomic(""));
}

TEST(List, Empty) {
  S s = list();  
  EXPECT_TRUE(islist(s));
  EXPECT_EQ(S::NIL,s);
  EXPECT_TRUE(s.null());
}

TEST(List, Singleton) {
  const S s = list("A");  
  EXPECT_TRUE(islist(s));
  EXPECT_TRUE(s.car().eq(S("A")));
  EXPECT_TRUE(s.car().eq("A")); 
  EXPECT_TRUE(s.cdr().eq(S::NIL)); 
  EXPECT_TRUE(s.cdr().eq("NIL")); 
  EXPECT_TRUE(s.cdr().eq(S("NIL")));
  EXPECT_EQ(S::NIL,s.cdr());
}

TEST(List, Many) {
  EXPECT_TRUE(islist(list("A", "B", "C")));
  EXPECT_TRUE(islist(list("A", "B", "C", "D" )));
  EXPECT_TRUE(islist(list("A", "B", "C", "D" )));
  EXPECT_TRUE(islist(list("A", "E", "B", "C", "D" )));
  EXPECT_TRUE(islist(list("A", "B", "E", "C", "E", "D" )));
  EXPECT_TRUE(islist(list("E", "X", "A", "E", "B", "C", "D" )));
  EXPECT_TRUE(islist(list("E", "E", "A", "B", "E", "C", "E", "D")));
  EXPECT_TRUE(islist(list("1", "2", "3", "4", "5", "6", "7", "8")));
  EXPECT_TRUE(islist(list("1", "2", "3", "4", "5", "6", "7", "8", "9")));
  EXPECT_TRUE(islist(list("0", "1", "2", "3", "4", "5", "6", "7", "8", "9")));
}


TEST(Exists, Trivial) {
  EXPECT_FALSE(exists(S("A"),list()));
}

TEST(Exists, Empty) {
  EXPECT_FALSE(exists(S("A"),list()));
  EXPECT_FALSE(exists(S("B"),list()));
  EXPECT_FALSE(exists(S::NIL,list()));
}

TEST(Exists, Singleton) {
  EXPECT_TRUE(exists(S("A"),list("A")));
  EXPECT_FALSE(exists(S("A"),list("B")));
  EXPECT_FALSE(exists(S::NIL,list("B")));
}

TEST(Exists, Many) {
  EXPECT_TRUE(exists(S("A"),list("A", "B", "C", "D")));
  EXPECT_TRUE(exists(S("B"),list("A", "B", "C", "D")));
  EXPECT_TRUE(exists(S("C"),list("A", "B", "C", "D")));
  EXPECT_TRUE(exists(S("D"),list("A", "B", "C", "D")));
  EXPECT_FALSE(exists(S("a"),list("B", "B", "C", "D")));
  EXPECT_FALSE(exists(S("A"),list("B", "B", "C", "D")));
  EXPECT_TRUE(exists(S("A"),list("B", "B", "a", "D")));
  EXPECT_TRUE(exists(S("a"),list("B", "B", "A", "D")));
  EXPECT_FALSE(exists(S("X"),list("B", "B", "A", "D","C")));
  EXPECT_FALSE(exists(S::NIL,list("B")));
}
