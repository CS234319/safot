#ifndef ACCOUNTING_H
#define ACCOUNTING_H
#include "chic.h"
#define Fluenter(name) auto name()  
#define does(...)       { return (__VA_ARGS__), *this; }
#define Capsule(...) private:struct{ __VA_ARGS__}_; public: 

Service {
  Capsule ( 
    Short items, pairs, used, unused;
    Integer popped, picked, pushed, requested, provided, missed, reused;   
    Fluenter(init) does(
                      items = pairs = used = unused = 
                      popped = picked = pushed = requested = provided = missed = reused = 0
                   )
  )
  const Short& 
    items = _.items, 
    pairs = _.pairs,
    used  = _.used,
    unused = _.unused;
  const Integer& 
    popped = _.popped, 
    picked = _.picked, 
    pushed = _.pushed, 
    requested = _.requested, 
    provided = _.provided, 
    missed = _.missed, 
    reused = _.reused;

  Fluenter(pop)     does(_.popped++ | _.used++ | _.unused--)
  Fluenter(pick)    does(_.picked++ | _.used++ | _.unused--)
  Fluenter(push)    does(_.pushed++ | _.used-- | _.unused++)
  Fluenter(request) does(_.requested++)
  Fluenter(provide) does(_.provided++)
  Fluenter(reuse)   does(_.provided++)
  Fluenter(miss)    does(_.missed++)
  Fluenter(item)    does(_.items++)
  Fluenter(unitem)  does(_.items--)

  auto init(Short n) does(_.init(), _.used = n)
} accounting;
#endif
