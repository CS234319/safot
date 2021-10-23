#import "chic.h"
xads asdf a asdfasf .
Perspective(Stained, Short, 
  Typed (Boolean) feature(black) below
  Typed (Boolean) feature(white) below
  Typed (Short) feature(flip) below
)
#if Implementation 
#import "layout.h"
Typed(Short)   feature(Stained::flip) is(matter + (1 << 15))
Typed(Boolean) feature(Stained::black) is (matter < $X_f$ || matter > $X_t$ + 1)
Typed(Boolean) feature(Stained::white) is (not black()) 
#endif
