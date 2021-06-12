#ifndef BASICS_H
#define BASICS_H
#include "00.h"

inline bool exists(S x, S xs) { return !xs.null() && (xs.car().eq(x) || exists(x, xs.cdr())); } 
inline bool islist(S s) { return s.null() || !s.atom() && islist(s.cdr()); }
inline S list() { return NIL; }
inline S list(S s) { return s.cons(list()); }
inline S list(S s1, S s2) { return s1.cons(list(s2)); }
inline S list(S s1, S s2, S s3) { return s1.cons(list(s2, s3)); }
inline S list(S s1, S s2, S s3, S s4) { return s1.cons(list(s2, s3, s4)); }
inline S list(S s1, S s2, S s3, S s4, S s5) { return s1.cons(list(s2, s3, s4, s5)); }
inline S list(S s1, S s2, S s3, S s4, S s5, S s6) {
  return s1.cons(list(s2, s3, s4, s5, s6)); }
inline S list(S s1, S s2, S s3, S s4, S s5, S s6, S s7) {
  return s1.cons(list(s2, s3, s4, s5, s6, s7)); }
inline S list(S s1, S s2, S s3, S s4, S s5, S s6, S s7, S s8) {
  return s1.cons(list(s2, s3, s4, s5, s6, s7, s8)); }
inline S list(S s1, S s2, S s3, S s4, S s5, S s6, S s7, S s8, S s9) {
  return s1.cons(list(s2, s3, s4, s5, s6, s7, s8, s9)); }
inline S list(S s1, S s2, S s3, S s4, S s5, S s6, S s7, S s8, S s9, S s10) {
  return s1.cons(list(s2, s3, s4, s5, s6, s7, s8, s9, s10)); }
inline S list(S s1, S s2, S s3, S s4, S s5, S s6, S s7, S s8, S s9, S s10, S s11) {
  return s1.cons(list(s2, s3, s4, s5, s6, s7, s8, s9, s10, s11)); }
#endif 
