#ifndef SX_H
#define SX_H
#include "chic.h"
#include "Handle.h"

Type Sx: private Handle { // An S-expression represented by its handle
  using Handle::inner;
  Sx(Short)      ;
  Sx(Handle)     ;
  Sx(Sx, Sx) ;
  Sx(Text t);

  Sx cons(Sx cdr) const { return Sx(*this, cdr); }
};

#undef NULL
// Fluenton sources of Names of atoms that represent atomic functions 
extern const Sx NIL, T; //
extern const Sx CAR, CDR, CONS;
extern const Sx ATOM, EQ, NE, NULL, COND;
extern const Sx QUOTE, EVAL;
extern const Sx DEFUN, NDEFUN; 
extern const Sx ERROR, SET;

// Named atoms for exceptions; for the idiom error(MISSING) to abort execution
// on the case an error of kind MISSING is found in the context of the S
// expression named s.
extern const Sx MISSING, REDUNDANT, UNDEFINED, INVALID, BUG, EMPTY, EXHAUSTED;

/*
  property Cons $_p$(); /// Interpreted as handle of Cons, retrieves the Cons behind (mutable)  
  property Atom $_a$(); /// Interpreted as handle of atom, retrieves its text representation 
*/
#endif
