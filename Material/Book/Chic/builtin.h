#import "S.h"
namespace Engine {
  namespace Builtins {
    extern S builtin(); 
    extern S exec(S builtin);
    extern S defun(S name, S parameters, S body);
    extern S ndefun(S name, S parameters, S body);
  }
}
