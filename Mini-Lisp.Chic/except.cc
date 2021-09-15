#include "except.h"
#include "print.h"
#include "a-list.h"
#include "mode.h"

/** Assertions like */
extern bool die(Pair p) { 
  err(), print("Error "), print(p.cdr), print(" on "), println(p.car), out();
  stack_dump();
  throw p;
}

extern bool die(S s) { 
  D(s);
  err(); 
  print("Error "), println(s), out(),out();
  stack_dump(); 
  throw s;
}

/** List of all exceptions that may be thrown during evaluation */
const S UNDEFINED_ATOM("Undefined atom"); 
const S MISSING_ARGUMENT("Missing arguments(s)"); 
const S REDUNDANT_ARGUMENT("Redundant argument(s)"); 
const S BAD_FUNCTION("Bad function structure"); 
const S BAD_ARGUMENTS("Bad arguments list"); 
const S BAD_PARAMETERS("Bad parameters list"); 

/** Exceptions raised in response to resource failures */
const S MEMORY_CONS("Computation exhausted the pool of CONS records");
const S MEMORY_ATOM("Computation exhausted the buffer allocated for ATOMS");

/** Exceptions raised in response to bugs detected at run time*/
extern const S STACK_UNDERFLOW("Bug: popping from an empty stack");
