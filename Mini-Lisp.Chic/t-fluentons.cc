#include <iostream>
#include "gtest/gtest.h"
#include "test.h"

static S t("t");
static S n("nil");
static S a0("");
static S a1("T");
static S a2("NIL");
static S a3("FOO BAR");
static S a4("BAR");
static S s1(t,n);
static S s2(s1,s1);
static S s3(s2,s1);

TEST(Fluenton, Quote) {
  CAREFULLY_EXPECT(EQ,S("A").l().q().eval().car(),"A"); 
}

TEST(Fluenton,n0) {
    EXPECT_TRUE(list().n0());
    EXPECT_FALSE(list(t).n0());
    EXPECT_FALSE(list(t, NIL).n0());
    EXPECT_FALSE(list(t, NIL, t).n0());
    EXPECT_FALSE(list(t, NIL, t, NIL).n0());
}

TEST(Fluenton,n1) {
    EXPECT_FALSE(list().n1());
    EXPECT_TRUE(list(t).n1());
    EXPECT_FALSE(list(t, NIL).n1());
    EXPECT_FALSE(list(t, NIL, t).n1());
    EXPECT_FALSE(list(t, NIL, t, NIL).n1());
}

TEST(Fluenton,n2) {
    EXPECT_FALSE(list().n2());
    EXPECT_FALSE(list(t).n2());
    EXPECT_TRUE(list(t, NIL).n2());
    EXPECT_FALSE(list(t, NIL, t).n2());
    EXPECT_FALSE(list(t, NIL, t, NIL).n2());
}

TEST(Fluenton,n3) {
    EXPECT_FALSE(list().n3());
    EXPECT_FALSE(list(t).n3());
    EXPECT_FALSE(list(t, NIL).n3());
    EXPECT_TRUE(list(t, NIL, t).n3());
    EXPECT_FALSE(list(t, NIL, t, NIL).n3());
}

TEST(Fluenton, more) {
    EXPECT_FALSE(list().more0());
    EXPECT_TRUE(list(t).more0());
    EXPECT_TRUE(list(t, NIL).more0());
    EXPECT_TRUE(list(t, NIL, t).more0());
    EXPECT_TRUE(list(t, NIL, t, NIL).more0());

    EXPECT_FALSE(list().more1());
    EXPECT_FALSE(list(t).more1());
    EXPECT_TRUE(list(t, NIL).more1());
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

TEST(Fluenton, T) {
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

TEST(Native,cons) {
  EXPECT_TRUE(a3.cons(s2).car().eq(a3));
  EXPECT_TRUE(s3.cons(a2).cdr().eq(a2));
}

TEST(Native,Throw) {
  EXPECT_EXCEPTION(throw a3.cons(a4).p(), a3, a4);
}


/*
    (error) ⇒ ✗
    (error 'A) ⇒ ✗
    (error 'message) ⇒ ✗
*/

TEST(Native, Error) {
  EXPECT_EXCEPTION(a4.error(a3), a4, a3);
}

TEST(Native, Error0) {
    EXPECT_EXCEPTION(parse("(error)").eval(), NIL, ERROR);
}

TEST(Native, ErrorC) {
    EXPECT_EXCEPTION(parse("error.a").eval(), S("a"), BAD_ARGUMENTS);
}

TEST(Native, Error1) {
    EXPECT_EXCEPTION(parse("(error 'A)").eval(), S("a"), BAD_ARGUMENTS);
}

TEST(Native, Error2) {
    EXPECT_EXCEPTION(parse("error.'A.'B").eval(), S("a") ,S("B"));
}

TEST(Native, Error3) {
    EXPECT_EXCEPTION(parse("(error A B C)").eval(), parse("(B C)"), S("A"));
}

TEST(Native,EQ) {
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
  EXPECT_FALSE(T.eq(list(a0,a1)));
  EXPECT_FALSE(list(a0,a1).eq(list(a0,a1)));
}

TEST(Native,car) {
  EXPECT_EQ(s1.car(), T);
  EXPECT_EQ(s2.car(), s1);
  EXPECT_EQ(s3.car(), s2);
  EXPECT_EXCEPTION(a0.car() , a0,CAR);
  EXPECT_EXCEPTION(a1.car() , a1,CAR);
  EXPECT_EXCEPTION(a2.car(),a2,CAR);
  EXPECT_EXCEPTION(a3.car(),a3,CAR);
}

TEST(Native, cdr) {
  EXPECT_EQ(s1.cdr(), n);
  EXPECT_EQ(s2.cdr(), s1);
  EXPECT_EQ(s3.cdr(), s1);
  EXPECT_EXCEPTION(a0.cdr(),a0,CDR);
  EXPECT_EXCEPTION(a1.cdr(),a1,CDR);
  EXPECT_EXCEPTION(a2.cdr(),a2,CDR);
  EXPECT_EXCEPTION(a3.cdr(),a3,CDR);
}

TEST(Native,atom) {
  EXPECT_TRUE(a0.atom());
  EXPECT_TRUE(a1.atom());
  EXPECT_TRUE(a2.atom());
  EXPECT_TRUE(a3.atom());
  EXPECT_FALSE(s1.atom());
  EXPECT_FALSE(s2.atom());
  EXPECT_FALSE(s3.atom());
}

TEST(Native,null) {
  EXPECT_FALSE(T.null());
  EXPECT_TRUE(n.null());
  EXPECT_FALSE(a0.null());
  EXPECT_FALSE(a1.null());
  EXPECT_TRUE(a2.null());
  EXPECT_FALSE(a3.null());
  EXPECT_FALSE(s1.null());
  EXPECT_FALSE(s2.null());
  EXPECT_FALSE(s3.null());
}

TEST(Eval,LiteralT) {
  CAREFULLY(EXPECT_EQ(T.eval(),T));
}

TEST(Eval,LiteralN) {
  CAREFULLY(EXPECT_EQ(NIL.eval(),NIL));
}

TEST(Eval,Literal_n) {
  CAREFULLY(EXPECT_EQ(n.eval(),NIL));
}

TEST(Native, Literals) {
  CAREFULLY(EXPECT_EQ(T.eval(),T));
  CAREFULLY(EXPECT_EQ(n.eval(),n));
}

TEST(Native, Undefined0) {
  EXPECT_EXCEPTION(S("foo bar").eval(),S("foo bar"),UNDEFINED_ATOM);
}

TEST(Apply, MissingVariable) {
  EXPECT_EXCEPTION(S(UNIQUE).eval()  ,S(UNIQUE),UNDEFINED_ATOM);
}

TEST(Apply, MissingFunction0) {
  EXPECT_EXCEPTION(list(UNIQUE).eval()  ,S(UNIQUE),UNDEFINED_ATOM);
}

TEST(Apply, MissingFunction1) {
  EXPECT_EXCEPTION(list(UNIQUE, T).eval()  ,S(UNIQUE),UNDEFINED_ATOM);
}

TEST(Apply, MissingFunction2) {
  EXPECT_EXCEPTION(list(UNIQUE, T, T).eval()  ,S(UNIQUE),UNDEFINED_ATOM);
}

TEST(Apply, BadFunction) {
  EXPECT_EXCEPTION(list(T, T).eval(), T, BAD_FUNCTION);
}

TEST(Apply, Sanity1) {
  EXPECT_EXCEPTION(list(NIL).eval(), NIL, BAD_FUNCTION);
}

TEST(Apply, Sanity2) {
  EXPECT_EXCEPTION(list(NIL, NIL).eval(), NIL, BAD_FUNCTION);
}

TEST(Apply, Sanity3) {
  EXPECT_EXCEPTION(list(NIL, list(NIL, NIL)).eval(), NIL, BAD_FUNCTION);
}

TEST(Apply, Sanity4) {
  EXPECT_EXCEPTION(list(NIL, NIL).eval(), NIL, BAD_FUNCTION);
}

TEST(Native, Nil) {
  CAREFULLY_EXPECT(EQ,NIL.eval(), NIL);
}

TEST(Native, T) {
  CAREFULLY_EXPECT(EQ,T.eval(), T);
}

TEST(Native, Null1) {
  EXPECT_T(list(NULL, NIL).eval());
}

TEST(Native, Null2) {
  EXPECT_T(list(NULL, list()).eval());
}

TEST(Native, Null3) {
  CAREFULLY_EXPECT_T(list(NULL, list(QUOTE, NIL)).eval());
}

TEST(Native, Null4) {
  S x = list(CONS,T,list(QUOTE, NIL));
  CAREFULLY_EXPECT_NIL(list(NULL, x).eval(), << x << x.eval() << x.eval().null());
}

TEST(Native, Null5) {
  CAREFULLY_EXPECT_NIL(list(NULL, T).eval());
}

TEST(Native, Null6) {
  CAREFULLY_EXPECT_NIL(list(NULL, a3.q()).eval());
} 

TEST(Native, Null7) {
  CAREFULLY_EXPECT_T(list(NULL, NIL).eval());
}

TEST(Native, Null8) {
  EXPECT_EXCEPTION(list(NULL, list(T, T)).eval(), T, BAD_FUNCTION);
}


TEST(Native, Quote0) {
  EXPECT_EQ(list(EVAL, list(QUOTE, T)).eval(), T);
}

TEST(Native, Quote1) {
  EXPECT_EQ(list(QUOTE, s3).eval(), s3);
}

TEST(Native, Atom0) {
  CAREFULLY_EXPECT(EQ,list("atom", "nil").eval(), T); 
}

TEST(Native, Atom1) {
  CAREFULLY_EXPECT(EQ,list(ATOM,NIL).eval(), T); 
}

TEST(Native, Atom2) {
  CAREFULLY_EXPECT(EQ,list("atom", "T").eval(), T, ); 
  CAREFULLY_EXPECT(EQ, list(ATOM,T).eval(), T, ); 
}

TEST(Native, Atom3) {
  CAREFULLY_EXPECT(EQ, list(ATOM,a2.q()).eval(), T); 
}

TEST(Native, Atom4) {
  CAREFULLY_EXPECT(EQ, list(ATOM,a0.q()).eval(), T); 
  CAREFULLY_EXPECT(EQ, list(ATOM,a1.q()).eval(), T); 
  CAREFULLY_EXPECT(EQ, list(ATOM,a2.q()).eval(), T); 
  CAREFULLY_EXPECT(EQ, list(ATOM,a3.q()).eval(), T); 
  CAREFULLY_EXPECT(EQ, list(ATOM,s1.q()).eval(), NIL); 
  CAREFULLY_EXPECT(EQ, list(ATOM,s2.q()).eval(), NIL); 
  CAREFULLY_EXPECT(EQ, list(ATOM,s3.q()).eval(), NIL); 
}

TEST(Native, Atom5) {
  CAREFULLY_EXPECT(EQ, list(ATOM,s3.q()).eval(), NIL); 
}

TEST(Native, Atom6) {
  S i = list(ATOM, list(QUOTE, pair("X","Y")), NDEFUN);
  EXPECT_EXCEPTION(i.eval() , list(NDEFUN),REDUNDANT_ARGUMENT);
}

TEST(Native, Atom7) {
  EXPECT_EXCEPTION(ATOM.l().eval() , __00,MISSING_ARGUMENT);
}

TEST(Native, Cdr1) {
  S i = list(CDR, list(QUOTE, S("X").cons(S("Y"))));
  S o = S("Y");
  CAREFULLY(EXPECT_EQ(i.eval(),o) << i); 
}

TEST(Native, Cdr2) {
  S i = list(CDR, list("A", "B", "C").q());
  CAREFULLY(EXPECT_EQ(i.eval(),list("B", "C")) << i); 
}

TEST(Native, Cdr3) {
  EXPECT_EXCEPTION(list(CDR, T, T).eval() , list(T), REDUNDANT_ARGUMENT);
}

TEST(Native, Cdr4) {
  EXPECT_EXCEPTION(list(CDR).eval() , list(__0), MISSING_ARGUMENT);
}

TEST(Native, Cdr5) {
  EXPECT_EXCEPTION(list(CDR,T).eval() , T, CDR);
}

TEST(Native, Car1) {
  S i = list(CAR, list(QUOTE, S("X").cons(S("Y"))));
  S o = S("X");
  CAREFULLY_EXPECT(EQ,i.eval(),o, << i); 
}

TEST(Native, Car2) {
  EXPECT_EXCEPTION(list(CAR, S("A"), S("B")).eval() , S("A"), UNDEFINED_ATOM);
}

TEST(Native, Car3) {
  EXPECT_EXCEPTION(parse("(car 'a 'b c)").eval(), S("c"), UNDEFINED_ATOM);
}

TEST(Native, Car4) {
  EXPECT_EXCEPTION(parse("(car 'a 'b 'c d)").eval(), S("d"), UNDEFINED_ATOM);
}

TEST(Native, Car5) {
  EXPECT_EXCEPTION(list(CAR).eval() , __00, MISSING_ARGUMENT);
}

TEST(Native, Car6) {
  EXPECT_EXCEPTION(list(CDR,T).eval() , T, CDR);
}

TEST(Native, Car7) {
  EXPECT_EXCEPTION(list(CAR, T, LAMBDA).eval() , list(LAMBDA), REDUNDANT_ARGUMENT);
}

TEST(Native, Car8) {
  S i = list(CAR, list(QUOTE, S("X").cons(S("Y"))));
  S o = S("X");
  CAREFULLY_EXPECT(EQ,i.eval(),o, << i); 
}

TEST(Native, Car9) {
  S i = list(CAR, list(QUOTE, S("X").cons(S("Y"))), CDR);
  EXPECT_EXCEPTION(i.eval() , list(CDR), REDUNDANT_ARGUMENT);
}

TEST(Native, Car10) {
  S i = CAR.l(); 
  EXPECT_EQ(i, list(CAR));
  EXPECT_EXCEPTION(i.eval(), __00, MISSING_ARGUMENT);
}

TEST(Native, Car11) {
  S i = list(CAR, list(QUOTE, S("X").cons(S("Y"))));
  S o = S("X");
  CAREFULLY_EXPECT(EQ,i.eval(),o, << i); 
}

TEST(Native, Car12) {
  S i =  list(CAR, list("A", "B", "C").q());
  S o = S("A");
  CAREFULLY(EXPECT_EQ(i.eval(),o) << i); 
}

TEST(Native, Cons0) {
  EXPECT_EXCEPTION(list(CONS).eval() , list(__1,__2), MISSING_ARGUMENT);
}

TEST(Native, Cons1) {
  EXPECT_EXCEPTION(list(CONS,T).eval() , list(__2), MISSING_ARGUMENT);
}

TEST(Native, Cons2) {
  EXPECT_EQ(list(CONS, T, T).eval() , T.cons(T));
}
