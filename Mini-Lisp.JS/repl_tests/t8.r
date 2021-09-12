(LAMBDA (XS F INIT) (COND ((NULL XS) INIT) (T (F (CAR XS) (REDUCE (CDR XS) F INIT)))))
(LAMBDA (XS F) (REDUCE XS (LAMBDA (X Y) (CONS (F X) Y)) NIL))
(A C); Still need to decide if this is the behavior we want,
	 ; but the current is surely not coherent.
