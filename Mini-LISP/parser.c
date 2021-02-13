#include "tokenizer.h"
#include "dump.h"

#define SILENT 1 
#if SILENT
#undef D
#define D(...) 0
#endif

namespace Tokenizer {
static char *head;

static inline char& C() {
  return *head;
}
extern void initialize(char *buffer) {
  head = buffer;
}

static char advance();
static H nextAtom();
static bool isToken();
static bool isAtom();
static bool isNewLine(); 
static bool isIgnored();

extern H next() {
  D(C(), head, isToken(), isIgnored(), isAtom(), isNewLine());
  if (!advance())
    return $;
  if (isToken())
    return *head++;
  D(C(), head, isToken(), isIgnored(), isAtom(), isNewLine());
  return nextAtom();
}

static char advance() {
  D(head,C(), (long)head, (int)C());
  for (; ; ++head) {
    D(head,C(), (long)head, (int)C());
    if (C() == '\0')
      break;
    if (isIgnored())
      continue;
    if (C() != ';')
      break;
    for ( ++head; C() != '\0' && !isNewLine(); ++head)
        ;
  }
  D(head,C(), (long)head, (int)C());
  return C();
}


static H nextAtom() {
  D(C(), head, isToken(), isIgnored(), isAtom(), isNewLine());
  const char * const begin = head;
  for (;C();++head)   
    if (!isAtom())
      break;
  D(begin, C(), (int)C(),head);
  char c = C();
  C() = '\0';
  H $ = Strings::allocate(begin);
  C() = c;
  D($);
  return $;
}

static bool isAtom() {
  return !isToken() && !isIgnored();
}

static bool isNewLine() {
  return C() == '\n' || C() == '\r' || C() == '\0';
}

static bool isIgnored() {
  return C() == ' ' || C() == '\t' || isNewLine() || C() < ' ' || C() >= 127;
}

static bool isToken() {
  for (const char *p = tokens; *p; ++p)
    if (C() == *p)
      return true;
  return false;
}
}
