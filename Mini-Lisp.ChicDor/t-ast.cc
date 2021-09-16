#include <string.h>
#include <gtest/gtest.h>
#include "test.h"
#include "basics.h"


static auto t(const char *s) {
  return Tokenizer::initialize(strdup(s));
}

static auto feed(String s) {
  Parser::reset();
  return Parser::supply(strdup(s));
}
using namespace Parser;


extern std::ostream& operator<<(std::ostream &os, S s); 

TEST(AST, AtomChar) {
  feed("z");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
  EXPECT_STREQ("Z", S(result()).asAtom());   
  reset();
}

TEST(AST, AtomLong) {
  feed("Atom");
  EXPECT_STREQ("ATOM", S(result()).asAtom());   
  reset();
}

TEST(AST, List0) {
  feed("()");
  EXPECT_EQ(NIL, result());
  reset();
}

TEST(AST, List1) {
  feed("(HELLO)");
  auto s = Parser::result();
  ASSERT_NE(NIL,s);
  ASSERT_FALSE(s.null());
  ASSERT_FALSE(s.atom());
  ASSERT_TRUE(islist(s));
  EXPECT_STREQ("HELLO",s.car().asAtom());
  EXPECT_EQ(NIL,s.cdr());
  reset();
}

TEST(AST, List2) {
  feed("(1 2)");
  auto s = Parser::result();
  ASSERT_NE(NIL,s);
  ASSERT_FALSE(s.null());
  ASSERT_FALSE(s.atom());
  ASSERT_TRUE(islist(s));
  EXPECT_STREQ("1",s.car().asAtom());
  s = s.cdr();
  EXPECT_STREQ("2",s.car().asAtom());
  EXPECT_EQ(NIL,s.cdr());
  reset();
}

TEST(AST, List3) {
  feed("(A B C)");
  auto s = Parser::result();
  ASSERT_NE(NIL,s);
  ASSERT_FALSE(s.null());
  ASSERT_FALSE(s.atom());
  ASSERT_TRUE(islist(s));
  EXPECT_STREQ("A",s.car().asAtom());
  s = s.cdr();
  EXPECT_STREQ("B",s.car().asAtom());
  s = s.cdr();
  EXPECT_STREQ("C",s.car().asAtom());
  EXPECT_EQ(NIL,s.cdr());
  reset();
}

TEST(AST, QuoteA) {
  feed("'Z");
  auto s = Parser::result();
  ASSERT_NE(NIL,s);
  ASSERT_FALSE(s.null());
  ASSERT_FALSE(s.atom());
  ASSERT_TRUE(islist(s));
  EXPECT_STREQ("QUOTE",s.car().asAtom());
  s = s.cdr();
  EXPECT_STREQ("Z",s.car().asAtom());
  EXPECT_EQ(NIL,s.cdr());
  reset();
}

TEST(AST, QuoteAA) {
  feed("''Z");
  auto s = Parser::result();
  ASSERT_NE(NIL,s);
  ASSERT_FALSE(s.null());
  ASSERT_FALSE(s.atom());
  ASSERT_TRUE(islist(s));
  EXPECT_STREQ("QUOTE",s.car().asAtom());
  s = s.cdr();
  ASSERT_FALSE(s.null());
  ASSERT_FALSE(s.atom());
  ASSERT_TRUE(islist(s));
  s = s.car();
  EXPECT_STREQ("QUOTE",s.car().asAtom());
  s = s.cdr();
  EXPECT_STREQ("Z",s.car().asAtom());
  EXPECT_EQ(NIL,s.cdr());
  reset();
}

TEST(AST, Pair) {
  feed("hello.world");
  S s = Parser::result();
  ASSERT_FALSE(s.null());
  ASSERT_FALSE(s.atom());
  ASSERT_FALSE(islist(s));
  EXPECT_STREQ("HELLO",s.car().asAtom());
  EXPECT_STREQ("WORLD",s.cdr().asAtom());
  reset();
}

TEST(AST, PairYZ) {
  feed("Y.Z");
  S s = Parser::result();
  ASSERT_FALSE(s.null());
  ASSERT_FALSE(s.atom());
  ASSERT_FALSE(islist(s));
  EXPECT_STREQ("Y",s.car().asAtom());
  EXPECT_STREQ("Z",s.cdr().asAtom());
  reset();
}

TEST(AST, AtomOutput) {
  feed("Y");
  EXPECT_STREQ("Y", ~Parser::result());
  reset();
}

TEST(AST, PairInList) {
  feed("(Y.Z)");
  EXPECT_STREQ("(Y.Z)", ~Parser::result());
  reset();
}

TEST(AST, PairX) {
  feed("Y.Z");
  EXPECT_STREQ("Y.Z", ~Parser::result());
  reset();
}

TEST(AST, QNestedList) {
  feed("((a b) '(c (d e)))");
  EXPECT_STREQ("((A B) (QUOTE (C (D E))))", ~Parser::result());
  reset();
}

TEST(AST, ListQuotePair) {
  feed("(c d).'(a b)");
  EXPECT_STREQ("((C D) QUOTE (A B))", ~Parser::result());
  reset();
}

TEST(AST, QuoteInList) {
  feed("(a 'b 'c)");
  EXPECT_STREQ("(A (QUOTE B) (QUOTE C))", ~Parser::result());
  reset();
}

TEST(AST, QuoteListInList) {
  feed("(a '(foo bar)  'c)");
  EXPECT_STREQ("(A (QUOTE (FOO BAR)) (QUOTE C))", ~Parser::result());
  reset();
}

TEST(AST, NIL) {
  feed("NIL");
  EXPECT_EQ(NIL, Parser::result());
  reset();
}

TEST(AST, EmptyListNiL) {
  feed("()");
  EXPECT_EQ(Status::accept, status());
  EXPECT_EQ(NIL, Parser::result());
  reset();
}

TEST(AST, LibT) {
  feed("(set (quote t) (quote t))");
  EXPECT_EQ(Status::accept, status());
  EXPECT_STREQ("(SET (QUOTE T) (QUOTE T))", ~Parser::result());
  reset();
}

TEST(AST, LibNil) {
  feed("(set (quote nil) (quote nil))");
  EXPECT_EQ(Status::accept, status());
  EXPECT_STREQ("(SET (QUOTE nil) (QUOTE nil))", ~Parser::result());
  reset();
}

TEST(AST, LibLambda) {
  feed("(set 'quote '(lambda (x) x)) ");
  EXPECT_EQ(Status::accept, status());
  EXPECT_STREQ("(SET (QUOTE QUOTE) (QUOTE (LAMBDA (X) X)))", ~Parser::result());
  reset();
}

TEST(AST, LibNLambda) {
  feed("(set 'quote '(nlambda (x) x)) ");
  EXPECT_EQ(Status::accept, status());
  EXPECT_STREQ("(SET (QUOTE QUOTE) (QUOTE (NLAMBDA (X) X)))", ~Parser::result());
  reset();
}

TEST(AST, LibDefun) {
  feed(""
"(set 'defun\n"
  "'(nlambda (name parameters body)\n"
    "(set name (lambda parameters body))))"
      ""
 "\n"
 "\n");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
  EXPECT_STREQ(""
"(SET (QUOTE DEFUN) " 
  "(QUOTE (NLAMBDA (NAME PARAMETERS BODY) " 
  "(SET NAME (LAMBDA PARAMETERS BODY)))))" 
"",
  ~Parser::result());
  reset();
}

TEST(AST, LibNDefun) {
  feed(""
    "(set 'ndefun\n"
      "'(nlambda (name parameters body)\n"
    "(set name (nlambda parameters body))))\n"
 "\n"
 "\n");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
  EXPECT_STREQ(""
      "(SET (QUOTE NDEFUN) " //
      "(QUOTE (NLAMBDA (NAME PARAMETERS BODY) " //
      "(SET NAME (NLAMBDA PARAMETERS BODY)))))" //
  "",~Parser::result());
  reset();
}

TEST(DISABLED_AST, SquareBrackets) {
  feed(""
    "(set 'ndefun\n"
      "'(nlambda (name parameters body)\n"
    "(set name (nlambda parameters body]\n"
 "\n"
 "\n");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
  EXPECT_STREQ(""
      "(SET (QUOTE NDEFUN) " "(QUOTE (NLAMBDA (NAME PARAMETERS BODY) " //
      "(SET NAME (NLAMBDA PARAMETERS BODY)))))"
  "",~Parser::result());
  reset();
}
