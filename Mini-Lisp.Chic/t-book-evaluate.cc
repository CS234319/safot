#include <string.h>
#include <gtest/gtest.h>
#include "test.h"
/**
 * Mini-lisp book - test evaluate
 */

S x("x");
S y("y");
S z("z");
S a("a");
S b("b");
S c("c");
extern S lookup(S s);

const S MISSING_NAMES("MISSING_NAMES");
const S MISSING_VALUES("MISSING_VALUES");
const S SOMETHING_WENT_WRONG("SOMETHING_WENT_WRONG");

TEST(BookEvaluate, Exists) {
    parse("(defun exists (x xs)  "
          "         (cond  "
          "             ((null xs) xs) "
          "             ((eq x (car xs)) t) "
          "             (t (exists x (cdr xs)))"
          "         )"
          ")"
          "").eval();

    // Test:
    EXPECT_EQ(parse("(exists 'a '(a b))").eval(), T);
    EXPECT_EQ(parse("(exists 'a '(x y))").eval(), NIL);
    EXPECT_EQ(parse("(exists 'a '())").eval(), NIL);
    EXPECT_EXCEPTION(parse("(exists)").eval(), list(S("X"),S("XS")), MISSING);
}


TEST(BookEvaluate, IsAtomic) {
    parse("(defun is-atomic(name) "
          "     (exists name '(atom car cdr cond cons eq error eval set)))").eval();

    // Test:
    EXPECT_EQ(parse("(is-atomic 'car)").eval(), T);
    EXPECT_EQ(parse("(is-atomic 'kkk)").eval(), NIL);
    EXPECT_EXCEPTION(parse("(is-atomic)").eval(), list(S("NAME")), MISSING);
}


TEST(BookEvaluate, Lookup) {
    parse("(defun lookup (id a-list) "
          "         (cond "
          "             ((null a-list) (error 'unbound_variable id)) "
          "             ((eq id (car (car a-list)) ) (cdr (car a-list))) "
          "             (t (lookup id (cdr a-list)))"
          "         )"
          ")"
          "").eval();

    // Test:
    EXPECT_EQ(parse("(lookup 'a '(a.x b.NIL c.NIL))").eval(), x);
    EXPECT_EQ(parse("(lookup 'a '(b.NIL a.x c.NIL))").eval(), x);
    EXPECT_EQ(parse("(lookup 'a '(b.NIL c.NIL a.x))").eval(), x);
    EXPECT_EXCEPTION(parse("(lookup)").eval(), list(S("ID"), S("a-list")) , MISSING);
}


TEST(BookEvaluate, Bind) {
    parse("(defun bind (names values a-list) "
            "       (cond ((null names) "
            "           (cond ((null values) a-list)"
            "               (t (error 'missing_names)))) "
            "           ((null values) "
            "               (error 'missing_values))  "
            "           (t  "
            "               (cons  "
            "                   (cons "
            "                       (car names) (car values))  "
            "                       (bind (cdr names) (cdr values) a-list)"
            "                   )"
            "               )"
            "           )"
            ")"
            "").eval();

    // Test:
    EXPECT_EQ(
    parse("(bind '(a b) '(x y) '())").eval(),
    list(a.cons(x), b.cons(y))
    );
    EXPECT_EQ(
    parse("(bind '(a b) '(x y) '())").eval(),
    list(a.cons(x), b.cons(y))
    );
    EXPECT_EQ(
    parse("(bind '(a b) '(x y) '(c.T z.T))").eval(),
    list(a.cons(x), b.cons(y), c.cons(T), z.cons(T))
    );
    EXPECT_EXCEPTION(parse("(bind)").eval(), list(S("NAMES"), S("VALUES"), S("a-list")), MISSING);
    EXPECT_EXCEPTION(
        parse("(bind '(a b) '(x y z) '())").eval(),
        list(MISSING_NAMES),
        INVALID
     );
    EXPECT_EXCEPTION(
        parse("(bind '(a b c) '(x y) '())").eval(),
        list(MISSING_VALUES),
        INVALID
    );
}


TEST(BookEvaluate, ApplyTrivialAtomic) {
    parse("(defun apply-trivial-atomic (atomic first second)"
                "(cond ((eq atomic 'atom) (atom first))"
                        "((eq atomic 'car) (car first))"
                        "((eq atomic 'cdr) (cdr first))"
                        "((eq atomic 'cons) (cons first second))"
                        "((eq atomic 'eq) (eq first second))"
                        "((eq atomic 'set) (set first second))"
                        "(t (error 'something_went_wrong))"
                ")"
            ")").eval();

    // Test:
    EXPECT_EQ(parse("(apply-trivial-atomic 'atom 'a NIL)").eval(), T);
    EXPECT_EQ(parse("(apply-trivial-atomic 'car '(a b) NIL)").eval(), a);
    EXPECT_EQ(parse("(apply-trivial-atomic 'cdr '(a b) NIL)").eval(), list(b));
    EXPECT_EQ(parse("(apply-trivial-atomic 'cons 'a 'b)").eval(), a.cons(b));
    EXPECT_EQ(parse("(apply-trivial-atomic 'eq 'a 'a)").eval(), T);
    EXPECT_EQ(parse("(apply-trivial-atomic 'eq 'a 'b)").eval(), NIL);
    parse("(apply-trivial-atomic 'set 'a 'b)").eval(); EXPECT_EQ(lookup(a), b);
    EXPECT_EXCEPTION(parse("(apply-trivial-atomic)").eval(), list(S("ATOMIC"), S("FIRST"), S("SECOND")), MISSING);
    EXPECT_EXCEPTION(
        parse("(apply-trivial-atomic 'zzz 'a NIL)").eval(),
        list(SOMETHING_WENT_WRONG),
        INVALID
    );
}


TEST(BookEvaluate, ApplyEagerAtomic) {
    parse("(defun apply-eager-atomic (atomic actuals a-list)"
                "(cond"
                    "((eq atomic 'error) (error actuals))"
                    "((eq atomic 'eval) (evaluate (car actuals) a-list))"
                    "(t (apply-trivial-atomic"
                            " atomic "
                            " (car actuals)"
                            " (car (cdr actuals))"
                        ")"
                    ")"
                ")"
            ") "
        "").eval();

    // Test:
    EXPECT_EQ(parse("(apply-eager-atomic 'atom '(a NIL) '())").eval(), T);
    EXPECT_EQ(parse("(apply-eager-atomic 'car '((a b) (NIL)) '())").eval(), a);
    EXPECT_EQ(parse("(apply-eager-atomic 'cdr '((a b) (NIL)) '())").eval(), list(b));
    EXPECT_EQ(parse("(apply-eager-atomic 'cons '(a b) '())").eval(), a.cons(b));
    EXPECT_EQ(parse("(apply-eager-atomic 'eq '(a a) '())").eval(), T);
    EXPECT_EQ(parse("(apply-eager-atomic 'eq '(a b) '())").eval(), NIL);
    parse("(apply-eager-atomic 'set '(y a) '())").eval(); EXPECT_EQ(lookup(y), a);
    EXPECT_EXCEPTION(parse("(apply-eager-atomic)").eval(),  list(S("ATOMIC"), S("ACTUALS"), S("A-LIST")), MISSING);
    EXPECT_EXCEPTION(parse("(apply-eager-atomic 'error 'a '())").eval(), list(a), INVALID);
}



