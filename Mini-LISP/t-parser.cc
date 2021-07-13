#include <string.h>
#include <gtest/gtest.h>
#include "parser.h"
#include "test.h"

#if !BUGGY
#undef D
#undef M
#define D(...) 0
#define M(...) 0
#else 
#include "dump.h"
#endif


static auto t(const char *s) {
  return Tokenizer::initialize(strdup(s));
}

static auto feed(const char *s) {
  Parser::reset();
  return Parser::supply(strdup(s));
}
using namespace Parser;

TEST(Symbol, isRule) {
  EXPECT_TRUE(isRule(Symbol::E1));
  EXPECT_FALSE(isRule(Symbol::E));
}

TEST(Parser, Initially) {
  reset();
  ASSERT_NE(Status::reject, status());
  ASSERT_NE(Status::accept, status());
  EXPECT_EQ(Status::ready, status());
}

typedef ::S SExp;
TEST(Parser, AtomCharTokenizer) {
  t("A");
  H h = Tokenizer::next();
  EXPECT_STREQ("A", SExp(h).asAtom());
}

TEST(Parser, AtomChar) {
  feed("z");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
}

extern std::ostream& operator<<(std::ostream &os, SExp s); 


TEST(Parser, Empty) {
  feed("");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::accept, status());
  EXPECT_EQ(Status::reject, status());
}

TEST(Parser, SingleTokenErroOpenParen) {
  feed("(");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::accept, status());
  EXPECT_EQ(Status::reject, status());
}

TEST(Parser, SingleTokenErroCloseParen) {
  feed(")");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::accept, status());
  EXPECT_EQ(Status::reject, status());
}

TEST(Parser, SingleTokenErroQuote) {
  feed("'");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::accept, status());
  EXPECT_EQ(Status::reject, status());
}

TEST(Parser, SingleTokenErroPeriod) {
  feed(".");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::accept, status());
  EXPECT_EQ(Status::reject, status());
}

TEST(Parser, SingleTokenErroSquare) {
  feed("[");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::accept, status());
  EXPECT_EQ(Status::reject, status());
}

TEST(Parser, AtomLong) {
  feed("Atom");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
}

TEST(Parser, List0) {
  feed("()");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
}


TEST(Parser, ListTokenizationGetNextTwice) {
  Tokenizer::initialize(strdup("(a)"));
  H token;
  token = Tokenizer::get();
  EXPECT_EQ(token, '(');
  EXPECT_STREQ("A", Strings::pool + Tokenizer::next());
  EXPECT_EQ(')', Tokenizer::get());
  EXPECT_EQ($, Tokenizer::get());

  Tokenizer::initialize(strdup("(a)"));
  EXPECT_EQ(Tokenizer::next(), '(');
  EXPECT_STREQ("A", Strings::pool + Tokenizer::next());
  EXPECT_EQ(')', Tokenizer::next());
  EXPECT_EQ($, Tokenizer::next());
}

TEST(Parser, ListTokenizationNextGet) {
  Tokenizer::initialize(strdup("(a)"));
  EXPECT_EQ(Tokenizer::next(), '(');
  EXPECT_STREQ("A", Strings::pool + Tokenizer::next());
  EXPECT_EQ(')', Tokenizer::next());
  EXPECT_EQ($, Tokenizer::next());

  Tokenizer::initialize(strdup("(a)"));
  H token;
  token = Tokenizer::get();
  EXPECT_EQ(token, '(');
  EXPECT_STREQ("A", Strings::pool + Tokenizer::next());
  EXPECT_EQ(')', Tokenizer::get());
  EXPECT_EQ($, Tokenizer::get());
}

TEST(Parser, ListTokenization) {
  Tokenizer::initialize(strdup("(a)"));
  EXPECT_EQ(Tokenizer::next(), '(');
  EXPECT_STREQ("A", Strings::pool + Tokenizer::next());
  EXPECT_EQ(')', Tokenizer::next());
  EXPECT_EQ($, Tokenizer::next());

  Tokenizer::initialize(strdup("(a)"));
  EXPECT_EQ(Tokenizer::get(), '(');
  EXPECT_STREQ("A", Strings::pool + Tokenizer::get());
  EXPECT_EQ(')', Tokenizer::get());
  EXPECT_EQ($, Tokenizer::get());
}

TEST(Parser, List1) {
  feed("(a)");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
}

TEST(Parser, List1x) {
  Tokenizer::initialize(strdup("(a)"));
  EXPECT_EQ(Tokenizer::next(), '(');
  EXPECT_STREQ("A", Strings::pool + Tokenizer::next());
  EXPECT_EQ(')', Tokenizer::next());
  EXPECT_EQ($, Tokenizer::next());

  Tokenizer::initialize(strdup("(a)"));
  EXPECT_EQ(Tokenizer::get(), '(');
  EXPECT_STREQ("A", Strings::pool + Tokenizer::get());
  EXPECT_EQ(')', Tokenizer::get());
  EXPECT_EQ($, Tokenizer::get());

  Tokenizer::initialize(strdup("(a)"));
  H h;

  h = Tokenizer::get();
  D(h);
  D(!Symbol(h));
  EXPECT_EQ(h, '(');

  h = Tokenizer::get();
  D(h);
  D(!Symbol(h));
  EXPECT_STREQ(Strings::pool + h, "A");

  h = Tokenizer::get();
  D(h);
  D(!Symbol(h));
  EXPECT_EQ(h, ')');

  feed("(a)");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
}

TEST(Parser, List2) {
  feed("(a b)");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
}

TEST(Parser, List3) {
  feed("(a b c)");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
}

TEST(Parser, List4) {
  feed("(a b c d)");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
}

TEST(Parser, Pair) {
  feed("a.b");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
}

TEST(Parser, PairInList) {
  feed("(a.b)");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
}

TEST(Parser, ListTokenizationWithGet) {
  Tokenizer::initialize(strdup("(a)"));
  H token;
  token = Tokenizer::get();
  EXPECT_EQ(token, '(');
  EXPECT_STREQ("A", Strings::pool + Tokenizer::next());
  EXPECT_EQ(')', Tokenizer::get());
  EXPECT_EQ($, Tokenizer::get());
}

TEST(Parser, ListTokenizationNext) {
  Tokenizer::initialize(strdup("(a)"));
  EXPECT_EQ(Tokenizer::next(), '(');
  EXPECT_STREQ("A", Strings::pool + Tokenizer::next());
  EXPECT_EQ(')', Tokenizer::next());
  EXPECT_EQ($, Tokenizer::next());
}

TEST(Parser, ParenPair) {
  feed("(a.b)");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
}
TEST(Parser, NilNilPair) {
  feed("().()");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
}
TEST(Parser, EmptyNilPair) {
  feed("().NIL");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
}
TEST(Parser, NestedList) {
  reset();
  feed("((a b) (c (d e)))");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
}

TEST(Parser, QuoteAtom) {
  feed("'A");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
}

TEST(Parser, QuotedListEmpty) {
  feed("'()");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
}

TEST(Parser, QuotedListSingleton) {
  feed("'(a)");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
}

TEST(Parser, QList2) {
  feed("'(a 'b)");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
}

TEST(Parser, QList3) {
  feed("(a 'b c)");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
}

TEST(Parser, QList4) {
  feed("'(a 'b c 'd)");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
}

TEST(Parser, QPair) {
  feed("'a.b");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
}

TEST(Parser, QPairBoth) {
  feed("'a.'b");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
}

TEST(Parser, qParenPair) {
  feed("'(a.b)");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
}
TEST(Parser, qNilNilPair) {
  feed("().'()");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
}

TEST(Parser, EmptyQNilPair) {
  feed("().'NIL");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
}
