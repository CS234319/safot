// An implementation of mini-lisp in mini-C++
//
#include "mini-lisp.hh"
#include "dump.h"
#include <iostream>

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

auto operator , (const S s1, const S s2) { 
  D(s1,s2);
  D(s1.islist(),s2.islist());
  if (s2.islist())
    return s1.cons(s2); 
  return list(s1,s2); 
}

auto operator , (const S s1, String s2) { 
  return (s1, S(s2));
}

auto operator , (String s1, const S s2) { 
  return (S(s1), s2);
}

std::ostream& operator<<(std::ostream& os, Pair p) {
   return os << "[" << p.car << "." << p.cdr << "]";
}

std::ostream& operator<<(std::ostream& os, S s) {
  if (s.null())
    return os << "nil";
  if (s.atom())
    return os << s.asAtom();
  if (!islist(s)) 
    return os << "(" << car(s) << "." << cdr(s) << ")";
  os << "(" ;
  for (;;) {
    os << S(s.car()); 
    if ((s = s.cdr()).null())
      break;
    os << " ";
  }
  return os << ")";
}

namespace Pairs {
  define(M = (1 << 15) - 1)
  static Pair buffer[M];
  Pair *const pool = buffer - 1;

  static H init() {
    for (H h = 1; h < M; ++h)
      pool[h].next = h + 1;
    pool[M].next = 0;
    return 1;
  }

  static H available = init();

  H allocate(H car, H cdr) {
    D(available, car,cdr);
    normally(available != 0);
    const H $ = available;
    available = pool[available].next;
    pool[$].car = car;
    pool[$].cdr = cdr;
    D($,pool[$].car,pool[$].cdr, S($), S(pool[$].car), S(pool[$].cdr));
    return $;
  }
  void free(H h) {
    pool[h].next = available;
    available = h;
  }
}

namespace Strings { // Atoms are never freed in mini-lisp
  define(M = 1024);
  char buffer[M] = "BOTTOM";
  char nil[] = "NIL"; 
  const char *const pool = nil;
  static H current = 0;
  static H size(String s) {
    for (H $ = 0;; ++$)
      if (s[$] == '\0')
        return $ + 1;
  }
  char upper(char c)  { return c < 'a' || c > 'z' ? c : c - 'a' + 'A';}

  bool eq(const char *s1, const char *s2) {
    for (; upper(*s1) == upper(*s2); ++s1, ++s2)
      if (*s1 == '\0')
        return true;
    return false;
  }

  H allocate(String s) {
    D(s, size(s), current, (long) buffer, (long) pool, pool-buffer);
    for (const char *p = pool + current; p <= pool; ++p)
      if (eq(s,p))  
        return  (D(s, p - pool)), p - pool;
    const H n = size(s);
    D(s, size(s), n);
    current -= n;
    normally(current < 0);
    normally(pool + current >= buffer);

    for (H h = 0; h < n; ++h) // Only case in code to change the pool 
      const_cast<char &>(pool[current + h]) = upper(s[h]);
    D(s, pool + current, current);
    return current;
  }
}

bool eq(S s1, S s2) {
  D(s1,s2);
  if (not (s1.atom()) or not (s2.atom()))
    return false;
  if (s1.index == s2.index)
    return true;
  using namespace Strings;
  D(pool + s1.index, pool + s2.index);
  return eq(pool + s1.index, pool + s2.index);
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
  if (eq(id,alist.car().car()))
    return alist.car().cdr();
  return lookup(id, alist.cdr());
}

S lookup(S s) {
  return lookup(s,alist);
} 


const S NIL(set(S("NIL"), S())); // (set (quote nil) (quote nil))
const S T(set(S("T"), S("T")));  // (set (quote t) (quote t))

S cons(S car, S cdr) { return S(car, cdr); }
S list() { return NIL; }
S list(S s) { return cons(s, NIL); } 
S list(S s1, S s2) { return cons(s1, list(s2)); }
S list(S s1, S s2, S s3) { return cons(s1, list(s2, s3)); }
S list(S s1, S s2, S s3, S s4) { return cons(s1, list(s2, s3, s4)); }
S list(S s1, S s2, S s3, S s4, S s5) { return cons(s1, list(s2, s3, s4, s5)); }
S list(S s1, S s2, S s3, S s4, S s5, S s6) { return cons(s1, list(s2, s3, s4, s5, s6)); }
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

static const S atomic_functions = list( "atom", "car", "cdr",
    "cond","cons","eq", "error","eval", "set");

bool atomic(S name) { // determine whether name denotes an atomic function
  return exists(name,atomic_functions);
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

#if 0
  (cond ((atom S-expression) ; recursion base: lookup of atom in a-list
          (lookup S-expression a-list))
        ((is-atomic (car S-expression)) ; case of handling atomic functions
          (evaluate-atomic S-expression a-list))
        (t ; recursive step---lambda applied to parameters
          (apply (evaluate (car S-expression) a-list) ; find lambda expression
                  (cdr S-expression) ; find actual parameters
                  a-list))))


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

(defun is-atomic(name); determine whether name denotes an atomic function
  (exists name '(atom car cdr cond cons eq error eval set)))

¢
\protect \pagebreak  [3]
¢
(defun exists (x xs) ; determine whether atom x is in list xs
  (cond ; Three cases to consider:
    ((null xs) xs) ; (i) list of xs is exhausted
    ((eq x (car xs)) t) ; (ii) item x is first in xs
    (t (exists x (cdr xs))))) ; (iii) otherwise, recurse on rest of xs

¢
\protect \pagebreak  [3]
¢
(defun lookup (id a-list) ; lookup id in an a-list
  (cond ; Three cases to consider:
    ((null a-list) ; (i) a-list was exhausted.
      (error 'unbound-variable id))
    ((eq id (car (car a-list))) ; (ii) found in first dotted-pair
      (car (cdr (car a-list)))) ; return value part of dotted pair
    (t (lookup id (cdr a-list))))) ; (iii) otherwise, recursive call on remainder of a-list

¢
\protect \pagebreak  [3]
¢
(defun bind (names values a-list) ; bind names to values, and append to a-list
  (cond ((null names) ; no more names left
        (cond ((null values) a-list) ; no more values left, binding done-> return a-list
              (t (error 'missing-names)))) ; more values than names
        ((null values) ; names is not nil but values is, i.e., more names than values
          (error 'missing-values))
        (t ; both names and values are not empty
          (cons ; create new binding and prepend it to result of recursive call
            (cons (car names) (car values)) ; new dotted-pair defines single binding
            (bind (cdr names) (cdr values) a-list))))) ; recursive call

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
