#ifndef __EXPRESSION_H_
#define __EXPRESSION_H_
#include <iostream>
/* Quick hacks for dumping; DALUT SOREFET; we do a lot of dumps for debugging,
 * no debugger in this project */

extern bool dumping;

#define FE_1(W,_1)                          
#define FE_2(W,_1,_2)                      W(_2)
#define FE_3(W,_1,_2,_3)                   W(_2)W(_3)
#define FE_4(W,_1,_2,_3,_4)                W(_2)W(_3)W(_4)
#define FE_5(W,_1,_2,_3,_4,_5)             W(_2)W(_3)W(_4)W(_5)
#define FE_6(W,_1,_2,_3,_4,_5,_6)          W(_2)W(_3)W(_4)W(_5)W(_6)
#define FE_7(W,_1,_2,_3,_4,_5,_6,_7)       W(_2)W(_3)W(_4)W(_5)W(_6)W(_7)
#define FE_8(W,_1,_2,_3,_4,_5,_6,_7,_8)    W(_2)W(_3)W(_4)W(_5)W(_6)W(_7)W(_8)
#define FE_9(W,_1,_2,_3,_4,_5,_6,_7,_8,_9) W(_2)W(_3)W(_4)W(_5)W(_6)W(_7)W(_8)W(_9)

#define GET_MACRO(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9, NAME,...) NAME
#define ITERATE(...) \
  GET_MACRO(_0,__VA_ARGS__,FE_9, FE_8,FE_7,FE_6, FE_5,FE_4,FE_3,FE_2,FE_1,FE_0)\
  (__EXPRESSION,__VA_ARGS__)

#define dITERATE(...) ITERATE(DUMMY,## __VA_ARGS__) 

#define D(...)        BEFORE                                      dITERATE(__VA_ARGS__) AFTER
#define M(X,...)      BEFORE __VALUE(X)                           dITERATE(__VA_ARGS__) AFTER
#define M2(X,Y,...)   BEFORE __VALUE(X) __VALUE(Y)                dITERATE(__VA_ARGS__) AFTER
#define M1(X,...)     BEFORE __VALUE(X)                           dITERATE(__VA_ARGS__) AFTER
#define M2(X,Y,...)   BEFORE __VALUE(X) __VALUE(Y)                dITERATE(__VA_ARGS__) AFTER
#define M3(X,Y,Z,...) BEFORE __VALUE(X) __VALUE(Y) __VALUE(Z)     dITERATE(__VA_ARGS__) AFTER
#define M4(X,Y,Z,W,...) BEFORE __VALUE(X) __VALUE(Y) __VALUE(Z) __VALUE(W)    dITERATE(__VA_ARGS__) AFTER
#define M5(X,Y,Z,W,U, ...) BEFORE __VALUE(X) __VALUE(Y) __VALUE(Z) __VALUE(W) __VALUE(U)    dITERATE(__VA_ARGS__) AFTER
#define M6(X,Y,Z,W,U,A,...) BEFORE __VALUE(X) __VALUE(Y) __VALUE(Z) __VALUE(W) __VALUE(U) __VALUE(A) dITERATE(__VA_ARGS__) AFTER
#define M7(X,Y,Z,W,U,A,B,...) BEFORE __VALUE(X) __VALUE(Y) __VALUE(Z) __VALUE(W) __VALUE(U)    __VALUE(A) __VALUE(B)   dITERATE(__VA_ARGS__) AFTER

#define __(X,...)     (std::cerr << std::endl), M(X, __VA_ARGS__) 
#define LOCATE  std::cerr\
  <<__FILE__\
  <<"("<<__LINE__<<")/" \
  <<__FUNCTION__ << "(): "

#define __EXPRESSION(X) <<#X<<"="<<X<<"; "
#define __VALUE(X) <<X<<" "
#define __SEP <<"; "


#define BEFORE  (dumping?0: (     \
                  dumping = true, \
                  (LOCATE
#define AFTER     <<std::endl       \
                  ),                 \
                  dumping = false)  \
                )

#endif /* __EXPRESSION_H_ */
