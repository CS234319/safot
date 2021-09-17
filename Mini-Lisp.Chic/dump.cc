#import  "dump.h"
#import "basics.h"
bool dumping = false;
std::ostream& operator<<(std::ostream &os, S s) { extern const S QUOTE;
  if (s.null()) return os << "nil";
  if (s.atom()) return os << s.asAtom();
  if (s.car().eq(QUOTE) && s.n2()) return  os << "'" << s.cdr().car();
  if (!islist(s)) return os << "" << s.car() << "." << s.cdr() << "";
  for (os << "("; !s.null() ;os << " ") {
    os << S(s.car());
    if ((s = s.cdr()).null()) 
      break;
  }
  return os << ")";
}
