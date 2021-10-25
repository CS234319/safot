#import  "except.h"
#import  "print.h"
#import  "a-list.h"
#import  "mode.h"

/** Assertions like */
extern bool die(Pair p) { 
  err(), print("Error "), print(p.cdr), print(" on "), println(p.car), out();
  Dump::calls(); 
  Engine::clear();
  throw p;
}

extern bool die(S s) { 
  D(s);
  err(); 
  print("Error "), println(s), out();
  Dump::calls(); 
  Engine::clear();
  throw s;
}

/** List of all exceptions that may be thrown during evaluation */
const S UNDEFINED_ATOM("Undefined atom"); 
const S MISSING_ARGUMENT("Too few argument(s)"); 
const S REDUNDANT_ARGUMENT("Redundant argument(s)"); 
const S BAD_FUNCTION("Bad function structure"); 
const S BAD_ARGUMENTS("Arguments are not a list"); 
const S BAD_PARAMETERS("Parameters are not a list");

/** Exceptions raised in response to resource failures */
const S MEMORY_CONS("drained cons records' pool");
const S MEMORY_ATOM("drained atom buffer");

/** Exceptions raised in response to bugs detected at run time*/
extern const S STACK_UNDERFLOW("Bug: popping from an empty stack");
