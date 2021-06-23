#include "Handle.h"
#include "layout.h"
Constructor(Handle::Handle(Short s)):  capsule(s) {}
Property(Short Handle::inner) Is(capsule);
Property(Boolean Handle::ok)  Is(capsule >= $X_f$ && capsule <= $X_t$)

#include "Test.h" 

TEST(Handle, Construct) {
  const Handle h = Handle(17);
}

TEST(Handle, Inspect) {
  const Handle h = Handle(19);
  EXPECT_EQ(h.inner(), 19);
}

TEST(Handle, ok) {
  const Handle h = Handle(23);
  EXPECT_TT(h.ok());
}
 
