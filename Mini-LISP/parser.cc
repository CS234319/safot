#include "parser.h"
#include "stack.h"
#include "tokenizer.h"

#include "dump.h"
#include "stack-trace.h"

#include <string.h>

#define DEBUG  

#ifdef DEBUG 
#include <sstream>
std::ostream& operator<<(std::ostream &os, S s); 
std::ostream& operator<<(std::ostream &os, std::ostringstream o);
String stack(); 
#else 
#undef D
#define D(...) 0
#endif

namespace Parser {
  /* Formal grammar of S expression
   https://www.cs.princeton.edu/courses/archive/spring20/cos320/LL1/

   E ::= X T
   T ::= . X
   T ::= ''
   X ::= ' X
   X ::= ( L )
   X ::= a 
   L ::= E L
   L ::= ''


   */

  S current, prev;
  extern S result() {
    return current; 
  }

  enum Status current_status = ready;

  extern enum Status status() {
    return current_status;
  }
  static void parse();
  enum Symbol : H {
    $ = Tokenizer::$, _, E, X, T, L, //
    _1, // _ ::= E $
    E1, // E ::= X T
    X1, // X ::= ' X 
    X2, // X ::= ( L ) 
    X3, // X ::= atom 
    T1, // T ::= . X 
    T2, // T ::= ''
    L1, // L ::= E L
    L2, // L ::= ''
  };
  static auto atom(Symbol s) {
    return s <= 0;
  }
  String operator ~(Symbol s) {
    if (s < 0)
      return S(s).asAtom();
    switch (s) {
      case 0: return "()";
      case Parser::$: return "$";
      case Parser::_: return "_";
      case Parser::E: return "E";
      case Parser::X: return "X";
      case Parser::T: return "T";
      case Parser::L: return "L";
      case Parser::_1: return "[_->E$]";
      case Parser::E1: return "[E->XT]";
      case Parser::X1: return "[X->'X]";
      case Parser::X2: return "[X->(L)]";
      case Parser::X3: return "[X->a]";
      case Parser::T1: return "[T->.X]";
      case Parser::T2: return "[T->'']";
      case Parser::L1: return "[L->EL]";
      case Parser::L2: return "[L->'']";
    }
    std::ostringstream o;
    o << int(s);
    if (s < 127)
      if (s > ' ')
        o << (char) s;
      else
        o << '/' << (int) s << '/';
    else
      o << (int) s;
    return strdup(o.str().c_str());
  }
  extern void supply(char *buffer) {
    D(buffer);
    Tokenizer::initialize(buffer);
    parse();
  }
 
  extern void reset() {
    while (!Stack::empty())
      Stack::pop();
    Stack::push(_);
    D(stack(), _);
    current_status = ready;
  }

  static void parse() {
    D(stack());
    while (!Stack::empty()) {
      M("LOOP", stack());
      Symbol token = (Symbol) Tokenizer::get();
      Symbol top  = (Symbol) Stack::pop();
      M("POP", ~token, ~top);
      if (atom(token) && top == 0) {
        M("Match",~token, ~top);
        continue;
      }
      if (token == top) {
        M("Match", ~token,~top);
        continue;
      }
      Tokenizer::unget();
      switch (top) {
        case _:
          ~_;
          _M("Shift",~_);
          if (token == '\'' || token == '(' || atom(token)) {
            Stack::push(E, $, _1);
            continue;
          }
          break;
        case _1:
          _M("Reduce",~_, stack(), ~token, ~top);
          continue;
        case E:
          _M("Shift",~E);
          if (token == '\'' || token == '(' || atom(token)) {
            Stack::push(X, T, E1, current);
            continue;
          }
          break;
        case E1:
          _M("Reduce",~E1);
          prev=Stack::pop();
          continue;
        case X:
          _M("Shift",~X);
          if (token == '\'') {
            Stack::push('\'', X, X1);
            D(stack());
            continue;
          }
          if (token == '(') {
            Stack::push('(', L, ')', X2);
            continue;
          }
          if (atom(token)) {
            prev = current;
            current = token;
            M("Set", current, prev);
            Stack::push(0, X3);
            continue;
          }
          break;
        case X1:
          _M("Reduce",~X1);
          current = list(QUOTE,current);
          M("Set", current, prev);
          continue;
        case X2:
          _M("Reduce",~X2);
          continue;
        case X3:
          _M("Reduce",~X3);
          continue;
        case T:
          _M("Shift",~T);
          if (exists(token, "()'") || token == $ || atom(token)) {
            Stack::push(T1);
            D(stack());
            continue;
          }
          if (token == '.') {
            Stack::push('.', X, T2);
            D(stack());
            continue;
          }
          break;
        case T1:
          // This is the case that the T part is empty.
          // in this case, the top stack element must be X.
          _M("Reduce",~T1);
          Stack::pop();
          continue;
        case T2:
          _M("Reduce",~T2);
          current = cons(prev, current);
          M("Set", current);
          continue;
        case L:
          _M("Shift",~L);
          if (exists(token,"'(") || atom(token)) {
            Stack::push(E, L, L1);
            D(stack());
            continue;
          }
          if (token == ')') {
            Stack::push(L2);
            D(stack());
            continue;
          }
          break;
        case L1:
          _M("Reduce",~L1);
          current = cons(prev, current);
          M("Set", current);
          continue;
        case L2:
          _M("Reduce",~L2);
          prev = current;
          current = NIL;
          M("Set", current, prev);
          continue;
      }
      M("REJECT", ~token, ~top, stack());
      current_status = reject;
      return;
    }
    current_status = accept;
  }

}

#ifdef DEBUG
#include <string.h>
std::ostream& operator<<(std::ostream &os, std::ostringstream o) {
  return os << o.str();
}

String stack() {
  static std::ostringstream o;
  o.str("");
  o << "->";
  using namespace Parser;
  for (H h = Stack::top; h != 0;) {
    Pair p = S(h).asCons();
    o << ~Symbol(p.data);
    if ((h = p.next) == 0)
      break;
    o << " ";
  }
  o << "]]";
  return strdup(o.str().c_str());
}
#endif
