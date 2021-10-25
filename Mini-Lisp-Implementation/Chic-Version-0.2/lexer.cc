#import "chic.h"
Module lexer {
  enum { undefined = 128, $};
  const Letter tokens[] = "()[].\'";
  // Retrieve the next token: if non-positive, this is an atom (including NIL)
  // else it is a character as per the table above
  Provides Unit reset(char buffer[]) below
  Provides Short peep(), get(), unget(), next() below 
}

#if Implementation
#define PRODUCTION
#import "mode.h"
#import "text.cc"

Module lexer {
  Hides char *head;
  Hides Short last; 
  Hides Boolean pending = false;

  Provides Unit reset(char *buffer) is (head = buffer then pending = false)



Provides Short unget() is (pending = true then last) 
Provides Short peep() {
  Short Short = get();
  unget();
  return Short;
}

Provides Short get() {
  if (!pending) 
    return last = next();
  pending = false;
  return last;
}

  Hides inline char& C() { return *head; }

static Short nextAtom();

static Letter advance();
static Boolean isToken();
static Boolean isAtom();
static Boolean isNewLine(); 
static Boolean isIgnored();


Provides Short next() {
  D(head, C());
  if (!advance())
    return $;
  D(head, C(), isToken());
  if (isToken())
    return *head++;
  D(head, C());
  return nextAtom();
}

static Letter advance() {
    D(head, *head, C());
  for (; ; ++head) {
    D(head, *head, C());
    if (C() == '\0')
      break;
    D(head, *head, C());
    if (isIgnored())
      continue;
    D(head, *head, C());
    if (C() != ';')
      break;
    D(head, *head, C());
    for (++head; C() != '\0' && !isNewLine(); ++head)
        ;
    D(head, *head, C());
  }
    D(head, *head, C());
  return C();
}

static Short nextAtom() {
  D(head,isToken());
  Text begin(head);
  for (;C();++head)   
    if (!isAtom())
      break;
  D(begin);
  Letter c = C();
  C() = '\0';
  let $ = text::request(begin);
  C() = c;
  D($);
  return $.handle();
}

static Boolean isNewLine() is( C() == '\n' || C() == '\r' || C() == '\0')
static Boolean isIgnored() is( C() == ' ' || C() == '\t' || isNewLine() || C() < ' ' || C() >= 127)
static Boolean isToken()   { return Text(tokens).contains(C()); } 
static Boolean isAtom()    is( !isToken() && !isIgnored() )
}
#endif

