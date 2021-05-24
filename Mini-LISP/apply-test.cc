/*
 * Unit tests for apply function.
 *
 * To validate the tests, you can use gcl.
 *
 */

#include <string.h>
#include <gtest/gtest.h>
#include "test.h"

// Helper function:
S parse_s(const char *s) {
    Parser::reset();
    Parser::supply(strdup(s));
    if (Parser::status() != Parser::Status::accept) {
        throw std::runtime_error("Unexpected parse_sr error"); // should not be here - we assume all unittest inputs are valid
    }
    return Parser::result();
}

// ----------------------------
// Test: primitives_functions
TEST(Apply, primitives_functions) {
    EXPECT_EQ(apply(
            parse_s("'atom"), parse_s("'(a)")
            ), S("T"));
    EXPECT_EQ(apply(
            parse_s("'null"), parse_s("'(a)")
            ), S("NIL"));
    EXPECT_EQ(apply(
            parse_s("'null"), parse_s("'(NIL)")
            ), S("T"));
    EXPECT_EQ(apply(
            parse_s("'cons"), parse_s("'(a b)")
            ), S("(A . B)"));
    EXPECT_EQ(apply(
            parse_s("'eq"), parse_s("'(a a)")
            ), S("T"));
    EXPECT_EQ(apply(
            parse_s("'eq"), parse_s("'(a b)")
            ), S("NIL"));
    EXPECT_EQ(apply(
            parse_s("'set"), parse_s("'(b T)")
            ), S("T"));
    EXPECT_EQ(apply(
            parse_s("'set"), parse_s("'(a '(b c))")
            ), S("'(B C)"));
    EXPECT_EQ(apply(
            parse_s("'eval"), parse_s("'(t)")
            ), S("T"));
    EXPECT_EQ(apply(
            parse_s("'eval"), parse_s("'(nil)")
            ), S("NIL"));
}

// ----------------------------
// Test: complicated_functions
TEST(Apply, complicated_functions) {
    EXPECT_EQ(apply(
            parse_s("(defun ret_nil(x) NIL)"), parse_s("'(a)")
            ), S("NIL"));
    EXPECT_EQ(apply(
            parse_s("(defun ret_nil(x y) NIL)"), parse_s("'(a b)")
            ), S("NIL"));
    EXPECT_EQ(apply(
            parse_s("(defun zcar(x)  (cond ((atom x) x) (t (car x))))"), parse_s("'(a)")
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
            parse_s("(defun is_in_list (val L) (cond (( null L ) NIL ) (( eql val ( car L ) ) T ) ( T ( is_in_list val ( cdr L ) ) ) ))"), parse_s("'(2 (2 3))")
            ), S("T"));
    EXPECT_EQ(apply(
            parse_s("(defun is_in_list (val L) (cond (( null L ) NIL ) (( eql val ( car L ) ) T ) ( T ( is_in_list val ( cdr L ) ) ) ))"), parse_s("'(2 (1 3))")
            ), S("F"));
}

// ----------------------------
// Test: self_apply:
TEST(Apply, self_apply) {
    EXPECT_EQ(apply(
            parse_s("'apply"), parse_s("'(null NIL NIL))")
            ), S("T"));
    EXPECT_EQ(apply(
            parse_s("'apply"), parse_s("'(null T NIL))")
            ), S("NIL"));
}




