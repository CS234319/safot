#ifndef BUILTIN_H
#define BUILTIN_H
#include "S.h"
extern S builtin(); 
extern S exec(S builtin);
extern S defun(S name, S parameters, S body);
extern S ndefun(S name, S parameters, S body);
#endif  // 
