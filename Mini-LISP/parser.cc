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
      case Parser::_1: return "{_ ::= E $}";
      case Parser::E1: return "{E ::= X T}";
      case Parser::X1: return "{X ::= ' X}";
      case Parser::X2: return "{S::= ( L )}";
      case Parser::X3: return "{S::= a}";
      case Parser::T1: return "{T::= . X}";
      case Parser::T2: return "{T ::= ''}";
      case Parser::L1: return "{L ::= E L}";
      case Parser::L2: return "{L ::= ''}";
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
    stack();
    D(stack());
    while (!Stack::empty()) {
      Symbol token = (Symbol) Tokenizer::get();
      Symbol top  = (Symbol) Stack::pop();
      M("LOOP", current,~token, ~top, stack(),prev);
      if (atom(token) && top == 0) {
        M("MATCH", ~token, ~(top));
        continue;
      }
      if (token == top) {
        D("MATCH", ~token, ~(top));
        continue;
      }
      Tokenizer::unget();
      switch (top) {
        case _:
          M("Shift",~_, stack(), ~token, ~top);
          if (token == '\'' || token == '(' || atom(token)) {
            D(stack());
            Stack::push(E, $, _1);
            D(stack());
            continue;
          }
          break;
        case _1:
          M("Reduce",~_, stack(), ~token, ~top);
          continue;
        case E:
          M("Shift",~E, ~token, ~top);
          if (token == '\'' || token == '(' || atom(token)) {
            Stack::push(X, T, E1);
            continue;
          }
          break;
        case E1:
          D("Reduce",~E1, stack(), ~token, ~top);
          continue;
        case X:
          D("Shift",~X, stack(), ~token, ~top);
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
            Stack::push(0, X3);
            continue;
          }
          break;
        case X1:
          M("Reduce",~X1, stack(), ~token, ~top);
          current = list(QUOTE,current);
          D(~X1, stack(), current, ~token, ~top);
          continue;
        case X2:
          M("Reduce",~X2, stack(), current, ~token, ~top);
          continue;
        case X3:
          M("Reduce",~X3, stack(), current, ~token, ~top);
          continue;
        case T:
          M("Shift",~T, stack(), ~token, ~top);
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
          D("Reduce",~T1, stack(), ~token, ~top);
          Stack::pop();
          continue;
        case T2:
          D("Reduce",~T2, stack(), ~token, ~top);
          current = cons(prev, current);
          continue;
        case L:
          D("Shift",~L, stack(), ~token, ~top);
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
          D("Reduce",~L1, stack(), ~token, ~top);
          current = cons(prev, current);
          continue;
        case L2:
          D("Reduce",~L2, stack(), ~token, ~top);
          prev = current;
          current = NIL;
          continue;
      }
      D("REJECT", ~token, ~top, stack());
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
