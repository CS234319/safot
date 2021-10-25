// #import "basics.h"
#import "dump.h"
#import "parser.cc"
#import "S.cc"
#import "Pushdown.cc"

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
#import "Cons.cc"

inline std::ostream& operator <<(std::ostream &os, Cons c) {
  return os << "[" << S(c.car()) << "." << S(c.cdr())  << "]";
}

inline String operator ~(S s) {
 std::ostringstream o;
 o << s;
 return strdup(o.str().c_str());
}

#import "LL.cc"
inline bool isRule(int i) is(i> LL::Symbol::MIN_RULE && i < LL::Symbol::MAX_RULE)  

inline String operator ~(LL::Symbol s) {
    if (s < 0)
      return S(s).text();
    switch (s) {
      case LL::$: return "$";
      case LL::s: return "s";
      case LL::Atom: return "Atom";
      case LL::E: return "E";
      case LL::X: return "X";
      case LL::T: return "T";
      case LL::L: return "L";
      case LL::s1: return "s1:s->E$";
      case LL::E1: return "E1:E->XT";
      case LL::X1: return "X1:X->'X";
      case LL::X2: return "X2:X->(L)";
      case LL::X3: return "X3:X->Atom";
      case LL::T1: return "T1:T->.X";
      case LL::T2: return "T2:T->''";
      case LL::L1: return "L1:L->EL";
      case LL::L2: return "L2:L->''";
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

#if 0
inline String stack() {
  static std::ostringstream o;
  o.str("");
  o << "[";
  using namespace parser;
  for (Item i = parser::stack.top; not i.x(); ) {
    o << i.head() << "@" << ~LL::Symbol(i.head());
    if ((i = i.rest()).x()) 
      break;
    o << " ";
  }
  o << "]";
  return strdup(o.str().c_str());
}
#endif
