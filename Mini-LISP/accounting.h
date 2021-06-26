#ifndef ACCOUNTING_H
#define ACCOUNTING_H
#include "chic.h"
Service {
  const Short& unused = inner.unused, used = inner.used;
  auto use()   { ++inner.used | --inner.unused; return *this; }
  auto unuse() { --inner.used | ++inner.unused; return *this; }
  auto request() { ++inner.requested; }
  void init(Short n) {
    inner.init(n); 
  }
  private: struct { 
    Integer requested, provided, missed, reused;   
    Short used, unused;
    void init(auto n) {
      unused = n, missed = used = 0;
      requested = provided = missed = reused = 0;
    }
  } inner;
} accounting;
#endif
