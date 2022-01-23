# rehearsal lecture

## 23/01/2022

---

### criteria for evaluation of a type system

these are the criteria we use to evaluate a type system of a new language we encounter:
1. existence and sophistication
2. orthogonality
3. strength

<!--vert-->

4. time of enforcement
5. responsibility for typing
6. equivalence
7. flexibility

<!--vert-->

### existence

does the language include a type system at all? or are all objects of one "degenerate" type?

take LISP - its only type is S-Expression

what about Assembly? what about C?

NOTE: compare nonexistence of a type system to existence of a dynamic type system. dynamic typed languages do have types, they're just checked at runtime and not at compile time. untyped languages are such that each value has its own particular semantics. 

<!--vert-->

### sophistication

type systems differ in their sophistication level - how complex a type can we construct?

1. degenerate typing/no typing - only a few predefined types, or none at all
2. non-recursive type systems - basic types can be defined by the programmer, but they cannot be recursive

<!--vert-->

3. recursive type systems - basic types can be defined by the programmer, including using recursion
4. functions are **first-class values** - like in ML, we'll see
5. highly advanced type constructors - a relative term used to describe languages that have desirable features like generics, user-defined overloading, inheritance, etc.

<!--vert-->

definition: we say a certain type of a programming language comprises **first-class values** if its values can be passed to functions, stored in variables, returned from functions, etc. otherwise, we say the type has **second-class values**.

<!--vert-->

typically, examples of types with first-class values are `int`, `float`, `bool`, etc.

in Pascal, functions are not first-class values, because for example you can't return them from functions.

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

indeed, `set of Boolean` and `set of Char` are defined in Pascal, but `set of Integer` is not. in fact, the power set operator only works for types with up to 256 values.

this makes Pascal's type system a non-orthogonal type system.

ML's type system is orthogonal.

<!--vert-->

### strength

how easy is it to break the association between the stream of bits that is a value, and the type of that value?

<!--vert-->

in C it is very easy:
```C
int x = 5;
printf("%lf", *(double*)&x);
// prints -152731274597227(...227 chars removed...)0962009858048.000000
```

try doing it in ML!

this is called *type punning*.

<!--vert-->

definition: we say a language has **strong typing** if its type system makes it impossible to break the association of a value with its type or subject a value to an operation which is not acceptable for its type.

<!--vert-->

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

<!--vert-->

definition: if in a language, two types are equivalent only if they are defined in the same location (i.e. they are the same type), we say the language has **nominal equivalence**.

<!--vert-->

languages with structural equivalence: Python, JavaScript, and more.

languages with nominal equivalence: Java, Pascal, and more.

<!--vert-->

### flexibility

languages vary in how flexible their type systems are. this is reflected in programmers' ability to use two main constructs:

- universal polymorphism - not discussed today, things like generics.
- ad-hoc polymorphism - overloading and coercion

<!--vert-->

### coercion

notice how, in every C function that receives a `double` parameter, we can also pass an `int`.
so, every C function of ints is *polymorphic* - it has many types.

for example, consider the following C function: ```double f(int x) { return x; }```. `f(5);` is a valid call and returns `5.0`.

<!--vert-->

definition: **coercion** is a conversion between values of one type to another which occurs implicitly - automatically.

most languages have built-in coercions, but not all.
most languages do not have user-defined coercion (programmers cannot define more coercions for their own types).

<!--vert-->

- ML does not have coercion at all.

- C and Java have pre-defined coercions.

- C++ has user-defined coercions.

<!--vert-->

sometimes coercions can be chained, for example, here is a coercion chain in C++:

```C++
unsigned char → char → int → long → double → long double`
```

<!--vert-->

### overloading

coercion refers to automatic generation of new types for functions. *overloading* refers to manual generation of new types for functions.

<!--vert-->

for example, consider the following Java functions:
```Java
public static void println(double x) { System.out.println(x); }
public static void println(String x) { System.out.println(x); }
```

on what types of values can these functions be called?
of course, `double` and `String`, but also `int`, `long`, and `float` (because of coercion).

<!--vert-->

the two functions `println: String->void`, `println: double->void` are two different functions, but they have the same name.
we could have given them different meanings, too.

<!--vert-->

most languages have both built-in and user-defined overloading, for example Java and C++.
some languages have only built-in overloading, for example, ML. 

overloading in ML is very limited: just `op+ : int*int->int` and `op+ : double*double->double` and the likes.

attempting to define another function in ML with the same name would just override the old function.

<!--vert-->

### overloading vs coercion

- overloading: a small number of distinct functions with the same name. semantic similarity is programmer-defined (programmers are responsible for making the functions do the same thing).
- coercion: many types for the same function caused by implicit conversions between function arguments. semantic similarity is defined outside the function (it's a property of the type).

<!--vert-->

# evaluation methods

<!--vert-->

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

another evaluation method is normal evaluation. 

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

one last piece of the puzzle is **short-circuit evaluation**.

it is *only* applicable to AND and OR operators. 

- for AND, if the first argument is false, the second argument is never evaluated.
- for OR, if the first argument is true, the second argument is never evaluated.

<!--vert-->

it is a form of lazy evaluation.

for example, `true || f(x)` will never call `f(x)`, and same for `false && f(x)`.

however, `f(x) || true` will call `f(x)`, and same for `f(x) && false`.

<!--vert-->

# minilisp

<!--vert-->

s-expression: either an atom, or a pair of s-expressions `(a.b)`

decomposition:

```lisp
(car (a.b)) ; returns a
(cdr (a.b)) ; returns b
```

trying to use `car` or `cdr` on an atom will throw an error

a special atom: `NIL` 

<!--vert-->

- a list in minilisp is an s-expression with a special form

- it is either `NIL`, or `(a.l)`, where `a` is an atom and `l` is a list

- not all s-expressions are lists

- list notation: `(a b c)`

<!--vert-->

in minilisp, the atom `t` represents the boolean value `true`, and the atom `NIL` represents the boolean value `false`

for example, the function `atom` checks if its argument is an atom:

```lisp
(atom NIL) ; returns t
(atom a) ; returns t
(atom (a.b)) ; returns NIL
```

<!--vert-->

the function `eq` checks if its arguments are atoms that are equal:

```lisp
(eq a a) ; returns t
(eq a b) ; returns NIL
(eq (a.b) (a.b)) ; returns NIL
```

<!--vert-->

the function `null` checks if its argument is `NIL`:
```lisp
(null NIL) ; returns t
(null (a.b)) ; returns NIL
(null a) ; returns NIL
```

<!--vert-->

the function `cond` returns the `cdr` of its first argument whose `car` is `t`

```lisp
(cond (nil (a.b)) (t (c.d)) (t (e.f))) ; returns (c.d)
```

<!--vert-->

### list evaluation in minilisp

in minilisp, by default, every list will be interpreted as a function call.

the list `(a b c)` will be interpreted as applying the function `a` on the list `(b c)`

in general, for the list `l`, apply the function `(car l)` on arguments `(cdr l)`

<!--vert-->

for example, the list `(+ 1 2)` in lisp will evaluate to 3

if we don't want this to happen, we put a quote before the list: `'(+ 1 2)`. now it's just a list

<!--vert-->

the function `set` creates a binding between an atom and an S-Expression:

```lisp
(set 'a '(c d)) ; creates a binding between 'a and (c d)
```

<!--vert-->

the function `defun` defines a function with a name, arguments, and body:

```lisp
(defun f x (x.x)) ; creates a function f that receives an argument x and returns (x.x)
```

<!--vert-->

### exercise

define the function `exists `in minilisp that takes an atom and a list and checks if the atom is in the list

example:

```lisp
(exists 'a '(a b c)) ; returns t
(exists 'd '(a b c)) ; returns NIL
```

<!--vert-->

```lisp

```
<!-- .element: data-thebe-executable-sml -->

NOTE: ```(defun exists (x xs) (cond ((eq xs nil) nil) ((eq x (car xs)) t) (t (exists x (cdr xs))))) ```

<!--vert-->
### exercise

define the function `equals_full` that takes two s-expressions and checks if they are equal structurally

example:

```lisp
(equals_full '(a b c) '(a b c)) ; returns t
(equals_full '(a b c) '(a b d)) ; returns NIL
```

<!--vert-->

```lisp

```
<!-- .element: data-thebe-executable-sml -->

NOTE: ```(defun equals_full (x y) (cond ((eq x y) t) ((atom x) NIL) ((atom y) NIL) ((equals_full (car x) (car y)) (equals_full (cdr x) (cdr y))))) ```

<!--vert-->

# SML exam questions

<!--vert-->

### question 1 - Spring 2014-2015 Moed A

consider the following declarations given in ML. what will ML respond to these declarations? if there are any warnings or errors, specify them

<!--vert-->

```SML
fun f a b = f b a;
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

NOTE: exception E1 of int, val f = fn : ('a -> 'b -> int) -> 'a -> int -> int

<!--vert-->

(not in the original exam)

```SML
exception E1 of int;
fun f (E1(x)) = if x = 1 then raise E1(x + 1) else x;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

NOTE: exception E1 of int, val f = fn : exn -> int, match nonexhaustive

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

