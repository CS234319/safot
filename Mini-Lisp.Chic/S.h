// #include <iostream>
#ifndef S_H
#define S_H

#include <cerrno>
#include "hacks.h"

// Representation of a dotted pair, i.e., an unlabeled internal node in the
// binary tree behind compound S-expression.
#ifdef WORK_AROUND
representation Pair {
    perspective(W cons: 64)
    perspective(H car, cdr :32)
    perspective(H data, next :32)
    perspective(H value, errorCode :32)
};
#else
representation Pair {
    perspective(W cons: 32)
    perspective(H car, cdr :16)
    perspective(H data, next :16)
    perspective(H value, errorCode :16)
};
#endif
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
 * Both pools are consecutive in memory: There is a large static buffer in
 * which both pools reside.
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
   * fluentons: these are methods provided by type S and specifically designed
   * to make it possible to write Mini-Lisp expressions in the fluent-, rather
   * than the list- or nested style. To demonstrate, consider the definition of
   * the Mini-Lisp library function lookup to conduct a search in a given
   * a-list:
   
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
      id.error(UNDEFINED_ATOM) : 
    a_list.car().car().eq(id) ?  
      a_list.car().cdr() : 
    lookup(id, a_list.cdr()); 
}

A fluenton is a method designed to be used in expressions such as the above, in
which instead of writing '(cdr (car a))' in 'cdr(car(a))', we write
a.car().cdr(). Most fluentons return an S, that can be fluently continued by a
another fluenton. Some fluentons are sinks: they return a boolean that can be
used in a conditional expression. 

Fluentons which do not implement an atomic function of mini-Lisp are called
auxiliary fluentons.
*/
// Fluenton sources of Names of atoms that represent atomic functions 
  // Unary atomic functions are parameterless fluentons 
  bool atom() const; /// sink: Atomic function of Mini-Lisp 
  bool pair() const; /// auxiliary sink: complements atom 
  bool null() const; /// sink: Atomic function of Mini-Lisp 
  bool t() const;    /// sink: Auxiliary fluenton, complements null
  S car() const;     /// atomic function of Mini-Lisp 
  S rac() const;     /// auxiliary: same as car, except no checking is made 
  S cdr() const;     /// atomic function of Mini-Lisp 
  S rdc() const;     /// auxiliary: same as car, except no checking is made 
  S eval() const;    /// atomic function of Mini-Lisp 
  S q() const;       /// Return the list (QUOTE this), where this is the receiver 
  S l() const;       /// returns a singleton list containing this S expression 

  // Another kind of fluentons, are those that convert their implicit
  // argument into some other type.
  Pair p() const;        /// Converts to type Pair 
  String a() const;        /// Converts to type Atom 
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

  bool more0() const;  /// Sink: true iff this is a list of length at least 0
  bool more1() const;  /// Sink: true iff this is a list of length at least 1 
  bool more2() const;  /// Sink: true iff this is a list of length at least 2
  bool more3() const;  /// Sink: true iff this is a list of length at least 3
  bool more4() const;  /// Sink: true iff this is a list of length at least 4

  bool less0() const;  /// Sink: true iff this is a list of length at most 0
  bool less1() const;  /// Sink: true iff this is a list of length at most 1 
  bool less2() const;  /// Sink: true iff this is a list of length at most 2
  bool less3() const;  /// Sink: true iff this is a list of length at most 3
  bool less4() const;  /// Sink: true iff this is a list of length at most 4

  S $1$() const;  /// Auxiliary pipe: first element in a list
  S $2$() const;  /// Auxiliary pipe: second element in a list
  S $3$() const;  /// Auxiliary pipe: third element in a list
  S $4$() const;  /// Auxiliary pipe: forth element in a list
};

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

// Named atoms for exceptions; for the idiom s.error(MISSING_ARGUMENT) to abort
// execution in the case that an error of kind MISSING_ARGUMENT occurs in the context of
// the S expression named s.

// Memory errors:
inline bool memory_error(S s) {
    // Using this function instead of die(S s),
    // because die allocate more memory via cons)
    errno = ENOMEM;
    throw s;
}
#undef construct
#endif // S_H 
