#include "io.h"

#include <string.h>
#include "parser.h"
#include "stack.h"
#include "stack-trace.h"

std::ostream& operator<<(std::ostream &os, std::ostringstream o) {
  return os << o.str();
}

std::ostream& operator<<(std::ostream &os, Pair p) {
  return os << "[" << p.car << "." << p.cdr << "]";
}

String operator ~(S s) {
 std::ostringstream o;
 o << s;
 return strdup(o.str().c_str());
}

std::ostream& operator<<(std::ostream &os, S s) {
  if (s.null())
    return os << "nil";
  if (s.atom())
    return os << s.asAtom();
  if (!islist(s))
    return os << "" << car(s) << "." << cdr(s) << "";
  os << "(";
  for (;;) {
    os << S(s.car());
    if ((s = s.cdr()).null())
      break;
    os << " ";
  }
  return os << ")";
}

bool isRule(int i) {
  return i> Parser::MIN_RULE && i < Parser::MAX_RULE;  
}

String operator ~(Parser::Symbol s) {
    if (atom(s))
      return S(s).asAtom();
    switch (s) {
      case Parser::$: return "$";
      case Parser::s: return "s";
      case Parser::Atom: return "Atom";
      case Parser::E: return "E";
      case Parser::X: return "X";
      case Parser::T: return "T";
      case Parser::L: return "L";
      case Parser::s1: return "s1:s->E$";
      case Parser::E1: return "E1:E->XT";
      case Parser::X1: return "X1:X->'X";
      case Parser::X2: return "X2:X->(L)";
      case Parser::X3: return "X3:X->Atom";
      case Parser::T1: return "T1:T->.X";
      case Parser::T2: return "T2:T->''";
      case Parser::L1: return "L1:L->EL";
      case Parser::L2: return "L2:L->''";
    }
    std::ostringstream o;
    if (s < 127)
      if (s > ' ')
        o << (char) s;
      else
        o << '/' << (int) s << '/';
    else
      o << (int) s;
    return strdup(o.str().c_str());
  }

static inline H& data(H h) {
  return Pairs::get(h).data;
}

static inline H next(H h) {
  return Pairs::get(h).next;
}

String stack() {
  static std::ostringstream o;
  o.str("");
  o << "[";
  using namespace Parser;
  Symbol::E1 < Symbol::L2;
  for (H h = Stack::top; h != 0;) {
    o << h << "@";
    o << ~Symbol(data(h));
    if ((h = next(h)) == 0)
      break;
    o << " ";
  }
  o << "]";
  return strdup(o.str().c_str());
}



//  String h2s(H h) { return ~*reinterpret_cast<Symbol*>(&h); }
