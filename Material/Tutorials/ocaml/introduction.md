# OCaml

## introduction

---

### basic usage

* REPL - `utop` or `ocaml`
* prompt (#)
* double-semicolon terminated

```text
    OCaml version 4.12.0
# 5 + 3;;
- : int = 8
```

<!--vert-->

### load from file

* create a file named `myfile.ml`
* start OCaml and

    ```ocaml
    #use "myfile.ml";;
    ```

* or:

    ```bash
    ocaml myfile.ml
    ```

<!--vert-->

### REPL

* OCaml can be used through a REPL
* expressions followed by **two semicolons** yield a response

    ```ocaml
    2 + 2;;
    ```
    <!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

* the response is the computed value and its type

<!--vert-->

OCaml can also be compiled

(more on that in the hw assignments)

---

### declaring constants

<!--vert-->

naming constants

```ocaml
let seconds = 60;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

using names in expressions

```ocaml
let seconds = 60;;
let minutes = 60;;
let hours = 24;;

seconds * minutes * hours;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

---

### legal names

<!--vert-->

### alphabetic names

* begins with a letter
* followed by letters, digits, underscore, or single quotes
* case sensitive

```ocaml
x
x'
uB40
hamlet_prince_of_denmark
h''3_H
```

<!--vert-->

### special names

* permitted over the characters:

    ```ocaml
    ~ ! ? $ & * + - / = > @ ^ | % < : #
    ```

* can't start with:

    ```ocaml
    ~ ! ? : .
    ```

* should not be one of:

    ```ocaml
    !=    #     &     &&    *     +     -     ~
    -.    ->    .     ..    .~    :     ::    |
    <     <-    =     >     ?     :>    :=    ||
    ```

<!--vert-->

* to name something with a symbolic name use parentheses:

    ```ocaml
    let ( +-+-+ ) = 1415;;
    ```
    <!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

* used mainly for defining operators (more on that later...)

    ```ocaml
    let (<->) x y = x * x + y * y;;
    3 <-> 4;;
    ```
    <!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

---

### ocaml keywords

```ocaml
and         as          assert      asr         begin
constraint  do          done        downto      else
exception   external    false       for         fun
functor     if          in          include     inherit
land        lazy        let         lor         lsl
lxor        match       method      mod         module
new         nonrec      object      of          open 
private     rec         sig         struct      then
true        try         type        val         virtual
while       with        class       end         function
initializer lsr         mutable     or          to
when
```

---

### calling functions

say `foo` is a function that takes 2 arguments

```ocaml
let foo x y = x + y;;
foo 1 2;; (*OK*)
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

```ocaml
foo (1 2);; (*compilation error!*)
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

```ocaml
foo (1, 2);; (*compilation error!*)
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

you may need to add parentheses at times

```ocaml
foo (-1) (-2);; (*OK*)
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

```ocaml
foo -1 -2;; (*compilation error! parsed as `((foo - 1) - 2)`*)
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

---

### OCaml atomic types

`int`, `float`, `string`, `char`, `bool`, `unit`

---

### int

* sequence of digits
  * 0
  * 01234
* `-` or `~-` for unary minus sign
  * `-23`
  * `-85601435654638`
* infix operators: `+` `-` `*` `/` `mod`

<!--vert-->

conventional precedence

```ocaml
let m, n, l, j = 39, 41, 82, 85;;
(((m * n) * l) - (m / j)) + j = m * n * l - m / j + j;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

NOTE: parentheses can be dropped without change of meaning

---

### float

* decimal point
  * `2.718281828`
  * `1.` is the same as `1.0`
* e notation
  * `7e-5`
  * `-1.2e12`
  * `-123.4e-2` is the same as `-1.234`
* infix operators: `+.` `-.` `*.` `/.` (all end with a dot) and `**` (exponentiation)
* `-.` or `~-.` for unary minus (`-` is allowed for literals)

<!--vert-->

### float functions

```ocaml
(*converts float to int*)
int_of_float 2.5;;

(*converts int to float*)
float_of_int 5;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

and many more: `sqrt`, `sin`, `cos`, `tan`, `exp`, `log` (all of type `float->float`)

---

### string

<!--vert-->

constants are written in double quotes

```ocaml
"ocaml is the best";;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

special characters `\n`, `\t`, `\"`, `\\`

<!--vert-->

concatenation

```ocaml
"Objective" ^ " " ^ "Caml";;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

comparison

```ocaml
"abc" < "cba";;

"zzz" > "aaa";;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

`String.length` returns the number of characters

```ocaml
String.length "ABC";;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

---

### char

<!--vert-->

chars are enclosed in single quotes

```ocaml
'a';;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

conversion between strings and chars

```ocaml
String.make 1 'c';;

String.get "hello" 0;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

conversion between chars and ASCII

```ocaml
Char.code 'a';;

Char.chr 97;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

---

### bool

the two values are

```ocaml
true;;

false;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

operators: `&&`, `||`, `not`

---

### unit

has only one value

```ocaml
();;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

---

### tuples - cartesian product type

the n-tuple whose components are `x1`, ..., `xn`:

```ocaml
(x1, x2, ..., xn)
```

(the parentheses are optional)

<!--vert-->

the tuple type is written using `*`

```ocaml
(1, 2, 3);;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

the components can be of any type, including tuples

```ocaml
let a = (1.5, 6.8);;

1, 1.5;;

("str", 1, true, ('0',0.1));;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

---

### records

records have fields identified by name

```ocaml
type person = {name: string; age: int};;

let me = {name="Ofir"; age=30};;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

selecting a field using `.`

```ocaml
me.name;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

a record is identified by its fields

```ocaml
let me = {name="Ofir"; age=30};;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

note that `me` is of type `person`, it was inferred from the field names

<!--vert-->

you can destructure records using `let`

```ocaml
let {name=name; age=age} = me;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

---

### lists

a list is a finite homogenous sequence of elements

```ocaml
[3; 5; 9];;
["a"; "list"];;
[];;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

note that elements are separated by a `;` and not by a `,`

```ocaml
[3, 4, 3];;

[1, 2 ; 3, 4];;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

elements may have any type but all elements must have the same type

```ocaml
[(1, "one"); (2, "two")];;

[[3.1;]; []; [1.0; -0.5]];;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

```ocaml
[1; "abc"];; (*Error!*)
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

---

### structural equality

* works as expected for most values
* `=` is used for equality
* `<>` is used for inequality

```ocaml
1 + 2 = 3;;
```

---

### physical equality

* implementation dependent
* `==` is used for equality
* `!=` is used for inequality

```ocaml
1 == 1;;
(*- : bool = true*)
"abc" == "abc";;
(*- : bool = false*)
let s = "abc";;
s == s;;
(*- : bool = true*)
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

---

### functions

```ocaml
let sq (x: int) = x * x;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

* keyword `let` starts the function declaration
* `sq` is the function name
* `x:int` is the formal parameter with type constraint
* `x * x` is the body and it is an **expression**

<!--vert-->

* the result of the function is the result of evaluating the **expression** of the function body with the actual parameter
* `int->int` is the standard mathematical notation for a function type that takes an integer and returns an integer

---

### applying a function

* simple function call

    ```ocaml
    sq 3;;
    ```
    <!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

* when a function is called the parameter is evaluated and then passed to the function

    ```ocaml
    sq (sq 3);;
    ```
    <!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

* note that parentheses are optional

    ```ocaml
    sq (3);;
    ```
    <!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

---

### arguments and results

* every function has one argument and one result
* any type can be passed/returned!!!
* tuples can be used to pass/return several arguments

```ocaml
let a = (3., 4.);;

let lengthvec ((x, y): float * float) = sqrt(x *. x +. y *. y);;

lengthvec a;;

lengthvec (5.0, 12.0);;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

---

### recursive functions

to define a recursive function you need the `rec` keyword

```ocaml
let rec factorial n =
    if n = 0
        then 1
        else n * (factorial (n - 1));;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

without `rec` we'll get an error:

```ocaml
let factorial n =
    if n = 0
        then 1
        else n * (factorial (n - 1));;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

---

### functions as values

* anonymous functions with `fun` notation

    ```ocaml
    fun (x:int) -> x * x;;

    (fun (x:int) -> x * x) 3;;
    ```
    <!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

* the following declarations are identical

    ```ocaml
    let sq (x:int) = x * x;;
    let sq = fun (x:int) -> x * x;;
    ```
    <!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

---

### returning functions

* functions can also be __returned__ from other functions

    ```ocaml
    let inttwice (f: (int->int)) = fun x -> f (f x);;
    ```
    <!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

* `->` is right associative so its type is equivalent to:

    ```ocaml
    val inttwice : (int -> int) -> (int -> int)
    ```

* example

    ```ocaml
    let f = inttwice (fun x -> x*x);;

    f 3;;
    ```
    <!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

---

### type inference

OCaml deduces the types in expressions

```ocaml
let rec facti (n, p) =
    if n = 0 then p else facti (n - 1, n * p);;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

* the constant `0` has type `int`
* therefore `n=0` involve integers so `n` has type `int`
* `n * p` is integer multiplication, so `p` has type `int`
* `facti` returns type `int`

---

### type constraints

constraining parameters

```ocaml
let foo (n: int) = n;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

constraining the return type

```ocaml
let foo n : int = n;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

constraining an expression's type

```ocaml
let foo n = (n : int);;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

#### what will be printed?

```ocaml
let min (x: float) y = if x < y then x else y;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

```ocaml
let min (x: string) y = if x < y then x else y;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

```ocaml
let min x y: float = if x < y then x else y;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

```ocaml
let min x y = if x < y then x else (y: string);;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

```ocaml
let min_abs x y = if x *. x < y *. y then x else y;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

write a function `foo` such that its type is:

```ocaml
val foo: int -> float -> float = <fun>
```

but you can't use type annotations

```ocaml
let foo
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

---

### polymorphic type checking

|                           |        | flexibility | security |
|:-------------------------:|:------:|:-----------:|:--------:|
|        weakly typed       |  lisp  |      ✔      |          |
|       strongly typed      |  Java  |             |     ✔    |
| polymorphic type checking | OCaml  |      ✔      |     ✔    |

and in OCaml most types are deduced automatically 😎

---

### polymorphic function definitions

* an object is polymorphic if it can be regarded as having any kind of type
* if type inference doesn't constrain a type then it's polymorphic
* a polymorphic type contains a type variable (e.g. `'a`)

```ocaml
let pairself x = (x, x);;

pairself 4.0;;

let pair (x,y) = (y,x);;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

---

### functions as values - the polymorphic case

<!--vert-->

```ocaml
let twice f = fun x -> f (f x);;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

```ocaml
let ident x = x;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

```ocaml
let g = twice (fun x -> x * x);;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

```ocaml
g 2;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

---

---

### side note - operators

a function of two arguments can be treated as an infix operator

```ocaml
let (--) x y = sqrt(x *. x +. y *. y);;
(*val ( -- ) : float -> float -> float = <fun>*)

3.0 -- 4.0;;
(*- : float = 5.*)

1.0 -- 3.0 -- 2.0 -- 5.0;;
(*- : float = 6.24499799839839831*)
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

the operator can be used as a regular function

```ocaml
(--);;
(*- : float -> float -> float = <fun>*)

(--) 1. 3.;;
(*- : float = 3.16227766016837952*)
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

precedence and associativity are predefined and determined by the characters used in the operator

![ocaml operators](../imgs/ocaml-operators.png)

---

### currying

any function of two arguments is actually a **curried** function of one argument $$\alpha\rightarrow (\beta \rightarrow \gamma)$$

<!--vert-->

```ocaml
let prefix pre post = pre ^ post;;
(*val prefix : string -> string -> string = <fun>*)
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

is equivalent to:

```ocaml
let prefix pre = fun post -> pre ^ post;;
(*val prefix : string -> string -> string = <fun>*)
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

reminder: `->` is right associative, so

```ocaml
val prefix : string -> string -> string
```

is equivalent to

```ocaml
val prefix : string -> (string -> string)
```

---

### partial application

you don't have to give the next arguments!

```ocaml
let doctorify = prefix "Dr. ";;
(*val doctorify : string -> string = <fun>*)

doctorify "Tomer";;
(*- : string = "Dr. Tomer"*)
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

---

### function calls

* a function call `F E1 E2 ... En`
* abbreviates `(...((F E1) E2)...) En`

```ocaml
(prefix "Dr. ") "Tomer";;
(*- : string = "Dr. Tomer"*)

prefix "Dr. " "Tomer";;
(*- : string = "Dr. Tomer"*)
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

---

### exam questions

#### what will be printed?

<!--vert-->

```ocaml
let rec f1 a b = f1 a b;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

```ocaml
let rec f2 g x = g (f2 g) x;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

```ocaml
let f3 x y z = (x, x y, y z);;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

```ocaml
let rec f4 f = f f4;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

---

### functional vs. imperative

* imperative - using commands to change the state
* functional - stateless. using expressions recursively to calculate the result
* example: Euclid's algorithm for the Greatest Common Divisor (GCD) of two natural numbers: `$$gcd(m,n) = \begin{cases}n,\;m = 0&\\gcd(n\;mod\;m,m), \;m>0\end{cases}$$`

<!--vert-->

### GCD - C vs. OCaml

an imperative C program:

```c
int gcd(int m, int n) {
    while (m != 0) {
        int tmp = m;
        m = n % m;
        n = tmp;
    }
    return n;
}
```

a functional program in OCaml:

```ocaml
let rec gcd m n = if m = 0 then n else gcd (n mod m) m;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

which one is more efficient? 🧐
