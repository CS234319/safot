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
TEST(ParseEvalAtomic, car) {
  CAREFULLY(EXPECT_EQ(eval("(car '())"), NIL));
  EXPECT_EQ(eval("(car nil)")    , NIL);
  EXPECT_EQ(eval("(car '(b.a))") , S("B"));
  EXPECT_EQ(eval("(car '(b a))") , S("B"));
}

// ----------------------------
// Test: cdr
TEST(ParseEvalAtomic, cdr) {
    EXPECT_EQ(eval("(cdr '())")    , NIL);
    EXPECT_EQ(eval("(cdr nil)")    , NIL);
    EXPECT_EQ(eval("(cdr '(a.b))") , S("b"));
    EXPECT_EQ(eval("(cdr '(a b))") , S("(b)"));
    EXPECT_EQ(eval("(cdr '(b))")   , NIL);
}

// ----------------------------
// Test: cons
TEST(ParseEvalAtomic, cons) {
    EXPECT_EQ(eval("(cons 'a '(b c))") , S("(A B C)"));
    EXPECT_EQ(eval("(cons 'b nil)")    , NIL);
    EXPECT_EQ(eval("(cons 'a 'b)")     , S("(A.B)"));
}

// ----------------------------
// Test: eq
TEST(ParseEvalAtomic, eq) {
    EXPECT_EQ(eval("(eq 'a 'a)")          , NIL);
    EXPECT_EQ(eval("(eq 'a 'b)")          , NIL);
    EXPECT_EQ(eval("(eq t t)")            , NIL);
    EXPECT_EQ(eval("(eq t nil)")          , NIL);
    EXPECT_EQ(eval("(eq nil nil)")        , NIL);
    EXPECT_EQ(eval("(eq '(a a) '(a a))")  , NIL);
}

// ----------------------------
// Test: cond
TEST(ParseEvalAtomic, cond) {
    EXPECT_EQ(eval("(cond (t 'A))")                     , S("A"));
    EXPECT_EQ(eval("(cond (nil 'A) (t 'B))")            , S("B"));
    EXPECT_EQ(eval("(cond (nil 'A) (t 'B) (t 'C))")     , S("B"));
    EXPECT_EQ(eval("(cond (nil 'A) (nil 'B) (nil 'C))") , NIL);
    EXPECT_EQ(eval("(cond)")                            , NIL);
}

// ----------------------------
// Test: set
TEST(ParseEvalAtomic, set) {
    EXPECT_EQ(eval("(set 'a '(b c))") , "(b c)"); // May not work, check it out.
    EXPECT_EQ(eval("(set 'b nil)")    , NIL);
}

// ----------------------------
// Test: atom
TEST(ParseEvalAtomic, atom) {
    EXPECT_EQ(eval("(atom nil)")    , NIL);
    EXPECT_EQ(eval("(atom t)")      , NIL);
    EXPECT_EQ(eval("(atom '(a a))") , NIL);
    EXPECT_EQ(eval("(atom 'a)")     , NIL);
}

// ----------------------------
// Test: eval
TEST(ParseEvalAtomic, eval) {
    EXPECT_EQ(eval("(eval t)")   , NIL);
    EXPECT_EQ(eval("(eval nil)") , NIL);
}

// ----------------------------
// Test: error
TEST(ParseEvalAtomic, error) {
    EXPECT_EQ(eval("(error)")         , S(""));
    EXPECT_EQ(eval("(error 'my_err)") , S("my_err"));
}

// ----------------------------
// Test: errors cases
TEST(ParseEvalAtomic, RealErrors) {
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
