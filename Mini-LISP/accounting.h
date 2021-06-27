#ifndef ACCOUNTING_H
#define ACCOUNTING_H
#include "chic.h"
#define Fluenter(name) auto name()  
#define doing(...)       { return (__VA_ARGS__), *this; }
#define Capsule(...) private:struct{ __VA_ARGS__}_; public: 

Service {
  Capsule ( 
    Short unused, used, pairs, items;
    Integer pushs, pops, picks;
    Integer collects, visits;
    Integer requests, reused, provided, hits, missed;   
    Fluenter(init) doing(
                      unused = used = pairs = items = 
                      pushs = pops = picks = 
                      collects = visits = 
                      requests = reused = provided = hits = missed = 
                      0
                   )
  )
 const Short& unused = _.unused, used = _.used, pairs = _.pairs, items = _.items;
 const Integer& pops = _.pops, pushs = _.pushs, picks = _.picks;
 const Integer& collects = _.collects, visits = _.visits;
 const Integer& requests = _.requests, reused = _.reused, provided = _.provided, hits = _.hits, missed = _.missed;

  private: 
    Fluenter(use)     doing(_.used++ | _.unused--)
    Fluenter(unuse)   doing(_.used-- | _.unused--)
    Fluenter(provide) doing(use() | _.provided++)
  public:
    operator int() { return 0; }
    Fluenter(push)    doing(_.pushs++ | unuse() )
    Fluenter(pop)     doing(_.pops++  | use())
    Fluenter(pick)    doing(_.picks++ | use())

    Fluenter(collect) doing(_.collects++)
    Fluenter(visit)   doing(_.visits++)

   Fluenter(request) doing(_.requests++)
   Fluenter(reuse)      doing(_.reused++)
   Fluenter(hit)     doing(provide() | _.hits++) 
   Fluenter(miss)    doing(provide() | _.missed++)

  Fluenter(item)    doing(_.items++)
  Fluenter(unitem)  doing(_.items--)

  auto init(Short n) doing(_.init(), _.used = n)
} accounting;
#endif
