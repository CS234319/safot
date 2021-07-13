#include "S.h"
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
static H last; 
static bool pending = false;

H peep() {
  H h = get();
  unget();
  return h;
}

H get() {
  if (!pending) 
    return last = next();
  pending = false;
  return last;
}

extern void initialize(String buffer) {
  head = const_cast<char *>(buffer);
  pending = false;
}

static char advance();
static H nextAtom();
static bool isToken();
static bool isAtom();
static bool isNewLine(); 
static bool isIgnored();

extern H unget() {
  pending = true;
  return last;
}

extern H next() {
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

static H nextAtom() {
  D(head,isToken());
  const char * const begin = head;
  for (;C();++head)   
    if (!isAtom())
      break;
  D(begin);
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
  return exists(C(),tokens);
}
}
extern bool exists(const char c, String s) {
  D(c, s);
  for (const char *p = s; *p; ++p)
    if (c == *p)
      return true;
  return false;
}


