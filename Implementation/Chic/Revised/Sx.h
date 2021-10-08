#import "Handle.h"
Type Sx: private Handle { // An S-expression represented by its handle
  using Handle::handle;
  typedef Sx Self;
  Sx(Short)      ;
  Sx(Handle)     ;
  Sx(Sx, Sx) ;
  Sx(Text t);
  Property(Boolean atom);
  Property(Sx car);
  Property(Sx cdr);
  Type Pair Pair() const;
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
  property Pair $_p$(); /// Interpreted as handle of Pair, retrieves the Pair behind (mutable)  
  property Atom $_a$(); /// Interpreted as handle of atom, retrieves its text representation 
*/
