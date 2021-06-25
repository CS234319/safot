#include "Handle.h"
#include "layout.h"
Constructor(Handle::Handle(Short s)):  capsule(s) {}
Property(Short Handle::handle) Is(capsule);
Property(Boolean Handle::ok)  Is(handle() >= $X_f$ && handle() <= $X_t$)
Property(Word& Handle::p)  Is(P[handle()]);

#include "Test.h" 

TEST(Handle, Construct) {
  const Handle h = Handle(17);
}

TEST(Handle, Inspect) {
  const Handle h = Handle(19);
  EXPECT_EQ(h.handle(), 19);
}

TEST(Handle, ok) {
  const Handle h = Handle(23);
  EXPECT_TT(h.ok());
}
 
