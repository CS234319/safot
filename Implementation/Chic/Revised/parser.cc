#import "parser.h"
#import "Pushdown.cc"

#import "atoms.h"
#import "lexer.cc"
#import "text.cc"

#import <string.h>

#define DEBUG1  

#ifdef DEBUG 
#import <sstream>
#import "dump.h"
#import "io.h"
#else 
#undef D
#define D(...) 0
#define M1(...) 0
#define M2(...) 0
#define M3(...) 0
#define M4(...) 0
#define __(...) 0
#endif

namespace parser {
  /* Formal grammar of S expression
   https://www.cs.princeton.edu/courses/archive/spring20/cos320/LL1/

   // Grammar:
   // Generated automatically S ::= E // Rule S1 
   E ::= X T   
   T ::= . X   
   T ::= ''    
   X ::= ' X   
   X ::= ( L ) 
   X ::= a     
   L ::= E L    
   L ::= ''    

   // AST: 
   E ::= X T   { $$ = NIL;                } // E1
   T ::= . X   { $-1 = pair($-1,$$);      } // T1 Tricky 
   T ::= ''                                 // T2 
   X ::= ' X   { $$ = $1                  } // X1 Copy
   X ::= ( L ) { $$ = $1                  } // X2 Copy
   X ::= a     { $$ = $1                  } // X3 Copy
   L ::= E L   { $$ = pair($1,$$);        } // L1: Pair 
   L ::= ''    { $$ = NIL;                } // L2: Initialize
   */

  static Pushdown stack;
  static enum Status current_status = ready;
  extern enum Status status() {
    return current_status;
  }
  S $$(NIL);
  extern S result() {
    return $$; 
  }

  static void parse();

  extern void supply(char *buffer) {
    D(buffer);
    lexer::initialize(buffer);
    parse();
  }
 
  Symbol token;
  Symbol top;

  void reduce() {
    M4("Reduce",~top,"returns",$$, stack());
  }
 
  void shift(Symbol rule) {
    M4("Shift",~rule,"on", ~token, $$,stack());
    stack.push(rule);            // Which rule we reduce 
    M2("---Shift",stack());
  }

  Short reserve() {
    M2("Reserve",~top, stack());
    stack.push(T);               // reserved location for result, defaults to atom T 
    M2("--Reserve",stack(), stack.top);
    return stack.top.head();
  }

  void store() {
    M4("Store on rule",~top, "of", $$, $$.handle(), ~top, stack());
    Item(stack.pop()).head($$.handle());
    M1(" --Store", $$.handle(), Pairs::get($$.handle()), ~top, stack());
  }

  void shift(Symbol rule, Short h1, Short h2, Short h3) {
    shift(rule);
    stack.push(h1, h2, h3);
    D(h1,h2,h3,stack());
  }

  void shift(Symbol rule, Short h1, Short h2) {
    shift(rule);
    stack.push(h1, h2);
  }

  void shift(Symbol rule, Short h) {
    shift(rule);
    stack.push(h);
  }
  void reset() {
    stack.clear();
    current_status = ready;
    shift(s);
  }

  static void parse() {
    D(stack());
    while (!stack.empty()) {
      top  = (Symbol) stack.pop();
      token = (Symbol) lexer::get();
      __("LOOP", $$, ~token, ~top, stack());
      if (atom(token) && top == Atom) {
        M1("Match Atom", ~token,~top);
        $$ = token;
        continue;
      }
      if (token == top) {
        M1("Match Ignore", ~token,~top);
        continue;
      }
      lexer::unget();
      switch (top) {
        case s:
          if (token == '\'' || token == '(' || atom(token)) {
            Short $1 = reserve();
            shift(s1, E, $1, $); 
            D(stack());
            continue;
          }
          break;
        case s1:
          $$ = stack.pop();
          continue;
        case E:
          if (token == '\'' || token == '(' || atom(token)) {
            shift(E1, X, T);
            continue;
          }
          break;
        case E1:
          store();
          continue;
        case X:
          if (token == '\'') {
            shift(X1,'\'',X); 
            continue;
          }
          if (token == '(') {
            shift(X2, '(', L, ')');
            continue;
          }
          if (atom(token)) {
            $$ = token;
            shift(X3,Atom);
            continue;
          }
          break;
        case X1:
          $$ = S(QUOTE,S($$,NIL)); 
          reduce();
          continue;
        case X2:
          reduce(); 
          continue;
        case X3:
          reduce(); 
          continue;
        case T:
          if (token == '.') {
            stack.poke(1, $$.handle());
            shift(T1, '.', X);
            continue;
          }
          if (text::contains(token, "()'") || token == $ || atom(token)) {
            shift(T2);
            continue;
          }
          break;
        case T1:
          reduce(); 
          M1("Update T1: ",$$, ~top, stack());
          $$ = S(stack.peep(1),$$);
          stack.poke(1,$$.handle());
          M1("Update T1: ",$$, ~top, stack());
          continue;
        case T2:
          reduce(); 
          continue;
        case L:
          if (exists(token,"'(") || atom(token)) {
            Short $1 = reserve(); 
            shift(L1, E, $1, L);
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
          $$ = S(stack.pop(),$$);
          M1("Set", $$);
          continue;
        case L2:
          $$ = NIL;
          reduce(); 
          continue;
      }
      M1("REJECT", ~token, ~top, stack());
      current_status = reject;
      return;
    }
    M1("ACCEPT",$$); 
    current_status = accept;
  }
}
