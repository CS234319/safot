(defun reduce (xs f init)
	(cond 	((null xs) init)
			(t (f (car xs) (reduce (cdr xs) f init)))))

(defun map (xs g) (reduce xs (lambda (x y) (cons (g x) y)) nil))

(map '([a . b] [c . d]) (lambda (x) (car x)))