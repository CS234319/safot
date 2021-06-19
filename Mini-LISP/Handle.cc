#include "Handle.h"

Handle::Handle(Short s): capsule(s) {}
Short Handle::inner() const { return capsule; }
