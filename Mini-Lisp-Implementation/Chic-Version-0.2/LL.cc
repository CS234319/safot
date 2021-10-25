#import "chic.h"
  /* Used in the LL(1) parsing algorithm; integer range tricks are used to
   * represent terminals, non-terminals, and even names of rules as a single
   * handle.  
   */
#import "lexer.cc"
namespace LL {
  enum Symbol: Short { 
    $ = lexer::$, s, Atom, // Special symbols, EOF, S
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
}
#if Implementation
#endif  
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
   L ::= ''    { $$ = NIL;                } // L2: Fill
   */


