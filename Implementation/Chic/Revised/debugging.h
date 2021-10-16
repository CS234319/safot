// #import "basics.h"
#import "dump.h"
#import "parser.h"
#import "S.h"
#import "Pushdown.h"

#import <cstring>
#import <iostream>
#import <sstream>
#import <string.h>

/** Auxiliary file that should not be used by production code, only 
 * for debugging. 
 */

/** An auxiliary file with lots of heavy weight C++ code and huge overhead.
 * This should not be in the production version. It is OK for testing and for
 * debugging.
 */
inline std::ostream& <<(std::ostream &os, std::ostringstream o) {
  return os << o.str();
}

inline std::ostream& <<(std::ostream &os, Pair p) {
  return os << "[" << S(p.car) << "." << S(p.cdr)  << "]";
}

inline String  ~(S s) {
 std::ostringstream o;
 o << s;
 return strdup(o.str().c_str());
}

inline bool isRule(int i) {
  return i> Parser::MIN_RULE && i < Parser::MAX_RULE;  
}

inline String  ~(Parser::Symbol s) {
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

inline H& data(H h) {
  return Pairs::get(h).data;
}

inline H next(H h) {
  return Pairs::get(h).next;
}

inline String stack() {
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
