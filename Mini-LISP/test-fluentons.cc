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
S a4("BAR");
S s1(t,n);
S s2(s1,s1);
S s3(s2,s1);

TEST(Atomic, cons) {
  EXPECT_TRUE(a3.cons(s2).car().eq(a3));
  EXPECT_TRUE(s3.cons(a2).cdr().eq(a2));
}

TEST(Fluenton, snoc) {
  EXPECT_TRUE(a3.snoc(s2).cdr().eq(a3));
  EXPECT_TRUE(s3.snoc(a2).car().eq(a2));
}

TEST(Implementation,Handles) {
  EXPECT_EQ(NIL.handle,0);
  EXPECT_EQ(NIL.handle,n.handle);
  EXPECT_EQ(T.handle,-2);
  EXPECT_EQ(t.handle, -2);
  EXPECT_EQ(a0.handle, -1);
  EXPECT_LE(S("IL").handle, 0);
  EXPECT_LE(S("L").handle, 0);
  EXPECT_LE(S("").handle, 0);
}

TEST(Atomic,Throw) {
  EXPECT_EXCEPTION(throw a3.cons(a4).p(), a3, a4);
}

TEST(Atomic,Error) {
  EXPECT_EXCEPTION(a4.error(a3), a4, a3);
}

TEST(Atomic,EQ) {
  EXPECT_FALSE(a0.eq(T));
  EXPECT_FALSE(a0.eq(NIL));
  EXPECT_FALSE(NIL.eq(T));
  EXPECT_FALSE(T.eq(NIL));
  EXPECT_TRUE(S("aBC").eq(S("AbC")));
  EXPECT_TRUE(S("ABC").eq(S("ABC")));
  EXPECT_TRUE(S("nIl").eq(NIL));
  EXPECT_TRUE(S("NIL").eq(S("nil")));
  EXPECT_TRUE(NIL.eq(S("nil")));
  EXPECT_TRUE(NIL.eq(S("NIL")));
  EXPECT_TRUE(NIL.eq(NIL));
  EXPECT_TRUE(T.eq(T));
  EXPECT_TRUE(T.eq("T"));
  EXPECT_TRUE(T.eq(S("T")));
}

TEST(Fluenton,NE) {
  EXPECT_TRUE(a0.ne(T));
  EXPECT_TRUE(a0.ne(NIL));
  EXPECT_TRUE(NIL.ne(T));
  EXPECT_TRUE(T.ne(NIL));
  EXPECT_FALSE(S("aBC").ne(S("AbC")));
  EXPECT_FALSE(S("ABC").ne(S("ABC")));
  EXPECT_FALSE(S("nIl").ne(NIL));
  EXPECT_FALSE(S("NIL").ne(S("nil")));
  EXPECT_FALSE(NIL.ne(S("nil")));
  EXPECT_FALSE(NIL.ne(S("NIL")));
  EXPECT_FALSE(NIL.ne(NIL));
  EXPECT_FALSE(T.ne(T));
  EXPECT_FALSE(T.ne("T"));
  EXPECT_FALSE(T.ne(S("T")));
}

TEST(Atomic,car) {
  EXPECT_EQ(s1.car(), t);
  EXPECT_EQ(s2.car(), s1);
  EXPECT_EQ(s3.car(), s2);
  EXPECT_EXCEPTION(a0.car() , a0,CAR);
  EXPECT_EXCEPTION(a1.car() , a1,CAR);
  EXPECT_EXCEPTION(a2.car(),a2,CAR);
  EXPECT_EXCEPTION(a3.car(),a3,CAR);
}

TEST(Atomic,cdr) {
  EXPECT_EQ(s1.cdr(), n);
  EXPECT_EQ(s2.cdr(), s1);
  EXPECT_EQ(s3.cdr(), s1);
  EXPECT_EXCEPTION(a0.cdr(),a0,CDR);
  EXPECT_EXCEPTION(a1.cdr(),a1,CDR);
  EXPECT_EXCEPTION(a2.cdr(),a2,CDR);
  EXPECT_EXCEPTION(a3.cdr(),a3,CDR);
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

TEST(Fluenton, t) {
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
  EXPECT_EXCEPTION(S("foo bar").eval(),S("foo bar"),UNDEFINED);
}

TEST(Atomic, EvalUndefined) {
  EXPECT_EXCEPTION(S(UNIQUE).eval()  ,S(UNIQUE),UNDEFINED);
}

TEST(Atomic, EvalNil) {
  CAREFULLY(EXPECT_EQ(NIL.eval(), NIL));
  CAREFULLY_EXPECT(EQ, NIL.eval(), NIL);
}

TEST(Atomic, EvalT) {
  CAREFULLY(EXPECT_EQ(T.eval(), T));
}

TEST(Atomic, EvalAtomNil) {
  CAREFULLY_EXPECT(EQ,list("atom", "nil").eval(), T); 
  CAREFULLY_EXPECT(EQ,list(ATOM,NIL).eval(), T); 
}

TEST(Atomic, EvalAtomT) {
  CAREFULLY_EXPECT(EQ,list("atom", "T").eval(), T, ); 
  CAREFULLY_EXPECT(EQ, list(ATOM,T).eval(), T, ); 
}

TEST(Atomic, EvalAtomS) {
  CAREFULLY_EXPECT(EQ, list(ATOM,a0).eval(), T); 
  CAREFULLY_EXPECT(EQ, list(ATOM,a1).eval(), T); 
  CAREFULLY_EXPECT(EQ, list(ATOM,a2).eval(), T); 
  CAREFULLY_EXPECT(EQ, list(ATOM,a3).eval(), T); 
  CAREFULLY_EXPECT(EQ, list(ATOM,s1).eval(), NIL); 
  CAREFULLY_EXPECT(EQ, list(ATOM,s2).eval(), NIL); 
  CAREFULLY_EXPECT(EQ, list(ATOM,s3).eval(), NIL); 
}



TEST(Atomic, EvalCDR) {
  S i = CDR.cons(S("X").cons("Y").q());
  S o = S("Y");
  CAREFULLY(EXPECT_EQ(i.eval(),o) << i); 
}

TEST(Atomic, EvalCAR) {
  S i = list(CAR, list(QUOTE, S("X").cons(S("Y"))));
  S o = S("X");
  CAREFULLY_EXPECT(EQ,i.eval(),o, << i); 
}

TEST(Fluenton, EvalQuote) {
  S i =  list("A", "B", "C").q();
  CAREFULLY_EXPECT(EQ,i.eval().cdr().car(),"B", << i); 
}

TEST(Atomic, EvalCARList) {
  S i =  list(CAR, list("A", "B", "C").q());
  S o = S("A");
  CAREFULLY(EXPECT_EQ(i.eval(),o) << i); 
}

