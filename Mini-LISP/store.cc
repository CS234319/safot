#include "chic.h"

/*@ The Primitive Types@
Our byte addressable underlining machine offers three primitive types: byte,
half, and, word whose sizes are 8, 16, and 32 bits respectively.  These types
are fixed width signed integers, represented in two's complement, and are
similar to the types byte, short, and int of the Java virtual machine. Punning
is allowed, and used extensively: A word is constituted by two consecutive
halves. No particular byte or halves ordering is assumed. */

typedef int8_t  byte; /// JVM's byte              |  8 bits signed integer | character in an atom
typedef int16_t half; /// Half a word/JVM's short | 16 bits signed integer | handle of an S-expression 
typedef int32_t word; /// Machine word/JVM's int  | 32 bits signed integer | an dotted pair S-expression   


/*@ Types for S-Expressions@ S-Expressions come in two varieties: (1) Dotted
 pairs (pairs for short) are compound S-expressions defined by two, smaller,
 S-expressions, and (2) atoms, which are a sequence of characters. 

 The type is represents S-expressions of both kinds.  However, this type not
 store the actual data of an S-expression, but rather a handle to this data.
 When the handle is used to access the data, we obtain a value whose type is
 either Atom or Pair */

Type S;     // An S-expression represented by its handle
Type Pair;  // A compound S-expression, i.e., a dotted pair
Type Atom;  // An atomic S-expression, i.e., a memory address


/*@ Types for S-Expressions@ S-Expressions come in two varieties: 
An atomic S-expression is a C like string: a memory address of a byte storing
the first character, of the atom's text. The full text of an atom
are the characters in this byte and all bytes that follow  until the first 
occurrence of the null byte, i.e., a byte in which all bits are zero, 
denoted in C by \verb/'\0'/ and mathematically by~$\natural$.  */

typedef const byte *const Atom; // Underlining representation of atoms as pointers to characters
Type S;
Type Pair;

Type S { // An S-expression represented by its handle
  Representation {
    perspective(half handle) // The inner representation 
  };
  // construct S(half h) by (handle(h));
  property bool null() returns (handle == 0)
  property bool atom() returns (handle <= 0)
  property bool pair() returns (handle > 0) 
  property bool eq(S s) returns (atom() && handle == s.handle)
  property Pair $_p$(); /// Interpreted as handle of pair, retrieves the pair behind (mutable)  
  property Atom $_a$(); /// Interpreted as handle of atom, retrieves its text representation 
};

Type Pair { // The different perspectives of a pair.
  Representation {
    perspective(word cons)        /// I.   | A single word with two halves: 
    perspective(const S car, cdr)       /// II.  | A pair of car and cdr, each in a half word.
    perspective(half foo, rest)   /// III. | An unused pair item in the list of pairs. 
    perspective(half value, next) /// IV.  | An data item in the stack used in the parser. 
  };
};


/*@ The Store$ 
The store provides an abstract memory model that manages the allocation and 
delallocation of S-expressions objects. These come in two varieites: Atomic 
S-expressions, the Pair,
whihstorage two kinds of entities:
the Pair, which represents 
fo higher levels of the . However, other portions of the implementation need
not worry about
the details of the frugality. Here we present an abstract model of a 
``store'' and the services it provides. 
*/

Context Store {
  Provides function S make(S, S);           /// Returns (handle of) pair with given values of (handles of) its two components
  Provides function S make(Atom);           /// Returns (handle of) atom with given text; 
  Provides procedure free(S);               /// Marks an S-expession handle previously returned by make as no longer in use 
}

Context Store { 
  Provides constant(word) $m$;                   /// halfow many bytes are used by the store 
  Provides constant(half) $M_1$;                 /// halfow many atoms are initially available 
  Provides constant(half) $M_2$;                 /// halfow many pairs are initially available 
  Provides function half available();            /// halfow many pairs remain available for allocation 
  Provides function half allocated();            /// halfow many pairs were allocated 
  Provides function half available();            /// halfow many chars remain available for allocation 
  Provides function half allocated();            /// halfow many chars were allocated 
}

Context Store { // Prototype for store.h
  Provides data array(char) A;
  Provides data array(Pair) P;
}

Context Store { 
  Let half $M_1$ = 1 << 12;
  Let half $M_2$ = (1 << 15) - $M_1$ + 3; 
  Let word $m$ = $M_1$ + $M_2$ * sizeof (Pair);
  Let half NIL_SIZE = sizeof "NIL";
}

static union  {
  char block[Store::$m$];
  struct {
   char A0[Store::$M_1$ - Store::NIL_SIZE];
   char A[Store::NIL_SIZE] = { 'N', 'I', 'L', '\0' };
   Pair P[Store::$M_2$];
  };
} memory; 


Context Store { 
  Let array(Pair) P = memory.P - 1;
  Let array(Pair) P0 = memory.P - 1;
  Let array(Pair) P1 = memory.P + $M_2$;
  Let array(char) A  = memory.A;
  Let array(char) A0  = memory.A0;
  Let array(char) A1  = memory.A + $M_1$;
}

Context Atoms { Let half $h_0$ = Store::A0 - Store::A, $h_1$ = 0;  } 
Context Pairs { Let half $h_0$ = memory.P - Store::P, $h_1$ = Store::P1 - memory.P;  } 


Context Store {   
  Let half $h_0$ = min(Atoms::$h_0$, Pairs::$h_0$), $h_1$ = max(Atoms::$h_1$, Pairs::$h_1$);
}

Context Pairs { Let half $n$ = $h_1$ - $h_0$ + 1; };
Context Atoms { Let half $n$ = $h_1$ - $h_0$ + 1; }; 
Context Store { Let half $n$ = $h_1$ - $h_0$ + 1; };

Context Store {
  half mark(half h)   { return h + (1 << 15); } 
  half marked(half h) { return h < Atoms::$h_0$ || h > Atoms::$h_1$; } 
}

#undef min
#undef max
#undef data
#undef function
#undef Type
#include "gtest/gtest.h"

int main(int argc, char **argv) {
//  ::testing::GTEST_FLAG(filter) = "Parser*ListTokenization";//":-:*Counter*";
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
TEST(SExpression, size) { 
  EXPECT_EQ(2, sizeof(S));
}


TEST(Atoms, $h_0$) { 
  using Context Atoms; 
  EXPECT_LT($h_0$,0);
  EXPECT_GE(Store::A - Store::A0,$h_0$);
}

TEST(Atoms, $h_1$) { 
  using Context Atoms; 
  EXPECT_EQ($h_1$, 0);
  EXPECT_EQ((Atom) Store::A + $h_1$, (Atom) Store::P);
}

TEST(Atoms, $n$) { 
  using Context Atoms; 
  EXPECT_GT($h_1$, $h_0$);
  EXPECT_GT($n$, 0);
  EXPECT_EQ($n$, sizeof memory.A0 + 1);
}

TEST(Pairs, $h_0$) { 
  using Context Pairs; 
  EXPECT_EQ($h_0$, 1);
}

TEST(Pairs, $h_1$) { 
  using Context Pairs; 
  EXPECT_GT($h_1$, $h_0$);
  EXPECT_EQ($h_1$, $n$);
  EXPECT_EQ(Store::P1 - memory.P, $h_1$);
  EXPECT_EQ(Store::$M_2$, $h_1$);
}

TEST(Pairs, $n$) { 
  using Context Pairs; 
  EXPECT_GT($n$,0);
  EXPECT_LT($n$,sizeof memory);
  EXPECT_LT($n$,sizeof memory.P);
  EXPECT_EQ($n$, Store::$M_2$);
  EXPECT_EQ($n$,sizeof memory.P / sizeof memory.P[0]);
}

TEST(Store, minimalSize) {
  using Context Store;
  EXPECT_GT((half) $M_1$, 100);
  EXPECT_GT((half) $M_2$, 100);
}

TEST(Store, overflow) {
  using Context Store;
  EXPECT_GT((half) $M_2$ + 1, 0);
  EXPECT_LT((half) - $M_1$ - 1, 0);
}

TEST(Marking, Pairs) { 
  using Context Pairs;
  EXPECT_LT(Store::mark($h_0$), Atoms::$h_0$);   
  EXPECT_LT(Store::mark($h_1$), Atoms::$h_0$);   
  EXPECT_LT(Store::mark(($h_0$ + $h_1$)/2), Atoms::$h_0$);   
  EXPECT_LT(Store::mark($h_1$-1), Atoms::$h_0$);   
  EXPECT_LT(Store::mark($h_0$+1), Atoms::$h_0$);   
  EXPECT_EQ(Store::mark(Store::mark($h_0$)), $h_0$);
  EXPECT_EQ(Store::mark(Store::mark($h_1$)), $h_1$);
  EXPECT_EQ(Store::mark(Store::mark(($h_0$ + $h_1$)/2)),($h_0$ + $h_1$)/2);
  EXPECT_EQ(Store::mark(Store::mark($h_0$ + 1)),$h_0$ + 1 );
  EXPECT_EQ(Store::mark(Store::mark($h_1$ + 1)), $h_1$ + 1);
}

TEST(Marking, Atoms1) { 
  using Context Atoms;
  EXPECT_GT(Store::mark($h_0$), $h_1$);   
  EXPECT_LT(Store::mark($h_1$),0);
  EXPECT_GT(Store::mark(($h_0$ + $h_1$)/2), Pairs::$h_1$);   
  EXPECT_GT(Store::mark($h_1$-1), Pairs::$h_1$);   
  EXPECT_GT(Store::mark($h_0$+1), Pairs::$h_1$);   
  EXPECT_EQ(Store::mark(Store::mark($h_0$)), $h_0$);
  EXPECT_EQ(Store::mark(Store::mark($h_1$)), $h_1$);
  EXPECT_EQ(Store::mark(Store::mark(($h_0$ + $h_1$)/2)),($h_0$ + $h_1$)/2);
  EXPECT_EQ(Store::mark(Store::mark($h_0$ + 1)),$h_0$ + 1 );
  EXPECT_EQ(Store::mark(Store::mark($h_1$ + 1)), $h_1$ + 1);
}

TEST(Marking, Atoms2) { 
  using Context Atoms;
  EXPECT_GT(Store::mark($h_0$), $h_1$);   
  EXPECT_LT(Store::mark($h_1$),0);
  EXPECT_GT(Store::mark(($h_0$ + $h_1$)/2), Pairs::$h_1$);   
  EXPECT_GT(Store::mark($h_1$-1), Pairs::$h_1$);   
  EXPECT_GT(Store::mark($h_0$+1), Pairs::$h_1$);   
  EXPECT_EQ(Store::mark(Store::mark($h_0$)), $h_0$);
  EXPECT_EQ(Store::mark(Store::mark($h_1$)), $h_1$);
  EXPECT_EQ(Store::mark(Store::mark(($h_0$ + $h_1$)/2)),($h_0$ + $h_1$)/2);
  EXPECT_EQ(Store::mark(Store::mark($h_0$ + 1)),$h_0$ + 1 );
  EXPECT_EQ(Store::mark(Store::mark($h_1$ + 1)), $h_1$ + 1);
}

TEST(Marking, MarkingIsMarked) { 
  using Context Store;
  for (half h = $h_0$; h <= $h_1$; ++h)
    EXPECT_TRUE(marked(mark(h)));
}

TEST(Store, PrimitiveSizs) { 
  using Context Store;
  EXPECT_EQ(sizeof(byte), 1);
  EXPECT_EQ(sizeof(char), 1);
  EXPECT_EQ(sizeof(half), 2);
  EXPECT_EQ(sizeof(word), 4);
  EXPECT_EQ(sizeof(Pair), 4);
  EXPECT_EQ(sizeof(S), 2);
}

TEST(Store, NIL) {
  using Context Store;
  EXPECT_STREQ((char *) memory.P, A1);
  EXPECT_STREQ(A, "NIL");
  EXPECT_STREQ((char *)P, "NIL");
}

TEST(Store, innerAndOuterArrays) {
  using Context Store;
  EXPECT_EQ(A,memory.A);
  EXPECT_GE(P + 1,memory.P);
  EXPECT_LE(P + 1,memory.P);
  EXPECT_EQ(P + 1 - memory.P,0);
  EXPECT_EQ(P + 1,memory.P);
}

TEST(Store, twoArrayAreConsecutive) {
  using Context Store;
  EXPECT_GE(memory.A + sizeof(memory.A), (char *)memory.P);
  EXPECT_LE(memory.A + sizeof(memory.A), (char *)memory.P);
  EXPECT_EQ(memory.A + sizeof(memory.A) - (char *)memory.P,0);
  EXPECT_EQ((void *)(memory.A + sizeof memory.A), (void *)memory.P); 
}

TEST(Store, computedSize) {
  using Context Store;
  EXPECT_LE(sizeof memory.block - $m$, 0);
  EXPECT_GE($m$ - sizeof memory.block, 0);
  EXPECT_EQ($m$ - sizeof memory.block, 0);
  EXPECT_EQ(sizeof memory.block, $m$);
}

TEST(Store, actualSize) {
  using Context Store;
  EXPECT_EQ(sizeof memory.block, sizeof memory);
  EXPECT_EQ(sizeof memory.block - sizeof memory, 0);
  EXPECT_EQ(sizeof memory - sizeof memory.block, 0);
}

TEST(Store, correctCounting) {
  using Context Store;
  EXPECT_EQ(sizeof memory.block, sizeof memory);
}

TEST(Store, ConversionToIntDoesNotBreakArrayLimits) {
  using Context Store;
  EXPECT_EQ((half) $M_1$, $M_1$); 
  EXPECT_EQ((half) $M_2$, $M_2$); 
}

TEST(ByteOrdering, Word) { 
  union {
    word w;
    struct {
      half h1;
      half h2;
    };
    struct {
      byte b1;
      byte b2;
      byte b3;
      byte b4;
    };
  } v;
  v.w = 0xDEAD'BEEF;
  EXPECT_EQ(v.h1,(half)  0xBEEF);
  EXPECT_EQ(v.h2,(half)  0xDEAD);
  EXPECT_EQ(v.b1,(byte)  0xEF);
  EXPECT_EQ(v.b2,(byte)  0xBE);
  EXPECT_EQ(v.b3,(byte)  0xAD);
  EXPECT_EQ(v.b4, (byte) 0xDE);
}

TEST(ByteOrdering, Half) { 
  union {
    half h;
    struct {
      byte b1;
      byte b2;
    };
  } v;
  v.h = 0xCAFE;
  EXPECT_EQ(v.b1, (byte) 0xFE);
  EXPECT_EQ(v.b2, (byte) 0xCA);
}


