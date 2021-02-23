
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

  S current = NIL;
  extern S result() {
    return current; 
  }

  enum Status current_status = ready;

  extern enum Status status() {
    return current_status;
  }
  static void parse();
  enum Symbol : H {
    $ = Tokenizer::$, Start, Atom, // Special symbols, EOF, Start
    E, X, T, L, 
    MIN_RULE, // DUMMY 
    Start1, // _ ::= E $
    E1, // E ::= X T
    X1, // X ::= ' X 
    X2, // X ::= ( L ) 
    X3, // X ::= atom 
    T1, // T ::= . X 
    T2, // T ::= ''
    L1, // L ::= E L
    L2, // L ::= ''
    MAX_RULE // DUMMY
  };
std::ostream& operator<<(std::ostream &os, Symbol s)  {
  os << "Symbol";
  os  << long(s);
  return os;
}
  static auto atom(Symbol s) {
    return s <= 0;
  }

  bool isRule(int i) {
    return i> MIN_RULE && i < MAX_RULE;  
  }

  String operator ~(Symbol s) {
    if (atom(s))
      return S(s).asAtom();
    switch (s) {
      case Parser::$: return "$";
      case Parser::Start: return "Start";
      case Parser::Atom: return "Atom";
      case Parser::E: return "E";
      case Parser::X: return "X";
      case Parser::T: return "T";
      case Parser::L: return "L";
      case Parser::Start1: return "Start:_->E$";
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


  extern void supply(char *buffer) {
    D(buffer);
    Tokenizer::initialize(buffer);
    parse();
  }
 
  extern void reset() {
    while (!Stack::empty())
      Stack::pop();
    Stack::push(Start);
    current_status = ready;
  }

  Symbol token;
  Symbol top;

  String h2s(H h) {
    return ~*reinterpret_cast<Symbol*>(&h);
  }

  void reduce() {
    M4("Reduce",~top,~token,stack());
  }

  void shift(Symbol rule) {
    M4("Shift",~rule,"on", ~token, current,stack());
    Stack::push(rule, current.index);
  }


  void shift(Symbol rule, H h1, H h2, H h3) {
    shift(rule);
    Stack::push(h1, h2, h3);
  }

  void shift(Symbol rule, H h1, H h2) {
    shift(rule);
    Stack::push(h1, h2);
  }

  void shift(Symbol rule, H h) {
    shift(rule);
    Stack::push(h);
    D(stack());
  }


  static void parse() {
    D(stack());
    while (!Stack::empty()) {
      M1("LOOP", current, stack());
      token = (Symbol) Tokenizer::get();
      top  = (Symbol) Stack::pop();
      M1("POP", ~token, ~top);
      if (atom(token) && top == Atom) {
        M1("Match Atom", ~token,~top);
        current = token;
        continue;
      }
      if (token == top) {
        M1("Match Ignore", ~token,~top);
        continue;
      }
      Tokenizer::unget();
      switch (top) {
        case Start:
          if (token == '\'' || token == '(' || atom(token)) {
            shift(Start1, E, $); 
            continue;
          }
          break;
        case Start1:
          reduce();
          Stack::pop();
          continue;
        case E:
          if (token == '\'' || token == '(' || atom(token)) {
            shift(E1, X, T);
            continue;
          }
          break;
        case E1:
          reduce();
          Stack::pop();
          continue;
        case X:
          if (token == '\'') {
            shift(X1,'\'');
            continue;
          }
          if (token == '(') {
            shift(X2, '(', L, ')');
            continue;
          }
          if (atom(token)) {
            current = token;
            shift(X3,Atom);
            continue;
          }
          break;
        case X1:
          reduce();
          current = list(QUOTE,Stack::pop());
          continue;
        case X2:
          reduce(); 
          current = Stack::pop();
          continue;
        case X3:
          reduce(); 
          Stack::pop();
          continue;
        case T:
          if (token == '.') {
            shift(T1, '.', X);
            continue;
          }
          if (exists(token, "()'") || token == $ || atom(token)) {
            shift(T2);
            continue;
          }
          break;
        case T1:
          reduce(); 
          current = cons(Stack::pop(), current);
          continue;
        case T2:
          reduce(); 
          Stack::pop();
          continue;
        case L:
          if (exists(token,"'(") || atom(token)) {
            shift(L1, E, L);
            D(stack());
            continue;
          }
          if (token == ')') {
            shift(L2);
            D(stack());
            continue;
          }
          break;
        case L1:
          reduce(); 
          current = cons(current, Stack::pop());
          M1("Set", current);
          continue;
        case L2:
          reduce(); 
          current = Stack::pop();
          continue;
      }
      M1("REJECT", ~token, ~top, stack());
      current_status = reject;
      return;
    }
    current_status = accept;
  }

}

#ifdef DEBUG
#include "io.h"
#include <string.h>
std::ostream& operator<<(std::ostream &os, std::ostringstream o) {
  return os << o.str();
}

String stack() {
  static std::ostringstream o;
  bool afterRule = false;
  o.str("");
  o << "[";
  using namespace Parser;
  Symbol::E1 < Symbol::L2;
  for (H h = Stack::top; h != 0;) {
    Pair p = S(h).asCons();
    H data = p.data;
    H next = p.next;
    if (afterRule) 
      afterRule = false,o << S(data);
    else 
      o << ~Symbol(data);
    if (isRule(data)) 
      afterRule = true;
    if ((h = next) == 0)
      break;
    o << " ";
  }
  o << "]";
  return strdup(o.str().c_str());
}
#endif
