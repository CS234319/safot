// An implementation of mini-lisp in mini-C++
#include "basics.h"

/* Nullary atomic functions */
bool S::atom() const { return handle <= 0; }
bool S::null() const { return handle == 0; }
bool S::t()    const { return handle != 0; }
S    S::q()    const { return snoc(S::QUOTE); }
S    S::car()  const { return atom() ? error(CAR) : asPair().car; }
S    S::cdr()  const { return atom() ? error(CDR) : asPair().cdr; }
S    S::eval() const { return ::eval(*this); }
S    S::error(S kind) const { throw cons(kind).asPair(); }

// Binary
S S::cons(S cdr) const { return S(*this, cdr); }
S S::snoc(S car) const { return S(car, *this); }
bool S::eq(S other) const { return handle == other.handle && atom(); }
bool S::ne(S other) const { return handle != other.handle && atom(); }

/* Complete the definition of struct S */
const S S::NIL("NIL"); // Always define longer names first 
const S S::SET("set"); // Save one letter by sharing with "T"
const S S::T("T");     // Always define longer names first 
const S S::NDEFUN("ndefun"); // Always define longer names first 
const S S::DEFUN("defun");
const S S::NLAMBDA("nlambda");
const S S::LAMBDA("lambda");
const S S::QUOTE("quote");
const S S::ATOM("atom");
const S S::CAR("car");
const S S::CDR("cdr");
const S S::COND("cond");
const S S::CONS("cons");
const S S::ERROR("error");
const S S::EVAL("eval");
const S S::EQ("eq");
const S S::NULL("null");
const S S::REDUNDANT("redundant"); 
const S S::MISSING("missing");
const S S::UNDEFINED("undefined");
const S S::INVALID("invalid");
const S S::BUG("bug");
const S S::EMPTY("empty");
const S S::EXHAUSTED("exhausted");

extern S eval(S s); 

const S S::ATOMIC_FUNCTIONS = list(
  S::CAR,   S::CDR,  S::CONS,
  S::ATOM,  S::NULL,  S::EQ,  S::COND, 
  S::ERROR, S::SET, S::EVAL, S::QUOTE
);
