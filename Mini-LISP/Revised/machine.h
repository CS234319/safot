#ifndef SX_H
#define SX_H

/*@ S-Expressions@ S-Expressions come in two varieties: (1) Dotted
 pairs (pairs for short) are compound S-expressions defined by two, smaller,
 S-expressions, and (2) atoms, which are a sequence of characters.  */


/*@ Type S@ represents S-expressions of both kinds. The type does not store the
 actual data of an S-expression, but rather a handle to this data.  When the
 handle is used to access the data, we obtain a value whose type is
 either Atom or Cons 
*/

Type Handle;     // An S-expression represented by its handle

/*@ Atoms$ An atomic S-expression is a C like string: a memory address of a
byte storing the first character of the atom's text. The text of an atom is
constituted by characters in this byte and the bytes that follow until the
first occurrence of the null byte, i.e., a byte in which all bits are zero, 
denoted in C by \verb/'\0'/ and mathematically by~$\natural$.  */

typedef const char *const Atom; // Underlining representation of atoms as pointers to characters

Type Cons;  // A compound S-expression, i.e., a dotted Cons


Type Cons { // The different perspectives of a Cons.
  Representation {
    perspective(Long w)        /// I.   | A single Long with two halves: 
    perspective(Short s1, s2)      /// V.  | A Cons of car and cdr, each in a Short Long.
  };
  auto set(Long w) { this->w = w; return this;}
  Cons(Short s1, Short s2): s1(s1), s2(s2) {}
  Cons() {}
};

/*@ The Store$ 
The store provides an abstract memory model that manages the frugal allocation
and de-allocation of S-expressions objects.
*/

Provides function Handle require(Handle, Handle);  /// Returns (handle of) newly allocated Cons with given values of (handles of) its two components
Provides function Handle require(Atom);          /// Returns (handle of) newly allocated atom with given text; 

// Provides function Handle make(Handle, Handle);     /// Returns (handle of) newly allocated Cons with given values of (handles of) its two components


Provides array(char) A;
Provides array(Cons) P;

Let Short $M_a$ = 1 << 12; 
Let Short $M_p$ = (1 << 15) - $M_a$ + 2; 

Let Short LIMBO = sizeof "NIL";

Let Short $A_f$ = LIMBO - $M_a$, $A_t$ = 0, $A_n$ = range($A_f$, $A_t$), $A_x$ = $A_f$ -1;
Let Short $P_f$ = 1, $P_t$ = $M_p$, $P_n$ = $M_p$, $P_x$ = 0;
Let Short $X_f$ = min($A_f$, $P_f$), $X_t$ = max($A_t$, $P_t$); 
Let Long $X_n$ = range($X_f$, $X_t$);
Let Short $X_x$ = $X_t$ + 1; 
#endif
