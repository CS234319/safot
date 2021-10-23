#import "chic.h"
#import "lexer.cc"
#import "S.cc"

/** An implementation of a simple, single instance hand tailored LL(1) parser.
 * Here is pseudo code describing its services.
 * <pre>
 * reset();
 * supply(buffer);
 * switch (status()) {
 *  case accept: use result() to retrieve tree 
 *  case reject: use reset() to supply() some more
 *  case ready: supply() some more; parser is waiting
 * }
 * </pre> */
namespace parser {
  extern S result(); // Result of parsing action; undefined if status is not accept 
  enum Status { ready, accept, reject}; // Should still work on resuming after NL 
  extern enum Status status();
  extern void supply(char *input); // What to parse, possibly in installments
  extern void reset(); // Must call before the first supply
}

#if Implementation

#import "Pushdown.cc"
#import "LL.cc"
namespace parser { 
  using namespace LL;
  using LL::Symbol;
  inline static auto atom(Symbol s) is(s <= 0)
  Pushdown stack;
  enum Status current_status = ready;
}

#import "Pushdown.cc"
#import "atoms.h"
#import "lexer.cc"
#import "text.cc"
#import "LL.cc"

#import <string.h>

#define PRODUCTION
#import "mode.h"
namespace parser {
  using LL::Symbol;
  Symbol token;
  Symbol top;
  extern enum Status status() is(current_status)
  S $$(NIL);
  extern S result() is($$) 

  static void parse();

  extern void supply(char *buffer) {
    D(buffer);
    lexer::reset(buffer);
    parse();
  }

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
    stack.push(LL::T);               // reserved location for result, defaults to atom T 
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
        $$ = S(token);
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
          $$ = S(stack.pop());
          continue;
        case E:
          if (token == '\'' || token == '(' || atom(token)) {
            shift(E1, X, LL::T);
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
            $$ = S(token);
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
        case LL::T:
          if (token == '.') {
            stack.poke(1, $$.handle());
            shift(T1, '.', X);
            continue;
          }
          if (Text("()'").contains(token) || token == $ || atom(token)) {
            shift(T2);
            continue;
          }
          break;
        case T1:
          reduce(); 
          M1("Update T1: ",$$, ~top, stack());
          $$ = S(S(stack.peep(1)),$$);
          stack.poke(1,$$.handle());
          M1("Update T1: ",$$, ~top, stack());
          continue;
        case T2:
          reduce(); 
          continue;
        case L:
          if (Text("(").contains(token) || atom(token)) {
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
          $$ = S(S(stack.pop()),$$);
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
#endif
