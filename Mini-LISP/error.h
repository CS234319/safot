#define FIND_NAME(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9, NAME,...) NAME
#define ITERATE(...) \
  FIND_NAME(_0,__VA_ARGS__,FE_9, FE_8,FE_7,FE_6, FE_5,FE_4,FE_3,FE_2,FE_1,FE_0)\
  (__EXPRESSION,__VA_ARGS__)

#define dITERATE(...) ITERATE(DUMMY,## __VA_ARGS__) 

#define E(...)        BEFORE                                      dITERATE(__VA_ARGS__) AFTER
#define E(X,...)     BEFORE __VALUE(X)                            dITERATE(__VA_ARGS__) AFTER
#define E1(X,...)     BEFORE __VALUE(X)                           dITERATE(__VA_ARGS__) AFTER
#define E2(X,Y,...)   BEFORE __VALUE(X) __VALUE(Y)                dITERATE(__VA_ARGS__) AFTER
#define E2(X,Y,...)   BEFORE __VALUE(X) __VALUE(Y)                dITERATE(__VA_ARGS__) AFTER
#define E3(X,Y,Z,...)   BEFORE __VALUE(X) __VALUE(Y) __VALUE(Z)     dITERATE(__VA_ARGS__) AFTER
#define E4(X,Y,Z,W,...) BEFORE __VALUE(X) __VALUE(Y) __VALUE(Z) __VALUE(W)    dITERATE(__VA_ARGS__) AFTER


static struct Error {
  char E0[0];
  char CAR_OF_ATOM,
  CAR_OF_NIL,
  CDR_OF_ATOM,
  CDR_OF_NIL,
  UNBOUND_VARIABLE,
  MISSING_VALUE,
  OTHER_ERROR,
  char E1[0];
};

inline S error(Error e) {  
  return os << o.str();
}

inline S error(String s, S s1) {  
  std::cerr << s << " " << s1.asAtom();  
  throw __LINE__; 
}


enum {
  CAR_OF_ATOM,
  CAR_OF_NIL,
  CAR_OF_ATOM,
  CAR_OF_NIL,
};
