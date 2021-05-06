#ifndef PARSER_H
#define PARSER_H
#include "mini-lisp.h"
#include "tokenizer.h"

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
 * </pre>
 */
namespace Parser {
  extern S result(); // Result of parrsing action; undefined if status is not accept 
  enum Status { ready, accept, reject}; // Should still work on resuming after NL 
  extern enum Status status();
  extern void supply(char *input); // What to parse, ideally in installments
  extern void reset(); // Must call before the first supply
  extern void supply(char *input); // What to parse, ideally in installments
  enum Status { ready, accept, reject}; // Should still work on resuming after NL 
  extern enum Status status();     // Returns the result of the most recent supply
  extern S result(); // Result of parrsing action; undefined if status is not accept 

  /* Used in the LL(1) parsing algorithm; integer range tricks are used to
   * represent terminals, non-terminals, and even names of rules as a single
   * handle.  
   */
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
