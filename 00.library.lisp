(defun null(x) (eq x nil))

(set 'quote
  '(nlambda (x) x))

(set 'lambda
  '(nlambda (parameters-list body) ('lambda parameters-list body)))

(set 'defun
  '(nlambda (name parameter-list body)
    (set name (lambda parameter-list body))))

(set 'ndefun
  '(nlambda (name parameter-list body)
    (set name (nlambda parameter-list body))))

