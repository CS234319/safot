#include "Sx.h"

#include "text.h"
#include "heap.h"
#include "Pair.h"

// Property(Pair Sx::pair(Sx cdr)) Is(Sx(*this, cdr));
Sx::Sx(Short s)      : Handle(s) {}
Sx::Sx(Handle h)     : Sx(h.handle()) {} 
Sx::Sx(Sx s1, Sx s2) : Sx(request(s1, s2).handle()) {}
Sx::Sx(Text t)       : Sx(request(t)) {}

Property(Boolean Sx::atom) Is(handle() <= 0);
Property(Sx Sx::car)  Is(p().s1) 
Property(Sx Sx::cdr)  Is(p().s2) 
// Property(Pair Sx::Pair)  Is(Pair(handle())) 

Pair Sx::Pair() const {
  return ::Pair(handle());
}
const Sx NIL("NIL"); // Always define longer names first 
const Sx SET("set"); // Save one letter by sharing with "T"
const Sx T("T");     // Always define longer names first 
const Sx NDEFUN("ndefun"); // Always define longer names first 
const Sx DEFUN("defun");
const Sx QUOTE("quote");
const Sx ATOM("atom");
const Sx CAR("car");
const Sx CDR("cdr");
const Sx COND("cond");
const Sx CONS("pair");
const Sx ERROR("error");
const Sx EVAL("eval");
const Sx EQ("eq");
const Sx NULL("null");
const Sx MISSING("missing");
const Sx UNDEFINED("undefined");
const Sx INVALID("invalid");
const Sx BUG("bug");
const Sx EMPTY("empty");
const Sx EXHAUSTED("exhausted");
