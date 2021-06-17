#include <functional>
typedef std::function<bool ()> Predicate;

#define UNIQUE(X)       UNIQUE1(X,__LINE__)
#define UNIQUE1(X,Y)    UNIQUE2(X,Y)
#define UNIQUE2(X,Y)    X##Y

#define Promise(P) \
  struct UNIQUE(Promise) {                                           \
    typedef const char *const string;                                \
    string file;                                                     \
    const long line;                                                 \
    string context, expression;                                      \
    Predicate condition;                                 \
    UNIQUE(Promise)(                                                 \
      string file_, long line_, string context_,                     \
        string expression_, Predicate condition_):       \
          file(file_), line(line_), context(context_),               \
            expression(expression_), condition(condition_) {}        \
    ~UNIQUE(Promise)() {                                             \ 
     if (condition()) return;                                       \
     (void) fprintf(stderr,"%s(%d)/%s: '%s' = broken promise\n",     \
         file, line, context, expression);                           \
    }                                                                \
  } UNIQUE(promise)                                                  \
    (__FILE__, __LINE__, __PRETTY_FUNCTION__, #P, [=]{return P;})  \  
;

#define Expect(P) \     
  struct UNIQUE(Expect) {                                            \
    typedef const char *const string;                                \
    string file;                                                     \
    const long line;                                                 \
    string context, expression;                                      \
    Predicate condition;                                 \
    UNIQUE(Expect)(                                                  \
      string file_, long line_, string context_,                     \
        string expression_, Predicate condition_):       \
          file(file_), line(line_), context(context_),               \
            expression(expression_), condition(condition_) {         \
   if (condition()) return;                                         \
   (void) fprintf(stderr,"%s(%d)/%s: '%s' = unmet expectation\n",    \
         file, line, context, expression);                           \
    }                                                                \
  } UNIQUE(Expect)                                                   \
    (__FILE__, __LINE__, __PRETTY_FUNCTION__, #P, [=]{return P;})    \  
;


      //throw this;                                                    \

int f() {
  int i = 3;
  Expect(i>2);
  i = 8;
  Promise(i>3);
}
#include "store.h"

#define DIE die(__LINE__) 
#include "stdio.h"

bool inline die(int t) { throw t;  }

inline Half mark(Half h)   { return h + (1 << 15); } 
inline bool marked(Half h) { return h < $X_f$ || h > $X_t$ + 1; } 

struct Is: $S_X$ { 
  Is(Half h): $S_X$(h) {}
  Is($S_X$ s): $S_X$(s) {}
  inline Half &h1() const { return P[handle].h1; }
  inline Half &h2() const { return P[handle].h2; }
  inline auto h1(Half h) const { P[handle].h1 = h; return *this;}
  inline auto h2(Half h) const { P[handle].h2 = h; return *this;}
  inline bool white() const { !marked(h1()) && !marked(h2()); } 
  inline bool black() const { marked(h1()) && marked(h2()); } 
  inline bool brown()   const { !marked(h1()) && marked(h2()); } 
};

struct White: Is {
  White(Half h): Is(h) {}
  void car(Half h) const { h1() = h; }
  void cdr(Half h) const { h2() = h; }
  Half car() const { return h1(); }
  Half cdr() const { return h2(); } 
};

struct Black: Is {
  Black(Half h): Is(h) {}
  auto prev(Half h) const { 
    Expect(!marked(h));
    h1() = mark(h); 
    return *this;
  }
  auto next(Half h) const { 
    Expect(!marked(h));
    h2() = mark(h); 
    return *this;
  }
  auto prev() const { 
    Expect(marked(h1()));
    return mark(h1()); 
  }
  auto next() const { 
    Expect(marked(h2()));
    return mark(h2()); 
  }
};

struct Brown: Is {
  Brown(Half h): Is(h) {}
  auto head(Half h) const { h1() = h;       return *this; }
  auto rest(Half h) const { h2() = mark(h); return *this; }
  Half head() { return h1(); }
  Half rest() { return mark(h2()); } 
}; 


static struct {
  inline bool white(Cons c) { return !marked(c.h1) && !marked(c.h2); } 
  inline bool black(Cons c) { return marked(c.h1) && marked(c.h2); } 
  inline bool brown(Cons c) { return !marked(c.h1) && marked(c.h2); } 
} is;

static struct {
  auto clean(Half &h) {
    if (marked(h)) h = mark(h);
    return *this;
  }
  auto stain(Half &h){
    if (!marked(h)) h = mark(h);
    return *this;
  }
  inline auto white(Half h) { 
    Expect(h >= $P_f$ && h <= $P_t$)
    Promise(Is(h).white());
    clean(P[h].h1).clean(P[h].h2);
    return White(h);
  } 
  inline auto black(Half h) { 
    f();
    Expect(h >= $P_f$ && h <= $P_t$)
    Promise(Is(h).black());
    stain(P[h].h1).stain(P[h].h2);
    return Black(h);
  } 
  inline auto brown(Half h) { 
    Expect(h >= $P_f$ && h <= $P_t$)
    Promise(Is(h).brown()) 
    clean(P[h].h1).stain(P[h].h2);
    return Brown(h);
  } 
} paint; 

#include <stdio.h>

static Half heapify();
static Half heap = heapify();

auto fresh() {
  heap != $P_x$ || DIE;
  auto const __ = Black(heap); 
  heap = __.next();
  __.prev($P_x$);
  return Brown(__.handle);
}

auto fresh(Half h1, Half h2) {
  return fresh().head(h1).rest(h2);
}

auto fresh(Cons c) {
  return fresh().head(c.h1).rest(c.h2);
}

Half hash(Cons c) {
  return $P_f$ + (c.w * 31 + 17) % $P_n$;
}

$S_X$ require(Cons c, Half h) {
  Expect(is.white(c));
  Promise(is.white(P[h]));
  if (P[h].w == c.w) return h; 
  if (!Is(h).black()) return fresh(c);
  const auto b = Black(h);
//  Sure(!marked(b.prev()));
//  Sure(!marked(b.next()));
  const Half prev = b.prev(), next = b.next();
//  Sure(!marked(prev));
// Sure(!marked(next));
//  Sure(prev == $P_x$ || Is(prev).black());
//  Sure(next == $P_x$ || Is(next).black());
  if (prev != $P_x$) Black(prev).next(next); 
  if (next != $P_x$) Black(next).prev(prev); 
  if (heap == h) heap = h;
  P[h] = c;
  return h;
}

$S_X$ require(Cons c) {
  return require(c, hash(c));
}
  
static Half heapify() {
  for (Half h = $P_f$; h <= $P_t$; ++h) 
    Is(h).h1(h-1).h2(h+1);
  Is($P_f$).h1($P_x$);
  Is($P_t$).h2($P_x$);
  for (Half h = $P_f$; h <= $P_t$; ++h) 
    paint.black(h); 
  return heap = $P_f$;
}

auto valid() {
  long __ = 0;
  for (Half h = heap, h2 = h ; h != $P_x$; h = Black(h).next()) { 
    ++__;
    if (!Is(h).black()) return __; 
    if (h2 != $P_x$) h2 = Black(h2).next();
    if (h2 != $P_x$) h2 = Black(h2).next();
    if (h == h2) return -__; 
  } 
  return 0L;
}

void free($S_X$ s) {
  auto const h = s.handle;
  Expect(Is(h).brown());
  Black(h).prev($P_x$).next(heap); 
  heap = h;
}

$S_X$ require(Half car, Half cdr) { return require(Cons(car,cdr)); }

#include <stdio.h>

Half length() {
  Half result = 0;
  for (Half h = heap; h != $P_x$; h = Black(h).next()) // printf("%d ", h), 
      ++result;
  return result;
}

#undef min
#undef max
#undef data
#undef function
#undef Type

#include "gtest/gtest.h"

TEST(Mark, FixedPoint) { 
  for (auto h = -32768; h != 32767; ++h)
    EXPECT_NE(h, mark(h)) << h;
}

TEST(Mark, Last) {
  EXPECT_FALSE(marked($P_t$ + 1));
}

TEST(Cons, hash) { 
  EXPECT_NE(hash(Cons(3,4)), hash(Cons(4,3)));
  EXPECT_NE(hash(Cons(3,4)), hash(Cons(4,3)));
  EXPECT_NE(hash(Cons(2,3)), hash(Cons(4,5)));
  EXPECT_NE(hash(Cons(2,3)), hash(Cons(4,5)));
  EXPECT_GT(hash(Cons(2,3)), 4);
  EXPECT_GT(hash(Cons(3,4)), 3);
  EXPECT_GT(hash(Cons(4,5)), 4);
}

TEST(Heapify, exists) { 
  try {
    heapify();
  } catch(int e) {
    ADD_FAILURE() << "Died at line " << e;
  }
}

TEST(Heapify, valid) { 
  try {
    heapify();
    EXPECT_EQ(valid(), 0);
  } catch(int e) {
    ADD_FAILURE() << "Died at line " << e;
  }
}

TEST(Heapify, length) { 
  try {
    heapify();
    valid();
    EXPECT_EQ(length(), $P_n$);
  } catch(int e) {
    ADD_FAILURE() << "Died at line " << e;
  }
}

TEST(Heapify, Black) { 
  heapify();
  EXPECT_NE(heap, $P_x$);
  EXPECT_EQ(heap, 1);
  EXPECT_EQ(heap, $P_f$);
  EXPECT_EQ(Black(1).next(), 2);
  EXPECT_EQ(Black(1).prev(), 0);
  EXPECT_EQ(Black(2).next(), 3);
  EXPECT_EQ(Black(2).prev(), 1);
  EXPECT_EQ(Black($P_t$).prev(), $P_t$-1);
  EXPECT_EQ(Black($P_t$).next(), $P_x$);
}

TEST(Heapify, BLACK) { 
  heapify();
  for (Half h = $P_f$; h <= $P_t$; ++h)
    EXPECT_TRUE(Is(h).black()) << h;
}

TEST(Fresh, exists) { 
  heapify();
  fresh(15,21);
}

TEST(Fresh, correct) { 
  heapify();
  auto f = fresh(15,21);
  EXPECT_EQ(f.head(), 15);
  EXPECT_EQ(f.head(), 15);
}

TEST(Fresh, 1) { 
  heapify();
  EXPECT_EQ(valid(),0);
  EXPECT_EQ(heap,1);
  auto s1 = fresh().handle;
  EXPECT_EQ(heap,2);
  EXPECT_EQ(s1,1);
  EXPECT_EQ(valid(),0);
  EXPECT_EQ(length(), $P_n$-1);
}

TEST(Fresh, 3) { 
  try {
    heapify();
    const auto s1 = fresh(2,3);
    const auto s2 = fresh(4,5);
    const auto s3 = fresh(6,7);
    free(s2);
    free(s1);
    free(s3);
  } catch(int e) {
    ADD_FAILURE() << "Died at line " << e;
  }
}

TEST(Fresh, Length) { 
  try {
    heapify();
    EXPECT_EQ(length(), $P_n$);

    const auto s1 = fresh(2,3);
    EXPECT_EQ(length(), $P_n$ - 1);

    const auto s2 = fresh(4,5);
    EXPECT_EQ(length(), $P_n$ - 2);

    const auto s3 = fresh(6,7);
    EXPECT_EQ(length(), $P_n$ - 3);

    free(s1);
    EXPECT_EQ(heap, 1);
    EXPECT_EQ(length(), $P_n$ - 2);

    free(s3);
    EXPECT_EQ(heap, 3);
    EXPECT_EQ(length(), $P_n$ - 1);

    free(s2);
    EXPECT_EQ(heap, 2);
    EXPECT_EQ(length(), $P_n$);
  } catch(int e) {
    ADD_FAILURE() << "Died at line " << e;
  }
}

TEST(Require, exists) { 
  try {
    heapify();
    require(0xDE,0xAD);
  } catch(int e) {
    ADD_FAILURE() << "Died at line " << e;
  }
}

TEST(Require, white) { 
  try {
    heapify();
    auto h = require(0xDE,0xAD).handle;
    EXPECT_TRUE(Is(h).white());
  } catch(int e) {
    ADD_FAILURE() << "Died at line " << e;
  }
}

TEST(Require, correct) { 
  try {
    heapify();
    auto h = require(0xDE,0xAD).handle;
    EXPECT_EQ(P[h].h1, 0xDE);
    EXPECT_EQ(P[h].h2, 0xAD);
  } catch(int e) {
    ADD_FAILURE() << "Died at line " << e;
  }
}

TEST(Require, 3) { 
  try {
    heapify();
    auto s1 = require(2,3);
    auto s2 = require(4,5);
    auto s3 = require(6,7);
  } catch(int e) {
    ADD_FAILURE() << "Died at line " << e;
  }
}

TEST(Require, correct3) { 
  heapify();
  EXPECT_EQ(valid(),0);
  EXPECT_EQ(heap,1);
  auto s1 = require(2,3);
  EXPECT_EQ(heap,1);
  EXPECT_NE(s1.handle,1);
  EXPECT_EQ(P[s1.handle].h1,2);
  EXPECT_EQ(P[s1.handle].h2,3);
  EXPECT_EQ(valid(),0);
  EXPECT_EQ(length(), $P_n$-1);
  auto s2 = require(4,5);
  EXPECT_EQ(P[s2.handle].h1,4);
  EXPECT_EQ(P[s2.handle].h2,5);
  EXPECT_EQ(valid(),0);
  EXPECT_EQ(heap,1);
  EXPECT_EQ(length(), $P_n$-2);
  auto s3 = require(6,7);
  EXPECT_EQ(heap,1);
  EXPECT_EQ(P[s3.handle].h1,6);
  EXPECT_EQ(P[s3.handle].h2,7);
}

TEST(Require, Scenario) { 
  heapify();
  EXPECT_EQ(valid(),0);
  EXPECT_EQ(heap,1);
  auto s1 = require(2,3);
  EXPECT_EQ(heap,1);
  EXPECT_EQ(s1.handle,hash(Cons(2,3)));
  EXPECT_EQ(P[s1.handle].h1,2);
  EXPECT_EQ(P[s1.handle].h2,3);
  EXPECT_EQ(valid(),0);
  EXPECT_EQ(length(), $P_n$-1);
  auto s2 = require(4,5);
  EXPECT_EQ(s2.handle,hash(Cons(4,5)));
  EXPECT_EQ(heap,1);
  EXPECT_EQ(P[s2.handle].h1,4);
  EXPECT_EQ(P[s2.handle].h2,5);
  EXPECT_EQ(valid(),0);
  EXPECT_EQ(length(), $P_n$-2);
  auto s3 = require(6,7);
  EXPECT_EQ(s3.handle,hash(Cons(6,7)));
  EXPECT_EQ(P[s3.handle].h1,6);
  EXPECT_EQ(P[s3.handle].h2,7);
  EXPECT_EQ(valid(),0);
  EXPECT_EQ(length(), $P_n$-3);
}

TEST(Is, correct) { 
  try {
    heapify();
    auto s = require(12,14);
    auto h = s.handle;
    EXPECT_TRUE(Is(h).white());
    EXPECT_FALSE(Is(h).black());
    EXPECT_FALSE(Is(h).brown());
    paint.black(h);
    EXPECT_FALSE(Is(h).white());
    EXPECT_TRUE (Is(h).black());
    EXPECT_FALSE(Is(h).brown());
    paint.brown(h);
    EXPECT_FALSE(Is(h).white());
    EXPECT_FALSE(Is(h).black());
    EXPECT_TRUE (Is(h).brown());
  } catch(int e) {
     ADD_FAILURE() << "Died at line " << e;
  }
}

TEST(Words, Reuse) { 
  heapify();
  EXPECT_EQ(valid(),0);
  EXPECT_EQ(length(), $P_n$);

  auto s1 = require(0,0);
  EXPECT_TRUE(Is(s1).white());
  EXPECT_EQ(s1.handle, hash(P[s1.handle]));
  EXPECT_EQ(valid(),0);
  EXPECT_EQ(length(), $P_n$-1);

  auto s2 = require(2,3);
  EXPECT_TRUE(Is(s2).white());
  EXPECT_EQ(s2.handle, hash(P[s2.handle]));
  EXPECT_EQ(valid(),0);
  EXPECT_EQ(length(), $P_n$-2);

  auto s3 = require(3,2);
  EXPECT_EQ(s3.handle, hash(P[s3.handle]));
  EXPECT_TRUE(Is(s3).white());
  EXPECT_EQ(valid(),0);
  EXPECT_EQ(length(), $P_n$-3);

  auto s4 = require(2,3);
  EXPECT_TRUE(Is(s4).white());
  EXPECT_EQ(s4.handle, hash(P[s4.handle]));
  EXPECT_EQ(valid(),0);
  EXPECT_EQ(length(), $P_n$-3);

  auto s5 = require(0,0);
  EXPECT_TRUE(Is(s5).white());
  EXPECT_EQ(s5.handle, hash(P[s5.handle]));
  EXPECT_EQ(length(), $P_n$-3);
  EXPECT_EQ(valid(),0);

  auto s6 = require(3,2);
  EXPECT_TRUE(Is(s6).white());
  EXPECT_EQ(s6.handle, hash(P[s6.handle]));
  EXPECT_EQ(length(), $P_n$-3);
  EXPECT_EQ(valid(),0);

  EXPECT_EQ(s1.handle, s5.handle);
  EXPECT_EQ(s2.handle, s4.handle);
  EXPECT_EQ(s3.handle, s6.handle);
}

TEST(Marking, Pairs) { 
  EXPECT_LT(mark($P_f$), $A_f$);   
  EXPECT_LT(mark($P_t$), $A_f$);   
  EXPECT_LT(mark(($P_f$ + $P_t$)/2), $A_f$);   
  EXPECT_LT(mark($P_f$-1), $A_f$);   
  EXPECT_LT(mark($P_f$+1), $A_f$);   
  EXPECT_EQ(mark(mark($P_f$)), $P_f$);
  EXPECT_EQ(mark(mark($P_t$)), $P_t$);
  EXPECT_EQ(mark(mark(($P_f$ + $P_t$)/2)),($P_f$ + $P_t$)/2);
  EXPECT_EQ(mark(mark($P_t$ + 1)),$P_t$ + 1 );
  EXPECT_EQ(mark(mark($P_t$ + 1)), $P_t$ + 1);
}

TEST(Marking, Atoms) { 
  EXPECT_GT(mark($A_f$), $A_t$);   
  EXPECT_LT(mark($A_t$),0);
  EXPECT_GT(mark(($A_f$ + $A_t$)/2), $P_t$);   
  EXPECT_GT(mark($A_t$ - 1), $P_t$);   
  EXPECT_GT(mark($A_f$ - 1), $P_t$);   
  EXPECT_EQ(mark(mark($A_f$)), $A_f$);
  EXPECT_EQ(mark(mark($A_f$ + 1)),$A_f$ + 1 );
  EXPECT_EQ(mark(mark($A_t$ + 1)), $A_t$ + 1);
  EXPECT_EQ(mark(mark($A_t$)), $A_t$);
  EXPECT_EQ(mark(mark(($A_f$ + $A_t$)/2)),($A_f$ + $A_t$)/2);
}

TEST(Marking, Bounds) { 
  EXPECT_LT(mark($P_f$), $P_f$);   
  EXPECT_LT(mark($P_t$), $P_t$);   
  EXPECT_LT(mark(($P_f$ + $P_t$)/2), $A_f$);
  EXPECT_LT(mark($P_f$-1), $X_f$);
  EXPECT_LT(mark($P_f$+1), $X_f$);   
  EXPECT_EQ(mark(mark($P_f$)), $P_f$);
  EXPECT_EQ(mark(mark($P_t$)), $P_t$);
  EXPECT_EQ(mark(mark(($P_f$ + $P_t$)/2)),($P_f$ + $P_t$)/2);
  EXPECT_EQ(mark(mark($P_f$ - 1)),$P_f$ - 1 );
  EXPECT_EQ(mark(mark($P_f$ + 1)), $P_f$ + 1);
  EXPECT_EQ(mark(mark($P_t$ - 1)),$P_t$ - 1 );
  EXPECT_EQ(mark(mark($P_t$ + 1)), $P_t$ + 1);
}

TEST(Marking, Atoms1) { 
  EXPECT_GT(mark($A_f$), $X_t$);   
  EXPECT_LT(mark($A_t$), $A_f$);
  EXPECT_GT(mark(($A_f$ + $A_t$)/2), $X_t$);
  EXPECT_GT(mark($A_t$-1), $X_t$);   
  EXPECT_GT(mark($A_f$+1), $X_t$);   
  EXPECT_EQ(mark(mark($A_f$)),$A_f$);
  EXPECT_EQ(mark(mark($A_t$)),$A_t$);
  EXPECT_EQ(mark(mark(($A_f$ + $A_t$)/2)),($A_f$ + $A_t$)/2);
  EXPECT_EQ(mark(mark($A_f$ - 1)), $A_f$ - 1 );
  EXPECT_EQ(mark(mark($A_t$ - 1)), $A_t$ - 1);
  EXPECT_EQ(mark(mark($A_f$ + 1)), $A_f$ + 1 );
  EXPECT_EQ(mark(mark($A_t$ + 1)), $A_t$ + 1);
}

