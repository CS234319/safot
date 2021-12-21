# rehearsal lecture

## 21/12/2021

---

### criteria for evaluation of a type system

these are the criteria we use to evaluate a type system of a new language we encounter:
1. existence
2. sophistication
3. orthogonality
4. strength
5. time of enforcement
6. responsibility for typing
7. equivalence
8. flexibility

<!--vert-->

### existence

does the language include a type system at all? or are all objects of one "degenerate" type?

take LISP - its only type is S-Expression

what about Assembly? what about C?

NOTE: compare nonexistence of a type system to existence of a dynamic type system. dynamic typed languages do have types, they're just checked at runtime and not at compile time. untyped languages are such that each value has its own particular semantics. 

<!--vert-->

### sophistication

type systems differ in their sophistication level - how complex a type can we construct?

1. no typing - as we saw
2. degenerate typing - only a few predefined types
3. non-recursive type systems - basic types can be defined by the programmer, but they cannot be recursive

<!--vert-->

4. recursive type systems - basic types can be defined by the programmer, including using recursion
5. functions are **first-class values** - like in ML, we'll see
6. highly advanced type constructors - desirable features like generics, user-defined overloading, inheritance, etc.

<!--vert-->

definition: we say a certain type of a programming language comprises **first-class values** if its values can be passed to functions, stored in variables, returned from functions, etc. otherwise, we say the type has **second-class values**.

in Pascal, functions are not first-class values.

<!--vert-->

### orthogonality

but... let's say we only care about first-class values. can we use all first-class values with all type constructors?

remember: it's okay to discriminate against second-class values

definition: if a language allows every type with first-class values to be used with every type constructor, we say the language has an **orthogonal** typing system

<!--vert-->

non-orthogonal type systems are very weird and unusual.

the prototypical example is Pascal - it has a non-orthogonal type system.

Pascal has a power-set type constructors, that receives a type and returns the type that contains all sets of values from the original type.

<!--vert-->

indeed, `set of Boolean` and `set of Char` is defined in Pascal, but `set of Integer` is not. in fact, the power set operator only works for types with up to 256 values.

this makes Pascal's type system a non-orthogonal type system.

ML's type system is orthogonal.

<!--vert-->

### strength

how easy is it to break the association between the stream of bits that is a value, and the type of that value?

in C it is very easy:
```C
int x = 5;
printf("%lf", *(double*)&x);
// prints -152731274597227(...227 chars removed...)0962009858048.000000
```

try doing it in ML!

<!--vert-->

definition: we say a language has **strong typing** if its type system makes it impossible to break the association of a value with its type or subject a value to an operation which is not acceptable for its type.

definition: we say a language has **weak typing** if it's relatively easy for a programmer to break or ignore the association between a value and its type.

<!--vert-->

strongly typed languages: SML, Java, Kotlin, Python, and more

weakly typed languages: C, C++, Pascal (why?), and more

NOTE: why - because of variant records

<!--vert-->

### time of enforcement

if we do an operation that may cause a type error, when will we actually get the type error?

in C, attempting to perform an illegal operation that should throw a type error will cause a compilation error.

in Python, performing an illegal operation will cause a runtime error only when the offending code is being executed.

<!--vert-->

definition: we say a language has **static typing** if it enforces the type of values at compile time.

definition: we say a language has **dynamic typing** if it enforces the type of values at runtime.

<!--vert-->

statically typed languages: C, C++, Java, ML, and more

dynamically typed languages: Python, JavaScript, and more

all interpreted languages (that do not undergo compilation) are obviously dynamically typed as there's no "compile time".

<!--vert-->

A statically and strongly typed language: Java

A statically and weakly typed language: C

A dynamically and strongly typed language: Python

A dynamically and weakly typed language: JavaScript

<!--vert-->

### responsibility

who is responsible for denoting the types of values?

in classic Java or C, the programmer is responsible for denoting the types of values:
```Java
final String s = "hello";
```

<!--vert-->

however, in SML, types can and almost always are inferred by the compiler:
```SML
val s = "hello";
```

<!--vert-->

definition: if in a PL, the programmer is responsible for denoting the types of values, we say the language has **explicit typing**, or **manifest typing**.

definition: if in a PL, the compiler can infer types of values from context, we say the language has **implicit typing**, or **inferred typing**.

<!--vert-->

languages with explicit typing: (classic) Java, (classic) C++, C, and more

languages with implicit typing: SML, Python, Kotlin, and more

<!--vert-->

### equivalence

when are two types equivalent? as in, they can be treated as the same type for all intents and purposes?

for example, if two Java classes `A` and `B` have the same methods and fields, is `A a = new B();` valid?

<!--vert-->

definition: if in a language, two types can be considered equivalent if they have the same legal operations (same "structure"), we say the language has **structural equivalence**.

definition: if in a language, two types are equivalent only if they are defined in the same location (i.e. they are the same type), we say the language has **nominal equivalence**.

<!--vert-->

languages with structural equivalence: Python, JavaScript, and more.

languages with nominal equivalence: Java, Pascal, and more.

<!--vert-->

### flexibility

- not yet discussed - in a few words, it's the ability of the programmer to use advanced constructs like polymorphism and coercion.
- you'll see it later

<!--vert-->

### evaluation methods

we'll now discuss another topic in PLs: evaluation methods.

consider the following expression: `f(a(), b(), c(), d())`

when will the functions `a`, `b`, `c`, `d` be called? in what order? how many times?

<!--vert-->

definition: we say a language uses **eager evaluation** if when evaluating a function call, all of its arguments are evaluated in some order before the function is called. the arguments will always be evaluated exactly once and the results will be cached.

definition: we say a language uses **lazy evaluation** if a function call's arguments are only evaluated whenever they are needed, and then the result is cached.

<!--vert-->

consider the following definitions in Java:
```Java
public static int a() { System.out.println("a"); return 1; }
public static int b() { System.out.println("b"); return 2; }
public static int f(int a, int b) {
    if (b == 1) return b;
    return a;
}
```

consider an evaluation of `f(a(), b());`

what will be printed in regular Java? what about a version of Java using lazy typing?

NOTE: regular Java - depends on evaluation order. if we assume left to right, then "a\nb\n" will be printed. lazy Java - "b\na\n".

<!--vert-->

have we already seen lazy evaluation?

yes! we saw it in SML sequences

in SML sequences, the values are not calculated until they are needed.

<!--vert-->

one last piece of the puzzle - normal evaluation

definition: we say a language uses **normal evaluation** if when evaluating a function call, the formal parameters in the function definition are replaced by the arguments of the function. this is similar to lazy evaluation, but parameters can be evaluated more than once.

<!--vert-->

```Java
public static int a() { System.out.println("a"); return 1; }
public static int b() { System.out.println("b"); return 2; }
public static int f(int a, int b) {
    if (b == a) 
        return b;
    return a;
}
```

what will `f(a(), b());` print under a normal evaluation order?

NOTE: assuming == evaluates its left argument first, "b\na\nb\n" will be printed.

<!--vert-->

# SML exam questions

<!--vert-->

### question 1 - Spring 2014-2015 Moed A

consider the following declarations given in ML. what will ML respond to these declarations? if there are any warnings or errors, specify them

<!--vert-->

```SML
fun f a b = f b a
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

NOTE: val f = fn : 'a -> 'a -> 'b

<!--vert-->

```SML
fun f x (0, y) = x
   | f 0 (y, x) = x(y)
   | f x (z, y) = x * y(z);
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

NOTE: val f = fn : int -> int * (int -> int) -> int

<!--vert-->

```SML
exception E1 of int;
fun f a b c = (a b (raise E1(5))) handle E1(x) => x + c;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

NOTE: val f = fn : ('a -> 'b -> int) -> 'a -> int -> int

<!--vert-->

### question 2 - Summer 2019 Moed B

for each of the following parts, fill in the blanks such that the following expression in ML evaluated to 42.

<!--vert-->

```SML
let val foo : ____ = ____ in foo 21 end;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

NOTE: `let val foo : int->int = fn x => 2 * x in foo 21 end;`

<!--vert-->

```SML
let val foo : ____ = ____ in foo (ref 42) end;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

NOTE: `let val foo : (int ref->int) = fn x => !x in foo (ref 42) end;`

<!--vert-->

```SML
let 
    val foo : ____ = ____
    val a = ref (6 * 9)
    val b = ref a
in 
    (foo b ; !a)
end;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

NOTE: `val foo : int ref ref -> unit = fn x => !x := 42`


<!--vert-->

```SML
let 
    val foo : ____ = ____
    val a = ref [ref 6, ref 9]
    val b = ref a
in 
    (foo b ; !(hd(!a)) * !(hd(tl(!a))))
end;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

NOTE: `val foo : int ref list ref ref -> unit = fn x => !x := [ref 6, ref 7]`

<!--vert-->

```SML
let 
    val foo : ____ = ____
in 
    foo ! 42
end;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

NOTE: `val foo : ('a ref -> 'a) -> int -> int = fn x => fn y => y`

