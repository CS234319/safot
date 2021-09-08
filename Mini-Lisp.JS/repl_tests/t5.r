(LAMBDA (X XS) (COND ((NULL XS) (CONS X NIL)) (T (CONS (CAR XS) (RECURSE X (CDR XS))))))
Traceback (most recent call last):
	APPEND[^(CAR (QUOTE C)), (QUOTE (A B))]
	CAR[C]
	** Error CAR in C
Traceback (most recent call last):
	APPEND[C, ^(CAR (QUOTE A))]
	CAR[A]
	** Error CAR in A
