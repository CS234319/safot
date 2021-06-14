#include "chic.h"

/*@ The Primitive Types@
Our byte addressable underlining machine offers three primitive types: byte,
half, and, word whose sizes are 8, 16, and 32 bits respectively.  These types
are fixed width signed integers, represented in two's complement, and are
similar to the types byte, short, and int of the Java virtual machine. Punning
is allowed, and used extensively: A word is constituted by two consecutive
halves. No particular byte or halves ordering is assumed. */

typedef int8_t  byte; /// JVM's byte              |  8 bits signed integer | character in an atom
typedef int16_t Half; /// Half a word/JVM's short | 16 bits signed integer | handle of an S-expression 
typedef int32_t Word; /// Machine word/JVM's int  | 32 bits signed integer | an dotted pair S-expression   

/*@ S-Expressions@ S-Expressions come in two varieties: (1) Dotted
 pairs (pairs for short) are compound S-expressions defined by two, smaller,
 S-expressions, and (2) atoms, which are a sequence of characters.  */


/*@ Type S@ represents S-expressions of both kinds. The type does not store the
 actual data of an S-expression, but rather a handle to this data.  When the
 handle is used to access the data, we obtain a value whose type is
 either Atom or Pair 
*/

struct $S_X$;     // An S-expression represented by its handle

/*@ Atoms$ An atomic S-expression is a C like string: a memory address of a
byte storing the first character of the atom's text. The text of an atom is
constituted by characters in this byte and the bytes that follow until the
first occurrence of the null byte, i.e., a byte in which all bits are zero, 
denoted in C by \verb/'\0'/ and mathematically by~$\natural$.  */

typedef const char *const Atom; // Underlining representation of atoms as pointers to characters

Type Pair;  // A compound S-expression, i.e., a dotted pair

struct $S_X$ { // An S-expression represented by its handle
  Representation {
    perspective(Half handle) // The inner representation 
  };
  $S_X$(Half h): handle(h) {}
  property Pair $_p$(); /// Interpreted as handle of pair, retrieves the pair behind (mutable)  
  property Atom $_a$(); /// Interpreted as handle of atom, retrieves its text representation 
};


Type Pair { // The different perspectives of a pair.
  Representation {
    perspective(Word cons)        /// I.   | A single word with two halves: 
    perspective(Half car, cdr)    /// II.  | A pair of car and cdr, each in a half word.
    perspective(Half prev, next)  /// III. | An unused pair item in the list of pairs. 
    perspective(Half head, rest)  /// IV.  | An data item in the stack used in the parser. 
    perspective(Half h1, h2)      /// V.  | A pair of car and cdr, each in a half word.
  };
  Pair(Half r, Half d): car(r), cdr(d) {}
  Pair() {}
};

/*@ The Store$ 
The store provides an abstract memory model that manages the frugal allocation
and de-allocation of S-expressions objects.
*/

Provides function $S_X$ make($S_X$, $S_X$);     /// Returns (handle of) newly allocated pair with given values of (handles of) its two components
Provides function $S_X$ make(Atom);             /// Returns (handle of) of newly allocated atom with given text; 
Provides function $S_X$ require($S_X$, $S_X$);  /// Same as make, but may reuse previously allocated pair
Provides function $S_X$ require(Atom);          /// Same as make, but may reuse previously allocated atom, or suffix of an atom 
Provides function Half free($S_X$);             /// Marks an S-expression handle previously returned by make as no longer in use 

Provides data array(char) A;
Provides data array(Pair) P;

Let Half $M_a$ = 1 << 12; 
Let Half $M_p$ = (1 << 15) - $M_a$ + 2; 

Let Half LIMBO = sizeof "NIL";

Let Half $A_f$ = LIMBO - $M_a$, $A_t$ = 0, $A_n$ = range($A_f$, $A_t$), $A_x$ = $A_f$ -1;
Let Half $P_f$ = 1, $P_t$ = $M_p$, $P_n$ = $M_p$, $P_x$ = 0;
Let Half $X_f$ = min($A_f$, $P_f$), $X_t$ = max($A_t$, $P_t$); 
Let Word $X_n$ = range($X_f$, $X_t$);
Let Half $X_x$ = $X_t$ + 1; 
