(defun exists (x xs)
                 (cond
                    ((null xs) xs)
                    ((eq x (car xs)) t)
                    (t (exists x (cdr xs)))
                 )
)

(defun id (x) x)
