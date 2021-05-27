// Poor man's edition of a bit cleaner C/C++
// 
#include <cstdint> // Standard header providing integer types with widths 

#define Context namespace
#define Provides extern
#define Let constexpr 

#define function   
#define property inline  
#define procedure void  
#define array(type) type *const

#define text const char* const // Underlining representation of atoms as pointers to characters

#define constant(type) type & 
#define variable(type) const type 
#define action void
#define modifier 
#define data 

#define max(x,y) (x > y ? x : y) 
#define min(x,y) (x < y ? x : y) 

typedef int8_t   byte; /// Byte                         | 8 bits signed integer  | (rarely used)
typedef int16_t  H;    /// Half a word (2 bytes)        | 16 bits signed integer | (used as handle) 
typedef int32_t  W;    /// A word of 32 bits (2 halves) | 32 bits signed integer | (used as pair) 

struct S { // handle of S expression
  H h; // the handle
};

union pair { // The perspectives of a pair.
  W cons: 32;                         /// I.   | A single word that can 
  struct { H car, cdr:16; };          /// II.  | A pair of car and cdr, each in a word.
  struct { H:16; H rest:16; };        /// III. | An no-data item in the pool of pairs. 
  struct { H data:16; H next:16; };   /// IV.  | An data item in the stack used in the parser. 
};

Context Store { // Prototype for store.h
  Provides data array(char) A;
  Provides data array(pair) P;
}

Context Pairs { Provides property variable(pair) fetch(H index); }  ///  Retrieves the pair behind a positive handle (mutable)  
Context Atoms { Provides property constant(text) fetch(H index); }  ///  Retrieves text of a handle (immutable) 

Context Store { 
  Provides procedure free(H index);   /// Marks a previously yielded handle as no longer in use 
  Provides modifier H yield(H, H);    /// Returns handle of pair with given values of its two handles 
  Provides function H yield(text);    /// Returns handle of atom with given text; 
  extern const H a;
  //, p, n; 
}

Context Pairs { Provides function H available(); }  /// How many pairs remain available for allocation 
Context Atoms { Provides function H available(); }  /// How many chars remain available for allocation 

Context Store { 
  Let H a = 1 << 12;
  Let H p = (1 << 15) - a + 3; 
  Let W n = a + p * sizeof (union pair);
  Let H NIL_SIZE = sizeof "NIL";
}

static union  {
  char block[Store::a + 4 * Store::p];
  struct {
   char A0[Store::a - Store::NIL_SIZE];
   char A[Store::NIL_SIZE] = { 'N', 'I', 'L', '\0' };
   pair P[Store::p];
  };
} all; 


Context Store { 
  Let array(pair) P = all.P - 1;
  Let array(pair) P0 = all.P - 1;
  Let array(pair) P1 = all.P + p;
  Let array(char) A  = all.A;
  Let array(char) A0  = all.A0;
  Let array(char) A1  = all.A + a;
}

Context Atoms { Let H $h_0$ = Store::A0 - Store::A, $h_1$ = 0;  } 
Context Pairs { Let H $h_0$ = all.P - Store::P, $h_1$ = Store::P1 - all.P;  } 

Context Store {   
  Let H $h_0$ = min(Atoms::$h_0$, Pairs::$h_0$), $h_1$ = max(Atoms::$h_1$, Pairs::$h_1$);
}

Context Pairs { Let H $n$ = $h_1$ - $h_0$ + 1; };
Context Atoms { Let H $n$ = $h_1$ - $h_0$ + 1; }; 
Context Store { Let H $n$ = $h_1$ - $h_0$ + 1; };

Context Store {
  H mark(H h)   { return h + (1 << 15); } 
  H marked(H h) { return h < Atoms::$h_0$ || h > Atoms::$h_1$; } 
}

#undef min
#undef max
#undef data
#undef function
#include "gtest/gtest.h"

int main(int argc, char **argv) {
//  ::testing::GTEST_FLAG(filter) = "Parser*ListTokenization";//":-:*Counter*";
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
TEST(Atoms, $h_0$) { 
  using Context Atoms; 
  EXPECT_LT($h_0$,0);
  EXPECT_GE(Store::A - Store::A0,$h_0$);
}

TEST(Atoms, $h_1$) { 
  using Context Atoms; 
  EXPECT_EQ($h_1$, 0);
  EXPECT_EQ(Store::A + $h_1$, (text) Store::P);
}

TEST(Atoms, $n$) { 
  using Context Atoms; 
  EXPECT_GT($h_1$, $h_0$);
  EXPECT_GT($n$, 0);
  EXPECT_EQ($n$, sizeof all.A0 + 1);
}

TEST(Pairs, $h_0$) { 
  using Context Pairs; 
  EXPECT_EQ($h_0$, 1);
}

TEST(Pairs, $h_1$) { 
  using Context Pairs; 
  EXPECT_GT($h_1$, $h_0$);
  EXPECT_EQ($h_1$, $n$);
  EXPECT_EQ(Store::P1 - all.P, $h_1$);
  EXPECT_EQ(Store::p, $h_1$);
}

TEST(Pairs, $n$) { 
  using Context Pairs; 
  EXPECT_GT($n$,0);
  EXPECT_LT($n$,sizeof all);
  EXPECT_LT($n$,sizeof all.P);
  EXPECT_EQ($n$, Store::p);
  EXPECT_EQ($n$,sizeof all.P / sizeof all.P[0]);
}

TEST(Store, minimalSize) {
  using Context Store;
  EXPECT_GT((H) a, 100);
  EXPECT_GT((H) p, 100);
}

TEST(Store, overflow) {
  using Context Store;
  EXPECT_GT((H) p + 1, 0);
  EXPECT_LT((H) - a - 1, 0);
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
  for (H h = $h_0$; h <= $h_1$; ++h)
    EXPECT_TRUE(marked(mark(h)));
}

TEST(Store, PrimitiveSizs) { 
  using Context Store;
  EXPECT_EQ(sizeof(byte), 1);
  EXPECT_EQ(sizeof(char), 1);
  EXPECT_EQ(sizeof(H), 2);
  EXPECT_EQ(sizeof(W), 4);
  EXPECT_EQ(sizeof(pair), 4);
}

TEST(Store, NIL) {
  using Context Store;
  EXPECT_STREQ((char *) all.P, A1);
  EXPECT_STREQ(A, "NIL");
  EXPECT_STREQ((char *)P, "NIL");
}

TEST(Store, innerAndOuterArrays) {
  using Context Store;
  EXPECT_EQ(A,all.A);
  EXPECT_GE(P + 1,all.P);
  EXPECT_LE(P + 1,all.P);
  EXPECT_EQ(P + 1 - all.P,0);
  EXPECT_EQ(P + 1,all.P);
}

TEST(Store, twoArrayAreConsecutive) {
  using Context Store;
  EXPECT_GE(all.A + sizeof(all.A), (char *)all.P);
  EXPECT_LE(all.A + sizeof(all.A), (char *)all.P);
  EXPECT_EQ(all.A + sizeof(all.A) - (char *)all.P,0);
  EXPECT_EQ((void *)(all.A + sizeof all.A), (void *)all.P); 
}

TEST(Store, computedSize) {
  using Context Store;
  EXPECT_EQ(sizeof all.block, n);
  EXPECT_EQ(sizeof all.block - n, 0);
  EXPECT_EQ(n - sizeof all.block, 0);
}

TEST(Store, actualSize) {
  using Context Store;
  EXPECT_EQ(sizeof all.block, sizeof all);
  EXPECT_EQ(sizeof all.block - sizeof all, 0);
  EXPECT_EQ(sizeof all - sizeof all.block, 0);
}

TEST(Store, correctCounting) {
  using Context Store;
  EXPECT_EQ(sizeof all.block, sizeof all);
}

TEST(Store, ConversionToIntDoesNotBreakArrayLimits) {
  using Context Store;
  EXPECT_EQ((H) a, a); 
  EXPECT_EQ((H) p, p); 
}



