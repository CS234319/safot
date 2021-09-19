#import "Knob.h"
Type Pristine: private Knob {
  // Decomposition
  using Knob::handle;
  using Knob::x;
  using Knob::Item, Knob::Pair;
  Constructor(Pristine());
  Constructor(Pristine(Short));
  Property(Pristine prev);
  Property(Pristine next);
  Property(Boolean ok);

  Pristine& prev(Pristine); 
  Pristine& next(Pristine); 
};
inline std::ostream& operator<<(std::ostream &os, Pristine p) {
  if (p.x())
    return  os << "Px";
  return os << "Pristine[" << p.prev().handle() << "." << p.next().handle()  << "]";
}
