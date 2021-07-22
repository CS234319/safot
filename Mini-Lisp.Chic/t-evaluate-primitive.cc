/*
 * Unit tests for eval_primitive function.
 *
 * eval_primitive function:
 * ------------------------
 * If the eval(s) function get an atomic-function f and params (as s-expression),
 * it will call eval_primitive(s), which will return a new s-expression
 * which is the return value of "(f params)", or in C syntax: f(params).
 * That function is part of the base of the recursion in the evaluation function.
 * (from the mini-Lisp documentation)
 *
 * Notes:
 * ------
 *  1) The unittest use the eval(s) function and not the eval_primitive(s) function directly.
 *  2) The unittest will check all the atomic functions in mini-Lisp:
 *       Structure: car, cdr, cons
 *       Logic    : eq, cond                  // cond has special case because the normal semantic
 *       More     : set, error, atom, eval
 *  3) Complex cases e.g: "(car (cons 'a 'b))" won't check here, but will be test in evaluate-test.cc
 *
 */

#include <string.h>
#include <gtest/gtest.h>
#include "test.h"
#include "mode.h"

static S a("a");
static S b("b");
static S c("c");
static S x("x");
static S y("y");
static S z("z");

// ----------------------------
// Test: car
TEST(ParseEvalAtomic, car) {
    EXPECT_EQ(parse("(car '(b a))").eval() , b);
    EXPECT_EQ(parse("(car '(b a x y z))").eval() , b);
}

// ----------------------------
// Test: cdr
TEST(ParseEvalAtomic, cdr) {
    EXPECT_EQ(parse("(cdr '(a b))").eval() , list(b));
    EXPECT_EQ(parse("(cdr '(a x y z))").eval() , list(x, y, z));
}

// ----------------------------
// Test: cons
TEST(ParseEvalAtomic, cons) {
    EXPECT_EQ(parse("(cons 'a '(b c))").eval() , list(a, b, c));
    EXPECT_EQ(parse("(cons 'b nil)").eval()    , b.cons(NIL));
    EXPECT_EQ(parse("(cons 'a 'b)").eval()     , a.cons(b));
}

// ----------------------------
// Test: eq
TEST(ParseEvalAtomic, eq) {
    EXPECT_EQ(parse("(eq 'a 'a)").eval()          , T);
    EXPECT_EQ(parse("(eq 'a 'b)").eval()          , NIL);
    EXPECT_EQ(parse("(eq t t)").eval()            , T);
    EXPECT_EQ(parse("(eq t nil)").eval()          , NIL);
    EXPECT_EQ(parse("(eq nil nil)").eval()        , T);
}

// ----------------------------
// Test: set
TEST(ParseEvalAtomic, set) {
    EXPECT_EQ(parse("(set 'a '(b c))").eval() , list(b, c));
    EXPECT_EQ(parse("(set 'b nil)").eval()    , NIL);
}

// ----------------------------
// Test: atom
TEST(ParseEvalAtomic, atom) {
    EXPECT_EQ(parse("(atom 'a)").eval()  , T);
    EXPECT_EQ(parse("(atom t)").eval()      , T);
    EXPECT_EQ(parse("(atom '(a a))").eval() , NIL);
}

// ----------------------------
// Test: eval
TEST(ParseEvalAtomic, eval) {
    EXPECT_EQ(parse("(eval t)").eval()   , T);
    EXPECT_EQ(parse("(eval nil)").eval() , NIL);
}

// ----------------------------
// Test: error
TEST(ParseEvalAtomic, error) {
    EXPECT_EXCEPTION(parse("(error)").eval()         , list(S("ERROR")) , NIL);
    EXPECT_EXCEPTION(parse("(error 'my_err)").eval() , list(S("MY_ERR")), INVALID);
}

// ----------------------------
// Test: errors cases
TEST(ParseEvalAtomic, RealErrors) {
    EXPECT_EXCEPTION(parse("(car ())").eval() , NIL, CAR);
    EXPECT_EXCEPTION(parse("(car t)").eval() , T, CAR);
    EXPECT_EXCEPTION(parse("(cdr t)").eval()  , T, CDR);
    EXPECT_EXCEPTION(parse("(cdr nil)").eval() , NIL, CDR);
}
