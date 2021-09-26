#import  "parser.h"
#import  "stack.h"
#import  "tokenizer.h"
#define PRODUCTION
#import  "mode.h"
#import  "atoms.h"

#import  <string.h>

namespace Parser {
  /* Formal grammar of S expression
   https://www.cs.princeton.edu/courses/archive/spring20/cos320/LL1/

  // Good grammar:
E ::= X T   
X ::= a     
T ::= . E   
T ::= ''    
X ::= ' X   
X ::= ( L ) 
L ::= E L    
L ::= ''  
E ::= [ E ]

  // Grammar:
   // Generated automatically S ::= E // Rule S1 
E ::= X T   
X ::= a     
T ::= . X   
T ::= ''    
X ::= ' X   
X ::= ( L ) 
L ::= E L    
L ::= ''    

Note: Observe that this grammar derives the dotted pair atom.atom, by 

E -> X T -> a T -> a . X -> a. a. 
   // AST: 
   E ::= X T   { $$ = NIL;                } // E1
   T ::= . X   { $-1 = cons($-1,$$);      } // T1 Tricky 
   T ::= ''                                 // T2 
   X ::= ' X   { $$ = $1                  } // X1 Copy
   X ::= ( L ) { $$ = $1                  } // X2 Copy
   X ::= a     { $$ = $1                  } // X3 Copy
   L ::= E L   { $$ = cons($1,$$);        } // L1: Cons 
   L ::= ''    { $$ = NIL;                } // L2: Initialize
   */

  static enum Status current_status = ready;
  extern enum Status status() {
    return current_status;
  }
  S $$ = NIL;
  extern S result() {
    return $$; 
  }

  static void parse();

  extern void supply(String buffer) {
    D(buffer);
    Tokenizer::initialize(buffer);
    parse();
  }
 
  Symbol token;
  Symbol top;
  static int p_counter = 0;

  void reduce() {
    M4("Reduce",~top,"returns",$$, stack());
  }

  void store() {
    M4("Store on rule",~top, "of", $$, $$.handle, ~top, stack());
    Pairs::get(Stack::pop()).data = $$.handle;
    M1(" --Store", $$.handle, Pairs::get($$.handle), ~top, stack());
  }

  H &location(H h) {
    return Pairs::get(Stack::peep(h)).data;
  }
 
 void shift(Symbol rule) {
    M4("Shift",~rule,"on", ~token, $$,stack());
    Stack::push(rule);            // Which rule we reduce 
    M2("---Shift",stack());
  }

  H reserve() {
    M2("Reserve",~top, stack());
    Stack::push(T);               // reserved location for result, defaults to atom T 
    M2("--Reserve",stack(), Stack::top);
    return Stack::top;
  }

  void shift(Symbol rule, H h1, H h2, H h3) {
    shift(rule);
    Stack::push(h1, h2, h3);
    D(h1,h2,h3,stack());
  }

  void shift(Symbol rule, H h1, H h2) {
    shift(rule);
    Stack::push(h1, h2);
  }

  void shift(Symbol rule, H h) {
    shift(rule);
    Stack::push(h);
  }
  void reset() {
    Stack::reset();
    current_status = ready;
    shift(s);
  }

  static void parse() {
    D(stack());
    p_counter += getParenthesesBalanceCounter();
    while (!Stack::empty()) {
      if (p_counter != 0 && Tokenizer::peep() == $){
          // If we have $, but the parenthesis are not balanced,
          // we don't want to continue the LL(1) parser with the $.
          //
          // What we want is to continue feeding our parser,
          // with other characters until we have a balanced word.
          //
          // Thus, after we have such a sentence, we can use the $.
          //
          // With that way, we can parse multi-line sentences in REPL.
          //
          current_status = ready;
          return;
      }
      top  = (Symbol) Stack::pop();
      token = (Symbol) Tokenizer::get();
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
      Tokenizer::unget();
      switch (top) {
        case s:
          if (token == '\'' || token == '(' || atom(token)) {
            H $1 = reserve();
            shift(s1, E, $1, $); 
            D(stack());
            continue;
          }
          break;
        case s1:
          $$ = Stack::pop();
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
          $$ = QUOTE.cons($$.cons(NIL)); 
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
            location(1) = $$.handle;
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
          M1("Update T1: ",$$, ~top, stack());
          $$ = S(location(1)).cons($$);
          location(1)= $$.handle;
          M1("Update T1: ",$$, ~top, stack());
          continue;
        case T2:
          reduce(); 
          continue;
        case L:
          if (exists(token,"'(") || atom(token)) {
            H $1 = reserve(); 
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
          $$ = S(Stack::pop()).cons($$);
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
