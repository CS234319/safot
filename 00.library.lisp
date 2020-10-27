(set (quote t) (quote t))
(set (quote nil) (quote nil))

(defun null(x) (eq x nil))

(set 'quote
  '(nlambda (x) x))

(set 'lambda
  '(nlambda (parameters-list body) ('lambda parameters body)))

(set 'nlambda
  '(nlambda (parameters-list body) ('nlambda parameters body)))

(set 'defun
  '(nlambda (name parameter-list body)
    (set name (lambda parameter-list body))))

(set 'ndefun
  '(nlambda (name parameter-list body)
    (set name (nlambda parameter-list body))))

