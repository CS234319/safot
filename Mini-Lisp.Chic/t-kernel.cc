#import  <string.h>
#import  <gtest/gtest.h>

#import  "test.h"
#import  "a-list.h"
#import  "print.h"
/** Mini-lisp book - test evaluate */
#undef PRODUCTION
#import  "mode.h"

using Engine::lookup;

S x("x"), y("y"), a("a"), b("b");

#define FIXTURE(name, parent, body) \
  struct name: parent {  \
    name() { CAREFULLY_EXPECT(NE, NIL,eval(body)); } \
  };

FIXTURE(exists,Test,
 "(defun exists (x xs)  "
        "         (cond  "
        "             ((null xs) xs) "
        "             ((eq x (car xs)) t) "
        "             (t (exists x (cdr xs)))"
        "         ))")
TEST_F(exists, T1) { D(Engine::globals); chatty(); EVAL_EQ("(exists 'a '(a b))", T) }
TEST_F(exists, T2) EVAL_EQ("(exists 'a '(x y))", NIL)                       
TEST_F(exists, T3) EVAL_EQ("(exists 'a '())", NIL)                           
TEST_F(exists, T4) EVAL_XX("(exists)", list(S("X"),S("XS")), MISSING_ARGUMENT)

FIXTURE(is_atomic, exists, 
  "(defun is-atomic(name) "
  "     (exists name '(atom car cdr cond cons eq error eval set)))")
TEST_F(is_atomic, T1)  EVAL_EQ("(is-atomic 'car)", T)
TEST_F(is_atomic, T2)  EVAL_EQ("(is-atomic 'kkk)", NIL);
TEST_F(is_atomic, T3)  EVAL_XX("(is-atomic)", list(S("NAME")), MISSING_ARGUMENT);

FIXTURE(lookup,Test, 
    "(defun lookup (id a-list) "
          "         (cond "
          "             ((null a-list) (error unbound_variable id)) "
          "             ((eq id (car (car a-list)) ) (cdr (car a-list))) "
          "             (t (lookup id (cdr a-list)))"
          "         )"
          ")"
)
TEST_F(lookup, T1)    EVAL_EQ("(lookup 'a '(a.x b.NIL c.NIL))", x);
TEST_F(lookup, T2)    EVAL_EQ("(lookup 'a '(b.NIL a.x c.NIL))", x);
TEST_F(lookup, T3)    EVAL_EQ("(lookup 'a '(b.NIL c.NIL a.x))", x);
TEST_F(lookup, T4)    EVAL_XX("(lookup)", list(S("ID"), S("a-list")) , MISSING_ARGUMENT);

FIXTURE(bind,Test, 
    "(defun bind (names values a-list) "
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
            ""
)
TEST_F(bind, T0) EVAL_EQ("(bind '(a b) '((x) (y)) ())","((a x) (b y))")  
TEST_F(bind, T1) EVAL_EQ("(bind '(a b) '((x) (y)) ())","((a x) (b y))")  
TEST_F(bind, T2) EVAL_EQ("(bind '(a b) '(x y) '(c.T z.T))", "(a.x b.y c.t z.T)")
TEST_F(bind, T3) EVAL_XX("(bind '(NAMES)  '(VALUES))", "(a-list)", MISSING_ARGUMENT)
TEST_F(bind, T4) EVAL_XX("(bind 'x 'y)", "(a-list)", MISSING_ARGUMENT)
TEST_F(bind, T5) EVAL_XX("(bind 'x 'y 'z 'a)", "('a)", REDUNDANT_ARGUMENT)
TEST_F(bind, T6) EVAL_XX("(bind '(a b) '(x y z) '())",  "missing_names", ERROR)
TEST_F(bind, T7) EVAL_XX("(bind '(a b c) '(x y) '())",  "missing_values", ERROR)

FIXTURE(apply_trivial_atomic, Test,
  "(defun apply-trivial-atomic (atomic first second)"
  "  (cond ((eq atomic 'atom) (atom first))"
  "        ((eq atomic 'car) (car first))"
  "        ((eq atomic 'cdr) (cdr first))"
  "        ((eq atomic 'cons) (cons first second))"
  "        ((eq atomic 'eq) (eq first second))"
  "        ((eq atomic 'set) (set first second))"
  "        (t (error 'something-went-wrong atomic))))"
)

TEST_F(apply_trivial_atomic, T1) EVAL_EQ("(apply-trivial-atomic 'atom 'a NIL)", T);
TEST_F(apply_trivial_atomic, T2) EVAL_EQ("(apply-trivial-atomic 'atom 'NIL NIL)", T);
TEST_F(apply_trivial_atomic, T3) EVAL_EQ("(apply-trivial-atomic 'atom '((a b)) NIL)", NIL);
TEST_F(apply_trivial_atomic, T4) EVAL_EQ("(apply-trivial-atomic 'car '(a b) NIL)", a);
TEST_F(apply_trivial_atomic, T5) EVAL_EQ("(apply-trivial-atomic 'cdr '(a b) NIL)", list(b));
TEST_F(apply_trivial_atomic, T6) EVAL_EQ("(apply-trivial-atomic 'cons 'a 'b)", a.cons(b));
TEST_F(apply_trivial_atomic, T7) EVAL_EQ("(apply-trivial-atomic 'eq 'a 'a)", T);
TEST_F(apply_trivial_atomic, T8) EVAL_EQ("(apply-trivial-atomic 'eq 'a 'b)", NIL);
TEST_F(apply_trivial_atomic, T9) { eval("(apply-trivial-atomic 'set 'a 'b)");  EVAL_EQ("a", "b"); }
TEST_F(apply_trivial_atomic, Error1) EVAL_XX("(apply-trivial-atomic)", "(ATOMIC FIRST SECOND)", MISSING_ARGUMENT)
TEST_F(apply_trivial_atomic, Error2) EVAL_XX("(apply-trivial-atomic 'zzz 'a NIL)", "(zzz)", "SOMETHING-WENT-WRONG")

FIXTURE(apply_eager_atomic, apply_trivial_atomic,
  "(defun apply-eager-atomic (atomic actuals a-list)"
  "  (cond"
  "    ((eq atomic 'error) (error actuals))"
  "    ((eq atomic 'eval) (evaluate (car actuals) a-list))"
  "    ((null (cdr actuals)) (apply-trivial-atomic atomic (car actuals) NIL)) "
  "    (t (apply-trivial-atomic atomic (car actuals) (car (cdr actuals)))) "
  "))")

TEST_F(apply_eager_atomic, T0) EVAL_EQ("(apply-eager-atomic 'atom '(a b) ())", T);
TEST_F(apply_eager_atomic, T1) EVAL_EQ("(apply-eager-atomic 'atom '(a) ())", T);
TEST_F(apply_eager_atomic, T2) EVAL_EQ("(apply-eager-atomic 'atom '(NIL) ())", T);
TEST_F(apply_eager_atomic, T3) EVAL_EQ("(apply-eager-atomic 'atom '((a)) ())", NIL);
TEST_F(apply_eager_atomic, T4) EVAL_EQ("(apply-eager-atomic 'car '((a b) (NIL)) '())", a);
TEST_F(apply_eager_atomic, T5) EVAL_EQ("(apply-eager-atomic 'cdr '((a b) (NIL)) '())", list(b));
TEST_F(apply_eager_atomic, T6) EVAL_EQ("(apply-eager-atomic 'cons '(a b) '())", a.cons(b));
TEST_F(apply_eager_atomic, T7) EVAL_EQ("(apply-eager-atomic 'eq '(a a) '())", T);
TEST_F(apply_eager_atomic, T8) EVAL_EQ("(apply-eager-atomic 'eq '(a b) '())", NIL);
TEST_F(apply_eager_atomic, T9) { eval("(apply-eager-atomic 'set 'y  nil)"); EVAL_EQ(lookup(y), a); }
TEST_F(apply_eager_atomic, T10) EVAL_XX("(apply-eager-atomic)",  list(S("ATOMIC"), S("ACTUALS"), S("A-LIST")), MISSING_ARGUMENT);

FIXTURE(evaluate_cond, Test,
  "(defun evaluate-cond(test-forms a-list)"
  "  (cond ((null test-forms) nil) "
  "        ((evaluate (car (car test-forms)) a-list) "
  "        (evaluate (car (cdr (car test-forms))) a-list)) "
  "        (t (evaluate-cond (cdr test-forms) a-list)))) "
)

FIXTURE(apply_atomic, Test,
  "(defun apply-atomic (atomic actuals a-list)"
  "  (cond ((eq 'cond atomic) "
  "            (evaluate-cond actuals a-list)) "
  "        (t (apply-eager-atomic ; all other atomics are eager"
  "              atomic"
  "              (evaluate-list actuals a-list)"
  "              a-list))))")
