(set 'num_list '(20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1))
(set 'lengths_list '(0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19))

((lambda (xs)
	(cond 	((null xs) t)
			(t (cdr 
				(cons 
					(set (car xs) xs) 
					(recurse (cdr xs))))))) num_list)

(defun length_aux (xs ys) 
	(cond 	((null xs) (car ys))
			(t (length_aux (cdr xs) (cdr ys)))))

(defun length (xs) (length_aux xs lengths_list))

(defun concat (x y) 
	(cond 	((null x) y)
			(t (concat (cdr x) (cons (car x) y)))))

(defun + (x y) (length (concat x y)))

(+ 3 5)
(+ 5 3)
(+ 1 2)

(defun subtract (x y) 
	(cond 	((null y) x)
			(t (subtract (cdr x) (cdr y)))))

(defun - (x y) (length (subtract x y)))

(- 15 7)
(- 7 15)
