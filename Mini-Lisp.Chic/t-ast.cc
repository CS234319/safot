#import  <string.h>
#import  <gtest/gtest.h>
#import  "test.h"
#import  "basics.h"


static auto t(const char *s) {
  return Tokenizer::initialize(strdup(s));
}


using namespace Parser;


extern std::ostream& operator<<(std::ostream &os, S s); 

TEST(AST, AtomChar) {
  parse("z");
  ASSERT_NE(Status::ready, status());
  ASSERT_NE(Status::reject, status());
  EXPECT_EQ(Status::accept, status());
  EXPECT_STREQ("Z", S(result()).asAtom());   
  Parser::reset();
}

TEST(AST, AtomLong) {
  parse("Atom");
  EXPECT_STREQ("ATOM", S(result()).asAtom());   
  Parser::reset();
}

TEST(AST, List0) {
  parse("()");
  EXPECT_EQ(NIL, result());
  Parser::reset();
}

TEST(AST, List1) {
  parse("(HELLO)");
  auto s = Parser::result();
  ASSERT_NE(NIL,s);
  ASSERT_FALSE(s.null());
  ASSERT_FALSE(s.atom());
  ASSERT_TRUE(islist(s));
  EXPECT_STREQ("HELLO",s.car().asAtom());
  EXPECT_EQ(NIL,s.cdr());
  Parser::reset();
}

TEST(AST, List2) {
  parse("(1 2)");
  auto s = Parser::result();
  ASSERT_NE(NIL,s);
  ASSERT_FALSE(s.null());
  ASSERT_FALSE(s.atom());
  ASSERT_TRUE(islist(s));
  EXPECT_STREQ("1",s.car().asAtom());
  s = s.cdr();
  EXPECT_STREQ("2",s.car().asAtom());
  EXPECT_EQ(NIL,s.cdr());
  Parser::reset();
}

TEST(AST, List3) {
  parse("(A B C)");
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
  Parser::reset();
}

TEST(AST, QuoteA) {
  parse("'Z");
  auto s = Parser::result();
  ASSERT_NE(NIL,s);
  ASSERT_FALSE(s.null());
  ASSERT_FALSE(s.atom());
  ASSERT_TRUE(islist(s));
  EXPECT_STREQ("QUOTE",s.car().asAtom());
  s = s.cdr();
  EXPECT_STREQ("Z",s.car().asAtom());
  EXPECT_EQ(NIL,s.cdr());
  Parser::reset();
}

TEST(AST, QuoteAA) {
  parse("''Z");
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
  Parser::reset();
}

TEST(AST, Pair) {
  parse("hello.world");
  S s = Parser::result();
  ASSERT_FALSE(s.null());
  ASSERT_FALSE(s.atom());
  ASSERT_FALSE(islist(s));
  EXPECT_STREQ("HELLO",s.car().asAtom());
  EXPECT_STREQ("WORLD",s.cdr().asAtom());
  Parser::reset();
}

TEST(AST, PairYZ) {
  parse("Y.Z");
  S s = Parser::result();
  ASSERT_FALSE(s.null());
  ASSERT_FALSE(s.atom());
  ASSERT_FALSE(islist(s));
  EXPECT_STREQ("Y",s.car().asAtom());
  EXPECT_STREQ("Z",s.cdr().asAtom());
  Parser::reset();
}

TEST(AST, AtomOutput) {
  parse("Y");
  EXPECT_STREQ("Y", ~Parser::result());
  Parser::reset();
}

TEST(AST, PairInList) {
  parse("(Y.Z)");
  EXPECT_STREQ("(Y.Z)", ~Parser::result());
  Parser::reset();
}

TEST(AST, PairX) {
  parse("Y.Z");
  EXPECT_STREQ("Y.Z", ~Parser::result());
  Parser::reset();
}

TEST(AST, QNestedList) {
  parse("((a b) '(c (d e)))");
  EXPECT_STREQ("((A B) '(C (D E)))", ~Parser::result());
  Parser::reset();
}

TEST(AST, PairIsList) {
  parse("(c d).(a b)");
  EXPECT_STREQ("((C D) A B)", ~Parser::result());
  Parser::reset();
}


TEST(AST, ListQuotePair) {
  parse("(c d).'(a b)");
  EXPECT_STRCASEEQ("((C D) quote (A B))", ~Parser::result());
  Parser::reset();
}

TEST(AST, QuoteInList) {
  parse("(a 'b 'c)");
  EXPECT_STREQ("(A 'B 'C)", ~Parser::result());
  Parser::reset();
}

TEST(AST, QuoteExtra) {
  parse("(quote a b c)");
  EXPECT_STREQ("(QUOTE A B C)", ~Parser::result());
  Parser::reset();
}


TEST(AST, QuoteListInList) {
  parse("(a '(foo bar)  'c)");
  EXPECT_STREQ("(A '(FOO BAR) 'C)", ~Parser::result());
  Parser::reset();
}

TEST(AST, NIL) {
  parse("NIL");
  EXPECT_EQ(NIL, Parser::result());
  Parser::reset();
}

TEST(AST, EmptyListNiL) {
  parse("()");
  EXPECT_EQ(Status::accept, status());
  EXPECT_EQ(NIL, Parser::result());
  Parser::reset();
}

TEST(AST, LibT) {
  parse("(set (quote t) (quote t))");
  EXPECT_EQ(Status::accept, status());
  EXPECT_STREQ("(SET 'T 'T)", ~Parser::result());
  Parser::reset();
}

TEST(AST, LibNil) {
  parse("(set (quote nil) (quote nil))");
  EXPECT_EQ(Status::accept, status());
  EXPECT_STRCASEEQ("(SET 'nil 'nil)", ~Parser::result());
  Parser::reset();
}

TEST(AST, LibLambda) {
  parse("(set 'quote '(lambda (x) x)) ");
  EXPECT_EQ(Status::accept, status());
  EXPECT_STREQ("(SET 'QUOTE '(LAMBDA (X) X))", ~Parser::result());
  Parser::reset();
}

TEST(AST, LibNLambda) {
  parse("(set 'quote '(nlambda (x) x)) ");
  EXPECT_EQ(Status::accept, status());
  EXPECT_STREQ("(SET 'QUOTE '(NLAMBDA (X) X))", ~Parser::result());
  Parser::reset();
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
  EXPECT_STREQ(expected, ~Parser::result());
  Parser::reset();
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
  EXPECT_STREQ(expected,~Parser::result());
  Parser::reset();
}

TEST(DISABLED_AST, SquareBrackets) {
  parse(""
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
  Parser::reset();
}
