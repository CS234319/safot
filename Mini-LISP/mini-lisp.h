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
};

/** A pool of all pairs is managed by the pairs module (see pairs.cc). The pool
 * is an array; an index into this array, also called a handle, is a half word
 * (type H), and can be thought of as a pointer. All indices are strictly
 * positive.
 */
namespace Pairs {
   extern Pair *const pool;         /* Array of all pair records, free and allocated */
   extern H allocate(H car, H cdr); /* Retrieve a free pair, and set it values */
   extern void free(H index);       /* Return a pair to the pool */
   extern H to_go();                /* How many pairs are still free */ 
   extern Pair& get(H index);       /* A convenience method that retrieves a pair by its handle */
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
extern S cons(S car, S cdr);
extern bool eq(S, S);
extern bool islist(S); 

/* An S expression is identified by a 16 bits handle (the type H).
 * It is an atom is the handle is non-positive (the index zero is 
 * reserved for the special NIL atom). It is an internal node 
 */
representation S { // Representation of an S expression
 /// Perspective I: a simple handle in an H data type 
  perspective(H index)
  construct S(H h) by (index(h));
  property bool null() returns  (index == 0)
  property bool atom() returns  (index <= 0)
  property String asAtom() returns  (Strings::pool + index)
  property bool isTrue() returns(!null())

  property Pair asPair() returns  (Pairs::get(index));
  property S car() returns (asPair().car)
  property S cdr() returns (asPair().cdr)

  property S cons(const S s) returns (::cons(*this,s));
  property S eq(const S s) returns (::eq(*this, s));
  property bool islist() returns (::islist(*this));

  // Perspective II: a sign bit (pool designator) and an index into 
  // into that pool. 
  perspective( H bits : 15;  bool sign: 1)
  construct S() by(bits(0), sign(0))

  construct S(S s1, S s2) by(index(Pairs::allocate(s1.index,s2.index)))
  construct S(String s) by(index(Strings::allocate(s)))
};


// Nullary atomic function
extern const S NIL,T, QUOTE;

// Unary atomic functions
extern S car(S);
extern S cdr(S);
// Unary library functions
extern S eval(S);

extern S apply(S s, S args);

// Binary atomic functions
extern bool eq(S, S);
extern S cons(S car, S cdr);
extern S set(S name, S value);

// Utility functions
extern S list() ;
extern S list(S);
extern S list(S, S);
extern S list(S, S, S );
extern S list(S, S, S, S);

static void error(String s) {  std::cerr << s;  throw __LINE__; }
static void error(String s, S s1) {  std::cerr << s << " " << s1.asAtom();  throw __LINE__; }

#undef construct
#endif // MINI_LISP_H 
