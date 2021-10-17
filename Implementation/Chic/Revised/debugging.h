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
inline std::ostream& operator <<(std::ostream &os, std::ostringstream o) {
  return os << o.str();
}

inline std::ostream& operator <<(std::ostream &os, Pair p) {
  return os << "[" << S(p.car()) << "." << S(p.cdr())  << "]";
}

inline Text operator ~(S s) {
 std::ostringstream o;
 o << s;
 return strdup(o.str().c_str());
}

inline bool isRule(int i) {
  return i> parser::MIN_RULE && i < parser::MAX_RULE;  
}

inline Text operator ~(parser::Symbol s) {
    if (atom(s))
      return S(s).asAtom();
    switch (s) {
      case parser::$: return "$";
      case parser::s: return "s";
      case parser::Atom: return "Atom";
      case parser::E: return "E";
      case parser::X: return "X";
      case parser::T: return "T";
      case parser::L: return "L";
      case parser::s1: return "s1:s->E$";
      case parser::E1: return "E1:E->XT";
      case parser::X1: return "X1:X->'X";
      case parser::X2: return "X2:X->(L)";
      case parser::X3: return "X3:X->Atom";
      case parser::T1: return "T1:T->.X";
      case parser::T2: return "T2:T->''";
      case parser::L1: return "L1:L->EL";
      case parser::L2: return "L2:L->''";
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

inline Short& data(Short h) {
  return Pairs::get(h).data;
}

inline Short next(Short h) {
  return Pairs::get(h).next;
}

inline Test stack() {
  static std::ostringstream o;
  o.str("");
  o << "[";
  using namespace parser;
  Symbol::E1 < Symbol::L2;
  for (Short h = Stack::top; h != 0;) {
    o << h << "@";
    o << ~Symbol(data(h));
    if ((h = next(h)) == 0)
      break;
    o << " ";
  }
  o << "]";
  return strdup(o.str().c_str());
}
