#include <iostream>
#include "mini-lisp.h"

std::ostream& operator<<(std::ostream &os, Pair p) {
  return os << "[" << p.car << "." << p.cdr << "]";
}

std::ostream& operator<<(std::ostream &os, S s) {
  if (s.null())
    return os << "nil";
  if (s.atom())
    return os << s.asAtom();
  if (!islist(s))
    return os << "(" << car(s) << "." << cdr(s) << ")";
  os << "(";
  for (;;) {
    os << S(s.car());
    if ((s = s.cdr()).null())
      break;
    os << " ";
  }
  return os << ")";
}

