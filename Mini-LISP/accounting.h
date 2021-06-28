#ifndef ACCOUNTING_H
#define ACCOUNTING_H
#include "Account.h"
Type Function {
  operator Integer() const { return provider(); }
  Provider provider;
  Function(Provider p): provider(p){} 
};

#define Closure(X) Function([&](){return(X);})

extern Type Accounting {
  int N;
  Clicker use, unuse;
  Account used = Account(use, unuse); 
  Function unused = Closure(N-used);  
  Account pairs = used.kind(), items = used.kind();
  Clicker allocate, pop = allocate.kind(), pick = allocate.kind();  
  Clicker release, push = release.kind(), collect = release.kind();
  Function live = Closure(allocate - release);
  Clicker visit, unvisit; 
  Clicker request, reuse = request.kind(), provide = request.kind(); 
  Clicker hit = provide.kind(), miss = provide.kind();   

  auto operator !() selfing(
      !pairs | !items | 
      !push  | !pop | !pick |
      !collect | !visit | 
      !request | !reuse | !hit | !miss 
  )
  auto init(Integer n) selfing(!*this, N = n) 
} accounting;
#endif
