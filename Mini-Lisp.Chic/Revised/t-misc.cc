#import "chic.h"
#import "Short.h"
#import "layout.h"
#import "Word.h"
#import "Knob.h"
#import "Pristine.h"
#import "Account.h"
#import "Handle.h"
#import "layout.h"
#import "text.h"
#import "Test.h"
#import "Clicker.h"

#import "Test.h"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(Memory, TotalSize) {
  using namespace std;
  EXPECT_EQ($A_n$, 4093);
  EXPECT_EQ($P_n$, 28674);
  EXPECT_EQ($P_n$ *sizeof(Word) + $A_n$ * sizeof(char), 118789);
}

TEST(Text, reusing) {
  EXPECT_EQ(LIMBO, 1 + strlen("NIL"));
  EXPECT_EQ(request("Hello").handle(), request("Hello").handle());
  EXPECT_EQ(request("World").handle(), request("World").handle());
  EXPECT_EQ(request("d").handle(), request("d").handle());
  EXPECT_EQ(request("ld").handle(), request("ld").handle());
  EXPECT_EQ(request("rld").handle(), request("rld").handle());
  EXPECT_EQ(request("orld").handle(), request("orld").handle());
  EXPECT_EQ(request("World").handle(), request("World").handle());
  EXPECT_EQ(request("o").handle(), request("o").handle());
}

TEST(Text, overlap) {
  EXPECT_EQ(request("Hello").handle(), request("Hello").handle());
  EXPECT_EQ(request("World").handle(), request("World").handle());
  EXPECT_EQ(request("llo").handle(), request("Hello").handle() + 2);
  EXPECT_EQ(request("ld").handle(), request("World").handle() + 3);
  EXPECT_EQ(request("o").handle(), request("Hello").handle() + 4);
}

TEST(SExpression, size) { 
  EXPECT_EQ(2, sizeof(Knob));
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

TEST(Handle, Construct) {
  const Handle h = Handle(17);
}

TEST(Handle, Inspect) {
  const Handle h = Handle(19);
  EXPECT_EQ(h.handle(), 19);
}

TEST(Handle, ok) {
  const Handle h = Handle(23);
  EXPECT_TT(h.ok());
}
TEST(Account, exists) {
  Account c;
}

TEST(Account, zero) {
  Account c;
  EXPECT_ZZ(c);
}

TEST(Account, increment) {
  Account c;
  EXPECT_EQ(c,0);
  ++c;
  EXPECT_EQ(c,1);
  ++++c;
  EXPECT_EQ(c,3);
 ++++++c; 
  EXPECT_EQ(c,6);
}

TEST(Account, clear) {
  Account c;
  ++++++c; 
  EXPECT_EQ(c,3);
  !c;
  EXPECT_EQ(c,0);
}

TEST(Account, decrement) {
  Account c;
  ++++++c; 
  EXPECT_EQ(c,3);
  --++--++--c; 
  EXPECT_EQ(c,2);
  --++--++--c; 
  EXPECT_EQ(c,1);
  --++--++--c; 
  EXPECT_EQ(c,0);
}

TEST(Account, priority) {
  Account c;
  EXPECT_EQ(c,0);
  !++++++c;
  EXPECT_EQ(c,0);
}

TEST(Account, kind) {
  Account c;
  Account c1 = c.kind(), c2 = c.kind(), c11 = c1.kind(), c111 = c11.kind();
  EXPECT_EQ(c,0);
  ++c1;
  EXPECT_EQ(c,1);
  EXPECT_EQ(c1,1);
  ++c2;
  EXPECT_EQ(c2,1);
  EXPECT_EQ(c,2);
  EXPECT_EQ(c1,1);
  EXPECT_EQ(c11,0);
  EXPECT_EQ(c111,0);
  ++c11;
  EXPECT_EQ(c,3);
  EXPECT_EQ(c1,2);
  EXPECT_EQ(c11,1);
  EXPECT_EQ(c111,0);
  --c11;
  EXPECT_EQ(c,2);
  EXPECT_EQ(c1,1);
  EXPECT_EQ(c11,0);
  EXPECT_EQ(c111,0);
  ++c11;
  EXPECT_EQ(c,3);
  EXPECT_EQ(c1,2);
  EXPECT_EQ(c11,1);
  EXPECT_EQ(c111,0);
  ++c111;
  EXPECT_EQ(c,4);
  EXPECT_EQ(c1,3);
  EXPECT_EQ(c11,2);
  EXPECT_EQ(c111,1);
  !c; 
  EXPECT_EQ(c,0);
  EXPECT_EQ(c1,3);
  EXPECT_EQ(c11,2);
  EXPECT_EQ(c111,1);
  !c1; 
  EXPECT_EQ(c,0);
  EXPECT_EQ(c1,0);
  EXPECT_EQ(c11,2);
  EXPECT_EQ(c111,1);
  !c11; 
  EXPECT_EQ(c,0);
  EXPECT_EQ(c1,0);
  EXPECT_EQ(c11,0);
  EXPECT_EQ(c111,1);
  ++c111; 
  EXPECT_EQ(c,1);
  EXPECT_EQ(c1,1);
  EXPECT_EQ(c11,1);
  EXPECT_EQ(c111,2);
  ++c111; 
  EXPECT_EQ(c,2);
  EXPECT_EQ(c1,2);
  EXPECT_EQ(c11,2);
  EXPECT_EQ(c111,3);
  --c11; 
  EXPECT_EQ(c,1);
  EXPECT_EQ(c1,1);
  EXPECT_EQ(c11,1);
  EXPECT_EQ(c111,3);

  !c111; 
  EXPECT_EQ(c,1);
  EXPECT_EQ(c1,1);
  EXPECT_EQ(c11,1);
  EXPECT_EQ(c111,0);
}

TEST(Clicker, exists) {
  Clicker c;
}

TEST(Clicker, zero) {
  Clicker c;
  EXPECT_ZZ(c);
}

TEST(Clicker, increment) {
  Clicker c;
  EXPECT_EQ(c,0);
  c();
  EXPECT_EQ(c,1);
  c()();
  EXPECT_EQ(c,3);
  c()()();
  EXPECT_EQ(c,6);
}

TEST(Clicker, clear) {
  Clicker c;
  EXPECT_EQ(c,0);
  c();
  c()();
  c()()();
  EXPECT_EQ(c,6);
  !c;
  EXPECT_EQ(c,0);
}

TEST(Clicker, priority) {
  Clicker c;
  EXPECT_EQ(c,0);
  !c()()();
  EXPECT_EQ(c,0);
}

TEST(Clicker, kind) {
  Clicker c;
  Clicker c1 = c.kind(), c2 = c.kind(), c11 = c1.kind(), c111 = c11.kind();
  EXPECT_EQ(c,0);
  c1();
  EXPECT_EQ(c,1);
  EXPECT_EQ(c1,1);
  c2();
  EXPECT_EQ(c2,1);
  EXPECT_EQ(c,2);
  EXPECT_EQ(c1,1);
  EXPECT_EQ(c11,0);
  EXPECT_EQ(c111,0);
  c11();
  EXPECT_EQ(c,3);
  EXPECT_EQ(c1,2);
  EXPECT_EQ(c11,1);
  EXPECT_EQ(c111,0);
  c111();
  EXPECT_EQ(c,4);
  EXPECT_EQ(c1,3);
  EXPECT_EQ(c11,2);
  EXPECT_EQ(c111,1);
  !c; 
  EXPECT_EQ(c,0);
  EXPECT_EQ(c1,3);
  EXPECT_EQ(c11,2);
  EXPECT_EQ(c111,1);
  !c1; 
  EXPECT_EQ(c,0);
  EXPECT_EQ(c1,0);
  EXPECT_EQ(c11,2);
  EXPECT_EQ(c111,1);
  !c11; 
  EXPECT_EQ(c,0);
  EXPECT_EQ(c1,0);
  EXPECT_EQ(c11,0);
  EXPECT_EQ(c111,1);
  !c111; 
  EXPECT_EQ(c,0);
  EXPECT_EQ(c1,0);
  EXPECT_EQ(c11,0);
  EXPECT_EQ(c111,0);
}



TEST(Atoms, $A_t$) { 
  EXPECT_ZZ($A_t$);
  EXPECT_EQ((const char *const) A + $A_t$, (const char *const) P);
}

#define G(X) #X << "=" << X << " "
TEST(A, $X$) { 
  EXPECT_GT($X_t$, 0);
  EXPECT_LT($X_f$, 0);
  EXPECT_EQ($X_n$, (Short)($A_n$ + $P_n$)); 
  EXPECT_EQ($X_n$, $A_n$ + $P_n$); 
  EXPECT_GT($X_t$, $X_f$);
  EXPECT_GT($X_n$, 0); 
  EXPECT_GT($X_n$, $X_t$); 
  EXPECT_EQ($X_n$, INT16_MAX)<< G($A_f$) << G($X_f$) << G($X_t$) << G($A_t$);
}

TEST(P, $P_f$) { 
  EXPECT_GT($P_f$, $A_t$);
  EXPECT_LT($P_f$, $P_t$);
  EXPECT_EQ($P_f$, 1);
}

TEST(P, $P_t$) { 
  EXPECT_GT($P_t$, $P_f$);
  EXPECT_EQ($P_t$, $P_n$);
}

TEST(Array, Properties) {
  EXPECT_TT($A_x$ < $A_f$ || $A_x$ > $A_t$);
  EXPECT_TT($A_f$ < $A_t$);
  EXPECT_TT($A_n$ > 0);
  EXPECT_EQ($A_t$ - $A_f$ + 1, $A_n$);

  EXPECT_TT($P_f$ < $P_t$);
  EXPECT_TT($P_n$ > 0);
  EXPECT_TT($P_x$ < $P_f$ || $P_x$ > $P_t$);
  EXPECT_EQ($P_t$ - $P_f$ + 1,  $P_n$);

  EXPECT_TT($X_x$ < $X_f$ || $X_x$ > $X_t$);
  EXPECT_TT($X_f$ < $X_t$);
  EXPECT_TT($X_n$ > 0);
  EXPECT_EQ($X_t$ - $X_f$ + 1, $X_n$);
}



TEST(P, $P_n$) { 
  EXPECT_GT($P_n$,0);
}

TEST(Word, hash) { 
  EXPECT_NE(Word(3,4).hash(), Word(4,3).hash());
  EXPECT_NE(Word(3,4).hash(), Word(4,3).hash());
  EXPECT_NE(Word(2,3).hash(), Word(4,5).hash());
  EXPECT_NE(Word(2,3).hash(), Word(4,5).hash());
  EXPECT_GT(Word(2,3).hash(), 4);
  EXPECT_GT(Word(3,4).hash(), 3);
  EXPECT_GT(Word(4,5).hash(), 4);
}

TEST(Word, churnHash) { 
  enum {N = 100000};
  int n = 0;
  for (Short i = 0;  ; i++) { 
    for (Short j = 0;  i <= j; j++) {
      const Short h = Word(i,j).hash();
      EXPECT_GE(h, $P_f$);
      EXPECT_LE(h, $P_t$);
      if (++n >= N)
        return;
    }
  }
}
TEST(Flip, distinct) { 
  for (auto s = -32768; s != 32767; ++s)
    EXPECT_NE(s, flip(s)) << s;
}

TEST(Flip, reversible) { 
  for (auto s = -32768; s != 32767; ++s)
    EXPECT_EQ(s, flip(flip(s))) << s;
}

TEST(Flip, Pairs) { 
  EXPECT_LT(flip($P_f$), $A_f$);   
  EXPECT_LT(flip($P_t$), $A_f$);   
  EXPECT_LT(flip(($P_f$ + $P_t$)/2), $A_f$);   
  EXPECT_LT(flip($P_f$-1), $A_f$);   
  EXPECT_LT(flip($P_f$+1), $A_f$);   
  EXPECT_EQ(flip(flip($P_f$)), $P_f$);
  EXPECT_EQ(flip(flip($P_t$)), $P_t$);
  EXPECT_EQ(flip(flip(($P_f$ + $P_t$)/2)),($P_f$ + $P_t$)/2);
  EXPECT_EQ(flip(flip($P_t$ + 1)),$P_t$ + 1 );
  EXPECT_EQ(flip(flip($P_t$ + 1)), $P_t$ + 1);
}

TEST(Flip, P) { 
  EXPECT_LT(flip($P_f$), $P_f$);   
  EXPECT_LT(flip($P_t$), $P_t$);   
  EXPECT_LT(flip(($P_f$ + $P_t$)/2), $A_f$);
  EXPECT_LT(flip($P_f$-1), $X_f$);
  EXPECT_LT(flip($P_f$+1), $X_f$);   
}

TEST(Flip, A) { 
  EXPECT_GT(flip($A_f$), $A_t$);   
  EXPECT_GT(flip(($A_f$ + $A_t$)/2), $P_t$);   
  EXPECT_GT(flip(($A_f$ + $A_t$)/2), $X_t$);
  EXPECT_GT(flip($A_f$), $X_t$);   
  EXPECT_GT(flip($A_f$ - 1), $P_t$);   
  EXPECT_GT(flip($A_f$+1), $X_t$);   
  EXPECT_GT(flip($A_t$ - 1), $P_t$);   
  EXPECT_GT(flip($A_t$-1), $X_t$);   
  EXPECT_LT(flip($A_t$), $A_f$);
  EXPECT_LT(flip($A_t$),0);
}

TEST(Layout, LIMBO) {
  EXPECT_STREQ(A, "NIL");
  EXPECT_STREQ((char *)P, "NIL");
}

TEST(Layout, $A_f$) { 
  EXPECT_LT($A_f$,0);
}

TEST(Layout, overlap) { 
  EXPECT_STREQ(reinterpret_cast<char *>(P), A);
}
