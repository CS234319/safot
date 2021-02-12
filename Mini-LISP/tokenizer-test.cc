#include "gtest/gtest.h"
#include "tokenizer.c"

TEST(Tokenizer, HelloWorld) {
  tokenize("Hello World\n");
  {
    S s = nextToken();
    EXPECT_EQ("hello",s);
  }
  {
    S s = nextToken();
    EXPECT_EQ("world",s);
  }
  EXPECT_EQ($,nextToken());
}

TEST(Tokenizer, RemoveComment) {
  tokenize("Hello World\n");
  nextToken();
  nextToken();
  EXPECT_EQ($,nextToken());
}
