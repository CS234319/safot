#include "Tokenizer.h"
#include "text.h"

#define SILENT 1
#if SILENT
#undef D
#define D(...) 0
#endif

namespace Tokenizer {
static char *head;
static Boolean pending = false;
static inline char& C(); 

extern void initialize(char *buffer) {
  head = buffer;
  pending = false;
}

static inline char& C() {
  return *head;
}

static Short last; 

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

static char advance();
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

static char advance() {
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
  char c = C();
  C() = '\0';
  let $ = request(begin);
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
  return exists(C(),tokens);
}
}

