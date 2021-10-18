#import  <string.h>
#import  <gtest/gtest.h>
#import  "Testee.h"
// #import  "basics.h"

#import "parser.h"
using namespace parser;

static auto t(const char *s) {
  return lexer::initialize(strdup(s));
}

extern std::ostream& <<(std::ostream &os, S s); 

TEST(AST, AtomChar) {
  parse("z");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
  EXPECT_STREQ("Z", S(result()).text());   
  parser::reset();
}

TEST(AST, AtomLong) {
  parse("Atom");
  EXPECT_STREQ("ATOM", S(result()).text());   
  parser::reset();
}

TEST(AST, List0) {
  parse("()");
  EXPECT_EQ(NIL, result());
  parser::reset();
}

TEST(AST, List1) {
  parse("(HELLO)");
  auto s = parser::result();
  ASSERT_NE(NIL,s);
  ASSERT_FALSE(s.null());
  ASSERT_FALSE(s.atom());
  ASSERT_TRUE(islist(s));
  EXPECT_STREQ("HELLO",s.car().text());
  EXPECT_EQ(NIL,s.cdr());
  parser::reset();
}

TEST(AST, List2) {
  parse("(1 2)");
  auto s = parser::result();
  ASSERT_NE(NIL,s);
  ASSERT_FALSE(s.null());
  ASSERT_FALSE(s.atom());
  ASSERT_TRUE(islist(s));
  EXPECT_STREQ("1",s.car().text());
  s = s.cdr();
  EXPECT_STREQ("2",s.car().text());
  EXPECT_EQ(NIL,s.cdr());
  parser::reset();
}

TEST(AST, List3) {
  parse("(A B C)");
  auto s = parser::result();
  ASSERT_NE(NIL,s);
  ASSERT_FALSE(s.null());
  ASSERT_FALSE(s.atom());
  ASSERT_TRUE(islist(s));
  EXPECT_STREQ("A",s.car().text());
  s = s.cdr();
  EXPECT_STREQ("B",s.car().text());
  s = s.cdr();
  EXPECT_STREQ("C",s.car().text());
  EXPECT_EQ(NIL,s.cdr());
  parser::reset();
}

TEST(AST, QuoteA) {
  parse("'Z");
  auto s = parser::result();
  ASSERT_NE(NIL,s);
  ASSERT_FALSE(s.null());
  ASSERT_FALSE(s.atom());
  ASSERT_TRUE(islist(s));
  EXPECT_STREQ("QUOTE",s.car().text());
  s = s.cdr();
  EXPECT_STREQ("Z",s.car().text());
  EXPECT_EQ(NIL,s.cdr());
  parser::reset();
}

TEST(AST, QuoteAA) {
  parse("''Z");
  auto s = parser::result();
  ASSERT_NE(NIL,s);
  ASSERT_FALSE(s.null());
  ASSERT_FALSE(s.atom());
  ASSERT_TRUE(islist(s));
  EXPECT_STREQ("QUOTE",s.car().text());
  s = s.cdr();
  ASSERT_FALSE(s.null());
  ASSERT_FALSE(s.atom());
  ASSERT_TRUE(islist(s));
  s = s.car();
  EXPECT_STREQ("QUOTE",s.car().text());
  s = s.cdr();
  EXPECT_STREQ("Z",s.car().text());
  EXPECT_EQ(NIL,s.cdr());
  parser::reset();
}

TEST(AST, Pair) {
  parse("hello.world");
  S s = parser::result();
  ASSERT_FALSE(s.null());
  ASSERT_FALSE(s.atom());
  ASSERT_FALSE(islist(s));
  EXPECT_STREQ("HELLO",s.car().text());
  EXPECT_STREQ("WORLD",s.cdr().text());
  parser::reset();
}

TEST(AST, PairYZ) {
  parse("Y.Z");
  S s = parser::result();
  ASSERT_FALSE(s.null());
  ASSERT_FALSE(s.atom());
  ASSERT_FALSE(islist(s));
  EXPECT_STREQ("Y",s.car().text());
  EXPECT_STREQ("Z",s.cdr().text());
  parser::reset();
}

TEST(AST, AtomOutput) {
  parse("Y");
  EXPECT_STREQ("Y", ~parser::result());
  parser::reset();
}

TEST(AST, PairInList) {
  parse("(Y.Z)");
  EXPECT_STREQ("(Y.Z)", ~parser::result());
  parser::reset();
}

TEST(AST, PairX) {
  parse("Y.Z");
  EXPECT_STREQ("Y.Z", ~parser::result());
  parser::reset();
}

TEST(AST, QNestedList) {
  parse("((a b) '(c (d e)))");
  EXPECT_STREQ("((A B) '(C (D E)))", ~parser::result());
  parser::reset();
}

TEST(AST, PairIsList) {
  parse("(c d).(a b)");
  EXPECT_STREQ("((C D) A B)", ~parser::result());
  parser::reset();
}


TEST(AST, ListQuotePair) {
  parse("(c d).'(a b)");
  EXPECT_STRCASEEQ("((C D) quote (A B))", ~parser::result());
  parser::reset();
}

TEST(AST, QuoteInList) {
  parse("(a 'b 'c)");
  EXPECT_STREQ("(A 'B 'C)", ~parser::result());
  parser::reset();
}

TEST(AST, QuoteExtra) {
  parse("(quote a b c)");
  EXPECT_STREQ("(QUOTE A B C)", ~parser::result());
  parser::reset();
}


TEST(AST, QuoteListInList) {
  parse("(a '(foo bar)  'c)");
  EXPECT_STREQ("(A '(FOO BAR) 'C)", ~parser::result());
  parser::reset();
}

TEST(AST, NIL) {
  parse("NIL");
  EXPECT_EQ(NIL, parser::result());
  parser::reset();
}

TEST(AST, EmptyListNiL) {
  parse("()");
  EXPECT_EQ(Status::accept, status());
  EXPECT_EQ(NIL, parser::result());
  parser::reset();
}

TEST(AST, LibT) {
  parse("(set (quote t) (quote t))");
  EXPECT_EQ(Status::accept, status());
  EXPECT_STREQ("(SET 'T 'T)", ~parser::result());
  parser::reset();
}

TEST(AST, LibNil) {
  parse("(set (quote nil) (quote nil))");
  EXPECT_EQ(Status::accept, status());
  EXPECT_STRCASEEQ("(SET 'nil 'nil)", ~parser::result());
  parser::reset();
}

TEST(AST, LibLambda) {
  parse("(set 'quote '(lambda (x) x)) ");
  EXPECT_EQ(Status::accept, status());
  EXPECT_STREQ("(SET 'QUOTE '(LAMBDA (X) X))", ~parser::result());
  parser::reset();
}

TEST(AST, LibNLambda) {
  parse("(set 'quote '(nlambda (x) x)) ");
  EXPECT_EQ(Status::accept, status());
  EXPECT_STREQ("(SET 'QUOTE '(NLAMBDA (X) X))", ~parser::result());
  parser::reset();
}

TEST(AST, LibDefun) {
  parse(""
"(set 'defun\n"
  "'(nlambda (name parameters body)\n"
    "(set name (lambda parameters body))))"
      ""
 "\n"
 "\n");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
  auto expected = "(SET 'DEFUN '(NLAMBDA (NAME PARAMETERS BODY) (SET NAME (LAMBDA PARAMETERS BODY))))";
  EXPECT_STREQ(expected, ~parser::result());
  parser::reset();
}

TEST(AST, LibNDefun) {
  parse(""
    "(set 'ndefun\n"
      "'(nlambda (name parameters body)\n"
    "(set name (nlambda parameters body))))\n"
 "\n"
 "\n");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
  auto expected = ""
      "(SET 'NDEFUN " //
      "'(NLAMBDA (NAME PARAMETERS BODY) " //
      "(SET NAME (NLAMBDA PARAMETERS BODY))))" //
  "";
  EXPECT_STREQ(expected,~parser::result());
  parser::reset();
}
