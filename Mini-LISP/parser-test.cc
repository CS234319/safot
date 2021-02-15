#include <string.h>
#include "gtest/gtest.h"
#include "parser.cc"
#include "test.h"
#include "dump.h"

static auto t(const char *s) {
  return Tokenizer::initialize(strdup(s));
}

auto supply(const char *s) {
  Parser::reset();
  return Parser::supply(strdup(s));
}
using namespace Parser;

TEST(Parser, Initially) {
  EXPECT_EQ(Status::ready, status());
}

TEST(Parser, Empty) {
  EXPECT_EQ(Status::ready, status());
  supply("");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::accept, status());
  EXPECT_EQ(Status::reject, status());
}

TEST(Parser, SingleTokenError) {
  supply("(");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::accept, status());
  EXPECT_EQ(Status::reject, status());
  supply(")");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::accept, status());
  EXPECT_EQ(Status::reject, status());
  supply("'");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::accept, status());
  EXPECT_EQ(Status::reject, status());
  supply(".");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::accept, status());
  ASSERT_NE(Status::accept, status());
  EXPECT_EQ(Status::reject, status());
  supply("[");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::accept, status());
  EXPECT_EQ(Status::reject, status());
}

TEST(Parser, AtomCharTokenizer) {
  t("A");
  H h =  Tokenizer::next();
  EXPECT_STREQ("A",S(h).asAtom()); 
}

TEST(Parser, AtomChar) {
  supply("A");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
}

TEST(Parser, AtomLong) {
  supply("A");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
}
TEST(Parser, List0) {
  EXPECT_EQ(Status::ready, status());
  supply("()");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
}
TEST(Parser, List1) {
  EXPECT_EQ(Status::ready, status());
  supply("(a)");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
}

TEST(Parser, List2) {
  supply("(a b)");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
}

TEST(Parser, List3) {
  supply("(a b c)");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
}

TEST(Parser, List4) {
  supply("(a b c d)");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
}

TEST(Parser, Pair) {
  supply("a.b");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
}

TEST(Parser, ParenPair) {
  supply("(a.b)");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
}
TEST(Parser, NilNilPair) {
  supply("().()");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
}
TEST(Parser, EmptyNilPair) {
  supply("().NIL");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
}
TEST(Parser, NestedList) {
  reset();
  supply("((a b) (c (d e)))");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
}

TEST(Parser, QuoteAtom) {
  supply("'A");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
}

TEST(Parser, QList0) {
  supply("'()");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
}
TEST(Parser, QList1) {
  supply("'(a)");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
}

TEST(Parser, QList2) {
  supply("'(a 'b)");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
}

TEST(Parser, QList3) {
  supply("(a 'b c)");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
}

TEST(Parser, QList4) {
  supply("'(a 'b c 'd)");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
}

TEST(Parser, QPair) {
  supply("'a.b");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
}

TEST(Parser, QPairBoth) {
  supply("'a.'b");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
}

TEST(Parser, qParenPair) {
  supply("'(a.b)");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
}
TEST(Parser, qNilNilPair) {
  supply("().'()");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
}

TEST(Parser, EmptyQNilPair) {
  supply("().'NIL");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
}
TEST(Parser, QNestedList) {
  supply("((a b) '(c (d e)))");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
}

