#include <iostream>
#include "gtest/gtest.h"
#include "test.h"

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

TEST(Fluenton,n0) {
    EXPECT_TRUE(list().n0());
    EXPECT_FALSE(list(T).n0());
    EXPECT_FALSE(list(T, NIL).n0());
    EXPECT_FALSE(list(T, NIL, T).n0());
    EXPECT_FALSE(list(T, NIL, T, NIL).n0());
}

TEST(Fluenton,n1) {
    EXPECT_FALSE(list().n1());
    EXPECT_TRUE(list(T).n1());
    EXPECT_FALSE(list(T, NIL).n1());
    EXPECT_FALSE(list(T, NIL, T).n1());
    EXPECT_FALSE(list(T, NIL, T, NIL).n1());
}

TEST(Fluenton,n2) {
    EXPECT_FALSE(list().n2());
    EXPECT_FALSE(list(T).n2());
    EXPECT_TRUE(list(T, NIL).n2());
    EXPECT_FALSE(list(T, NIL, T).n2());
    EXPECT_FALSE(list(T, NIL, T, NIL).n2());
}

TEST(Fluenton,n3) {
    EXPECT_FALSE(list().n3());
    EXPECT_FALSE(list(T).n3());
    EXPECT_FALSE(list(T, NIL).n3());
    EXPECT_TRUE(list(T, NIL, T).n3());
    EXPECT_FALSE(list(T, NIL, T, NIL).n3());
}

TEST(Fluentons, more) {
    EXPECT_FALSE(list().more0());
    EXPECT_TRUE(list(T).more0());
    EXPECT_TRUE(list(T, NIL).more0());
    EXPECT_TRUE(list(T, NIL, T).more0());
    EXPECT_TRUE(list(T, NIL, T, NIL).more0());

    EXPECT_FALSE(list().more1());
    EXPECT_FALSE(list(T).more1());
    EXPECT_TRUE(list(T, NIL).more1());
    EXPECT_TRUE(list(T, NIL, T).more1());
    EXPECT_TRUE(list(T, NIL, T, NIL).more1());

    EXPECT_FALSE(list().more2());
    EXPECT_FALSE(list(T).more2());
    EXPECT_FALSE(list(T, NIL).more2());
    EXPECT_TRUE(list(T, NIL, T).more2());
    EXPECT_TRUE(list(T, NIL, T, NIL).more2());

    EXPECT_FALSE(list().more3());
    EXPECT_FALSE(list(T).more3());
    EXPECT_FALSE(list(T, NIL).more3());
    EXPECT_FALSE(list(T, NIL, T).more3());
    EXPECT_TRUE(list(T, NIL, T, NIL).more3());
}

TEST(Fluenton,less) {
    EXPECT_FALSE(list().less0());
    EXPECT_FALSE(list(T).less0());
    EXPECT_FALSE(list(T, NIL).less0());
    EXPECT_FALSE(list(T, NIL, T).less0());
    EXPECT_FALSE(list(T, NIL, T, NIL).less0());

    EXPECT_TRUE(list().less1());
    EXPECT_FALSE(list(T).less1());
    EXPECT_FALSE(list(T, NIL).less1());
    EXPECT_FALSE(list(T, NIL, T).less1());
    EXPECT_FALSE(list(T, NIL, T, NIL).less1());

    EXPECT_TRUE(list().less2());
    EXPECT_TRUE(list(T).less2());
    EXPECT_FALSE(list(T, NIL).less2());
    EXPECT_FALSE(list(T, NIL, T).less2());
    EXPECT_FALSE(list(T, NIL, T, NIL).less2());

    EXPECT_TRUE(list().less3());
    EXPECT_TRUE(list(T).less3());
    EXPECT_TRUE(list(T, NIL).less3());
    EXPECT_FALSE(list(T, NIL, T).less3());
    EXPECT_FALSE(list(T, NIL, T, NIL).less3());
}

TEST(Fluenton, EvalQuote) {
  S i =  list("A", "B", "C").q();
  CAREFULLY_EXPECT(EQ,i.eval().cdr().car(),"B", << i); 
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

TEST(Fluenton, l) {
  EXPECT_EQ(a3.l().car(), a3);
  EXPECT_EQ(s2.l().cdr(), NIL);
}

TEST(Fluenton, rac) {
    // Sanity check:
    EXPECT_FALSE(islist(list(T).rac()));
    EXPECT_FALSE(islist(list(T, NIL, ATOM, CAR).rac()));

    // Data check:
    EXPECT_TRUE(list(T).rac().eq(T));
    EXPECT_TRUE(list(T, NIL).rac().eq(NIL));
    EXPECT_TRUE(list(T, NIL, ATOM).rac().eq(ATOM));
    EXPECT_TRUE(list(T, NIL, ATOM, CAR).rac().eq(CAR));
}

TEST(Fluenton, rdc) {
    // Sanity check:
    EXPECT_TRUE(islist(list(T).rdc()));
    EXPECT_TRUE(islist(list(T, NIL, ATOM, CAR).rdc()));

    // Check sizes:
    EXPECT_TRUE(list(T, NIL).rdc().n1());
    EXPECT_TRUE(list(T, NIL, ATOM).rdc().n2());
    EXPECT_TRUE(list(T, NIL, ATOM, CAR).rdc().n3());

    // Check data:
    EXPECT_TRUE(list(T, NIL).rdc().rac().eq(T));
    EXPECT_TRUE(list(T, NIL, ATOM).rdc().rac().eq(NIL));
    EXPECT_TRUE(list(T, NIL, ATOM, CAR).rdc().rac().eq(ATOM));
}

TEST(Fluenton, snoc) {
  EXPECT_TRUE(a3.snoc(s2).cdr().eq(a3));
  EXPECT_TRUE(s3.snoc(a2).car().eq(a2));
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

TEST(FluentWhichIsAtomic,cons) {
  EXPECT_TRUE(a3.cons(s2).car().eq(a3));
  EXPECT_TRUE(s3.cons(a2).cdr().eq(a2));
}


TEST(FluentWhichIsAtomic,Throw) {
  EXPECT_EXCEPTION(throw a3.cons(a4).p(), a3, a4);
}

TEST(FluentWhichIsAtomic,Error) {
  EXPECT_EXCEPTION(a4.error(a3), a4, a3);
}


TEST(FluentWhichIsAtomic,EQ) {
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

TEST(FluentWhichIsAtomic,car) {
  EXPECT_EQ(s1.car(), t);
  EXPECT_EQ(s2.car(), s1);
  EXPECT_EQ(s3.car(), s2);
  EXPECT_EXCEPTION(a0.car() , a0,CAR);
  EXPECT_EXCEPTION(a1.car() , a1,CAR);
  EXPECT_EXCEPTION(a2.car(),a2,CAR);
  EXPECT_EXCEPTION(a3.car(),a3,CAR);
}

TEST(FluentWhichIsAtomic,cdr) {
  EXPECT_EQ(s1.cdr(), n);
  EXPECT_EQ(s2.cdr(), s1);
  EXPECT_EQ(s3.cdr(), s1);
  EXPECT_EXCEPTION(a0.cdr(),a0,CDR);
  EXPECT_EXCEPTION(a1.cdr(),a1,CDR);
  EXPECT_EXCEPTION(a2.cdr(),a2,CDR);
  EXPECT_EXCEPTION(a3.cdr(),a3,CDR);
}

TEST(FluentWhichIsAtomic,atom) {
  EXPECT_TRUE(a0.atom());
  EXPECT_TRUE(a1.atom());
  EXPECT_TRUE(a2.atom());
  EXPECT_TRUE(a3.atom());
  EXPECT_FALSE(s1.atom());
  EXPECT_FALSE(s2.atom());
  EXPECT_FALSE(s3.atom());
}

TEST(FluentWhichIsAtomic,null) {
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


TEST(FluentWhichIsAtomic,EvalLiterals) {
  CAREFULLY(EXPECT_EQ(t.eval(),t));
  CAREFULLY(EXPECT_EQ(n.eval(),n));
}

TEST(FluentWhichIsAtomic,EvalUndefined0) {
  EXPECT_EXCEPTION(S("foo bar").eval(),S("foo bar"),UNDEFINED);
}

TEST(FluentWhichIsAtomic,EvalUndefined) {
  EXPECT_EXCEPTION(S(UNIQUE).eval()  ,S(UNIQUE),UNDEFINED);
}

TEST(FluentWhichIsAtomic,EvalSanityT) {
  EXPECT_EXCEPTION(list(T, T).eval(), list(T,T), INVALID);
}

TEST(FluentWhichIsAtomic,EvalSanity1) {
  EXPECT_EXCEPTION(list(NIL).eval(), list(NIL), INVALID);
  EXPECT_EXCEPTION(list(NIL, NIL).eval(), list(NIL, NIL), INVALID);
  EXPECT_EXCEPTION(list(NIL, list(NIL, NIL)).eval(), 
                   list(NIL, list(NIL, NIL)), INVALID);
}

TEST(FluentWhichIsAtomic,EvalSanity2) {
  EXPECT_EXCEPTION(list(NIL, NIL).eval(), list(NIL, NIL), INVALID);
}

TEST(FluentWhichIsAtomic,EvalNil) {
  CAREFULLY_EXPECT(EQ,NIL.eval(), NIL);
  EXPECT_EXCEPTION(list(NIL, T).eval(),list(NIL, T),INVALID);
}

TEST(FluentWhichIsAtomic,EvalT) {
  CAREFULLY_EXPECT(EQ,T.eval(), T);
  EXPECT_EXCEPTION(list(T, NIL).eval(),list(T, NIL), INVALID);
}

TEST(FluentWhichIsAtomic,EvalNullTrue) {
  EXPECT_T(list(NULL, NIL).eval());
  EXPECT_T(list(NULL, list()).eval());
}

TEST(FluentWhichIsAtomic,EvalNullFalseQuote) {
  CAREFULLY_EXPECT_NIL(list(NULL, a3.q()).eval());
} 

TEST(FluentWhichIsAtomic,EvalNullMore) {
  EXPECT_EXCEPTION(list(NULL, list(T, T)).eval(), list(T,T), INVALID);
  CAREFULLY_EXPECT_T(list(NULL, NIL).eval());
}

TEST(FluentWhichIsAtomic,EvalAndQuote) {
  EXPECT_EQ(list(EVAL, list(QUOTE, T)).eval(), T);
}

TEST(FluentWhichIsAtomic,EvaluatingQuote) {
  EXPECT_EQ(list(QUOTE, s3).eval(), s3);
}

TEST(FluentWhichIsAtomic,EvalAtomNil) {
  CAREFULLY_EXPECT(EQ,list("atom", "nil").eval(), T); 
  CAREFULLY_EXPECT(EQ,list(ATOM,NIL).eval(), T); 
}

TEST(FluentWhichIsAtomic,EvalAtomT) {
  CAREFULLY_EXPECT(EQ,list("atom", "T").eval(), T, ); 
  CAREFULLY_EXPECT(EQ, list(ATOM,T).eval(), T, ); 
}

TEST(FluentWhichIsAtomic,EvalAtomS) {
  CAREFULLY_EXPECT(EQ, list(ATOM,a0.q()).eval(), T); 
  CAREFULLY_EXPECT(EQ, list(ATOM,a1.q()).eval(), T); 
  CAREFULLY_EXPECT(EQ, list(ATOM,a2.q()).eval(), T); 
  CAREFULLY_EXPECT(EQ, list(ATOM,a3.q()).eval(), T); 
  CAREFULLY_EXPECT(EQ, list(ATOM,s1.q()).eval(), NIL); 
  CAREFULLY_EXPECT(EQ, list(ATOM,s2.q()).eval(), NIL); 
  CAREFULLY_EXPECT(EQ, list(ATOM,s3.q()).eval(), NIL); 
}

TEST(FluentWhichIsAtomic,EvalAtomNasty) {
  CAREFULLY_EXPECT(EQ, list(ATOM,s3.q()).eval(), NIL); 
}


TEST(FluentWhichIsAtomic,EvalCDR) {
  S i = list(CDR, list(QUOTE, S("X").cons(S("Y"))));
  S o = S("Y");
  CAREFULLY(EXPECT_EQ(i.eval(),o) << i); 
}

TEST(FluentWhichIsAtomic,EvalCDRList) {
  S i = list(CDR, list("A", "B", "C").q());
  CAREFULLY(EXPECT_EQ(i.eval(),list("B", "C")) << i); 
}


TEST(FluentWhichIsAtomic,EvalCAR) {
  S i = list(CAR, list(QUOTE, S("X").cons(S("Y"))));
  S o = S("X");
  CAREFULLY_EXPECT(EQ,i.eval(),o, << i); 
}

TEST(FluentWhichIsAtomic,EvalCAR_EXTRA) {
  S i = list(CAR, list(QUOTE, S("X").cons(S("Y"))), NIL);
  EXPECT_EXCEPTION(i.eval() , i,REDUNDANT);
}

TEST(FluentWhichIsAtomic,EvalCAR_MISSING) {
  S i = CAR.l(); 
  EXPECT_EQ(i, list(CAR));
  EXPECT_EXCEPTION(i.eval(), i, MISSING);
}

TEST(FluentWhichIsAtomic,EvalAtom_EXTRA) {
  S i = list(ATOM, list(QUOTE, S("X").cons(S("Y"))), NIL);
  EXPECT_EXCEPTION(i.eval() , i,REDUNDANT);
}

TEST(FluentWhichIsAtomic,EvalAtom_MISSING) {
  S i = ATOM.l(); 
  EXPECT_EXCEPTION(i.eval() , i,MISSING);
}

TEST(FluentWhichIsAtomic,EvalCAR_Missing) {
  S i = list(CAR, list(QUOTE, S("X").cons(S("Y"))));
  S o = S("X");
  CAREFULLY_EXPECT(EQ,i.eval(),o, << i); 
}

TEST(FluentWhichIsAtomic,EvalCARList) {
  S i =  list(CAR, list("A", "B", "C").q());
  S o = S("A");
  CAREFULLY(EXPECT_EQ(i.eval(),o) << i); 
}
