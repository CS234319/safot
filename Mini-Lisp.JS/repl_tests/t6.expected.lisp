(20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1)
(0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19)
T
(LAMBDA (XS YS) (COND ((NULL XS) (CAR YS)) (T (LENGTH_AUX (CDR XS) (CDR YS)))))
(LAMBDA (XS) (LENGTH_AUX XS LENGTHS_LIST))
(LAMBDA (X Y) (COND ((NULL X) Y) (T (CONCAT (CDR X) (CONS (CAR X) Y)))))
(LAMBDA (X Y) (LENGTH (CONCAT X Y)))
8
8
3
(LAMBDA (X Y) (COND ((NULL Y) X) (T (SUBTRACT (CDR X) (CDR Y)))))
(LAMBDA (X Y) (LENGTH (SUBTRACT X Y)))
8
Traceback (most recent call last):
	-[(7 6 5 4 3 2 1), (15 14 13 12 11 10 9 8 7 6 5 4 3 2 1)]
	LENGTH[^(SUBTRACT X Y)]
	SUBTRACT[(7 6 5 4 3 2 1), (15 14 13 12 11 10 9 8 7 6 5 4 3 2 1)]
	COND[((NULL Y) X), (T (SUBTRACT (CDR X) (CDR Y)))]
	SUBTRACT[(6 5 4 3 2 1), (14 13 12 11 10 9 8 7 6 5 4 3 2 1)]
	COND[((NULL Y) X), (T (SUBTRACT (CDR X) (CDR Y)))]
	SUBTRACT[(5 4 3 2 1), (13 12 11 10 9 8 7 6 5 4 3 2 1)]
	COND[((NULL Y) X), (T (SUBTRACT (CDR X) (CDR Y)))]
	SUBTRACT[(4 3 2 1), (12 11 10 9 8 7 6 5 4 3 2 1)]
	COND[((NULL Y) X), (T (SUBTRACT (CDR X) (CDR Y)))]
	SUBTRACT[(3 2 1), (11 10 9 8 7 6 5 4 3 2 1)]
	COND[((NULL Y) X), (T (SUBTRACT (CDR X) (CDR Y)))]
	SUBTRACT[(2 1), (10 9 8 7 6 5 4 3 2 1)]
	COND[((NULL Y) X), (T (SUBTRACT (CDR X) (CDR Y)))]
	SUBTRACT[(1), (9 8 7 6 5 4 3 2 1)]
	COND[((NULL Y) X), (T (SUBTRACT (CDR X) (CDR Y)))]
	SUBTRACT[NIL, (8 7 6 5 4 3 2 1)]
	COND[((NULL Y) X), (T (SUBTRACT (CDR X) (CDR Y)))]
	SUBTRACT[^(CDR X), (CDR Y)]
	CDR[NIL]
	** Error CDR in NIL
