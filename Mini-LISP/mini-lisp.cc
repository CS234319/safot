// An implementation of mini-lisp in mini-C++
#include "mini-lisp.h"
#include "dump.h"
#include "stack-trace.h"

#define SILENT 1 
#if SILENT
#undef D
#define D(...) 0
#endif

extern bool islist(S s) {
  if (s.null())
    return true;
  if (s.atom())
    return false;
  return islist(s.cdr());
}

auto operator ,(const S s1, const S s2) {
  D(s1, s2);
  D(s1.islist(), s2.islist());
  if (s2.islist())
    return s1.cons(s2);
  return list(s1, s2);
}

auto operator ,(const S s1, String s2) {
  return (s1, S(s2));
}

auto operator ,(String s1, const S s2) {
  return (S(s1), s2);
}


bool eq(S s1, S s2) {
  D(s1, s2);
  if (not (s1.atom()) or not (s2.atom()))
    return false;
  if (s1.index == s2.index)
    return true;
  using namespace Strings;
  D(pool + s1.index, pool + s2.index);
  return Strings::eq(pool + s1.index, pool + s2.index);
}

S car(S s) {
  normally(!s.atom());
  return s.car();
}

S cdr(S s) {
  normally(!s.atom());
  return s.cdr();
}

S alist = S();

S set(S name, S value) {
  D(name, value, alist);
  alist = S(S(name, value), alist);
  D(name, value, alist);
  return value;
}

static void error(String s);
static void error(String s, S s1);

static S lookup(S id, S alist) { // lookup id in an a-list
  if (alist.null())
    return NIL;
  if (eq(id, alist.car().car()))
    return alist.car().cdr();
  return lookup(id, alist.cdr());
}

S lookup(S s) {
  return lookup(s, alist);
}
S bind(S names, S values, S alist) {
  if (names.null()) {
    if (values.null()) 
      return alist;
    error("Redundant argument");
    return NIL;
  }
  if (values.null()) {
    error("Missing argument");
    return NIL;
  }
  return S(S(car(names), car(values),bind(cdr(names), cdr(values), alist));
}

const S NIL(set(S("NIL"), S())); // (set (quote nil) (quote nil))
const S T(set(S("T"), S("T")));  // (set (quote t) (quote t))
const S QUOTE("quote");

S cons(S car, S cdr) {
  return S(car, cdr);
}
S list() {
  return NIL;
}
S list(S s) {
  return cons(s, NIL);
}
S list(S s1, S s2) {
  return cons(s1, list(s2));
}
S list(S s1, S s2, S s3) {
  return cons(s1, list(s2, s3));
}
S list(S s1, S s2, S s3, S s4) {
  return cons(s1, list(s2, s3, s4));
}
S list(S s1, S s2, S s3, S s4, S s5) {
  return cons(s1, list(s2, s3, s4, s5));
}
S list(S s1, S s2, S s3, S s4, S s5, S s6) {
  return cons(s1, list(s2, s3, s4, s5, s6));
}
S list(S s1, S s2, S s3, S s4, S s5, S s6, S s7) {
  return cons(s1, list(s2, s3, s4, s5, s6, s7));
}
S list(S s1, S s2, S s3, S s4, S s5, S s6, S s7, S s8) {
  return cons(s1, list(s2, s3, s4, s5, s6, s7, s8));
}
S list(S s1, S s2, S s3, S s4, S s5, S s6, S s7, S s8, S s9) {
  return cons(s1, list(s2, s3, s4, s5, s6, s7, s8, s9));
}
S list(S s1, S s2, S s3, S s4, S s5, S s6, S s7, S s8, S s9, S s10) {
  return cons(s1, list(s2, s3, s4, s5, s6, s7, s8, s9, s10));
}

const S nlambda("nlambda"), lambda("lambda"), quote("quote");
const S ndefun("ndefun"), defun("defun");

bool exists(S x, S xs) { // determine whether atom x is in list xs
  if (xs.null())
    return false;
  if (eq(x, xs.car()))
    return true;
  return exists(x, xs.cdr());
}

static const S atomic_functions = list("atom", "car", "cdr", "cond", "cons",
    "eq", "error", "eval", "set");

bool atomic(S name) { // determine whether name denotes an atomic function
  return exists(name, atomic_functions);
}

S evaluate_atomic(S atomic, S args) {
  return NIL;
}

S apply(S s, S args) {
  return NIL;
}

S eval(S s) {
  if (s.atom())
    return lookup(s);
  if (atomic(s.car()))
    return evaluate_atomic(s.car(), s.cdr());
  return apply(eval(s.car()), s.cdr());
}

S Defun(S name, S parameters, S body) {
  set(name, list(lambda, parameters, body));
}

S Ndefun(S name, S parameters, S body) {
  set(name, list(nlambda, parameters, body));
}


int main() {
set(defun, 
      list(nlambda, 
         list(name, parameters, body), 
         list(set, name, list(lambda parameters body))));
}
#if 0
(defun is-atomic(name); determine whether name denotes an atomic function
  (exists name '(atom car cdr cond cons eq error eval set)))

\protect \pagebreak  [3]
¢
¢
\protect \pagebreak  [3]
¢
(defun evaluate(S-expression a-list) ; evaluate S-expression in the environment defined by a-list
  (cond ((atom S-expression) ; recursion base: lookup of atom in a-list
          (lookup S-expression a-list))
        ((is-atomic (car S-expression)) ; case of handling atomic functions
          (evaluate-atomic S-expression a-list))
        (t ; recursive step---lambda applied to parameters
          (apply (evaluate (car S-expression) a-list) ; find lambda expression
                  (cdr S-expression) ; find actual parameters
                  a-list))))

¢
\protect \pagebreak  [3]
¢
(defun apply(lambda-expression actuals a-list)
  (apply-decomposed-lambda
    (car lambda-expression) ; tag=lambda or nlambda
    (car (cdr lambda-expression)); list of formal parameters
    (car (cdr (cdr lambda-expression))); body
    actuals
    a-list))

¢
\protect \pagebreak  [3]
¢
(defun apply-decompsed-lambda(tag formals body actuals a-list)
  (evaluate body
    (cond (eq tag 'nlambda) (bind formals actuals a-list)
          (eq tag 'lambda) (bind formals (evaluate-list actuals a-list) a-list)
          (t (error 'unknown-lambda tag)))))

¢
\protect \pagebreak  [3]
¢
(defun evaluate-list(S-expressions a-list)
  (cond ((null S-expressions) nil) ; no more S-expressions to evaluate
    (t (cons
          (evaluate (car S-expressions) a-list) ; evaluate first S-Expression
          (evaluate-list (cdr S-expressions) a-list))))) ; recursive call on remainder

¢
\protect \pagebreak  [3]
¢
(defun evaluate-atomic (S-expression a-list)
  (apply-atomic (car S-expression) (cdr S-expression) a-list))

¢
\protect \pagebreak  [3]
¢
(defun apply-atomic (atomic actuals a-list)
  (cond ((eq 'cond atomic) ; special case: cond has normal semantics
            (evaluate-cond actuals a-list)) ; don't evaluate actuals
        (t (apply-eager-atomic ; all other atomics are eager
              atomic
              (evaluate-list actuals a-list)
              a-list)))|)

¢
\protect \pagebreak  [3]
¢
(defun evaluate-cond(test-forms a-list)
  (cond ((null test-forms) nil) ; if no more test-forms, return nil
        ((evaluate (car (car test-forms)) a-list) ; evaluate condition part of the first test-form
        (evaluate (car (cdr (car test-forms)) a-list))) ; if true, evaluate value part (second part) of the first test-form
        (t (evaluate-cond (cdr test-forms) a-list)))) ; otherwise, recurse on rest of test-forms

¢
\protect \pagebreak  [3]
¢
(defun apply-eager-atomic (atomic actuals a-list)
  (cond
    ((eq atomic 'error) (error actuals))
    ((eq atomic 'eval) (evaluate (car actuals) a-list))
    (t (apply-trivial-atomic
        atomic ; one of ¢\tt atom¢, car, cdr, cons, eq, set
        (car actuals); first actual parameter
        (car (cdr actuals)))))) ; second actual parameter, could be nil

¢
\protect \pagebreak  [3]
¢
(defun apply-trivial-atomic (atomic first second)
  (cond ((eq atomic 'atom) (atom first))
        ((eq atomic 'car) (car first))
        ((eq atomic 'cdr) (cdr first))
        ((eq atomic 'cons) (cons first second))
        ((eq atomic 'eq) (eq first second))
        ((eq atomic 'set) (set first second))
        (t (error 'something-went-wrong atomic))))

¢
\protect \pagebreak  [3]
¢
#endif
