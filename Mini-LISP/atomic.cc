// An implementation of mini-lisp in mini-C++
#include "basics.h"

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

extern S eval(S s); 

/* Nullary atomic functions */
bool S::atom() const { return handle <= 0; }
bool S::null() const { return handle == 0; }
bool S::t()    const { return handle != 0; }
S    S::car()  const { return atom() ? error(CAR) : asPair().car; }
S    S::cdr()  const { return atom() ? error(CDR) : asPair().cdr; }
S    S::eval() const { return ::eval(*this); }
S    S::error(S kind) const { throw cons(kind).asPair(); }

// Binary
S S::cons(S cdr) const { return S(*this, cdr); }

bool S::eq(S other) const { return handle == other.handle && atom(); }

const S S::ATOMIC_FUNCTIONS = list(S::ATOM,S::CAR,S::CDR,S::COND,S::CONS,S::EQ,S::ERROR,S::EVAL,S::NULL, S::SET);
