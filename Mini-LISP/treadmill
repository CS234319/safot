(defun apply-atomic (atomic actuals a-list)
  (cond ((eq 'cond atomic) ; special case: cond has normal semantics
            (evaluate-cond actuals a-list)) ; don't evaluate actuals
        (t (apply-eager-atomic ; all other atomics are eager
              atomic
              (evaluate-list actuals a-list)
              a-list)))|)
(defun evaluate-cond(test-forms a-list)
  (cond ((null test-forms) nil) ; if no more test-forms, return nil
        ((evaluate (car (car test-forms)) a-list) ; evaluate condition part of the first test-form
        (evaluate (car (cdr (car test-forms)) a-list))) ; if true, evaluate value part (second part) of the first test-form
        (t (evaluate-cond (cdr test-forms) a-list)))) ; otherwise, recurse on rest of test-forms
(defun apply-eager-atomic (atomic actuals a-list)
  (cond
    ((eq atomic 'error) (error actuals))
    ((eq atomic 'eval) (evaluate (car actuals) a-list))
    (t (apply-trivial-atomic
        atomic ; one of ¢\tt atom¢, car, cdr, cons, eq, set
        (car actuals); first actual parameter
        (car (cdr actuals)))))) ; second actual parameter, could be nil
(defun apply-trivial-atomic (atomic first second)
  (cond ((eq atomic 'atom) (atom first))
        ((eq atomic 'car) (car first))
        ((eq atomic 'cdr) (cdr first))
        ((eq atomic 'cons) (cons first second))
        ((eq atomic 'eq) (eq first second))
        ((eq atomic 'set) (set first second))
        (t (error 'something-went-wrong atomic))))
(defun is-atomic(name); determine whether name denotes an atomic function
  (exists name '(atom car cdr cond cons eq error eval set)))
(defun exists (x xs) ; determine whether atom x is in list xs
  (cond ; Three cases to consider:
    ((null xs) xs) ; (i) list of xs is exhausted
    ((eq x (car xs)) t) ; (ii) item x is first in xs
    (t (exists x (cdr xs))))) ; (iii) otherwise, recurse on rest of xs
(defun lookup (id a-list) ; lookup id in an a-list
  (cond ; Three cases to consider:
    ((null a-list) ; (i) a-list was exhausted.
      (error 'unbound-variable id))
    ((eq id (car (car a-list))) ; (ii) found in first dotted-pair
      (car (cdr (car a-list)))) ; return value part of dotted pair
    (t (lookup id (cdr a-list))))) ; (iii) otherwise, recursive call on remainder of a-list
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
(defun evaluate(S-expression a-list) ; evaluate S-expression in the environment defined by a-list
  (cond ((atom S-expression) ; recursion base: lookup of atom in a-list
          (lookup S-expression a-list))
        ((is-atomic (car S-expression)) ; case of handling atomic functions
          (evaluate-atomic S-expression a-list))
        (t ; recursive step---lambda applied to parameters
          (apply (evaluate (car S-expression) a-list) ; find lambda expression
                  (cdr S-expression) ; find actual parameters
                  a-list))))
(defun apply(lambda-expression actuals a-list)
  (apply-decomposed-lambda
    (car lambda-expression) ; tag=lambda or nlambda
    (car (cdr lambda-expression)); list of formal parameters
    (car (cdr (cdr lambda-expression))); body
    actuals
    a-list))
(defun apply-decompsed-lambda(tag formals body actuals a-list)
  (evaluate body
    (cond ((eq tag 'nlambda) (bind formals actuals a-list))
          ((eq tag 'lambda) (bind formals (evaluate-list actuals a-list) a-list))
          (t (error 'unkown-lambda tag))
)))
(defun evaluate-list(S-expressions a-list)
  (cond ((null S-expressions) nil) ; no more S-expressions to evaluate
    (t (cons
          (evaluate (car S-expressions) a-list) ; evaluate first S-Expression
          (evaluate-list (cdr S-expressions) a-list))))) ; recursive call on remainder
(defun evaluate-atomic (S-expression a-list)
  (apply-atomic (car S-expression) (cdr S-expression) a-list))
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
    (cond ((eq tag 'nlambda) (bind formals actuals a-list))
          ((eq tag 'lambda) (bind formals (evaluate-list actuals a-list) a-list))
          (t (error 'unkown-lambda tag))
)))

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
(set (quote t) (quote t))
(set (quote nil) (quote nil))
(defun null(x) (eq x nil))
(set 'quote '(nlambda (x) x))
(set 'lambda '(nlambda (parameters body) ('lambda parameters body)))
(set 'nlambda '(nlambda (parameters body) ('nlambda parameters body)))
(set 'defun '(nlambda (name parameters body)
  (set name (lambda parameters body))))
(set 'ndefun '(nlambda (name parameters body)
    (set name (nlambda parameters body))))
(set (quote t) (quote t))
(set (quote nil) (quote nil))

(defun null(x) (eq x nil))

(set 'quote '(nlambda (x) x))

(set 'lambda '(nlambda (parameters body) ('lambda parameters body)))

(set 'nlambda '(nlambda (parameters body) ('nlambda parameters body)))

(set 'defun '(nlambda (name parameters body)
  (set name (lambda parameters body))))

(set 'ndefun '(nlambda (name parameters body)
    (set name (nlambda parameters body))))

(defun apply-atomic (atomic actuals a-list)
  (cond ((eq 'cond atomic) ; special case: cond has normal semantics
            (evaluate-cond actuals a-list)) ; don't evaluate actuals
        (t (apply-eager-atomic ; all other atomics are eager
              atomic
              (evaluate-list actuals a-list)
              a-list)))|)
(defun evaluate-cond(test-forms a-list)
  (cond ((null test-forms) nil) ; if no more test-forms, return nil
        ((evaluate (car (car test-forms)) a-list) ; evaluate condition part of the first test-form
        (evaluate (car (cdr (car test-forms)) a-list))) ; if true, evaluate value part (second part) of the first test-form
        (t (evaluate-cond (cdr test-forms) a-list)))) ; otherwise, recurse on rest of test-forms
(defun apply-eager-atomic (atomic actuals a-list)
  (cond
    ((eq atomic 'error) (error actuals))
    ((eq atomic 'eval) (evaluate (car actuals) a-list))
    (t (apply-trivial-atomic
        atomic ; one of ¢\tt atom¢, car, cdr, cons, eq, set
        (car actuals); first actual parameter
        (car (cdr actuals)))))) ; second actual parameter, could be nil
(defun apply-trivial-atomic (atomic first second)
  (cond ((eq atomic 'atom) (atom first))
        ((eq atomic 'car) (car first))
        ((eq atomic 'cdr) (cdr first))
        ((eq atomic 'cons) (cons first second))
        ((eq atomic 'eq) (eq first second))
        ((eq atomic 'set) (set first second))
        (t (error 'something-went-wrong atomic))))
(defun is-atomic(name); determine whether name denotes an atomic function
  (exists name '(atom car cdr cond cons eq error eval set)))
(defun exists (x xs) ; determine whether atom x is in list xs
  (cond ; Three cases to consider:
    ((null xs) xs) ; (i) list of xs is exhausted
    ((eq x (car xs)) t) ; (ii) item x is first in xs
    (t (exists x (cdr xs))))) ; (iii) otherwise, recurse on rest of xs
(defun lookup (id a-list) ; lookup id in an a-list
  (cond ; Three cases to consider:
    ((null a-list) ; (i) a-list was exhausted.
      (error 'unbound-variable id))
    ((eq id (car (car a-list))) ; (ii) found in first dotted-pair
      (car (cdr (car a-list)))) ; return value part of dotted pair
    (t (lookup id (cdr a-list))))) ; (iii) otherwise, recursive call on remainder of a-list
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
(defun evaluate(S-expression a-list) ; evaluate S-expression in the environment defined by a-list
  (cond ((atom S-expression) ; recursion base: lookup of atom in a-list
          (lookup S-expression a-list))
        ((is-atomic (car S-expression)) ; case of handling atomic functions
          (evaluate-atomic S-expression a-list))
        (t ; recursive step---lambda applied to parameters
          (apply (evaluate (car S-expression) a-list) ; find lambda expression
                  (cdr S-expression) ; find actual parameters
                  a-list))))
(defun apply(lambda-expression actuals a-list)
  (apply-decomposed-lambda
    (car lambda-expression) ; tag=lambda or nlambda
    (car (cdr lambda-expression)); list of formal parameters
    (car (cdr (cdr lambda-expression))); body
    actuals
    a-list))
(defun apply-decompsed-lambda(tag formals body actuals a-list)
  (evaluate body
    (cond ((eq tag 'nlambda) (bind formals actuals a-list))
          ((eq tag 'lambda) (bind formals (evaluate-list actuals a-list) a-list))
          (t (error 'unkown-lambda tag))
)))
(defun evaluate-list(S-expressions a-list)
  (cond ((null S-expressions) nil) ; no more S-expressions to evaluate
    (t (cons
          (evaluate (car S-expressions) a-list) ; evaluate first S-Expression
          (evaluate-list (cdr S-expressions) a-list))))) ; recursive call on remainder
(defun evaluate-atomic (S-expression a-list)
  (apply-atomic (car S-expression) (cdr S-expression) a-list))
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
    (cond ((eq tag 'nlambda) (bind formals actuals a-list))
          ((eq tag 'lambda) (bind formals (evaluate-list actuals a-list) a-list))
          (t (error 'unkown-lambda tag))
)))

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
(set (quote t) (quote t))
(set (quote nil) (quote nil))
(defun null(x) (eq x nil))
(set 'quote
  '(nlambda (x) x))
(set 'lambda
  '(nlambda (parameters-list body) ('lambda parameters-list body)))
(set 'nlambda
  '(nlambda (parameters-list body) ('nlambda parameters-list body)))
(set 'defun
  '(nlambda (name parameters body)
    (set name (lambda parameters body))))
(set 'ndefun
  '(nlambda (name parameters body)
    (set name (nlambda parameters body))))
(set (quote t) (quote t))
(set (quote nil) (quote nil))

(defun null(x) (eq x nil))

(set 'quote
  '(nlambda (x) x))

(set 'lambda
  '(nlambda (parameters-list body) ('lambda parameters-list body)))

(set 'nlambda
  '(nlambda (parameters-list body) ('nlambda parameters-list body)))

(set 'defun
  '(nlambda (name parameters body)
    (set name (lambda parameters body))))

(set 'ndefun
  '(nlambda (name parameters body)
    (set name (nlambda parameters body))))

