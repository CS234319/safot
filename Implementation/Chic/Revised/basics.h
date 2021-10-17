/* A set of utility functions which make it possible to write the engine without nitty gritty details */
#import "S.h"

extern const S __0, __1, __2, __3, __00, __12, __123;
inline bool exists(S x, S xs) Is(!xs.null() and (xs.car().eq(x) or exists(x, xs.cdr())))
inline bool islist(S s) Is(s.null() || !s.atom() and islist(s.cdr()))
inline S pair(S car, S cdr) Is(S(car,cdr))

inline S list() Is(S())
inline S list(S a) Is(a,list())
inline S list(S a, S b) Is(a,list(b))
inline S list(S a, S b, S c) Is(a,list(b, c))
inline S list(S a, S b, S c, S d) Is(a,list(b, c, d))
inline S list(S a, S b, S c, S d, S e) Is(a,list(b, c, d, e))
inline S list(S a, S b, S c, S d, S e, S f) Is(a,list(b, c, d, e, f))
inline S list(S a, S b, S c, S d, S e, S f, S g) Is(a,list(b, c, d, e, f, g))
inline S list(S a, S b, S c, S d, S e, S f, S g, S h) Is(a,list(b, c, d, e, f, g, h))
inline S list(S a, S b, S c, S d, S e, S f, S g, S h, S i) Is(a,list(b, c, d, e, f, g, h, i))
inline S list(S a, S b, S c, S d, S e, S f, S g, S h, S i, S j) Is(a,list(b, c, d, e, f, g, h, i, j))
inline S list(S a, S b, S c, S d, S e, S f, S g, S h, S i, S j, S k) Is(a,list(b, c, d, e, f, g, h, i, j, k))
inline S list(S a, S b, S c, S d, S e, S f, S g, S h, S i, S j, S k, S l) Is(a,list(b, c, d, e, f, g, h, i, j, k, l))
inline S list(S a, S b, S c, S d, S e, S f, S g, S h, S i, S j, S k, S l, S m) Is(a,list(b, c, d, e, f, g, h, i, j, k, l, m))
inline S list(S a, S b, S c, S d, S e, S f, S g, S h, S i, S j, S k, S l, S m, S n) Is(a,list(b, c, d, e, f, g, h, i, j, k, l, m, n))
inline S list(S a, S b, S c, S d, S e, S f, S g, S h, S i, S j, S k, S l, S m, S n, S o) Is(a,list(b, c, d, e, f, g, h, i, j, k, l, m, n, o))
inline S list(S a, S b, S c, S d, S e, S f, S g, S h, S i, S j, S k, S l, S m, S n, S o, S p) Is(a,list(b, c, d, e, f, g, h, i, j, k, l, m, n, o, p))
inline S list(S a, S b, S c, S d, S e, S f, S g, S h, S i, S j, S k, S l, S m, S n, S o, S p, S q) Is(a,list(b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q))
inline S list(S a, S b, S c, S d, S e, S f, S g, S h, S i, S j, S k, S l, S m, S n, S o, S p, S q, S r) Is(a,list(b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r))
inline S list(S a, S b, S c, S d, S e, S f, S g, S h, S i, S j, S k, S l, S m, S n, S o, S p, S q, S r, S s) Is(a,list(b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s))
inline S list(S a, S b, S c, S d, S e, S f, S g, S h, S i, S j, S k, S l, S m, S n, S o, S p, S q, S r, S s, S t) Is(a,list(b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t))
