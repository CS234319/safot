#include "mini-lisp.hh"
#include "parser.h"
#include "dump.h"

#include "tokenizer.h"
#define SILENT 1 
#if SILENT
#undef D
#define D(...) 0
#endif

namespace Parser {
  /* Formal grammar of S expression
  https://www.cs.princeton.edu/courses/archive/spring20/cos320/LL1/
E ::= a  
E ::= ( L )   
L ::= S L
L ::= ''

E ::= ' E
E ::= a  
E ::= ( X )   
X ::= E T 
T ::= . E
T ::= L 
L ::= E L 
L ::= '' 



*/
  namespace Stack {
    static H top = 0;
    extern auto push(H data) {
      top = Pairs::allocate(data,top);
    }
    extern auto push(H data1,H data2) {
      push(data2);
      push(data1);
    }
    extern auto push(H data1,H data2, H data3) {
      push(data3);
      push(data1, data2);
    }
    extern bool empty() { return top == 0; } 
    extern H pop() {
      auto free = top;
      auto p = S(top).asCons();
      auto $ = p.data;
      top = p.next;
      Pairs::free(free);
      return $;
    }
  }

  extern S result() {
    return NIL;
  }

  extern enum Status status() {
    return ready;
  }
  extern void supply(char *buffer) {
    Tokenizer::initialize(buffer);
  }
  enum { $ = Tokenizer::$, S, E, X, T, L};
  extern void reset() {
    while (!Stack::empty())
      Stack::pop();
    Stack::push($);
  }

int go() {
	while (!Stack::empty()) {
    auto token = Tokenizer::get();
    auto top = Stack::pop(); 
    if (token == top)
      continue; 
    Tokenizer::unget();
    switch (top) {
      case S: 
        if (token == '\'' || token == '(' || token < 0) {
          Stack::push(E,$);
          continue;
        }
        break;
      case E: 
        if (token == '\'')  { 
          Stack::push('\'',E);
          continue;
        }
        if (token <= 0)  { 
          Stack::push(0,E);
          continue;
        }
        if (token == '(')  { 
          Stack::push('(',X, ')');
          continue;
        }
        break;
      case X: 
        if (token == '\'')  { 
          Stack::push(E,T);
          continue;
        }
        if (token <= 0)  { 
          Stack::push(E,T);
          continue;
        }
        if (token == '(')  { 
          Stack::push('(',X, ')');
          continue;
        }
        break;
       case T: 
        if (token == '\'' || token <= 0 || token == '(' || token == ')') {
          Stack::push(L);
          continue;
        }
        if (token == '.') {
          Stack::push('.',L);
          continue;
        }
        break;
       case L: 
        if (token == '\'' || token <= 0 || token == '(') {
          Stack::push(E,L);
          continue;
        }
        if (token == ')') {
          continue;
        }
        break;
     }
	}
  return 1;
}

}
