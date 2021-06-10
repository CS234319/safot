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
  EXPECT_EQ(S::NIL,S::NIL);
  EXPECT_NE(S::NIL,S::T);
  EXPECT_NE(S::T,S::NIL);
  EXPECT_EQ(S::T,S::T);
  EXPECT_NE(S::T.cons(S::T),S::T.cons(S::T));
  EXPECT_NE(S::NIL.cons(S::NIL),S::NIL.cons(S::NIL));
  EXPECT_EQ(S::LAMBDA, S::LAMBDA);
  EXPECT_EQ(S::LAMBDA, S("lambda"));
  EXPECT_NE(S::LAMBDA, S::NLAMBDA);
  EXPECT_NE(S::NLAMBDA, S::LAMBDA);
  EXPECT_NE(S::NLAMBDA, S::LAMBDA);
  EXPECT_EQ(S::NLAMBDA, S::NLAMBDA);
}

TEST(Strings, NIL) {
  EXPECT_EQ(0,S::NIL.handle);
  EXPECT_EQ(0,S("NIL").handle);
  EXPECT_EQ(S::NIL,S("NIL"));
}
}


