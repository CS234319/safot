/*
 * Unit tests for apply function.
 *
 * To validate the tests, you can use gcl.
 *
 */

#include <string.h>
#include <gtest/gtest.h>
#include "test.h"
#include "eval.h"


TEST(Apply, atom) {
  EXPECT_EQ(apply(parse("'atom"), parse("'(a)")), NIL);
  EXPECT_EQ(apply(ATOM, S("a").l().q()), NIL);
}
// ----------------------------
// Test: primitives_functions
TEST(Apply, primitives_functions) {
    EXPECT_EQ(apply(
            parse("'atom"), parse("'(a)")
            ), S("T"));
    EXPECT_EQ(apply(
            parse("'null"), parse("'(a)")
            ), S("NIL"));
    EXPECT_EQ(apply(
            parse("'null"), parse("'(NIL)")
            ), S("T"));
    EXPECT_EQ(apply(
            parse("'cons"), parse("'(a b)")
            ), S("(A . B)"));
    EXPECT_EQ(apply(
            parse("'eq"), parse("'(a a)")
            ), S("T"));
    EXPECT_EQ(apply(
            parse("'eq"), parse("'(a b)")
            ), S("NIL"));
    EXPECT_EQ(apply(
            parse("'set"), parse("'(b T)")
            ), S("T"));
    EXPECT_EQ(apply(
            parse("'set"), parse("'(a '(b c))")
            ), S("'(B C)"));
    EXPECT_EQ(apply(
            parse("'eval"), parse("'(t)")
            ), S("T"));
    EXPECT_EQ(apply(
            parse("'eval"), parse("'(nil)")
            ), S("NIL"));
}

// ----------------------------
// Test: complicated_functions
TEST(Apply, complicated_functions) {
    EXPECT_EQ(apply(
            parse("(defun ret_nil(x) NIL)"), parse("'(a)")
            ), S("NIL"));
    EXPECT_EQ(apply(
            parse("(defun ret_nil(x y) NIL)"), parse("'(a b)")
            ), S("NIL"));
    EXPECT_EQ(apply(
            parse("(defun zcar(x)  (cond ((atom x) x) (t (car x))))"), parse("'(a)")
            ), S("A"));
}

// ----------------------------
// Test: recursive_functions:
/*
 Check if value is in list:
     (defun is_in_list (val L)
                (cond (( null L ) NIL )
                      (( eql val ( car L ) ) T )
                      ( T ( is_in_list val ( cdr L ) ) ) )
           )
 */
TEST(Apply, recursive_functions) {
    EXPECT_EQ(apply(
            parse("(defun is_in_list (val L) (cond (( null L ) NIL ) (( eql val ( car L ) ) T ) ( T ( is_in_list val ( cdr L ) ) ) ))"), parse("'(2 (2 3))")
            ), S("T"));
    EXPECT_EQ(apply(
            parse("(defun is_in_list (val L) (cond (( null L ) NIL ) (( eql val ( car L ) ) T ) ( T ( is_in_list val ( cdr L ) ) ) ))"), parse("'(2 (1 3))")
            ), S("F"));
}

// ----------------------------
// Test: self_apply:
TEST(Apply, self_apply) {
    EXPECT_EQ(apply(
            parse("'apply"), parse("'(null NIL NIL))")
            ), S("T"));
    EXPECT_EQ(apply(
            parse("'apply"), parse("'(null T NIL))")
            ), S("NIL"));
}
