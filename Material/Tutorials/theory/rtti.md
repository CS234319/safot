# RTTI

---



### motivation

we would like to implement a garbage collection algorithm, i.e., mark & sweep or stop & copy.

either way, we need a way to find all "reachable" variables from a certain pile of bits. how do we traverse a network of
data connected to other data? 

<!--vert-->
for example, a class instance may have fields in it, which may themselves have fields in them.
the same 16 bytes may be interpreted in countless different ways, and when we reach a value, we do not know what's in it!

<!--vert-->
here is an example. we consider the following C `struct`s: 
```C
struct S1 {
    int a;
    int b;
    int c;
}
```
```C
struct S2 {
    long a;
    int b;
}
```
assuming a 4 byte `int` and 8 byte `long`, any 96 bit long sequence can fit either struct!
<!--vert-->
when we encounter a 96 bit sequence, how can we know whether it should be interpreted as `S1`, as `S2` or in any other way?
now, imagine a longer struct that has fields that are themselves structs. the interpretation problem becomes very hard.

we conclude that if we want to keep track of types *in runtime*, we must save type information for our data.
<!--vert-->
the problem of traversal on networks of objects is not specific to garbage collection algorithms, and recurs in various other places like deep cloning and serialization.

it is especially pronounced in languages with dynamic typing - types must be checked in runtime, and therefore, we must save type information so it is available in runtime.
<!--vert-->
statically-typed languages can check for *type errors* in compile time and from there assume all field accesses are valid.

however, in dynamically-typed languages, saving type information is indeed necessary for any type of type checking to function correctly.

actually, we find that, in some cases, it can be beneficial in statically-typed languages as well.

---

### the solution
<!--vert-->
**RTTI**: runtime type information
- additional data attached to each cell in memory
- specifies the type of the data to which it is attached
- is useful in both statically- and dynamically-typed languages
<!--vert-->
in both statically- and dynamically-typed languages which have it, RTTI is used for serialization, deep-cloning and garbage collection
these are purposes that require traversal of a type structure that has to be known in runtime.

in dynamically-typed languages, the RTTI is also used for type checking, which is done in runtime.

<!--vert-->
C & C++ have a "no hidden costs" policy - when a programmer allocates memory, it should be guaranteed that no extra memory is used.
therefore, these languages *do not* have RTTI (except for a very limited form in C++ for the implementation of `virtual`).
 
this is why these languages **do not, and can not**, have general purpose GC, serialization, cloning or any "deep" operations.
 
<!--vert-->
let's consider the following snippet regarding a variable `today` which has fields `day`, `month`, `year`:
```javascript
today.day = 35;
```
this snippet is valid Java as well as valid JavaScript. however, when ran, both languages work differently to interpret it.
<!--vert-->
in Java, we first dereference `today`, ignoring RTTI (it is not used for field access in Java), advance by `off(day)` and update the field.
the offset `off(day)` is known in compile-time, because Java is statically-typed.

in JavaScript, we also dereference `today`, but we must examine the RTTI to determine `off(day)` to then advance by it and update the field.
this is because JavaScript is dynamically-typed.

<!--vert-->
JavaScript's dynamic typing causes it to not know the required offsets in compile time. 

this example demonstrates the difference between statically- and dynamically-typed languages in their use of RTTI.

