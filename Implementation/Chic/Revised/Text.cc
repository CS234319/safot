#import "chic.h"

Perspective(Text, Letter * const,
  Feature (empty) is (*inner != '\0')
  Feature (more)  is (not empty())
  Feature (first) is (*inner) 
  Feature (rest)  is (Text(1 + inner)) 
  Typed (Short)   feature (size)  below
  Typed (Boolean) query (contains) with (Letter l) below
  Typed (Boolean) query (eq) with (Text t) below
  Typed (Letter)  action(into) with(String s) below
 // is (s[0] = first() and (empty() or rest().into(s+1)))
)

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
