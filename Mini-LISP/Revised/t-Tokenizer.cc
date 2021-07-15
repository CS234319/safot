#include "Tokenizer.h"
#include "Test.h"

static void t(const char *s) { Tokenizer::initialize(strdup(s)); }

using Tokenizer::next;
using Tokenizer::$;

static const char* nextS() {
  Short h = next();
  return Strings::pool + h;
}

TEST(Tokenizer, ListTokenizationWithGet) {
  Tokenizer::initialize(strdup("(a)"));
  Short token = Tokenizer::get();
  EXPECT_EQ(token, '(');
  EXPECT_STREQ("A", nextS());
  EXPECT_EQ(')', Tokenizer::get());
  EXPECT_EQ($, Tokenizer::get());
}

TEST(Tokenizer, ListTokenizationTwice) {
  {
    Tokenizer::initialize(strdup("(a)"));
    Short token;
    token = Tokenizer::get();
    EXPECT_EQ(token, '(');
    EXPECT_STREQ("A", nextS());
    EXPECT_EQ(')', Tokenizer::get());
    EXPECT_EQ($, Tokenizer::get());
  }
  {
    Tokenizer::initialize(strdup("(a)"));
    Short token;
    token = Tokenizer::get();
    EXPECT_EQ(token, '(');
    EXPECT_STREQ("A", nextS());
    EXPECT_EQ(')', Tokenizer::get());
    EXPECT_EQ($, Tokenizer::get());
  }
}

TEST(Tokenizer, ListTokenizationThrice) {
  {
    Tokenizer::initialize(strdup("(a)"));
    Short token;
    token = Tokenizer::get();
    EXPECT_EQ(token, '(');
    EXPECT_STREQ("A", nextS());
    EXPECT_EQ(')', Tokenizer::get());
    EXPECT_EQ($, Tokenizer::get());
  }
  {
    Tokenizer::initialize(strdup("(a)"));
    Short token;
    token = Tokenizer::get();
    EXPECT_EQ(token, '(');
    EXPECT_STREQ("A", nextS());
    EXPECT_EQ(')', Tokenizer::get());
    EXPECT_EQ($, Tokenizer::get());
  }
}

TEST(Tokenizer, Empty) {
  t("");
  EXPECT_EQ($, next());
}

TEST(Tokenizer, EmptyComment) {
  t(";foo bar");
  EXPECT_EQ($, next());
}

TEST(Tokenizer, Char) {
  t("A");
  EXPECT_STREQ("A", nextS());
}

TEST(Tokenizer, Atom) {
  t("atom");
  auto s = nextS();
  EXPECT_STREQ("ATOM", s);
}

TEST(Tokenizer, AtomSpaced) {
  t(" atom  ");
  EXPECT_STREQ("ATOM", nextS());
}

TEST(Tokenizer, AtomCommented) {
  t(" atom ; some comment ");
  EXPECT_STREQ("ATOM", nextS());
}

TEST(Tokenizer, HelloWorld) {
  t("Hello World\n");
  EXPECT_STREQ("HELLO", nextS());
  EXPECT_STREQ("WORLD", nextS());
}

TEST(Tokenizer, IdemPotent) {
  t("");
  EXPECT_EQ($, next());
  EXPECT_EQ($, next());
  EXPECT_EQ($, next());
}

TEST(Tokenizer, OneComment) {
  t("Hello ;foo bar\n World");
  EXPECT_STREQ("HELLO", nextS());
  EXPECT_STREQ("WORLD", nextS());
  EXPECT_EQ($, next());
}

TEST(Tokenizer, RemoveComments) {
  t("Hello ; foo bar \n World\n; foo bar");
  EXPECT_STREQ("HELLO", nextS());
  EXPECT_STREQ("WORLD", nextS());
}

TEST(Tokenizer, HelloWorldEOF) {
  t("Hello World\n");
  EXPECT_STREQ("HELLO", nextS());
  EXPECT_STREQ("WORLD", nextS());
  EXPECT_EQ($, next());
}

TEST(Tokenizer, HelloWorldEOFAgain) {
  t("Hello\n   World\n");
  EXPECT_STREQ("HELLO", nextS());
  EXPECT_STREQ("WORLD", nextS());
  EXPECT_EQ($, next());
}

TEST(Tokenizer, ConcreteTokens) {
  using Tokenizer::tokens;
  t(tokens);
  for (int i = 0; tokens[i] != '\0'; ++i)
    ASSERT_EQ(tokens[i], next());
}
