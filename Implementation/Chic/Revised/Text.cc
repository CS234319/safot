#import "chic.h"

Type Text { 
  Representation (Letter * const capsule) 
  Initialize (Text) from (Letter *letters) by (capsule(letters))
  Feature (empty) is (*capsule == '\0')
  Feature (more)  is (not empty())
  Feature (first) is (*capsule) 
  Feature (rest)  is (Text(1 + capsule)) 
  Typed (Short) feature (size)  below
  Typed (Boolean) query (contains) with (Letter l) below
  Typed (Boolean) query (eq) with (Text t) below
};

#if Implementation 
Typed (Short) feature (Text::size)  is (empty() ? 0 : 1 + rest().size())
Typed (Boolean) query (Text::contains) with (Letter l) is (
    more() and (l == first() || rest().contains(l))
) 
Typed (Boolean) query (Text::eq) with (Text t) is (
    empty() and t.empty()
  or
    more() == t.more() and first() == t.first() and rest().eq(t.rest())
)
#endif
