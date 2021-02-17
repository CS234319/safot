#include <string.h>
#include <gtest/gtest.h>
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

TEST(Parser, AtomCharTokenizer) {
  t("A");
  H h = Tokenizer::next();
  EXPECT_STREQ("A", S(h).asAtom());
}

TEST(Parser, AtomChar) {
  supply("A");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
}

extern std::ostream& operator<<(std::ostream &os, S s); 

TEST(AST, AtomChar) {
  supply("A");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
  EXPECT_STREQ("A", S(result()).asAtom());   
}


TEST(Parser, Empty) {
  supply("");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::accept, status());
  EXPECT_EQ(Status::reject, status());
}

TEST(Parser, SingleTokenErrorOpenParen) {
  supply("(");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::accept, status());
  EXPECT_EQ(Status::reject, status());
}

TEST(Parser, SingleTokenErrorCloseParen) {
  supply(")");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::accept, status());
  EXPECT_EQ(Status::reject, status());
}

TEST(Parser, SingleTokenErrorQuote) {
  supply("'");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::accept, status());
  EXPECT_EQ(Status::reject, status());
}

TEST(Parser, SingleTokenErrorPeriod) {
  supply(".");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::accept, status());
  EXPECT_EQ(Status::reject, status());
}

TEST(Parser, SingleTokenErrorSquare) {
  supply("[");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::accept, status());
  EXPECT_EQ(Status::reject, status());
}

TEST(Parser, AtomLong) {
  supply("Atom");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
}

TEST(AST, AtomLong) {
  supply("Atom");
  EXPECT_STREQ("ATOM", S(result()).asAtom());   
}

TEST(AST, List0) {
  supply("()");
  EXPECT_EQ(NIL, result());
}

TEST(AST, List1) {
  supply("(HELLO)");
  auto s = Parser::result();
  D(s);
  ASSERT_NE(NIL,s);
  ASSERT_FALSE(s.null());
  ASSERT_FALSE(s.atom());
  ASSERT_TRUE(islist(s));
  EXPECT_STREQ("HELLO",car(s).asAtom());
  EXPECT_EQ(NIL,cdr(s));
}

TEST(AST, List2) {
  supply("(1 2)");
  auto s = Parser::result();
  D(s);
  ASSERT_NE(NIL,s);
  ASSERT_FALSE(s.null());
  ASSERT_FALSE(s.atom());
  ASSERT_TRUE(islist(s));
  EXPECT_STREQ("1",car(s).asAtom());
  s = cdr(s);
  EXPECT_STREQ("2",car(s).asAtom());
  EXPECT_EQ(NIL,cdr(s));
}

TEST(AST, List3) {
  supply("(X Y Z)");
  auto s = Parser::result();
  D(s);
  ASSERT_NE(NIL,s);
  ASSERT_FALSE(s.null());
  ASSERT_FALSE(s.atom());
  ASSERT_TRUE(islist(s));
  EXPECT_STREQ("X",car(s).asAtom());
  s = cdr(s);
  EXPECT_STREQ("Y",car(s).asAtom());
  s = cdr(s);
  EXPECT_STREQ("Z",car(s).asAtom());
  EXPECT_EQ(NIL,cdr(s));
}



TEST(Parser, List0) {
  supply("()");
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
  supply("(a)");
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

TEST(AST, Pair) {
  supply("hello.world");
  S s = Parser::result();
  ASSERT_FALSE(s.null());
  ASSERT_FALSE(s.atom());
  ASSERT_FALSE(islist(s));
  EXPECT_STREQ("HELLO",car(s).asAtom());
  EXPECT_STREQ("WORLD",cdr(s).asAtom());
}

TEST(Parser, PairInList) {
  supply("(a.b)");
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

TEST(Parser, QuotedListEmpty) {
  supply("'()");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
}

TEST(Parser, QuotedListSingleton) {
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

