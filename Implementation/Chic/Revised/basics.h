/* A set of utility functions which make it possible to write the engine without nitty gritty details */
#import "S.cc"

#define Sugar(X) inline auto X 

extern const S __0, __1, __2, __3, __00, __12, __123;
inline bool exists(S x, S xs) is(!xs.null() and (xs.car().eq(x) or exists(x, xs.cdr())))
inline bool islist(S s) is(s.null() || !s.atom() and islist(s.cdr()))
Sugar(list) from() is(S())
Sugar(list) from(S a) is(S(a,list()))
Sugar(list) from(S a, S b) is(S(a,list(b)))
Sugar(list) from(S a, S b, S c) is(S(a,list(b, c)))
Sugar(list) from(S a, S b, S c, S d) is(S(a,list(b, c, d)))
Sugar(list) from(S a, S b, S c, S d, S e) is(S(a,list(b, c, d, e)))
Sugar(list) from(S a, S b, S c, S d, S e, S f) is(S(a,list(b, c, d, e, f)))
Sugar(list) from(S a, S b, S c, S d, S e, S f, S g) is(S(a,list(b, c, d, e, f, g)))
Sugar(list) from(S a, S b, S c, S d, S e, S f, S g, S h) is(S(a,list(b, c, d, e, f, g, h)))
Sugar(list) from(S a, S b, S c, S d, S e, S f, S g, S h, S i) is(S(a,list(b, c, d, e, f, g, h, i)))
Sugar(list) from(S a, S b, S c, S d, S e, S f, S g, S h, S i, S j) is(S(a,list(b, c, d, e, f, g, h, i, j)))
Sugar(list) from(S a, S b, S c, S d, S e, S f, S g, S h, S i, S j, S k) is(S(a,list(b, c, d, e, f, g, h, i, j, k)))
Sugar(list) from(S a, S b, S c, S d, S e, S f, S g, S h, S i, S j, S k, S l) is(S(a,list(b, c, d, e, f, g, h, i, j, k, l)))
Sugar(list) from(S a, S b, S c, S d, S e, S f, S g, S h, S i, S j, S k, S l, S m) is(S(a,list(b, c, d, e, f, g, h, i, j, k, l, m)))
Sugar(list) from(S a, S b, S c, S d, S e, S f, S g, S h, S i, S j, S k, S l, S m, S n) is(S(a,list(b, c, d, e, f, g, h, i, j, k, l, m, n)))
Sugar(list) from(S a, S b, S c, S d, S e, S f, S g, S h, S i, S j, S k, S l, S m, S n, S o) is(S(a,list(b, c, d, e, f, g, h, i, j, k, l, m, n, o)))
Sugar(list) from(S a, S b, S c, S d, S e, S f, S g, S h, S i, S j, S k, S l, S m, S n, S o, S p) is(S(a,list(b, c, d, e, f, g, h, i, j, k, l, m, n, o, p)))
Sugar(list) from(S a, S b, S c, S d, S e, S f, S g, S h, S i, S j, S k, S l, S m, S n, S o, S p, S q) is(S(a,list(b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q)))
Sugar(list) from(S a, S b, S c, S d, S e, S f, S g, S h, S i, S j, S k, S l, S m, S n, S o, S p, S q, S r) is(S(a,list(b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r)))
Sugar(list) from(S a, S b, S c, S d, S e, S f, S g, S h, S i, S j, S k, S l, S m, S n, S o, S p, S q, S r, S s) is(S(a,list(b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s)))
Sugar(list) from(S a, S b, S c, S d, S e, S f, S g, S h, S i, S j, S k, S l, S m, S n, S o, S p, S q, S r, S s, S t) is(S(a,list(b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t)))
