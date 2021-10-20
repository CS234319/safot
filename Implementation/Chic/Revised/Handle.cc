#import "chic.h"
Type Text below
Type Word below
Perspective(Handle, Short, 
  Feature(handle) is(matter)
  Initialize(Handle) from(nothing) below 
  Property(Boolean ok) below
  Property(Word& cons) below
  Property(Text text) below 
)

#if Implementation
#import "Word.cc"
#import "Text.cc"
#import "layout.h"
Initializing(Handle) from(nothing) by (Handle($X_x$))
Property(Boolean Handle::ok)  is(matter >= $X_f$ and matter <= $X_t$)
int f() {
  int i;
  Handle h;
  Handle h1((short)i);
  Handle h2();
  Handle h3(0);
  Handle h4(h3);
  Handle h5((Short)h1);
  Handle h6((short)i);

}
#endif

