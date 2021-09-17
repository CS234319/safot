#import "atoms.h"

#define _(T) T(#T)
/* Primitives */
const S _(NIL), _(T); 
const S _(ATOM), _(CAR), _(CDR), _(COND);
const S _(CONS), _(EQ);   
/* Auxiliary */ 
const S  _(ERROR), _(EVAL), _(SET);
/* Library */
const S _(NDEFUN), _(DEFUN), _(NLAMBDA), _(LAMBDA), _(QUOTE), _(NULL);
// Stack trace:
const S _(RECURSE);

// Arguments to natives 
const S __0(".."), __1("1.."), __2("2.."), __3("3..");
