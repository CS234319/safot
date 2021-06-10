#include <iostream>
#include "gtest/gtest.h"
#include "test.h"

// Mark here every exceptions that was tested; 
// Add test that all exceptions were checked.
// Add tests that error strings are meaningful; consult with Yossi on how

/**
 * Tests of mini-lisp basics; should be renamed one day
 */
S t("t");
S n("NIL");
S a0("");
S a1("T");
S a2("NIL");
S a3("FOO BAR");
S s1(t,n);
S s2(s1,s1);
S s3(s2,s1);

TEST(Atomic, cons) {
  EXPECT_TRUE(a3.cons(s2).car().eq(a3));
  EXPECT_TRUE(s3.cons(a2).cdr().eq(a2));
}

TEST(Atomic, snoc) {
  EXPECT_TRUE(a3.snoc(s2).cdr().eq(a3));
  EXPECT_TRUE(s3.snoc(a2).car().eq(a2));
}

TEST(Atomic,Handles) {
  EXPECT_EQ(S::NIL.handle,0);
  EXPECT_EQ(S::NIL.handle,n.handle);
  EXPECT_EQ(S::T.handle,-2);
  EXPECT_EQ(t.handle, -2);
  EXPECT_EQ(a0.handle, -1);
  EXPECT_LE(S("IL").handle, 0);
  EXPECT_LE(S("L").handle, 0);
  EXPECT_LE(S("").handle, 0);
}

TEST(Atomic,Throw) {
  EXPECT_EXCEPTION(throw S::CDR.cons(S::CAR).asPair(), S::CDR, S::CAR);
}

TEST(Atomic,Error) {
  EXPECT_EXCEPTION(S::NDEFUN.error(S::LAMBDA), S::NDEFUN, S::LAMBDA);
}

TEST(Atomic,EQ) {
  EXPECT_FALSE(a0.eq(S::T));
  EXPECT_FALSE(a0.eq(S::NIL));
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

TEST(Atomic,NE) {
  EXPECT_TRUE(a0.ne(S::T));
  EXPECT_TRUE(a0.ne(S::NIL));
  EXPECT_TRUE(S::NIL.ne(S::T));
  EXPECT_TRUE(S::T.ne(S::NIL));
  EXPECT_FALSE(S("aBC").ne(S("AbC")));
  EXPECT_FALSE(S("ABC").ne(S("ABC")));
  EXPECT_FALSE(S("nIl").ne(S::NIL));
  EXPECT_FALSE(S("NIL").ne(S("nil")));
  EXPECT_FALSE(S::NIL.ne(S("nil")));
  EXPECT_FALSE(S::NIL.ne(S("NIL")));
  EXPECT_FALSE(S::NIL.ne(S::NIL));
  EXPECT_FALSE(S::T.ne(S::T));
  EXPECT_FALSE(S::T.ne("T"));
  EXPECT_FALSE(S::T.ne(S("T")));
}

TEST(Atomic,car) {
  EXPECT_EQ(s1.car(), t);
  EXPECT_EQ(s2.car(), s1);
  EXPECT_EQ(s3.car(), s2);
  EXPECT_EXCEPTION(a0.car() , a0,S::CAR);
  EXPECT_EXCEPTION(a1.car() , a1,S::CAR);
  EXPECT_EXCEPTION(a2.car(),a2,S::CAR);
  EXPECT_EXCEPTION(a3.car(),a3,S::CAR);
}

TEST(Atomic,cdr) {
  EXPECT_EQ(s1.cdr(), n);
  EXPECT_EQ(s2.cdr(), s1);
  EXPECT_EQ(s3.cdr(), s1);
  EXPECT_EXCEPTION(a0.cdr(),a0,S::CDR);
  EXPECT_EXCEPTION(a1.cdr(),a1,S::CDR);
  EXPECT_EXCEPTION(a2.cdr(),a2,S::CDR);
  EXPECT_EXCEPTION(a3.cdr(),a3,S::CDR);
}

TEST(Atomic,atom) {
  EXPECT_TRUE(a0.atom());
  EXPECT_TRUE(a1.atom());
  EXPECT_TRUE(a2.atom());
  EXPECT_TRUE(a3.atom());
  EXPECT_FALSE(s1.atom());
  EXPECT_FALSE(s2.atom());
  EXPECT_FALSE(s3.atom());
}

TEST(Atomic, t) {
  EXPECT_TRUE(a0.t());
  EXPECT_TRUE(a1.t());
  EXPECT_FALSE(a2.t());
  EXPECT_TRUE(a3.t());
  EXPECT_TRUE(s1.t());
  EXPECT_TRUE(s2.t());
  EXPECT_TRUE(s3.t());
}

TEST(Atomic, null) {
  EXPECT_FALSE(t.null());
  EXPECT_TRUE(n.null());
  EXPECT_FALSE(a0.null());
  EXPECT_FALSE(a1.null());
  EXPECT_TRUE(a2.null());
  EXPECT_FALSE(a3.null());
  EXPECT_FALSE(s1.null());
  EXPECT_FALSE(s2.null());
  EXPECT_FALSE(s3.null());
}


TEST(Atomic, EvalLiterals) {
  CAREFULLY(EXPECT_EQ(t.eval(),t));
  CAREFULLY(EXPECT_EQ(n.eval(),n));
}

TEST(Atomic, EvalUndefined0) {
  EXPECT_EXCEPTION(S("foo bar").eval(),S("foo bar"),S::UNDEFINED);
}

TEST(Atomic, EvalUndefined) {
  EXPECT_EXCEPTION(S(UNIQUE).eval()  ,S(UNIQUE),S::UNDEFINED);
}

TEST(Atomic, EvalNil) {
  CAREFULLY(EXPECT_EQ(S::NIL.eval(), S::NIL));
}

TEST(Atomic, EvalT) {
  CAREFULLY(EXPECT_EQ(S::T.eval(), S::T));
}

TEST(Atomic, EvalAtom) {
  S q = list("atom", "nil"); 
  S s = q.eval();
  CAREFULLY(EXPECT_EQ(s, S::T)); 
}

TEST(Atomic, EvalCDR) {
  S i = S::CDR.cons(S("X").cons("Y").q());
  S o = S("Y");
  CAREFULLY(EXPECT_EQ(i.eval(),o) << i); 
}

TEST(Atomic, EvalCAR) {
  S i = S::CAR.cons(S("X").cons("Y").q());
  S o = S("X");
  CAREFULLY(EXPECT_EQ(i.eval(),o) << i); 
}

TEST(Atomic, EvalCARList) {
  S i =  list(S::CAR, list("A", "B", "C")).q();
  S o = S("A");
  CAREFULLY(EXPECT_EQ(i.eval(),o) << i); 
}

