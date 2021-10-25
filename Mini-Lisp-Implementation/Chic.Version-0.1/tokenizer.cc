#import  "S.h"
#import  "tokenizer.h"
#import  "mode.h"

namespace Tokenizer {
static char *head;
static inline char& C() { return *head; }
static H last; 
static bool pending = false;

H peep() {
  H h = get();
  unget();
  return h;
}

H get() {
  if (!pending) return last = next();
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
  if (!advance())
    return $;
  if (isToken())
    return *head++;
  return nextAtom();
}

static char advance() {
  for (; ; ++head) {
    if (C() == '\0') break;
    if (isIgnored()) continue;
    if (C() != ';') break;
    for (++head; C() != '\0' && !isNewLine(); ++head)
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

static bool isAtom() { return !isToken() && !isIgnored(); }
static bool isNewLine() { return C() == '\n' || C() == '\r' || C() == '\0'; }
static bool isIgnored() { return C() == ' ' || C() == '\t' || isNewLine() || C() < ' ' || C() >= 127; }
static bool isToken() { return exists(C(),tokens); }
}

extern bool exists(const char c, String s) {
  for (const char *p = s; *p; ++p)
    if (c == *p)
      return true;
  return false;
}

extern int getParenthesesBalanceCounter() {
    int count = 0;
    auto saved_head = Tokenizer::head;
    auto res = Tokenizer::next();
    while(res != Tokenizer::$) {
        if (res == '(') {
            count ++;
        } else if (res == ')') {
            count --;
        }
        res = Tokenizer::next();
    }
    Tokenizer::head = saved_head;
    return count;
}
