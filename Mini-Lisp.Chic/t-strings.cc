#import  <iostream>
#import  "gtest/gtest.h"
#import  "strings.h"
#import  "test.h"

namespace Strings {
  extern char *buffer; 

TEST(Strings, Layout) {
// EXPECT_EQ(nil, buffer + sizeof(data.buffer));
//  EXPECT_EQ(nil - buffer, sizeof(data.buffer));
//  EXPECT_EQ(nil, pool);
}

TEST(Strings, Indices) {
  EXPECT_EQ(NIL,NIL);
  EXPECT_NE(NIL,T);
  EXPECT_NE(T,NIL);
  EXPECT_EQ(T,T);
  EXPECT_NE(T.cons(T),T.cons(T));
  EXPECT_NE(NIL.cons(NIL),NIL.cons(NIL));
  EXPECT_EQ(CAR.handle, S("CAR").handle);
  EXPECT_EQ(CDR.handle, S("CDR").handle);
}

TEST(Strings, NIL) {
  EXPECT_EQ(0,NIL.handle);
  EXPECT_EQ(0,S("NIL").handle);
  EXPECT_EQ(NIL,S("NIL"));
}

TEST(Strings,Handles) {
  EXPECT_EQ(NIL.handle,0);
  EXPECT_EQ(T.handle,-2);
  EXPECT_LE(S("IL").handle, 0);
  EXPECT_LE(S("L").handle, 0);
  EXPECT_LE(S("").handle, 0);
}

}

