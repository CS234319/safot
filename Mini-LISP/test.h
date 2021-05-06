#include "io.h"
inline auto operator == (const S s1,const S s2) { return s1.index == s2.index; }
inline auto operator != (const S s1,const S s2) { return s1.index != s2.index; }
inline auto operator !(const S s) { return s.null(); }
