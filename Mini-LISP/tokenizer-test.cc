#include "gtest/gtest.h"
#include "tokenizer.cc"
#include "test.h"

#include <string.h>

static void t(const char *s) {
  Tokenizer::initialize(strdup(s));
}

using Tokenizer::next;
using Tokenizer::$;

static const char *nextS() {
  H h = next();
  D(h);
  D(Strings::pool + h);
  return Strings::pool + h;
}

TEST(Tokenizer, Empty) {
  t("");
  EXPECT_EQ($,next());
}

TEST(Tokenizer, EmptyComment) {
  t(";foo bar");
  EXPECT_EQ($,next());
}

TEST(Tokenizer, Char) {
  t("A");
  EXPECT_STREQ("A",nextS());
}


TEST(Tokenizer, Atom) {
  t("atom");
  auto s = nextS();
  D(s);
  D("A");
  EXPECT_STREQ("ATOM",s);
}

TEST(Tokenizer, AtomSpaced) {
  t(" atom  ");
  EXPECT_STREQ("ATOM",nextS());
}

TEST(Tokenizer, AtomCommented) {
  t(" atom ; some comment ");
  EXPECT_STREQ("ATOM",nextS());
}

TEST(Tokenizer, HelloWorld) {
  t("Hello World\n");
  EXPECT_STREQ("HELLO",nextS());
  EXPECT_STREQ("WORLD",nextS());
}

TEST(Tokenizer, IdemPotent) {
  t("");
  EXPECT_EQ($,next());
  EXPECT_EQ($,next());
  EXPECT_EQ($,next());
}


TEST(Tokenizer, OneComment) {
  t("Hello ;foo bar\n World");
  EXPECT_STREQ("HELLO",nextS());
  EXPECT_STREQ("WORLD",nextS());
  EXPECT_EQ($,next());
}



TEST(Tokenizer, RemoveComments) {
  t("Hello ; foo bar \n World\n; foo bar");
  EXPECT_STREQ("HELLO",nextS());
  EXPECT_STREQ("WORLD",nextS());
}



TEST(Tokenizer, HelloWorldEOF) {
  t("Hello World\n");
  EXPECT_STREQ("HELLO",nextS());
  EXPECT_STREQ("WORLD",nextS());
  EXPECT_EQ($,next());
}

TEST(Tokenizer, HelloWorldEOFAgain) {
  t("Hello\n   World\n");
  EXPECT_STREQ("HELLO",nextS());
  EXPECT_STREQ("WORLD",nextS());
  EXPECT_EQ($,next());
}


TEST(Tokenizer, ConcreteTokens) {
  using Tokenizer::tokens;
  t(tokens);
  for (int i = 0; tokens[i] != '\0'; ++i)
    ASSERT_EQ(tokens[i],next());
}





