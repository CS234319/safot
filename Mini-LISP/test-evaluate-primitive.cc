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
#include "eval.h"
#include "test.h"

// ----------------------------
// Test: car
TEST(EvalPrimitive, car) {
  CAREFULLY(EXPECT_EQ(eval("(car '())"), S("NIL")));
  EXPECT_EQ(eval("(car nil)")    , S("NIL"));
  EXPECT_EQ(eval("(car '(b.a))") , S("B"));
  EXPECT_EQ(eval("(car '(b a))") , S("B"));
}

// ----------------------------
// Test: cdr
TEST(EvalPrimitive, cdr) {
    EXPECT_EQ(eval("(cdr '())")    , S("NIL"));
    EXPECT_EQ(eval("(cdr nil)")    , S("NIL"));
    EXPECT_EQ(eval("(cdr '(a.b))") , S("b"));
    EXPECT_EQ(eval("(cdr '(a b))") , S("(b)"));
    EXPECT_EQ(eval("(cdr '(b))")   , S("NIL"));
}

// ----------------------------
// Test: cons
TEST(EvalPrimitive, cons) {
    EXPECT_EQ(eval("(cons 'a '(b c))") , S("(A B C)"));
    EXPECT_EQ(eval("(cons 'b nil)")    , S("NIL"));
    EXPECT_EQ(eval("(cons 'a 'b)")     , S("(A.B)"));
}

// ----------------------------
// Test: eq
TEST(EvalPrimitive, eq) {
    EXPECT_EQ(eval("(eq 'a 'a)")          , S("T"));
    EXPECT_EQ(eval("(eq 'a 'b)")          , S("NIL"));
    EXPECT_EQ(eval("(eq t t)")            , S("T"));
    EXPECT_EQ(eval("(eq t nil)")          , S("NIL"));
    EXPECT_EQ(eval("(eq nil nil)")        , S("T"));
    EXPECT_EQ(eval("(eq '(a a) '(a a))")  , S("NIL"));
}

// ----------------------------
// Test: cond
TEST(EvalPrimitive, cond) {
    EXPECT_EQ(eval("(cond (t 'A))")                     , S("A"));
    EXPECT_EQ(eval("(cond (nil 'A) (t 'B))")            , S("B"));
    EXPECT_EQ(eval("(cond (nil 'A) (t 'B) (t 'C))")     , S("B"));
    EXPECT_EQ(eval("(cond (nil 'A) (nil 'B) (nil 'C))") , S("NIL"));
    EXPECT_EQ(eval("(cond)")                            , S("NIL"));
}

// ----------------------------
// Test: set
TEST(EvalPrimitive, set) {
    EXPECT_EQ(eval("(set 'a '(b c))") , S("(b c)"));
    EXPECT_EQ(eval("(set 'b nil)")    , S("NIL"));
}

// ----------------------------
// Test: atom
TEST(EvalPrimitive, atom) {
    EXPECT_EQ(eval("(atom nil)")    , S("T"));
    EXPECT_EQ(eval("(atom t)")      , S("T"));
    EXPECT_EQ(eval("(atom '(a a))") , S("NIL"));
    EXPECT_EQ(eval("(atom 'a)")     , S("T"));
}

// ----------------------------
// Test: eval
TEST(EvalPrimitive, eval) {
    EXPECT_EQ(eval("(eval t)")   , S("T"));
    EXPECT_EQ(eval("(eval nil)") , S("NIL"));
}

// ----------------------------
// Test: error
TEST(EvalPrimitive, error) {
    EXPECT_EQ(eval("(error)")         , S(""));
    EXPECT_EQ(eval("(error 'my_err)") , S("my_err"));
}

// ----------------------------
// Test: errors cases
TEST(EvalPrimitive, RealErrors) {
    /*
     * According to mini-Lisp doc:
     *     If apply−trivial−atomic failed, error message is: "something−went−wrong atomic"
     *     In lisp syntax: "(error 'something−went−wrong atomic)"
     *
     * Note:
     *     Atom,ic function: "cond" can't failed.
     *
     */
    EXPECT_EQ(eval("(car 'a)") , S("something−went−wrong-atomic"));
    EXPECT_EQ(eval("(car ())") , S("something−went−wrong-atomic"));
    EXPECT_EQ(eval("(cdr t)")  , S("something−went−wrong-atomic"));
    EXPECT_EQ(eval("(cdr ())") , S("something−went−wrong-atomic"));
    EXPECT_EQ(eval("(cdr nil)"), S("something−went−wrong-atomic"));
}
