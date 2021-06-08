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

#define max(x,y) (x > y ? x : y) 
#define min(x,y) (x < y ? x : y) 
