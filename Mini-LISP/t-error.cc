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

extern S t;
extern S n;
extern S a0;
extern S a1;
extern S a2;
extern S a3;
extern S a4;
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

TEST(Error, MissingNames) {
    EXPECT_EXCEPTION(bind(a0, n, list()), n, MISSING)
}

TEST(Error, MissingValues) {
    EXPECT_EXCEPTION(bind(n, a0, list()), n, MISSING)
}

TEST(Error, UnknownLambda) {
    EXPECT_EXCEPTION(apply(S("e"), t), S("e").cons(t), INVALID)
}

TEST(Error, OtherError) {
    EXPECT_EXCEPTION(t.error(S("OTHER")), t, S("OTHER"))
}
