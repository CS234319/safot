#import "chic.h"
#import "Account.cc"

Type Function {
  As(Integer) is(provider())
  Provider provider;
  Function(Provider p): provider(p){} 
};

#define Closure(X) Function([&](){return(X);})

Provides Type Accounting {
  int N;
  Clicker use, unuse;
  Account used = Account(use, unuse); 
  Function unused = Closure(N-used);  
  Account pairs = used.kind(), items = used.kind();
  Clicker allocate, pop = allocate.kind(), pick = allocate.kind();  
  Clicker release,  push = release.kind(); 
  Clicker collect;
  Function live = Closure(allocate - release);
  Clicker visit, leave; 
  Clicker request, reuse = request.kind(), provide = request.kind(); 
  Clicker hit = provide.kind(), miss = provide.kind();   
  auto reset(Integer n) selfing(this->~Accounting(), N = n) 
} accounting;
#if Implementation
Accounting accounting;
#endif
