#import  "test.h"
/** An auxiliary file with lots of heavy weight C++ code and huge overhead.
 * This should not be in the production version. It is OK for testing and for
 * debugging.
 */
#import  <string.h>
#import  "basics.h"
#import  "parser.h"
#import  "stack.h"

extern bool operator == (const S s1, const S s2) { 
  if (s1.handle == s2.handle)
    return true;
  if (s1.atom() || s2.atom()) return s1.eq(s2); 
  return s1.car() == s2.car() && s1.cdr() == s2.cdr();
}


namespace Tested {
  extern S parse(const char *s) {
      Parser::reset();
      Parser::supply(strdup(s));
      if (Parser::status() != Parser::Status::accept) {
          Parser::reset();
          ADD_FAILURE() << "Parser crashed on " << s; 
      }
      return Parser::result();
  }

static auto feed(String s) {
  Parser::reset();
  return Parser::supply(strdup(s));
}
void reset() {
  Parser::reset();
  Engine::reset();
  Stack::reset();
}

}

// extern auto operator != (const S s1,const S s2) { return s1.handle == s2.handle; }

#if 0
String operator ~(S s) {
 std::ostringstream o;
 o << s;
 return strdup(o.str().c_str());
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
#endif
