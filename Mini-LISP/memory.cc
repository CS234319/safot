/* @Primitive types characterizing the machine@ 
We begin with a  definition  of the basic types that characterize our presumed JVM like machine 
i.e., byte addressable, two-complement and where words (W) are 32 bits wide, 
half words (H) are 16 bits, and bytes (B) are 8 bits. */

#include <cstdint> // Standard header providing width integer types 

typedef int8_t  byte; // A byte, 8 bits 
typedef int16_t H; // Half a word, 16 bits; two bytes
typedef int32_t W; // A full word of 32 bits; four bytes, two half words

/* @S-Expressions and  handles@ An S-expression is either a  dotted pair 
(consistuted by two, smaller, S-expressions) or an atom (which is a string of 
characters.  An S-expression is represented by a 16 bits handle (the 
type H) encoding an integer $h$,
\[2^{15} \le h \le 2^{15}-1\] 

The handle of a dotted pair is always positive. The handle of the 
special atom  NIL is zero; handles of all other atoms are negative. The sign bit 
of a handle is therefore 
a boolean: if it set, then the handle is an atom.
*/
struct S { // handle of S expression
  H h; // the handle
};
/*
A handle makes it possible access the representation of the actual data: in the case
of an  expression.
*/
/* @Represenation of atoms@ Also, for the purpose of our implementation we
represent ``atoms'' (A) as the address of the first byte in sequence of bytes that
end in the null byte, i.e., a byte in which all bits are zero, denoted in C by \verb/'\0'/ and mathematically by~$\natural$. 
\[
\verb/'\0'/ = \natural= 
\begin{tikzpicture}[start chain=going right]
\foreach \i in {1,...,8} \node [draw,on chain] {0};
\end{tikzpicture}
\]
*/

typedef const char *const atom; // Underlining representation of strings as pointers to characters


union pair { // The perspectives of a pair.
  W cons: 32;                         // I.   A single word that can 
  struct { H car, cdr:16; };          // II.  A pair of car and cdr, each in a word.
  struct { H:16; H rest:16; };        // III. An no-data item in the pool of pairs. 
  struct { H data:16; H next:16; };   // IV.  An data item in the stack used in the parser. 
};

/* @Handles as indices@ An S-expresion is either a %
dotted pair (consistuted by two, smaller, S-expressions) or an atom. %
Such an expression is represented by a half-word that represents an integer $h$, %
\[2^{15} \le h \le 2^{15}-1\] 
\begin{description}
    \item[Dotted Pairs] If $h>0$, then the S-experssion that $h$ represents is a %
    dotted-pair. The value of $h$ is interpeted as an index in the pairs' pool: %
    an array $P$ of pairs whose indices are in the range $1,2,\ldots p$, and %
    where $p>0$ is the number of pairs in the the statically allocated %
    memory block used for storing pairs. %

*/

/* 

We need to make array $P$ follow arrary $A$ in memory to conserve as much memory 
as possible. To do so, we allocate a memory block of $a + 4*p$ bytes, and use 
two perspectives to access it.
*/

#define ARRAY(type) type *const

namespace Memory { // Prototype for memory.h
  extern ARRAY(char) A ;
  extern ARRAY(pair) P;
  namespace Atoms { 
   typedef const char* const string;
   extern string retrieve(H h);   
   extern H allocate(string);       // Returns an index in A in which a character sequence is identical to the parameter; 
   extern H available();            // How many characters are still available on A 
   extern bool eq(string, string);  // Check two strings for equality.
   extern string (H index);       //  A convenience method that retrieves a pair by its handle
  };

  namespace Pairs {
    extern H first; 
    extern H allocate(H, H);         //  Retrieve a free pair, and set it values 
    extern void free(H index);       //  Return a pair to the pool
    extern H available();            //  How many pairs are still free 
    extern pair& get(H index);       //  A convenience method that retrieves a pair by its handle
  }
};


namespace Memory { 
  static union  {
    enum: H { a = 1 << 13 }; 
    enum: H { p = 1 << 15 - a }; 
    enum: unsigned H  { n = a + p * sizeof (union pair)};
    enum: H { NIL_SIZE = 4 };
    char block[a + 4 *p];
    struct {
     char A0[a - NIL_SIZE];
     char A[NIL_SIZE] = { 'N', 'I', 'L', '\0' };
     pair P[p];
    };
  } all; 
  ARRAY(pair) P = all.P - 1;
  ARRAY(pair) P0 = all.P - 1;
  ARRAY(pair) P1 = all.P + all.p;
  ARRAY(char) A  = all.A;
  ARRAY(char) A0  = all.A0;
  ARRAY(char) A1  = all.A + all.a;
};
namespace Memory::Pairs {
  enum {min = 1; max = p;};
}


#include "gtest/gtest.h"

TEST(Memory, ByteFlipping) { 
  using namespace Memory;
  EXPECT_EQ(sizeof(byte), 1);
  EXPECT_EQ(sizeof(char), 1);
  EXPECT_EQ(sizeof(H), 2);
  EXPECT_EQ(sizeof(W), 4);
  EXPECT_EQ(sizeof(pair), 4);
};


TEST(Memory, PrimitiveSizs) { 
  using namespace Memory;
  EXPECT_EQ(sizeof(byte), 1);
  EXPECT_EQ(sizeof(char), 1);
  EXPECT_EQ(sizeof(H), 2);
  EXPECT_EQ(sizeof(W), 4);
  EXPECT_EQ(sizeof(pair), 4);
};

TEST(Memory, NIL) {
  using namespace Memory;
  EXPECT_STREQ((char *) all.P, A1);
  EXPECT_STREQ(A, "NIL");
  EXPECT_STREQ((char *)P, "NIL");
};

TEST(Memory, innerAndOuterArrays) {
  using namespace Memory;
  EXPECT_EQ(A,all.A);
  EXPECT_GE(P + 1,all.P);
  EXPECT_LE(P + 1,all.P);
  EXPECT_EQ(P + 1 - all.P,0);
  EXPECT_EQ(P + 1,all.P);
};

TEST(Memory, twoArrayAreConsecutive) {
  using namespace Memory;
  EXPECT_GE(all.A + sizeof(all.A), (char *)all.P);
  EXPECT_LE(all.A + sizeof(all.A), (char *)all.P);
  EXPECT_EQ(all.A + sizeof(all.A) - (char *)all.P,0);
  EXPECT_EQ((void *)(all.A + sizeof all.A), (void *)all.P); 
};

TEST(Memory, totalSize) {
  using namespace Memory;
  EXPECT_EQ(sizeof all.block, all.n);
  EXPECT_EQ(sizeof all.block - all.n, 0);
  EXPECT_EQ(all.n - sizeof all.block, 0);
};

TEST(Memory, ConversionToIntDoesNotBreakEnums) {
  using namespace Memory;
  EXPECT_EQ((H) all.a, all.a); 
  EXPECT_EQ((H) all.p, all.p); 
  EXPECT_EQ((unsigned H) all.n, all.n); 
}


TEST(Memory, minimalSize) {
  using namespace Memory;
  EXPECT_GT((H) all.a, 100);
  EXPECT_GT((H) all.p, 100);
};


TEST(Memory, overflow) {
  using namespace Memory;
  EXPECT_GT((H) all.p + 1, 0);
  EXPECT_LT((H) - all.a - 1, 0);
};


int main(int argc, char **argv) {
//  ::testing::GTEST_FLAG(filter) = "Parser*ListTokenization";//":-:*Counter*";
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

