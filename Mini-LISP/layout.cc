#include "layout.h"
#include "Word.h"

Let Long $m$ = $M_a$ + $M_p$ * sizeof (Word);

static union {
  char block[$m$];
  struct {
   char $A_0$[$M_a$ - LIMBO];
   char A[LIMBO] = { 'N', 'I', 'L', '\0' };
   Word P[$M_p$];
  };
} memory; 

Let array(Word) P = memory.P - 1;
Let array(Word) $P_0$ = memory.P - 1;
Let array(Word) $P_1$ = memory.P + $M_p$;
Let array(char) A  = memory.A;
Let array(char) $A_0$  = memory.$A_0$;
Let array(char) $A_1$  = memory.A + $M_a$;

// Global:
Provides constant(Long) $m$;    /// how many bytes are used by the store 
// Atoms:
Provides constant(Short) $M_a$;  /// how many atoms are initially available 
Provides function Short $v_a$(); /// how many chars remain available for allocation 
Provides function Short $u_a$(); /// how many chars were allocated 
// Pairs
Provides constant(Short) $M_p$;  /// how many pairs are initially available 


Provides Short m$_p$;              /// how many are currently available 
Provides Short made$_p$;           /// how many pairs were made, reuses are counted
Provides Short free$n_p$;          /// how many pairs were freed 
Provides Short collected$n_p$;     /// how many pairs were garbage collected 

#include "Knob.h"
#undef min
#undef max
#undef data
#undef function
#undef Type

#include "gtest/gtest.h"

int main(int argc, char **argv) {
  try {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
  } catch (int i) {
    std::cerr << i;
  }
}

TEST(SExpression, size) { 
  EXPECT_EQ(2, sizeof(Knob));
}

TEST(Atoms, $A_f$) { 
  EXPECT_LT($A_f$,0);
  EXPECT_GE(A - $A_0$,$A_f$);
}

TEST(Atoms, $A_t$) { 
  EXPECT_EQ($A_t$, 0);
  EXPECT_EQ((const char *const) A + $A_t$, (const char *const) P);
}

#define G(X) #X << "=" << X << " "
TEST(Atoms, $X$) { 
  EXPECT_GT($X_t$, 0);
  EXPECT_LT($X_f$, 0);
  EXPECT_EQ($X_n$, (Short)($A_n$ + $P_n$)); 
  EXPECT_EQ($X_n$, $A_n$ + $P_n$); 
  EXPECT_GT($X_t$, $X_f$);
  EXPECT_GT($X_n$, 0); 
  EXPECT_GT($X_n$, $X_t$); 
  EXPECT_EQ($X_n$, INT16_MAX)<< G($A_f$) << G($X_f$) << G($X_t$) << G($A_t$);
}

TEST(Pairs, $P_f$) { 
  EXPECT_GT($P_f$, $A_t$);
  EXPECT_LT($P_f$, $P_t$);
  EXPECT_EQ($P_f$, 1);
}

TEST(Pairs, $P_t$) { 
  EXPECT_GT($P_t$, $P_f$);
  EXPECT_EQ($P_t$, $P_n$);
  EXPECT_EQ($P_1$ - memory.P, $P_t$);
  EXPECT_EQ($M_p$, $P_t$);
}

TEST(Pairs, $P_n$) { 
  EXPECT_GT($P_n$,0);
  EXPECT_LT($P_n$,sizeof memory);
  EXPECT_LT($P_n$,sizeof memory.P);
  EXPECT_EQ($P_n$, $M_p$);
  EXPECT_EQ($M_p$,sizeof memory.P / sizeof memory.P[0]);
}

TEST(Store, minimalSize) {
  EXPECT_GT((Short) $M_a$, 100);
  EXPECT_GT((Short) $M_p$, 100);
}

TEST(Store, overflow) {
  EXPECT_GT((Short) $M_p$ + 1, 0);
  EXPECT_LT((Short) - $M_a$ - 1, 0);
}


TEST(Array, Properties) {
  EXPECT_TRUE($A_x$ < $A_f$ || $A_x$ > $A_t$);
  EXPECT_TRUE($A_f$ < $A_t$);
  EXPECT_TRUE($A_n$ > 0);
  EXPECT_EQ($A_t$ - $A_f$ + 1, $A_n$);

  EXPECT_TRUE($P_f$ < $P_t$);
  EXPECT_TRUE($P_n$ > 0);
  EXPECT_TRUE($P_x$ < $P_f$ || $P_x$ > $P_t$);
  EXPECT_EQ($P_t$ - $P_f$ + 1,  $P_n$);

  EXPECT_TRUE($X_x$ < $X_f$ || $X_x$ > $X_t$);
  EXPECT_TRUE($X_f$ < $X_t$);
  EXPECT_TRUE($X_n$ > 0);
  EXPECT_EQ($X_t$ - $X_f$ + 1, $X_n$);
}

TEST(Store, PrimitiveSizs) { 
  struct S: Knob {};
  EXPECT_EQ(sizeof(byte), 1);
  EXPECT_EQ(sizeof(char), 1);
  EXPECT_EQ(sizeof(Short), 2);
  EXPECT_EQ(sizeof(Long), 4);
  EXPECT_EQ(sizeof(Word), 4);
  EXPECT_EQ(sizeof(Knob), 2);
  EXPECT_EQ(sizeof(S), 2);
}

TEST(Store, LIMBO) {
  EXPECT_STREQ(A, "NIL");
  EXPECT_STREQ((char *)P, "NIL");
}

TEST(Store, NIL) {
  EXPECT_STREQ((char *) (memory.P - 1), memory.A);
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
  EXPECT_EQ((Short) $M_a$, $M_a$); 
  EXPECT_EQ((Short) $M_p$, $M_p$); 
}

TEST(ByteOrdering, Long) { 
  union {
    Long w;
    struct {
      Short s1;
      Short s2;
    };
    struct {
      byte b1;
      byte b2;
      byte b3;
      byte b4;
    };
  } v;
  v.w = 0xDEAD'BEEF;
  EXPECT_EQ(v.s1,(Short)  0xBEEF);
  EXPECT_EQ(v.s2,(Short)  0xDEAD);
  EXPECT_EQ(v.b1,(byte)  0xEF);
  EXPECT_EQ(v.b2,(byte)  0xBE);
  EXPECT_EQ(v.b3,(byte)  0xAD);
  EXPECT_EQ(v.b4, (byte) 0xDE);
}

TEST(ByteOrdering, Short) { 
  union {
    Short h;
    struct {
      byte b1;
      byte b2;
    };
  } v;
  v.h = 0xCAFE;
  EXPECT_EQ(v.b1, (byte) 0xFE);
  EXPECT_EQ(v.b2, (byte) 0xCA);
}
