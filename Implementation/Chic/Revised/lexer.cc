#import "chic.h"
Module lexer {
  enum { undefined = 128, $};
  const Letter tokens[] = "()[].\'";
  // Retrieve the next token: if non-positive, this is an atom (including NIL)
  // else it is a character as per the table above
  Provides void initialize(Letter buffer[]) below
  Provides Short next() below 
  Provides Short get() below 
  Provides Short unget() below 
  Provides Short peep() below
  Provides Short peep(),get() below
}

#if Implementation
#define PRODUCTION
#import "mode.h"

Module lexer {
  Hides char *head;
  Hides Short last; 
  Hides Boolean pending = false;
  Hides inline Letter& C(); 
  Hides inline Letter& C() { return *head; }

extern void initialize(Letter *buffer) {
  head = buffer;
  pending = false;
}



Short peep() {
  Short Short = get();
  unget();
  return Short;
}

Short get() {
  if (!pending) 
    return last = next();
  pending = false;
  return last;
}

static Short nextAtom();

static Letter advance();
static Boolean isToken();
static Boolean isAtom();
static Boolean isNewLine(); 
static Boolean isIgnored();

extern Short unget() {
  pending = true;
  return last;
}

extern Short next() {
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
  Text begin = head;
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

static Boolean isAtom() {
  return !isToken() && !isIgnored();
}

static Boolean isNewLine() {
  return C() == '\n' || C() == '\r' || C() == '\0';
}

static Boolean isIgnored() {
  return C() == ' ' || C() == '\t' || isNewLine() || C() < ' ' || C() >= 127;
}

static Boolean isToken() {
  return text::exists(C(),tokens);
}
}
#endif

