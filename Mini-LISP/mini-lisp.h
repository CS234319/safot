#include <cstdint>
#include <iostream>
#ifndef MINI_LISP_H
#define MINI_LISP_H 

#include "hacks.h"

// Representation of a dotted pair, i.e., an unlabeled internal node in the
// binary tree behind compound S-expression.
representation Pair { 
  perspective(W cons: 32)
  perspective(H car, cdr :16)
  perspective(H data, next :16)
  perspective(H value, errorCode :16)
};

/** A pool of all pairs is managed by the pairs module (see pairs.cc). The pool
 * is an array; an index into this array, also called a handle, is a half word
 * (type H), and can be thought of as a pointer. All indices are strictly
 * positive.
 */
namespace Pairs {
   extern Pair *const pool;         /* Array of all pair records, free and allocated */
   extern H allocate(H car, H cdr); /* Retrieve a free pair, and set it values */
   extern void free(H handle);       /* Return a pair to the pool */
   extern H to_go();                /* How many pairs are still free */ 
   extern Pair& get(H handle);       /* A convenience method that retrieves a pair by its handle */
};

/** A pool of all strings used by the program  is managed by the strings module
 * (see strings.cc).  Note that unlike pairs, there is no dynamic allocation of
 * strings at run time. All strings are atoms in the input program.  An index
 * into this array, called a handle, is a half word (type H), and can be
 * thought of as a pointer. 
 *
 * Allocation is done
 */
namespace Strings { 
  extern String pool;              // The array of characters.
  extern H allocate(String);       // Allocate a sequence of 
  extern bool eq(String, String);  // Compare two strings equality.
  extern String nil;
};

/** Handles are therefore 16 bits integers; a positive integer designates a
 * pair, i.e., an internal node; a negative pair represents a string. A zero
 * integer designates the NIL atom.  There is a bit of trickery to make sure
 * that if the index zero, the string behind it happens to be NIL. In a sense
 * the zero is also an index into the strings array.
 *
 * Both pools are consecutive in memory: There is a large static buffer in which 
 * both pools reside.
 */

union S; 


/* An S expression is identified by a 16 bits handle (the type H).
 * It is an atom is the handle is non-positive (the index zero is 
 * reserved for the special NIL atom). It is an internal node */
representation S { // Representation of an S expression
 /// Perspective I: a simple handle in an H data type 
  perspective(H handle)
  construct S(H h) by (handle(h));
  property String asAtom() returns  (Strings::pool + handle)

  property Pair asPair() returns  (Pairs::get(handle))

  construct S(S car, S cdr) by(handle(Pairs::allocate(car.handle,cdr.handle)))
  construct S(String s) by(handle(Strings::allocate(s)))
  /* Nullary atomic/utility functions are public data members; */ 

  /** Unary atomic functions are methods that take no parameters*/
  bool atom() const; 
  bool null() const; 
  bool t() const; 
  S car() const; 
  S cdr() const;
  S eval() const; 
  S q() const; 
  /** Binary atomic functions are methods that take one parameter */
  bool eq(S other) const; 
  bool ne(S other) const; 
  S cons(S cdr) const;
  S snoc(S car) const;
  S error(S kind) const; 
};
#undef NULL
// Names of atoms that represent atomic functions 
extern const S NIL, T; //
extern const S CAR, CDR, CONS;
extern const S NULL, ATOM, EQ, COND;
extern const S QUOTE, EVAL;
extern const S DEFUN, NDEFUN; 
extern const S ERROR, SET;
 // Named atoms for exceptions
extern const S MISSING, UNDEFINED, INVALID, BUG, EMPTY, EXHAUSTED;

inline bool die(S s) { throw BUG.cons(s); }
extern const S REDUNDANT;

#undef construct
#endif // MINI_LISP_H 
   
