(defun reduce (xs f init)
	(cond 	((null xs) init)
			(t (f (car xs) (reduce (cdr xs) f init)))))

(defun map (xs f) (reduce xs (lambda (x y) (cons (f x) y)) nil))

(map '(c . d) (lambda (x) (car x)))