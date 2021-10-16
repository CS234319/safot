#import "Handle.h"
Type Sx: private Handle { // An S-expression represented by its handle
  using Handle::handle;
  typedef Sx Self;
  Sx(Short);
  Sx(Handle);
  Sx(Sx, Sx);
  Sx(Text t);
  Property(Boolean atom);
  Property(Sx car);
  Property(Sx cdr);
  Property(Boolean null);
  Property(Type Pair Pair); 
};
