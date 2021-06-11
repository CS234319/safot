#include <iostream>
#include "gtest/gtest.h"
#include "strings.h"
#include "test.h"

 
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
}

