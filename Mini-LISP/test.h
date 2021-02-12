inline auto operator == (const S s1,const S s2) { return s1.index == s2.index; }
inline auto operator != (const S s1,const S s2) { return s1.index != s2.index; }
inline auto operator !(const S s) { return s.null(); }
static void error(String s) {  std::cerr << s;  throw __LINE__; }
static void error(String s, S s1) {  std::cerr << s << s1;  throw __LINE__; }
