#import "S.h"

extern bool die(S s);
extern bool die(Pair p);
// Named atoms for exceptions; for the idiom s.error(MISSING_ARGUMENT) to abort
// execution in the case that an error of kind MISSING_ARGUMENT occurs in the context of
// the S expression named s.

// Exceptions that may be thrown during evaluation as a result of errors of the
// client: Use idiom s.error(MISSING_ARGUMENT) to abort execution in the case
// that an error of kind MISSING_ARGUMENT occurs in the context of the S
// expression named s.
/** Thrown if an atom is undefined */ extern const S UNDEFINED_ATOM; 
/** Thrown if an argument is missing in function application */ extern const S MISSING_ARGUMENT; 
/** Thrown in case of redundant argument in function application */ extern const S REDUNDANT_ARGUMENT; 
/** Thrown if parameters are not a list nor an atom */ extern const S BAD_PARAMETERS; 
/** Thrown if arguments are not a list */ extern const S BAD_ARGUMENTS; 
/** Thrown if the function is not a lambda */ extern const S BAD_FUNCTION; 

// Exceptions raised in response to resource failures
/** Thrown if no more cons records are available */ extern const S  MEMORY_CONS;
/** Thrown if the pool of atoms was exhausted */ extern const S   MEMORY_ATOM;

/** Exceptions raised in response to bugs detected at run time*/
extern const S STACK_UNDERFLOW;


extern const S RECURSE;
