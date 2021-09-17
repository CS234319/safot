#import  <iostream>
#import  "gtest/gtest.h"
#import  "test.h"
#import  "a-list.h"
#import  "eval.h"


S nothing(S s) { return s; }
/**
 * Tests of all types of error in Mini-Lisp
 *
 * CarOfAtom         e.g:  S("(car 'a')").eval()
 * CarOfNil          e.g:  S("(car ())").eval()
 * CdrOfAtom         e.g:  S("(cdr t)").eval()
 * CdrOfNil          e.g:  S("(cdr ())").eval()
 * UnboundVariable   e.g:  S("(eval 'a)").eval()
 * MissingNames      e.g:  bind(S("('a 'b)"), S("('x 'y 'z)")
 * MissingValues     e.g:  bind(S("('a 'b 'c)"), S("('x 'y)")
 * UnknownLambda     e.g:  S("(f 'a)").eval()
 * OtherError        e.g:  S("(error 'a)").eval()
 *
 */
namespace Engine {
  namespace Inner {
      extern S align(S s1, S s2, S e1, S e2);
      extern S check(S l, S e);
  }
}
using Engine::Inner::check;
using Engine::Inner::align;
static inline auto align(S s1, S s2) { return align(s1, s2, MISSING_ARGUMENT, REDUNDANT_ARGUMENT); }

static S t("t");
static S n("NIL");
static S id("id");
static S a1("T");
static S a2("NIL");
static S a3("FOO BAR");
static S a4("BAR");
static S s1(t,n);
static S s2(s1,s1);
static S s3(s2,s1);

using Engine::apply, Engine::push; 

TEST(Except, UNDEFINED_ATOM) {
  reset();
    S x("x");
    EXPECT_EXCEPTION(list(CONS, x).eval(), x, UNDEFINED_ATOM);
}

TEST(Except, REDUNDANT_ARGUMENT) {
    S x("x");
    S y("y");
    S z("z");
    EXPECT_EXCEPTION(list(CONS, x.q(), y.q(), z.q()).eval(), list(z.q()), REDUNDANT_ARGUMENT);
}

TEST(Except, CarOfAtom) {
    EXPECT_EXCEPTION(ATOM.car(), ATOM, CAR)
    EXPECT_EXCEPTION(a4.car(), a4, CAR)
}

TEST(Except, CarOfNil) {
    EXPECT_EXCEPTION(list().car(), n, CAR)
    EXPECT_EXCEPTION(n.car(), n, CAR)
}

TEST(Except, CdrOfAtom) {
    EXPECT_EXCEPTION(ATOM.cdr(), ATOM, CDR)
    EXPECT_EXCEPTION(a4.cdr(), a4, CDR)
}

TEST(Except, CdrOfNil) {
    EXPECT_EXCEPTION(list().cdr(), n, CDR)
    EXPECT_EXCEPTION(n.cdr(), n, CDR)
}

TEST(Except, BAD_FUNCTION1) {
  S f("my function"), x("x"), y("y"), z("z");
  push(f, list(LAMBDA)); 
  EXPECT_EXCEPTION(list(f, x, y).eval(), f, BAD_FUNCTION);
}

TEST(Except, BAD_FUNCTION2) {
  S f("my function"), x("x"), y("y"), z("z");
  push(f, list()); 
  EXPECT_EXCEPTION(list(f, x, y).eval(), f, BAD_FUNCTION);
}

TEST(Except, BAD_FUNCTION3) {
  S f("my function"), x("x"), y("y"), z("z");
  push(f, list(LAMBDA,x)); 
  EXPECT_EXCEPTION(list(f, x, y).eval(), f, BAD_FUNCTION);
}

TEST(Except, BAD_FUNCTION4) {
  S f("my function"), x("x"), y("y"), z("z");
  push(f, list(LAMBDA,x,y,z)); 
  EXPECT_EXCEPTION(list(f, x, y).eval(), f, BAD_FUNCTION);
}

TEST(Except, BadFunction3) {
    EXPECT_EXCEPTION(apply(NIL.eval(), S("e")), NIL, BAD_FUNCTION)
}

TEST(Error, Align1) {
    EXPECT_EXCEPTION(align(id, list()), id, MISSING_ARGUMENT)
}

TEST(Error, Align2) {
    EXPECT_EXCEPTION(align(list(), id), id, REDUNDANT_ARGUMENT)
}


TEST(Error, Align3) {
  EXPECT_EXCEPTION(align(list(id,id,id), list(id, id, t, n)), list(n), REDUNDANT_ARGUMENT)
}

TEST(Error, Align4) {
  EXPECT_EXCEPTION(align(list(id,a1), list(id)), list(a1), MISSING_ARGUMENT)
}

TEST(Error, MissingFunction) {
    EXPECT_EXCEPTION(apply(S("e"), t), S("e"), UNDEFINED_ATOM)
}

TEST(Error, OtherError) {
    EXPECT_EXCEPTION(t.error(S("OTHER")), t, S("OTHER"))
}

TEST(Error, InternalCheck1) {
    EXPECT_EXCEPTION(check(id, BAD_ARGUMENTS), id, BAD_ARGUMENTS)
}

TEST(Error, InternalCheck2) {
    EXPECT_EXCEPTION(check(id.cons(a3), BAD_ARGUMENTS), a3, BAD_ARGUMENTS)
}
