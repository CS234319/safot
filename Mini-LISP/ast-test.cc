#include <string.h>
#include <gtest/gtest.h>
#include "test.h"

static auto t(const char *s) {
  return Tokenizer::initialize(strdup(s));
}

static auto supply(const char *s) {
  Parser::reset();
  return Parser::supply(strdup(s));
}
using namespace Parser;


extern std::ostream& operator<<(std::ostream &os, S s); 

TEST(AST, AtomChar) {
  supply("z");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
  EXPECT_STREQ("Z", S(result()).asAtom());   
  reset();
}

TEST(AST, AtomLong) {
  supply("Atom");
  EXPECT_STREQ("ATOM", S(result()).asAtom());   
  reset();
}

TEST(AST, List0) {
  supply("()");
  EXPECT_EQ(NIL, result());
  reset();
}

TEST(AST, List1) {
  supply("(HELLO)");
  auto s = Parser::result();
  ASSERT_NE(NIL,s);
  ASSERT_FALSE(s.null());
  ASSERT_FALSE(s.atom());
  ASSERT_TRUE(islist(s));
  EXPECT_STREQ("HELLO",car(s).asAtom());
  EXPECT_EQ(NIL,cdr(s));
  reset();
}

TEST(AST, List2) {
  supply("(1 2)");
  auto s = Parser::result();
  ASSERT_NE(NIL,s);
  ASSERT_FALSE(s.null());
  ASSERT_FALSE(s.atom());
  ASSERT_TRUE(islist(s));
  EXPECT_STREQ("1",car(s).asAtom());
  s = cdr(s);
  EXPECT_STREQ("2",car(s).asAtom());
  EXPECT_EQ(NIL,cdr(s));
  reset();
}

TEST(AST, List3) {
  supply("(A B C)");
  auto s = Parser::result();
  ASSERT_NE(NIL,s);
  ASSERT_FALSE(s.null());
  ASSERT_FALSE(s.atom());
  ASSERT_TRUE(islist(s));
  EXPECT_STREQ("A",car(s).asAtom());
  s = cdr(s);
  EXPECT_STREQ("B",car(s).asAtom());
  s = cdr(s);
  EXPECT_STREQ("C",car(s).asAtom());
  EXPECT_EQ(NIL,cdr(s));
  reset();
}

TEST(AST, QuoteA) {
  supply("'Z");
  auto s = Parser::result();
  ASSERT_NE(NIL,s);
  ASSERT_FALSE(s.null());
  ASSERT_FALSE(s.atom());
  ASSERT_TRUE(islist(s));
  EXPECT_STREQ("QUOTE",car(s).asAtom());
  s = cdr(s);
  EXPECT_STREQ("Z",car(s).asAtom());
  EXPECT_EQ(NIL,cdr(s));
  reset();
}

TEST(AST, QuoteAA) {
  supply("''Z");
  auto s = Parser::result();
  ASSERT_NE(NIL,s);
  ASSERT_FALSE(s.null());
  ASSERT_FALSE(s.atom());
  ASSERT_TRUE(islist(s));
  EXPECT_STREQ("QUOTE",car(s).asAtom());
  s = cdr(s);
  ASSERT_FALSE(s.null());
  ASSERT_FALSE(s.atom());
  ASSERT_TRUE(islist(s));
  s = car(s);
  EXPECT_STREQ("QUOTE",car(s).asAtom());
  s = cdr(s);
  EXPECT_STREQ("Z",car(s).asAtom());
  EXPECT_EQ(NIL,cdr(s));
  reset();
}

TEST(AST, Pair) {
  supply("hello.world");
  S s = Parser::result();
  ASSERT_FALSE(s.null());
  ASSERT_FALSE(s.atom());
  ASSERT_FALSE(islist(s));
  EXPECT_STREQ("HELLO",car(s).asAtom());
  EXPECT_STREQ("WORLD",cdr(s).asAtom());
  reset();
}

TEST(AST, PairYZ) {
  supply("Y.Z");
  S s = Parser::result();
  ASSERT_FALSE(s.null());
  ASSERT_FALSE(s.atom());
  ASSERT_FALSE(islist(s));
  EXPECT_STREQ("Y",car(s).asAtom());
  EXPECT_STREQ("Z",cdr(s).asAtom());
  reset();
}

TEST(AST, AtomOutput) {
  supply("Y");
  EXPECT_STREQ("Y", ~Parser::result());
  reset();
}

TEST(AST, PairInList) {
  supply("(Y.Z)");
  EXPECT_STREQ("(Y.Z)", ~Parser::result());
  reset();
}

TEST(AST, PairX) {
  supply("Y.Z");
  EXPECT_STREQ("Y.Z", ~Parser::result());
  reset();
}

TEST(AST, QNestedList) {
  supply("((a b) '(c (d e)))");
  EXPECT_STREQ("((A B) (QUOTE (C (D E))))", ~Parser::result());
  reset();
}

TEST(AST, ListQuotePair) {
  supply("(c d).'(a b)");
  EXPECT_STREQ("((C D) QUOTE (A B))", ~Parser::result());
  reset();
}

TEST(AST, QuoteInList) {
  supply("(a 'b 'c)");
  EXPECT_STREQ("(A (QUOTE B) (QUOTE C))", ~Parser::result());
  reset();
}

TEST(AST, QuoteListInList) {
  supply("(a '(foo bar)  'c)");
  EXPECT_STREQ("(A (QUOTE (FOO BAR)) (QUOTE C))", ~Parser::result());
  reset();
}

TEST(AST, NIL) {
  supply("NIL");
  EXPECT_EQ(NIL, Parser::result());
  reset();
}

TEST(AST, EmptyListNiL) {
  supply("()");
  EXPECT_EQ(Status::accept, status());
  EXPECT_EQ(NIL, Parser::result());
  reset();
}

TEST(AST, LibT) {
  supply("(set (quote t) (quote t))");
  EXPECT_EQ(Status::accept, status());
  EXPECT_STREQ("(SET (QUOTE T) (QUOTE T))", ~Parser::result());
  reset();
}

TEST(AST, LibNil) {
  supply("(set (quote nil) (quote nil))");
  EXPECT_EQ(Status::accept, status());
  EXPECT_STREQ("(SET (QUOTE nil) (QUOTE nil))", ~Parser::result());
  reset();
}

TEST(AST, LibLambda) {
  supply("(set 'quote '(lambda (x) x)) ");
  EXPECT_EQ(Status::accept, status());
  EXPECT_STREQ("(SET (QUOTE QUOTE) (QUOTE (LAMBDA (X) X)))", ~Parser::result());
  reset();
}

TEST(AST, LibNLambda) {
  supply("(set 'quote '(nlambda (x) x)) ");
  EXPECT_EQ(Status::accept, status());
  EXPECT_STREQ("(SET (QUOTE QUOTE) (QUOTE (NLAMBDA (X) X)))", ~Parser::result());
  reset();
}

TEST(AST, LibDefun) {
  supply(""
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
//    "(SET (QUOTE DEFUN) (QUOTE (NLAMBDA (NAME PARAMETERS BODY)) (SET NAME (LAMBDA PARAMETERS BODY)))))"
//    "(SET (QUOTE DEFUN) (QUOTE (NLAMBDA (NAME PARAMETERS BODY) (SET NAME (LAMBDA PARAMETERS BODY)))))"

//    (SET (QUOTE NDEFUN) (QUOTE (NLAMBDA (NAME PARAMETERS BODY) (SET NAME (NLAMBDA PARAMETERS BODY)))))
//
//    (SET (QUOTE NDEFUN) (QUOTE (NLAMBDA (NAME PARAMETERS BODY) (SET NAME (NLAMBDA PARAMETERS BODY)))))"

TEST(AST, LibNDefun) {
  supply(""
    "(set 'ndefun\n"
      "'(nlambda (name parameters body)\n"
    "(set name (nlambda parameters body))))\n"
 "\n"
 "\n");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
  EXPECT_STREQ(""
      "(SET (QUOTE NDEFUN) " "(QUOTE (NLAMBDA (NAME PARAMETERS BODY) " "(SET NAME (NLAMBDA PARAMETERS BODY)))))"
  "",~Parser::result());
  reset();
}
