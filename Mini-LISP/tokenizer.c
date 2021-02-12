#include "tokenizer.h"

static char *head;

static inline char& C() {
  return *head;
}
extern void tokenize(char *buffer) {
  head = buffer;
}

static char advance();
static S nextAtom();
static bool isToken();
static bool isAtom();
static bool isNewLine(); 
static bool isIgnored();

extern H nextToken() {
  if (!advance())
    return $;
  if (isToken())
    return C();
  return nextAtom();
}

static S nextAtom() {
  const char * const begin = head;
  for (;C();++head)   
    if (!isAtom())
      break;
  char c = C();
  *head = '\0';
  S $ = Strings::allocate(begin);
  C() = c;
  return $;
}


static char advance() {
  for (; isIgnored(); ++head)
    if (C() == ';')
      for ( ; isNewLine(); ++head)
        ;
  return C();
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
