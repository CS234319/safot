#include <functional>
typedef std::function<bool ()> Predicate;

#define UNIQUE(X)       UNIQUE1(X,__LINE__)
#define UNIQUE1(X,Y)    UNIQUE2(X,Y)
#define UNIQUE2(X,Y)    X##Y

#define Promise(P) \
  struct UNIQUE(Promise) {                                               \
    typedef const char *const String;                                    \
    String file;                                                         \
    const long line;                                                     \
    String context, expression;                                          \
    Predicate predicate;                                                 \
    UNIQUE(Promise)(String f, long l, String c, String e, Predicate p):  \
      file(f), line(l), context(c), expression(e), predicate(p) {}       \ 
    ~UNIQUE(Promise)() {                                                 \ 
       if (predicate()) return;                                          \
       (void) fprintf(stderr,"%s(%d)/%s: '%s' = broken promise\n",       \
           file, line, context, expression);                             \
        throw this;                                                      \
    }                                                                    \
  } UNIQUE(promise)                                                      \
    (__FILE__, __LINE__, __PRETTY_FUNCTION__, #P, [=]{return P;})        \  
;

#define Expect(P) \     
  struct UNIQUE(Expect) {                                                \
    typedef const char *const String;                                    \
    String file;                                                         \
    const long line;                                                     \
    String context, expression;                                          \
    Predicate predicate;                                                 \
    UNIQUE(Expect)(String f, long l, String c, String e, Predicate p):   \
      file(f), line(l), context(c), expression(e), predicate(p) {        \ 
        if (predicate()) return;                                         \
         (void) fprintf(stderr,"%s(%d)/%s: '%s' = unmet expectation\n",  \
             file, line, context, expression);                           \
        throw this;                                                      \
    }                                                                    \
  } UNIQUE(Expect)                                                       \
    (__FILE__, __LINE__, __PRETTY_FUNCTION__, #P, [=]{return P;})        \  
;


