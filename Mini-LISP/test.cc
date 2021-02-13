#include <iostream>
#include "gtest/gtest.h"
#include "mini-lisp.cc"
#include "test.hh"

TEST(Comma, Two) {
  S a = S("A");
  EXPECT_TRUE(a.atom());
  EXPECT_FALSE(a.islist());
  S b = S("B");
  EXPECT_TRUE(b.atom());
  EXPECT_FALSE(b.islist());
  S s = (a,b);
  EXPECT_FALSE(s.atom());
  EXPECT_TRUE(s.islist());
  EXPECT_EQ("A",s.car());
  EXPECT_EQ("B",s.cdr().car());
  EXPECT_EQ("NIL",s.cdr().cdr());
  EXPECT_TRUE(exists("A",s));
  EXPECT_TRUE(exists("B",s));
}

TEST(Comma, TwoStrings) {
  S s = ("a",("b", NIL));
  EXPECT_FALSE(s.atom());
  EXPECT_TRUE(s.islist());
  EXPECT_EQ("A",s.car());
  EXPECT_EQ("B",s.cdr().car());
  EXPECT_EQ("NIL",s.cdr().cdr());
  EXPECT_TRUE(exists("A",s));
  EXPECT_TRUE(exists("B",s));
}


TEST(List, Empty) {
  S s = list();  
  EXPECT_TRUE(s.islist());
  EXPECT_EQ(NIL,s);
}

TEST(List, Singleton) {
  const S s = list("A");  
  EXPECT_TRUE(s.islist());
  EXPECT_TRUE(eq(s.car(), S("A")));
  EXPECT_TRUE(eq(s.car(), "A")); 
  EXPECT_TRUE(eq(s.cdr(), NIL)); 
  EXPECT_TRUE(eq(s.cdr(), "NIL")); 
  EXPECT_TRUE(eq(s.cdr(), S("NIL")));
  EXPECT_EQ(NIL,s.cdr());
}


TEST(Strings, Indices) {
  EXPECT_EQ(NIL,NIL);
  EXPECT_NE(NIL,T);
  EXPECT_NE(T,NIL);
  EXPECT_EQ(T,T);
  EXPECT_NE(cons(T,T),cons(T,T));
  EXPECT_EQ(lambda,lambda);
  EXPECT_EQ(lambda,S("lambda"));
  EXPECT_NE(lambda,nlambda);
  EXPECT_NE(nlambda,lambda);
  EXPECT_EQ(nlambda,nlambda);
}

TEST(Strings, NIL) {
  EXPECT_EQ(0,NIL.index);
  EXPECT_EQ(0,S("NIL").index);
  EXPECT_EQ(NIL,S("NIL"));
}

TEST(EQ, Basics) {
  EXPECT_TRUE(eq(T, S("T")));
  EXPECT_TRUE(eq(S("ABC"), S("ABC")));
  EXPECT_TRUE(eq(S("aBC"), S("AbC")));
  EXPECT_FALSE(eq(T,NIL));
  EXPECT_TRUE(eq(T,T));
}

TEST(Strings, Representation) {
  using namespace Strings;
  EXPECT_EQ(nil, buffer + sizeof(buffer));
  EXPECT_EQ(nil, pool);
}


TEST(EQ, Trivial) {
  EXPECT_TRUE(eq(T, S("T")));
  EXPECT_TRUE(eq(S("ABC"), S("ABC")));
  EXPECT_FALSE(eq(T,NIL));
  EXPECT_TRUE(eq(T,T));
}

TEST(EQ, NIL) {
  ASSERT_TRUE(eq(NIL,NIL));
  EXPECT_FALSE(eq(NIL,T));
  EXPECT_FALSE(eq(T,NIL));
  ASSERT_TRUE(eq(S("NIL"),S("nil")));
  ASSERT_TRUE(eq(NIL,S("nil")));
  ASSERT_TRUE(eq(NIL,S("NIL")));
  ASSERT_TRUE(eq(S("nIl"), NIL));
}

TEST(Exists, Empty) {
  EXPECT_FALSE(exists(S("A"),list()));
  EXPECT_FALSE(exists(S("B"),list()));
  EXPECT_FALSE(exists(NIL,list()));
}

TEST(Exists, Singleton) {
  EXPECT_TRUE(exists(S("A"),list("A")));
  EXPECT_FALSE(exists(S("A"),list("B")));
  EXPECT_FALSE(exists(NIL,list("B")));
}

TEST(Exists, Long) {
  EXPECT_TRUE(exists(S("A"),list("A", "B", "C", "D")));
  EXPECT_TRUE(exists(S("B"),list("A", "B", "C", "D")));
  EXPECT_TRUE(exists(S("C"),list("A", "B", "C", "D")));
  EXPECT_TRUE(exists(S("D"),list("A", "B", "C", "D")));
  EXPECT_FALSE(exists(S("a"),list("B", "B", "C", "D")));
  EXPECT_FALSE(exists(S("A"),list("B", "B", "C", "D")));
  EXPECT_TRUE(exists(S("A"),list("B", "B", "a", "D")));
  EXPECT_TRUE(exists(S("a"),list("B", "B", "A", "D")));
  EXPECT_FALSE(exists(NIL,list("B")));
}

TEST(Lookup, T) {
  EXPECT_TRUE(lookup("T").eq("T"));
}

TEST(Lookup, NIL1) {
  S n1 = S("NIL");
  D(n1);
  S n2 = S("nil");
  D(n1,n2);
  EXPECT_EQ(n1.index,n2.index);
}

TEST(Lookup, NIL2) {
  S n1 = S("NIL");
  D(n1);
  S n2 = S("NIL");
  D(n1,n2);
  EXPECT_TRUE(lookup("NIL").eq("NIL"));
}

TEST(Lookup, Failure) {
  D(alist);
  EXPECT_FALSE(lookup("X"));
  EXPECT_FALSE(lookup("Y"));
}

TEST(Lookup, AfterSet) {
  D(alist);
  set("X","Y");
  EXPECT_TRUE(lookup("X"));
  EXPECT_FALSE(lookup("Y"));
  EXPECT_EQ(lookup("X"), S("Y"));
}

TEST(AtomicFunctionsList, AfterSet) {
  D(alist);
  EXPECT_TRUE(exists("car", atomic_functions));
  EXPECT_TRUE(exists("cdr", atomic_functions));
  EXPECT_TRUE(exists("cons", atomic_functions));
  EXPECT_TRUE(atomic("car"));
  EXPECT_TRUE(atomic("cdr"));
  EXPECT_TRUE(atomic("cons"));
  EXPECT_FALSE(atomic("NIL"));
  EXPECT_FALSE(atomic("T"));
  EXPECT_FALSE(atomic("X"));
  EXPECT_FALSE(atomic(""));
}

int main(int argc, char **argv) {
  // ::testing::GTEST_FLAG(filter) = "*Stack*";//":-:*Counter*";
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
