/* A set of utility functions which make it possible to write the engine without nitty gritty details */
#import "S.h"

extern const S __0, __1, __2, __3, __00, __12, __123;
inline bool exists(S x, S xs) { return !xs.null() && (xs.car().eq(x) || exists(x, xs.cdr())); } 
inline bool islist(S s) { return s.null() || !s.atom() && islist(s.cdr()); }
inline S pair(S car, S cdr) { return car.cons(cdr); }
inline S list() { return NIL0; }
inline S list(S s) { return s.cons(list()); }
inline S list(S a, S b) { return a.cons(list(b)); }
inline S list(S a, S b, S c) { return a.cons(list(b, c)); }
inline S list(S a, S b, S c, S d) { return a.cons(list(b, c, d)); }
inline S list(S a, S b, S c, S d, S e) { return a.cons(list(b, c, d, e)); }
inline S list(S a, S b, S c, S d, S e, S f) {
  return a.cons(list(b, c, d, e, f)); }
inline S list(S a, S b, S c, S d, S e, S f, S g) {
  return a.cons(list(b, c, d, e, f, g)); }
inline S list(S a, S b, S c, S d, S e, S f, S g, S h) {
  return a.cons(list(b, c, d, e, f, g, h)); }
inline S list(S a, S b, S c, S d, S e, S f, S g, S h, S i) {
  return a.cons(list(b, c, d, e, f, g, h, i)); }
inline S list(S a, S b, S c, S d, S e, S f, S g, S h, S i, S j) {
  return a.cons(list(b, c, d, e, f, g, h, i, j)); }
inline S list(S a, S b, S c, S d, S e, S f, S g, S h, S i, S j, S k) {
    return a.cons(list(b, c, d, e, f, g, h, i, j, k)); }
inline S list(S a, S b, S c, S d, S e, S f, S g, S h, S i, S j, S k, S l) {
    return a.cons(list(b, c, d, e, f, g, h, i, j, k, l)); }
inline S list(S a, S b, S c, S d, S e, S f, S g, S h, S i, S j, S k, S l, S m) {
    return a.cons(list(b, c, d, e, f, g, h, i, j, k, l, m)); }
inline S list(S a, S b, S c, S d, S e, S f, S g, S h, S i, S j, S k, S l, S m, S n) {
    return a.cons(list(b, c, d, e, f, g, h, i, j, k, l, m, n)); }
inline S list(S a, S b, S c, S d, S e, S f, S g, S h, S i, S j, S k, S l, S m, S n, S o) {
    return a.cons(list(b, c, d, e, f, g, h, i, j, k, l, m, n, o)); }
inline S list(S a, S b, S c, S d, S e, S f, S g, S h, S i, S j, S k, S l, S m, S n, S o, S p) {
    return a.cons(list(b, c, d, e, f, g, h, i, j, k, l, m, n, o, p)); }
inline S list(S a, S b, S c, S d, S e, S f, S g, S h, S i, S j, S k, S l, S m, S n, S o, S p, S q) {
    return a.cons(list(b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q)); }
