#include <cstdint>
#include <iostream>
#ifndef MINI_LISP_H
#define MINI_LISP_H 

#include "hacks.h"

representation Pair { // Representation of a dotted pair
  perspective(W cons: 32)
  perspective(H car, cdr :16)
  perspective(H data, next :16)
};

namespace Pairs {
   extern Pair *const pool;
   extern H allocate(H car, H cdr);
   extern void free(H index);
   extern H to_go();
   extern Pair& get(H index);
};

namespace Strings { // Atoms are never freed in mini-lisp
  extern String pool;
  extern H allocate(String);
  extern bool eq(String, String);
};


union S; 
extern S cons(S car, S cdr);
extern bool eq(S, S);
extern bool islist(S); 

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
extern S eval(S);

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
