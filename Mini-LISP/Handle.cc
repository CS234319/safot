#include "Handle.h"
#include "layout.h"
Constructor(Handle::Handle(Short s)):  capsule(s) {}
Property(Short Handle::handle) Is(capsule);
Property(Boolean Handle::ok)  Is(handle() >= $X_f$ && handle() <= $X_t$)
Property(Word& Handle::p)  Is(P[handle()]);
