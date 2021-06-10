#include "basics.h"
bool exists(S x, S xs) { return !xs.null() && (xs.car().eq(x) || exists(x, xs.cdr())); } 
bool islist(S s) { return s.null() || !s.atom() && islist(s.cdr()); }
S list() { return NIL; }
S list(S s) { return s.cons(list()); }
S list(S s1, S s2) { return s1.cons(list(s2)); }
S list(S s1, S s2, S s3) { return s1.cons(list(s2, s3)); }
S list(S s1, S s2, S s3, S s4) { return s1.cons(list(s2, s3, s4)); }
S list(S s1, S s2, S s3, S s4, S s5) { return s1.cons(list(s2, s3, s4, s5)); }
S list(S s1, S s2, S s3, S s4, S s5, S s6) {
  return s1.cons(list(s2, s3, s4, s5, s6)); }
S list(S s1, S s2, S s3, S s4, S s5, S s6, S s7) {
  return s1.cons(list(s2, s3, s4, s5, s6, s7)); }
S list(S s1, S s2, S s3, S s4, S s5, S s6, S s7, S s8) {
  return s1.cons(list(s2, s3, s4, s5, s6, s7, s8)); }
S list(S s1, S s2, S s3, S s4, S s5, S s6, S s7, S s8, S s9) {
  return s1.cons(list(s2, s3, s4, s5, s6, s7, s8, s9)); }
S list(S s1, S s2, S s3, S s4, S s5, S s6, S s7, S s8, S s9, S s10) {
  return s1.cons(list(s2, s3, s4, s5, s6, s7, s8, s9, s10)); }
S list(S s1, S s2, S s3, S s4, S s5, S s6, S s7, S s8, S s9, S s10, S s11) {
  return s1.cons(list(s2, s3, s4, s5, s6, s7, s8, s9, s10, S s11)); }
