#include "parser.h"
#include "stack.h"
#include "tokenizer.h"

#include "dump.h"
#include "stack-trace.h"

#include <string.h>


#define DEBUG 0 

#ifndef DEBUG 
#undef D
#define D(...) 0
#else 
#include <sstream>
std::ostream& operator<<(std::ostream &os, std::ostringstream o);
String stack(); 
#endif

namespace Parser {
  /* Formal grammar of S expression
   https://www.cs.princeton.edu/courses/archive/spring20/cos320/LL1/
   E ::= a
   E ::= ( L )
   L ::= S L
   L ::= ''

   E ::= ' E
   E ::= X T
   T ::= . X
   T ::= ''
   X ::= ( L )
   X ::= a 
   L ::= E L
   L ::= ''
   */

    S current, prev, prev2;
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
    E1, // E ::= ' E
    E2, // E ::= X T
    X1, // X ::= ( L )
    X2, // X ::= a 
    T1, // T ::= . X 
    T2, // T ::= ''
    L1, // L ::= E L
    L2, // L ::= ''
  };
  String operator !(Symbol s) {
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
      case Parser::_1: return "/_ ::= E $/";
      case Parser::E1: return "/' E/";
      case Parser::E2: return "/X T/";
      case Parser::X1: return "/( L )/";
      case Parser::X2: return "/S::= a/";
      case Parser::T1: return "/T::= . X/";
      case Parser::T2: return "/T ::= ''/";
      case Parser::L1: return "/L ::= E L/";
      case Parser::L2: return "/L ::= ''/";
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
    H h = Tokenizer::get();
    D(h, Symbol(h), S(h).asAtom(), !Symbol(h));
    Tokenizer::unget();
    parse();
    D(buffer);
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
      D("LOOP", !token, !top, stack(), !current, !prev,);
      if (token <= 0 && top == 0) {
        D("ATOM", !token, !(top));
        continue;
      }
      if (token == top) {
        D("MATCH", !token, !(top));
        continue;
      }
      Tokenizer::unget();
      switch (top) {
        case _:
          D(_, stack(), !token, !top);
          if (token == '\'' || token == '(' || token < 0) {
            D(_1);
            D(stack());
            Stack::push(E, $, _1);
            D(stack(),!_1);
            continue;
          }
          break;
        case _1:
          D(_, stack(), !token, !top);
          continue;
        case E:
          D(E, !token, !top);
          if (token == '\'') {
            Stack::push('\'', E, E1);
            D(stack());
            continue;
          }
          if (token == '(' || token <= 0) {
            Stack::push(X, T, E2);
            D(stack());
            continue;
          }
          break;
        case E1:
          prev = current;
          current = list(QUOTE, current);
          continue;
        case E2:
          prev2 = prev;
          prev = current;
          current = cons(prev, current);
          prev2 = prev;
          continue;
        case X:
          if (token == '(') {
            Stack::push('(', L, ')', X1);
            D(stack());
            continue;
          }
          if (token <= 0) {
            prev = current;
            current = token;
            Stack::push(0, X2);
            D(stack());
            continue;
          }
        case X1:
          continue;
        case X2:
          continue;
        case T:
          if (exists(token, "()'") || token == $ || token <= 0) {
            Stack::push(T1);
            D(stack());
          }
          continue;
          if (token == '.') {
            Stack::push('.', X, T2);
            D(stack());
            continue;
          }
          break;
        case T1:
          continue;
        case T2:
          prev2 = prev;
          current = cons(prev, current);
          prev = prev2;
          continue;
        case L:
          if (exists(token,"'(") || token <= 0) {
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
          prev2 = prev;
          prev = current;
          current = cons(prev, current);
          prev = prev2;
          continue;
        case L2:
          current = cons(current,NIL);
          continue;
      }
      D("REJECT", !token, !top, stack());
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
  D(o.str());
  using namespace Parser;
  for (H h = Stack::top; h != 0;) {
    Pair p = S(h).asCons();
    o << !Symbol(p.data);
    if ((h = p.next) == 0)
      break;
    o << " ";
  }
  o << "]]";
  return strdup(o.str().c_str());
}
#endif


