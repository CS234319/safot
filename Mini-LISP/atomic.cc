// An implementation of mini-lisp in mini-C++
#include "basics.h"
#include "eval.h"

const S REDUNDANT("redundant"); 

/* Nullary atomic functions */
bool S::atom() const { return handle <= 0; }
bool S::null() const { return handle == 0; }
bool S::t()    const { return handle != 0; }
S    S::q()    const { return snoc(QUOTE); }
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
const S NIL("NIL"); // Always define longer names first 
const S SET("set"); // Save one letter by sharing with "T"
const S T("T");     // Always define longer names first 
const S NDEFUN("ndefun"); // Always define longer names first 
const S DEFUN("defun");
const S QUOTE("quote");
const S ATOM("atom");
const S CAR("car");
const S CDR("cdr");
const S COND("cond");
const S CONS("cons");
const S ERROR("error");
const S EVAL("eval");
const S EQ("eq");
const S NULL("null");
const S MISSING("missing");
const S UNDEFINED("undefined");
const S INVALID("invalid");
const S BUG("bug");
const S EMPTY("empty");
const S EXHAUSTED("exhausted");

extern S eval(S s); 


