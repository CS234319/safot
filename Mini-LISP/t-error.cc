#include <iostream>
#include "gtest/gtest.h"
#include "test.h"

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


extern S bind(S s1, S s2, S alist);
extern S apply(S f, S args);

TEST(Error, CarOfAtom) {
    EXPECT_EXCEPTION(ATOM.car(), ATOM, CAR)
    EXPECT_EXCEPTION(a4.car(), a4, CAR)
}

TEST(Error, CarOfNil) {
    EXPECT_EXCEPTION(list().car(), n, CAR)
    EXPECT_EXCEPTION(n.car(), n, CAR)
}

TEST(Error, CdrOfAtom) {
    EXPECT_EXCEPTION(ATOM.cdr(), ATOM, CDR)
    EXPECT_EXCEPTION(a4.cdr(), a4, CDR)
}

TEST(Error, CdrOfNil) {
    EXPECT_EXCEPTION(list().cdr(), n, CDR)
    EXPECT_EXCEPTION(n.cdr(), n, CDR)
}

TEST(Error, UnboundVariable) {
    EXPECT_EXCEPTION(apply(S("null"), S("e")), S("null").cons(S("e")), INVALID)
}

TEST(Error, InvalidNames1) {
    EXPECT_EXCEPTION(bind(id, list(), list()), id, MISSING)
}

TEST(Error, InvalidNames2) {
    EXPECT_EXCEPTION(bind(id, list(id), list()), id, CAR)
}

TEST(Error, InvalidValues1) {
    EXPECT_EXCEPTION(bind(list(), id, list()), id, REDUNDANT)
}

TEST(Error, InvalidValues2) {
    EXPECT_EXCEPTION(bind(list(id), id, list()), id, CAR)
}

TEST(Error, RedundantValues) {
  EXPECT_EXCEPTION(bind(list(id,id,id), list(id, id, t, n), list()), list(n), REDUNDANT)
}

TEST(Error, MissingValues) {
  EXPECT_EXCEPTION(bind(list(id,a1), list(id), list()), list(a1), MISSING)
}

TEST(Error, UnknownLambda) {
    EXPECT_EXCEPTION(apply(S("e"), t), S("e").cons(t), INVALID)
}

TEST(Error, OtherError) {
    EXPECT_EXCEPTION(t.error(S("OTHER")), t, S("OTHER"))
}
