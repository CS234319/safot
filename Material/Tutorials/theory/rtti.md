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
#### example
consider the following C `struct`s
```C
struct S1 {
    int x;
};
struct S2 {
    int *ptr;
};
```
<!--vert-->

assuming `sizeof(int) == sizeof(int*) && sizeof(int*) == 8`, and given an 8 bit long variable, how can we know if it has to be interpreted as `S1` or as `S2`?
this is a problem because it shows that *we cannot tell apart pointers and data*, making implementing GC impossible. 

conclusion: we must have type information at *runtime*
<!--vert-->
the problem of traversal on networks of objects is not specific to garbage collection algorithms, and recurs in various other places like deep cloning and serialization.

it is especially pronounced in languages with dynamic typing - types must be checked in runtime, and therefore, we must save type information so it is available in runtime.
<!--vert-->
statically-typed languages can check for *type errors* in compile time and from there assume all field accesses are valid.

in dynamically-typed languages RTTI is necessary for type checking

statically-typed languages can benefit from RTTI too

---

### the solution
<!--vert-->
**RTTI**: runtime type information
- additional data attached to each cell in memory
- specifies the type of the data to which it is attached
- is useful in both statically- and dynamically-typed languages
<!--vert-->
RTTI is used for:

* serialization
* deep-cloning
* garbage collection

NOTE: these are purposes that require traversal of a type structure that has to be known in runtime

in dynamically-typed languages, also:
* type checking

<!--vert-->
C & C++ have a "no hidden costs" policy - when a programmer allocates memory, it should be guaranteed that no extra memory is used.
therefore, these languages *do not* have RTTI

NOTE: except for a very limited form in C++ for the implementation of `virtual`, i.e., `vptr` and `vtbl`

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

NOTE: in this case, C would operate similarly to Java, except it has no RTTI to ignore.

<!--vert-->
JavaScript's dynamic typing causes it to not know the required offsets in compile time. 

this example demonstrates the difference between statically- and dynamically-typed languages in their use of RTTI.
