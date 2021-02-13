#include "mini-lisp.hh"
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

static H last; 
static bool pending = false;

extern H get() {
  if (!pending) 
    return last = next();
  pending = false;
  return pending;
}

extern H unget() {
  pending = false;
  return last;
}

extern H next() {
  if (!advance())
    return $;
  if (isToken())
    return *head++;
  return nextAtom();
}

static char advance() {
  for (; ; ++head) {
    if (C() == '\0')
      break;
    if (isIgnored())
      continue;
    if (C() != ';')
      break;
    for ( ++head; C() != '\0' && !isNewLine(); ++head)
        ;
  }
  return C();
}


static H nextAtom() {
  const char * const begin = head;
  for (;C();++head)   
    if (!isAtom())
      break;
  char c = C();
  C() = '\0';
  H $ = Strings::allocate(begin);
  C() = c;
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
