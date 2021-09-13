(set 'append (lambda (x xs)
		(cond ((null xs) (cons x nil))
				(t (cons (car xs) (append x (cdr xs)))))))
(append (car '(c d)) '(a b))
(append 'a)
(append 'a 'b 'c)) ;Should be rejected