#include "S.h"
#undef NULL
extern const S 
/* Primitives */
/*   Unary   */ ATOM, CAR, CDR, COND, 
/*   Binary  */ CONS, EQ, 
/* Add-ons */   EVAL, ERROR, SET, 
/* Library */
/*   Variables */ NIL, T, 
/*   Unary:    */ NULL, QUOTE,
/*   Ternary:  */ DEFUN, NDEFUN, LAMBDA, NLAMBDA
;
// Stack trace:
extern const S RECURSE;
// Arguments to natives 
extern const S __0, __1, __2, __3;
