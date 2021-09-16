#include <string.h>
#include <gtest/gtest.h>
#include "test.h"
/** Mini-lisp book - test evaluate */

extern S lookup(S s);

inline S prepare(S s) { return s; } 
inline S eval(String s) { return parse(s).eval(); }
inline S eval(S s) { return s.eval(); }
S x("x"), y("y"), a("a"), b("b");

#define EVAL_EQ(x,y)    CAREFULLY_EXPECT(EQ, eval(x), prepare(y));
#define EVAL_XX(x,y,z)  EXPECT_EXCEPTION(eval(x), prepare(y), prepare(z)); 

static const S MISSING_ARGUMENT_VALUES("MISSING_ARGUMENT_VALUES");
static const S SOMETHING_WENT_WRONG("SOMETHING_WENT_WRONG");
static const S MISSING_ARGUMENT_NAMES("MISSING_ARGUMENT_NAMES");

struct Kernel: ::testing::Test {
};

extern S lookup(S s);


TEST(Kernel, Exists) {
    eval("(defun exists (x xs)  "
          "         (cond  "
          "             ((null xs) xs) "
          "             ((eq x (car xs)) t) "
          "             (t (exists x (cdr xs)))"
          "         )"
          ")"
          ""
    );

    // Test:
    EVAL_EQ("(exists 'a '(a b))", T);
    EVAL_EQ("(exists 'a '(x y))", NIL);
    EVAL_EQ("(exists 'a '())", NIL);
    EVAL_XX("(exists)", list(S("X"),S("XS")), MISSING_ARGUMENT);
}


TEST(Kernel, IsAtomic) {
    eval("(defun is-atomic(name) "
          "     (exists name '(atom car cdr cond cons eq error eval set)))");

    // Test:
    EVAL_EQ("(is-atomic 'car)", T);
    EVAL_EQ("(is-atomic 'kkk)", NIL);
    EVAL_XX("(is-atomic)", list(S("NAME")), MISSING_ARGUMENT);
}


TEST(Kernel, Lookup) {
    eval("(defun lookup (id a-list) "
          "         (cond "
          "             ((null a-list) (error 'unbound_variable id)) "
          "             ((eq id (car (car a-list)) ) (cdr (car a-list))) "
          "             (t (lookup id (cdr a-list)))"
          "         )"
          ")"
          "");

    // Test:
    EVAL_EQ("(lookup 'a '(a.x b.NIL c.NIL))", x);
    EVAL_EQ("(lookup 'a '(b.NIL a.x c.NIL))", x);
    EVAL_EQ("(lookup 'a '(b.NIL c.NIL a.x))", x);
    EVAL_XX("(lookup)", list(S("ID"), S("a-list")) , MISSING_ARGUMENT);
}



TEST(Kernel, Bind) {
    eval("(defun bind (names values a-list) "
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
            "");

    // Test:
    EVAL_EQ("(bind '(a b) '(x y) '())","((a.x) (b.y))");  
    EVAL_EQ("(bind '(a b) '(x y) '(c.T z.T))", "(a.x b.y c.t z.T)");
    EVAL_XX("(bind)", list(S("NAMES"), S("VALUES"), S("a-list")), MISSING_ARGUMENT);
    EVAL_XX("(bind '(a b) '(x y z) '())", "(error)", MISSING_ARGUMENT_NAMES);
    EVAL_XX("(bind '(a b c) '(x y) '())", "ERROR", MISSING_ARGUMENT_VALUES.q())
}


TEST(Kernel, ApplyTrivialAtomic) {
    eval("(defun apply-trivial-atomic (atomic first second)"
                "(cond ((eq atomic 'atom) (atom first))"
                        "((eq atomic 'car) (car first))"
                        "((eq atomic 'cdr) (cdr first))"
                        "((eq atomic 'cons) (cons first second))"
                        "((eq atomic 'eq) (eq first second))"
                        "((eq atomic 'set) (set first second))"
                        "(t (error 'something_went_wrong))"
                ")"
            ")"
      );

    // Test:
    EVAL_EQ("(apply-trivial-atomic 'atom 'a NIL)", T);
    EVAL_EQ("(apply-trivial-atomic 'car '(a b) NIL)", a);
    EVAL_EQ("(apply-trivial-atomic 'cdr '(a b) NIL)", list(b));
    EVAL_EQ("(apply-trivial-atomic 'cons 'a 'b)", a.cons(b));
    EVAL_EQ("(apply-trivial-atomic 'eq 'a 'a)", T);
    EVAL_EQ("(apply-trivial-atomic 'eq 'a 'b)", NIL);
    eval("(apply-trivial-atomic 'set 'a 'b)"); 
    EVAL_EQ(lookup(a), b);
    EVAL_XX("(apply-trivial-atomic)", "(ATOMIC FIRST SECOND)", MISSING_ARGUMENT)
    EVAL_XX("(apply-trivial-atomic 'zzz 'a NIL)", "ERROR.SOMETHING_WENT_WRONG", "")
}


TEST(Kernel, ApplyEagerAtomic) {
  eval(
    "(defun apply-eager-atomic (atomic actuals a-list)"
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
        "");

    // Test:
    EVAL_EQ("(apply-eager-atomic 'atom '(a NIL) '())", T);
    EVAL_EQ("(apply-eager-atomic 'car '((a b) (NIL)) '())", a);
    EVAL_EQ("(apply-eager-atomic 'cdr '((a b) (NIL)) '())", list(b));
    EVAL_EQ("(apply-eager-atomic 'cons '(a b) '())", a.cons(b));
    EVAL_EQ("(apply-eager-atomic 'eq '(a a) '())", T);
    EVAL_EQ("(apply-eager-atomic 'eq '(a b) '())", NIL);
    "(apply-eager-atomic 'set '(y a) '())"; EVAL_EQ(lookup(y), a);
    EVAL_XX("(apply-eager-atomic)",  list(S("ATOMIC"), S("ACTUALS"), S("A-LIST")), MISSING_ARGUMENT);
    EVAL_XX("(apply-eager-atomic 'error 'a '())", list(S("ERROR"), S("ACTUALS")), a);
}
