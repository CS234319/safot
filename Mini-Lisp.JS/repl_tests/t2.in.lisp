(cond ((eq 'a 'a) '(a b c)) ((set 'a 'c) '(a a a)))
(eval 'a)