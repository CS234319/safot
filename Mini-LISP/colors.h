inline Half mark(Half h)   { return h + (1 << 15); } 
inline bool marked(Half h) { return h < $X_f$ || h > $X_t$; } 

static struct {
  inline bool white(Half h) { !marked(P[h].h1) && !marked(P[h].h2); } 
  inline bool red(Half h)   { marked(P[h].h1)  && !marked(P[h].h2); } 
  inline bool black(Half h) { !marked(P[h].h1) && marked(P[h].h2); } 
} is;

static struct {
  inline bool white(Half h) { return !is.white(h); }  
  inline bool red(Half h)   { return !is.red(h); }  
  inline bool black(Half h) { return !is.black(h); }  
} isnt;

static struct {
  auto white(Half h) { 
    !marked(P[h].h1)  || DIE;
    !marked(P[h].h2) || DIE;
    return P[h];
  }
  auto red(Half h) { 
    marked(P[h].h1)  || DIE;
    !marked(P[h].h2)  || DIE;
    return Pair(mark(P[h].h1), P[h].h2);
  }
  auto black(Half h) { 
    !marked(P[h].h1) || DIE;
    marked(P[h].h2)  || DIE;
    return Pair(P[h].h1, mark(P[h].h2));
  }
} into;

static struct {
  struct {
    inline auto car(Half h) { return into.white(h).car; }
    inline auto cdr(Half h) { return into.white(h).cdr; }
  } white; 
  struct {
    inline auto prev(Half h) { return into.red(h).prev; }
    inline auto next(Half h) { return into.red(h).next; }
  } red;
  struct {
    inline auto head(Half h) { return into.black(h).head; }
    inline auto rest(Half h) { return into.black(h).rest; }
   } black;
} get;

static struct {
  inline void white(Half h) { 
    if (marked(P[h].h1)) P[h].h1 =  mark(P[h].h1);
    if (marked(P[h].h2)) P[h].h2 =  mark(P[h].h2);
  } 
  inline void red(Half h) { 
    if (!marked(P[h].h1)) P[h].h1 = mark(P[h].h1);
    if (marked(P[h].h2)) P[h].h2  = mark(P[h].h2);
  } 
  inline void black(Half h) { 
    if (marked(P[h].h1)) P[h].h1  = mark(P[h].h1);
    if (!marked(P[h].h2)) P[h].h2 = mark(P[h].h2);
  } 
} paint; 

auto white1(Half h) { return h; }
auto white2(Half h) { return h; }
auto red1(Half h) { return mark(h); }
auto red2(Half h) { return h; }
auto black1(Half h) { return h; }
auto black2(Half h) { return mark(h);  }

struct White: $S_X$ {
  White(Half h): $S_X$(h) {}
  void car(Half h) { P[handle].car = white1(h); }
  void cdr(Half h) { P[handle].cdr = white2(h); }
};

struct Red: $S_X$ {
  Red(Half h): $S_X$(h) {}
  void prev(Half h) { P[handle].prev = red1(h); }
  void next(Half h) { P[handle].next = red2(h); }
};

struct Black: $S_X$ {
  Black(Half h): $S_X$(h) {}
  void head(Half h) { P[handle].head = black1(h); }
  void rest(Half h) { P[handle].rest = black2(h); }
}; 

static struct {
 White white(Half h) { return White(h); }  
 Red red(Half h) { return Red(h); } 
 Black black(Half h) { return Black(h); } 
} set;


