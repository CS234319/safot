#import  <iostream>
#import  "gtest/gtest.h"
#import  "S.h"
#import  "test.h"

namespace Pairs {
  extern H allocate(); 
  /* Sanity of free/allocate; someday: deal with exhausted memory */
  TEST(Pairs, Representation) {
    using namespace Pairs;
    H before = Pairs::to_go();
    H h = Pairs::allocate();
    EXPECT_EQ(Pairs::to_go(), before - 1);
    Pairs::free(h);
    H h1 = Pairs::allocate();
    EXPECT_EQ(h, h1);
    EXPECT_EQ(Pairs::to_go(), before - 1);
    Pairs::free(h);
    EXPECT_EQ(Pairs::to_go(), before);
  }

  TEST(Pairs, A_CONS_B) {
    S A("A"), B("B");
    EXPECT_NE(A.cons(B).handle,A.cons(B).handle);
  }

  TEST(Pairs, A_CONS_B_Allocated) {
    H A(S("A").handle), B(S("B").handle);
    EXPECT_NE(Pairs::allocate(A,B), Pairs::allocate(A,B));
  }


  TEST(Pairs, A_CONS_B_Inverse) {
    S A("A"), B("B");
    EXPECT_NE(A.cons(B),B.cons(A));
  }


  TEST(Pairs, T_CONS_T_handles) {
    EXPECT_NE(T.cons(T).handle,T.cons(T).handle);
  }

  TEST(Pairs, T_CONS_T) {
    EXPECT_EQ(T.cons(T),T.cons(T));
  }

  TEST(Pairs, NIL_Cons_NIL) {
    EXPECT_NE(NIL.cons(NIL).handle,NIL.cons(NIL).handle);
  }

}

