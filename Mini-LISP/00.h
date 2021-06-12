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


  construct S(S car, S cdr) by(handle(Pairs::allocate(car.handle,cdr.handle)))
  construct S(String s) by(handle(Strings::allocate(s)))

  /** Most atomic functions of mini-lisp are implemented as a collection of
   * fluentons: these are methods provided by type S designed to make it
   * possible to write Mini-Lisp expressions in the fluent-, rather than the
   * list- or nested style. To demonstrate, consider the definition of the Mini-Lisp
   * library function lookup to conduct a search in a given a-list:
   
(defun lookup (id a-list) 
  (cond 
    ((null a-list) 
      (error 'unbound-variable id))
    ((eq id (car (car a-list))) 
      (car (cdr (car a-list)))) 
    (t (lookup id (cdr a-list))))) 

With the fluentons of type S, this function is written as 

S lookup(S id, S a_list) { 
  return 
    a_list.null() ?  
      id.error(UNDEFINED) : 
    a_list.car().car().eq(id) ?  
      a_list.car().cdr() : 
    lookup(id, a_list.cdr()); 
}

A fluenton is a method designed to be used in expressions such as the above, in
which instead of writing '(cdr (car a)}' in 'cdr(car(a))', we write
a.car().cdr(). Most fluentons return an S, that can be fluently continued by a
another fluenton. Some fluentons are sinks: they return a boolean that can be
used in a conditional expression. 

Fluentons which do not implement an atomic function of mini-Lisp are called
auxiliary fluentons.
*/

  // Unary atomic functions are parameterless fluentons 
  bool atom() const; /// sink: Atomic function of Mini-Lisp 
  bool pair() const; /// auxiliary sink: complements atom 
  bool null() const; /// sink: Atomic function of Mini-Lisp 
  bool t() const;    /// sink: Auxiliary fluenton, complements null
  S car() const;     /// atomic function of Mini-Lisp 
  S cdr() const;     /// atomic function of Mini-Lisp 
  S eval() const;    /// atomic function of Mini-Lisp 
  S q() const;       /// implements library functions quote
  S l() const;       /// returns a singleton list containing this S expression 

  // Another kind of fluentons, are those that convert their implicit
  // argument into some other type.
  Pair p() const;        /// Converts to type Pair 
  Pair a() const;        /// Converts to type Atom 
  // Binary atomic functions are fluentons that take one parameter */
  bool eq(S other) const; /// Sink: Atomic function of Mini-Lisp 
  bool ne(S other) const; /// Sink: Auxiliary fluenton, complements eq 
  S cons(S cdr) const;    /// Atomic function of Mini-Lisp 
  S snoc(S car) const;    /// Auxiliary fluenton, complements eq 
  S error(S kind) const;  /// Atomic function of Mini-Lisp

  // More fluentons
  bool n0() const;  /// Sink: true iff this is a list of length 0
  bool n1() const;  /// Sink: true iff this is a list of length 1
  bool n2() const;  /// Sink: true iff this is a list of length 2
  bool n3() const;  /// Sink: true iff this is a list of length 3

  S $1$() const;  /// first element in a list
  S $2$() const;  /// second element in a list
  S $3$() const;  /// third element in a list
};

#undef NULL
// Fluenton sources of Names of atoms that represent atomic functions 
extern const S NIL, T; //
extern const S CAR, CDR, CONS;
extern const S ATOM, EQ, NE, NULL, COND;
extern const S QUOTE, EVAL;
extern const S DEFUN, NDEFUN; 
extern const S ERROR, SET;

// Named atoms for exceptions; for the idiom error(MISSING) to abort execution
// on the case an error of kind MISSING is found in the context of the S
// expression named s.
extern const S MISSING, REDUNDANT, UNDEFINED, INVALID, BUG, EMPTY, EXHAUSTED;

// Additional fluentons.
inline bool die(S s) { throw BUG.cons(s); }

#undef construct
#endif // MINI_LISP_H 
