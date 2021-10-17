#import "Handle.h"
#import "layout.h"
Constructor(Handle::Handle(Short s)):  capsule(s) {}
Property(Short Handle::handle) is(capsule);
Property(Boolean Handle::ok)  is(handle() >= $X_f$ && handle() <= $X_t$)
Property(Word& Handle::cons)  is(P[handle()]);
