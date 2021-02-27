#ifndef PARSER_H
#define PARSER_H
#include "mini-lisp.h"
#include "tokenizer.h"

namespace Parser {
  extern S result();
  enum Status { ready, accept, reject};
  extern enum Status status();
  extern void supply(char *input);
  extern void reset();
  enum Symbol : H {
    $ = Tokenizer::$, s, Atom, // Special symbols, EOF, S
    E, X, T, L, 
    MIN_RULE, // DUMMY 
    s1, // _ ::= E $
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
  inline static auto atom(Symbol s) {
    return s <= 0;
  }
}
#endif
