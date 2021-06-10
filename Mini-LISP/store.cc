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

/*@ Types for S-Expressions@ S-Expressions come in two varieties: (1) Dotted
 pairs (pairs for short) are compound S-expressions defined by two, smaller,
 S-expressions, and (2) atoms, which are a sequence of characters. 

 The type is represents S-expressions of both kinds.  However, this type not
 store the actual data of an S-expression, but rather a handle to this data.
 When the handle is used to access the data, we obtain a value whose type is
 either Atom or Pair */

Type S;     // An S-expression represented by its handle
Type Pair;  // A compound S-expression, i.e., a dotted pair
// Type Atom;  // An atomic S-expression, i.e., a memory address


/*@ Types for S-Expressions@ S-Expressions come in two varieties: 
An atomic S-expression is a C like string: a memory address of a byte storing
the first character, of the atom's text. The full text of an atom
are the characters in this byte and all bytes that follow  until the first 
occurrence of the null byte, i.e., a byte in which all bits are zero, 
denoted in C by \verb/'\0'/ and mathematically by~$\natural$.  */

typedef const char *const Atom; // Underlining representation of atoms as pointers to characters
Type S;
Type Pair;

Type S { // An S-expression represented by its handle
  Representation {
    perspective(Half handle) // The inner representation 
  };
  // construct S(Half h) by (handle(h));
  property bool null() returns (handle == 0)
  property bool atom() returns (handle <= 0)
  property bool pair() returns (handle > 0) 
  property bool eq(S s) returns (atom() && handle == s.handle)
  S(Half h): handle(h) {} 
  property Pair $_p$(); /// Interpreted as handle of pair, retrieves the pair behind (mutable)  
  property Atom $_a$(); /// Interpreted as handle of atom, retrieves its text representation 
};

Type Pair { // The different perspectives of a pair.
  Representation {
    perspective(Word cons)        /// I.   | A single word with two halves: 
    perspective(Half car, cdr)    /// II.  | A pair of car and cdr, each in a half word.
    perspective(Half prev, next)  /// III. | An unused pair item in the list of pairs. 
    perspective(Half head, rest)  /// IV.  | An data item in the stack used in the parser. 
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
  Provides function S make(S car, S cdr); /// Returns (handle of) pair with given values of (handles of) its two components
  Provides function S make(Atom);         /// Returns (handle of) atom with given text; 
  Provides procedure free(S);             /// Marks an S-expression handle previously returned by make as no longer in use 
}

Context Store { 
  // Global:
  Provides constant(Word) $m$;    /// how many bytes are used by the store 
  // Atoms:
  Provides constant(Half) $M_a$;  /// how many atoms are initially available 
  Provides function Half $v_a$(); /// how many chars remain available for allocation 
  Provides function Half $u_a$(); /// how many chars were allocated 
  Allocate Half current = 0;
  // Pairs
  Provides constant(Half) $M_p$;  /// how many pairs are initially available 
  Provides function Half $v_p$(); /// how many pairs remain available for allocation 
  Provides function Half $u_p$(); /// how many pairs were allocated 
}

Context Store { // Prototype for store.h
  Provides data array(char) A;
  Provides data array(Pair) P;
}

Context Store { 
  Let Half $M_a$ = 1 << 12;
  Let Half $M_p$ = (1 << 15) - $M_a$ + 3; 
  Let Word $m$ = $M_a$ + $M_p$ * sizeof (Pair);
  Let Half NIL_SIZE = sizeof "NIL";
}

Allocate static union  {
  char block[Store::$m$];
  struct {
   char $A_0$[Store::$M_a$ - Store::NIL_SIZE];
   char A[Store::NIL_SIZE] = { 'N', 'I', 'L', '\0' };
   Pair P[Store::$M_p$];
  };
} memory; 

Context Store { 
  using Context Store;
constexpr auto x =3;
constexpr auto y = x *x;
  Let array(Pair) P = memory.P - 1;
  Let array(Pair) $P_0$ = memory.P - 1;
  Let array(Pair) $P_1$ = memory.P + $M_p$;
  Let array(char) A  = memory.A;
  Let array(char) $A_0$  = memory.$A_0$;
  Let array(char) $A_1$  = memory.A + $M_a$;
  Let Half $L_a$ = $A_0$ - A, $H_a$ = 0;   
  Let Half $L_p$ = memory.P - P, $H_p$ = $P_1$ - memory.P;   
  Let Half $L$ = min($L_a$, $L_p$ ), $H$ = max($H_a$, $H_p$);
  Let Half $N_p$ = $H_p$ - $L_p$ + 1;
  Let Half $N_a$ = $H_a$ - $H_a$ + 1;
  Let Half $N$ = $H$ - $L$ + 1;
  Half  
}


Context Store {   
}

Context Store {
  Half flip(Half h)   { return h + (1 << 15); } 
  bool red(Half h) { return h < $L$ || h > $H$; } 
  void flip(Pair &p)  { Pair.car = flip(p.car); }
  bool red(Pair p) { return red(p.car);  }
}

/* Making an S expression from an input string is by moving the pool pointer
 * down and then copying the input there. A bit of optimization saves some
 * space by refraining from allocating the same string twice; moreover, there
 * is also a minimal attempt to allow one string to be realizes the suffix of a
 * previously allocated string */ 

static Half size(const char *s) { for (Half $ = 0;; ++$) if (s[$] == '\0') return $ + 1; }
static char upper(char c) { return c < 'a' || c > 'z' ? c : c - 'a' + 'A'; }
static bool eq(const char *s1, const char *s2) {
  for (; upper(*s1) == upper(*s2); ++s1, ++s2)
    if (*s1 == '\0')
      return true;
  return false;
}

S Store::make(Atom s) {
  for (Half $ = 0; $ >= current; --$) 
    if (eq(s, A+$))
      return $;
  const Half n = ::size(s);
  current -= n;
  for (Half h = 0; h < n; ++h) // Only case in code to change the pool 
    const_cast<char&>(A[current + h]) = ::upper(s[h]);
  return S(current);
}

static Half init() {
  for (Half h = $L_p$  + 1; h < $H_p$; ++h) {
    P[h].prev = h - 1;
    P[h].next = h + 1;
  }
  P[$L_p$ ].prev = 0;
  P[$L_p$ ].next = $L_p$  + 1;
  P[$H_p$].prev = $H_p$ - 1;
  P[$H_p$].next = 0;
  for (Half h = $L_p$; h <= $H_p$; ++h) 
    flip[P[h]];
  return $L_p$;
}

static Half next = init;
static Half $v_p$ = $n_p$; 

static Half make(Pair p) {
  const Half h = 1 + (p.cons ^ (p.cons <<< 7)) % $N_p$;
  if (P[h].cons == p.cons) 
    return h;
  if (h == next || !red(P[h])) {
    flip(P[next]);
    next = P[next].next;
    flip(P[next]);
    P[h] = p;
    return h;
  }
  flip(P[h]);
  const Half prev = P[h].prev, next = P[h].next;
  if (prev != 0) {
    flip(P[prev]);
    P[prev].next = next; 
    flip(P[prev]);
  }
  if (next != 0) {
    flip(P[next]);
    P[next].prev = prev; 
    flip(P[next]);
  }
  return h;
}

S make(Half car, Half cdr) {
  return make(Pair(car,cdr));
}

void free(Half h) {
  D(h, remaining);
  pool[h].next = next(), remaining++, next() = h;
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

using Context Store;

TEST(Atoms, $L_a$) { 
  EXPECT_LT($L_a$,0);
  EXPECT_GE(A - $A_0$,$L_a$);
}

TEST(Atoms, $H_a$) { 
  EXPECT_EQ($H_a$, 0);
  EXPECT_EQ((const char *const) A + $H_a$, (const char *const) P);
}

TEST(Atoms, $N$) { 
  EXPECT_GT($H_a$, $L_a$);
  EXPECT_GT($N$, 0);
  EXPECT_EQ($N$, sizeof memory.$A_0$ + 1);
}

TEST(Pairs, $L_p$) { 
  EXPECT_GT($L_p$, $H_a$);
  EXPECT_LT($L_p$, $H_p$);
  EXPECT_EQ($L_p$, 1);
}

TEST(Pairs, $H_p$) { 
  EXPECT_GT($H_p$, $L_p$);
  EXPECT_EQ($H_p$, $N_p$);
  EXPECT_EQ($P_1$ - memory.P, $H_p$);
  EXPECT_EQ($M_p$, $H_p$);
}

TEST(Pairs, $N_p$) { 
  EXPECT_GT($N_p$,0);
  EXPECT_LT($N_p$,sizeof memory);
  EXPECT_LT($N_p$,sizeof memory.P);
  EXPECT_EQ($N_p$, $M_p$);
  EXPECT_EQ($N$,sizeof memory.P / sizeof memory.P[0]);
}

TEST(Store, minimalSize) {
  EXPECT_GT((Half) $M_a$, 100);
  EXPECT_GT((Half) $M_p$, 100);
}

TEST(Store, overflow) {
  EXPECT_GT((Half) $M_p$ + 1, 0);
  EXPECT_LT((Half) - $M_a$ - 1, 0);
}

TEST(Marking, Pairs) { 
  EXPECT_LT(flip($L_p$), $L_a$);   
  EXPECT_LT(flip($H_p$), $L_a$);   
  EXPECT_LT(flip(($L_p$ + $H_p$)/2), $L_a$);   
  EXPECT_LT(flip($L_p$-1), $L_a$);   
  EXPECT_LT(flip($L_p$+1), $L_a$);   
  EXPECT_EQ(flip(flip($p_p$)), $p_p$);
  EXPECT_EQ(flip(flip($H_p$)), $H_p$);
  EXPECT_EQ(flip(flip(($p_p$ + $H_p$)/2)),($p_p$ + $H_p$)/2);
  EXPECT_EQ(flip(flip($H_p$ + 1)),$H_p$ + 1 );
  EXPECT_EQ(flip(flip($H_p$ + 1)), $H_p$ + 1);
}

TEST(Marking, Atoms) { 
  EXPECT_GT(flip($L_a$), $H_a$);   
  EXPECT_LT(flip($H_a$),0);
  EXPECT_GT(flip(($L_a$ + $H_a$)/2), $H_p$);   
  EXPECT_GT(flip($H_a$-1), $H_p$);   
  EXPECT_GT(flip($L_a$+1), $H_p$);   
  EXPECT_EQ(flip(flip($L_a$)), $L_a$);
  EXPECT_EQ(flip(flip($H_a$)), $H_a$);
  EXPECT_EQ(flip(flip(($L_a$ + $H_a$)/2)),($L_a$ + $H_a$)/2);
  EXPECT_EQ(flip(flip($L_a$ + 1)),$L_a$ + 1 );
  EXPECT_EQ(flip(flip($H_a$ + 1)), $H_a$ + 1);
}

TEST(Marking, MarkingIsMarked) { 
  for (Half h = $L$; h <= $H$; ++h)
    EXPECT_TRUE(red(flip(h)));
}

TEST(Store, PrimitiveSizs) { 
  EXPECT_EQ(sizeof(byte), 1);
  EXPECT_EQ(sizeof(char), 1);
  EXPECT_EQ(sizeof(Half), 2);
  EXPECT_EQ(sizeof(Word), 4);
  EXPECT_EQ(sizeof(Pair), 4);
  EXPECT_EQ(sizeof(S), 2);
}

TEST(Store, NIL) {
  EXPECT_STREQ((char *) memory.P, $A_1$);
  EXPECT_STREQ(A, "NIL");
  EXPECT_STREQ((char *)P, "NIL");
}

TEST(Store, innerAndOuterArrays) {
  EXPECT_EQ(A,memory.A);
  EXPECT_GE(P + 1,memory.P);
  EXPECT_LE(P + 1,memory.P);
  EXPECT_EQ(P + 1 - memory.P,0);
  EXPECT_EQ(P + 1,memory.P);
}

TEST(Store, twoArrayAreConsecutive) {
  EXPECT_GE(memory.A + sizeof(memory.A), (char *)memory.P);
  EXPECT_LE(memory.A + sizeof(memory.A), (char *)memory.P);
  EXPECT_EQ(memory.A + sizeof(memory.A) - (char *)memory.P,0);
  EXPECT_EQ((void *)(memory.A + sizeof memory.A), (void *)memory.P); 
}

TEST(Store, computedSize) {
  EXPECT_LE(sizeof memory.block - $m$, 0);
  EXPECT_GE($m$ - sizeof memory.block, 0);
  EXPECT_EQ($m$ - sizeof memory.block, 0);
  EXPECT_EQ(sizeof memory.block, $m$);
}

TEST(Store, actualSize) {
  EXPECT_EQ(sizeof memory.block, sizeof memory);
  EXPECT_EQ(sizeof memory.block - sizeof memory, 0);
  EXPECT_EQ(sizeof memory - sizeof memory.block, 0);
}

TEST(Store, correctCounting) {
  EXPECT_EQ(sizeof memory.block, sizeof memory);
}

TEST(Store, ConversionToIntDoesNotBreakArrayLimits) {
  EXPECT_EQ((Half) $M_a$, $M_a$); 
  EXPECT_EQ((Half) $M_p$, $M_p$); 
}

TEST(ByteOrdering, Word) { 
  union {
    Word w;
    struct {
      Half h1;
      Half h2;
    };
    struct {
      byte b1;
      byte b2;
      byte b3;
      byte b4;
    };
  } v;
  v.w = 0xDEAD'BEEF;
  EXPECT_EQ(v.h1,(Half)  0xBEEF);
  EXPECT_EQ(v.h2,(Half)  0xDEAD);
  EXPECT_EQ(v.b1,(byte)  0xEF);
  EXPECT_EQ(v.b2,(byte)  0xBE);
  EXPECT_EQ(v.b3,(byte)  0xAD);
  EXPECT_EQ(v.b4, (byte) 0xDE);
}

TEST(ByteOrdering, Half) { 
  union {
    Half h;
    struct {
      byte b1;
      byte b2;
    };
  } v;
  v.h = 0xCAFE;
  EXPECT_EQ(v.b1, (byte) 0xFE);
  EXPECT_EQ(v.b2, (byte) 0xCA);
}
