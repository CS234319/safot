#import "S.h"
namespace Engine {
  extern S builtin(); 
  extern S exec(S builtin);
  extern S defun(S name, S parameters, S body);
  extern S ndefun(S name, S parameters, S body);
}
