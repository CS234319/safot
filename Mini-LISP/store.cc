#define Constant(type) enum:type 
#define Context namespace
#define Provides extern
#define Define constexpr 
#define Implements inline

#define function   
#define property inline  
#define procedure void  
#define array(type) type *const

#define text const char* const 
#define constant(type) type & 
#define variable(type) const type 
#define action void
#define modifier 
#define data 

#include <cstdint> // Standard header providing width integer types 

typedef int8_t   byte; /// Byte                         | 8 bits signed integer  | (rarely used)
typedef int16_t  H;    /// Half a word (2 bytes)        | 16 bits signed integer | (used as handle) 
typedef int32_t  W;    /// A word of 32 bits (2 halves) | 32 bits signed integer | (used as pair) 


struct S { // handle of S expression
  H h; // the handle
};

typedef const char *const atom; // Underlining representation of strings as pointers to characters

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

Context Pairs { Provides property variable(pair) fetch(H index); }  ///  Retrieves pair of a handle 
Context Atoms { Provides property constant(text) fetch(H index); }  ///  Retrieves text of a handle 

Context Store { 
  Provides modifier H yield(H, H);    /// Fetch (possibly newly allocated) pair with given contents 
  Provides function H yield(text);    /// Fetch (possibly newly allocated) atom with given contents 
  Provides procedure free(H index);   /// Marks a previously yielded handle as no longer in use 
}

Context Pairs { Provides function H available(); }  /// How many pairs remain available for allocation 
Context Atoms { Provides function H available(); }  /// How many chars remain available for allocation 


Context Store { 
  static union  {
    Constant(H)  { a = 1 << 12 }; 
    Constant(H)  { p = (1 << 15) - a + 3}; 
    Constant(H)  { NIL_SIZE = 4 };
    Constant(W)  { n = a + p * sizeof (union pair)};
    char block[a + 4 *p];
    struct {
     char A0[a - NIL_SIZE];
     char A[NIL_SIZE] = { 'N', 'I', 'L', '\0' };
     pair P[p];
    };
  } all; 
  Define array(pair) P = all.P - 1;
  Define array(pair) P0 = all.P - 1;
  Define array(pair) P1 = all.P + all.p;
  Define array(char) A  = all.A;
  constexpr array(char) A0  = all.A0;
  constexpr array(char) A1  = all.A + all.a;
}

#define MIN(x,y) (x < y ? x : y) 
#define MAX(x,y) (x > y ? x : y) 


Context Atoms { Constant(H) { min = A0 - A,   max = A0 - A };  } 
Context Pairs { Constant(H) { min = P0 - P,   max = P1 - P };  } 
Context Store { Constant(H) { min = MIN(Atoms::min, Pairs::min) };     
Context Store { Constant(H) { max = MAX(Atoms::min, Pairs::min) };     

Context Pairs  { Constant(H) { range = max - min + 1}; };
Context Atoms  { Constant(H) { range = max - min + 1}; }; 
Context Store { Constant(H) { range = max - min + 1}; };

Context Store {
  H mark(H h)   { return h + (1 << 15); } 
  H marked(H h) { return h < Atoms::min || h > Atoms::max; } 
}

#include "gtest/gtest.h"

TEST(Store, RangesAtoms) { 
  using Context Store::Atoms; 
  EXPECT_EQ(A + min, P + 1);
  EXPECT_EQ(A + max, A);
  EXPECT_EQ(range, a  - 4);
};

TEST(Store, RangesPairs) { 
  using Context Store::Pairs; 
  EXPECT_EQ(P + min, Store::P);
  EXPECT_EQ(P + max, Store::P1);
  EXPECT_EQ(range, p);
};


TEST(Store, RangesPairs) { 
  using Context Store::Pairs; 
  EXPECT_EQ(A + Store::min, A0);
  EXPECT_EQ(A + Store::max, A);
};



TEST(Store, MarkingPairs) { 
  using Context Store::Pairs;
  EXPECT_LT(Store::mark(min), Store::Atoms::min);   
  EXPECT_LT(Store::mark(max), Store::Atoms::min);   
  EXPECT_LT(Store::mark((min + max)/2), Store::Atoms::min);   
  EXPECT_LT(Store::mark(max-1), Store::Atoms::min);   
  EXPECT_LT(Store::mark(min+1), Store::Atoms::min);   
  EXPECT_EQ(Store::mark(Store::mark(min)), min);
  EXPECT_EQ(Store::mark(Store::mark(max)), max);
  EXPECT_EQ(Store::mark(Store::mark((min + max)/2)),(min + max)/2);
  EXPECT_EQ(Store::mark(Store::mark(min + 1)),min + 1 );
  EXPECT_EQ(Store::mark(Store::mark(max + 1)), max + 1);
};

TEST(Store, MarkingAtoms) { 
  using Context Store::Atoms;
  EXPECT_GT(Store::mark(min), Store::Pairs::max);   
  EXPECT_LT(Store::mark(max),0);
  EXPECT_GT(Store::mark((min + max)/2), Store::Pairs::max);   
  EXPECT_GT(Store::mark(max-1), Store::Pairs::max);   
  EXPECT_GT(Store::mark(min+1), Store::Pairs::max);   
  EXPECT_EQ(Store::mark(Store::mark(min)), min);
  EXPECT_EQ(Store::mark(Store::mark(max)), max);
  EXPECT_EQ(Store::mark(Store::mark((min + max)/2)),(min + max)/2);
  EXPECT_EQ(Store::mark(Store::mark(min + 1)),min + 1 );
  EXPECT_EQ(Store::mark(Store::mark(max + 1)), max + 1);
};

TEST(Store, MarkingIsMarked) { 
  using Context Store;
  for (H h = min; h <= max; ++h)
    EXPECT_TRUE(marked(mark(h)));
};




TEST(Store, PrimitiveSizs) { 
  using Context Store;
  EXPECT_EQ(sizeof(byte), 1);
  EXPECT_EQ(sizeof(char), 1);
  EXPECT_EQ(sizeof(H), 2);
  EXPECT_EQ(sizeof(W), 4);
  EXPECT_EQ(sizeof(pair), 4);
};

TEST(Store, NIL) {
  using Context Store;
  EXPECT_STREQ((char *) all.P, A1);
  EXPECT_STREQ(A, "NIL");
  EXPECT_STREQ((char *)P, "NIL");
};

TEST(Store, innerAndOuterArrays) {
  using Context Store;
  EXPECT_EQ(A,all.A);
  EXPECT_GE(P + 1,all.P);
  EXPECT_LE(P + 1,all.P);
  EXPECT_EQ(P + 1 - all.P,0);
  EXPECT_EQ(P + 1,all.P);
};

TEST(Store, twoArrayAreConsecutive) {
  using Context Store;
  EXPECT_GE(all.A + sizeof(all.A), (char *)all.P);
  EXPECT_LE(all.A + sizeof(all.A), (char *)all.P);
  EXPECT_EQ(all.A + sizeof(all.A) - (char *)all.P,0);
  EXPECT_EQ((void *)(all.A + sizeof all.A), (void *)all.P); 
};

TEST(Store, totalSize) {
  using Context Store;
  EXPECT_EQ(sizeof all.block, all.n);
  EXPECT_EQ(sizeof all.block - all.n, 0);
  EXPECT_EQ(all.n - sizeof all.block, 0);
};

TEST(Store, ConversionToIntDoesNotBreakArrayLimits) {
  using Context Store;
  EXPECT_EQ((H) all.a, all.a); 
  EXPECT_EQ((H) all.p, all.p); 
}


TEST(Store, minimalSize) {
  using Context Store;
  EXPECT_GT((H) all.a, 100);
  EXPECT_GT((H) all.p, 100);
};


TEST(Store, overflow) {
  using Context Store;
  EXPECT_GT((H) all.p + 1, 0);
  EXPECT_LT((H) - all.a - 1, 0);
};


int main(int argc, char **argv) {
//  ::testing::GTEST_FLAG(filter) = "Parser*ListTokenization";//":-:*Counter*";
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
