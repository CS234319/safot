#include "S.h"
#undef NULL
extern const S NIL;



extern const S 
/* Elementary: */ NIL, T, 
/* Primitives */
/*   Unary   */ ATOM, CAR, CDR, COND, 
/*   Binary  */ CONS, EQ, 
/* Add-ons */   EVAL, ERROR, SET, 
/* Library */
/*   Unary:    */ NULL, QUOTE,
/*   Ternary:  */ DEFUN, NDEFUN, LAMBDA, NLAMBDA,
/* Backdoor */ GLOBALS, RESET 
;
// Stack trace:
extern const S RECURSE;
// Arguments to natives 
extern const S __0, __1, __2, __3;
