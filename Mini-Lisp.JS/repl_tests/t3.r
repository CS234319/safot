(LAMBDA (X XS) (COND ((NULL XS) (CONS X NIL)) (T (CONS (CAR XS) (APPEND X (CDR XS))))))
(A B C)
Traceback (most recent call last):
	APPEND[^(QUOTE A)]
	** Error MISSING in ((LAMBDA (X XS) (COND ((NULL XS) (CONS X NIL)) (T (CONS (CAR XS) (APPEND X (CDR XS)))))) (QUOTE A))
?
