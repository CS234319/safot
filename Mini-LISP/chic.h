// Poor man's edition of a bit cleaner C/C++
//
#include <cstdint>         // Standard header providing integer types with widths 
#define Context namespace
#define Provides extern
#define Let constexpr 
#define Allocate 

#define function   
#define property inline  
#define procedure void  
#define array(type) type *const


#define variable(type) type & 
#define constant(type) const type 
#define action void
#define modifier 
#define data 


#define perspective(...) struct{__VA_ARGS__;};
#define Representation union
#define Type union


#define	returns(x) const {return x;}
#define by(...) :__VA_ARGS__{}

template<typename T> constexpr T max(T h1, T h2) { return h1 > h2 ? h1 : h2; } 
template<typename T> constexpr T min(T h1, T h2) { return h1 < h2 ? h1 : h2; } 
template<typename T> constexpr T range(T h1, T h2) { return h2 - h1 + 1; } 
