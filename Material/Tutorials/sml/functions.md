# Standard ML

## functions

---

### side note - operators

a function of two arguments can be treated as an infix operator

```sml
fun d (x,y) = Math.sqrt (x*x + y*y);
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

convert to an infix operator

```sml
infix d;

3.0 d 4.0;

1.0 d 3.0 d 2.0 d 5.0;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

the infix declaration can come __before__ the function definition

```sml
infix d;
fun (x d y) = Math.sqrt(x*x + y*y);

d;
(*stdIn:40.1 Error: expression or pattern begins with infix identifier "d"*)

op d;
(*val it = fn : real * real -> real*)

op d(1.0,3.0);
(*val it = 3.16227766017 : real*)
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

---

### curried functions

any function of two arguments `$(\alpha * \beta)\rightarrow \gamma$` can be expressed as a **curried** function of one argument `$\alpha\rightarrow (\beta \rightarrow \gamma)$`

```sml
fun prefix (pre, post) = pre ^ post;
(*val prefix = fn : string * string -> string*)
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

the curried version

```sml
fun prefix pre = fn post => pre^post;
(*val prefix = fn : string -> string -> string*)
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

reminder: `->` is right associative

```sml
val prefix = fn : string -> string -> string
(*is equivalent to*)
val prefix = fn : string -> (string -> string)
```

---

### partial application

you don't have to give the next arguments!

```sml
prefix "Dr. ";
(*val it = fn : string -> string*)

it "Tomer";
(*val it = "Dr. Tomer" : string*)
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

as always, functions are values

```sml
val doctorify = prefix "Dr. ";
(*val doctorify = fn : string -> string*)

doctorify "Jackal";
(*val it = "Dr. Jackal" : string*)
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

---

### currying = syntactic sugar

```sml
fun prefix pre post = pre ^ post;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

is equivalent to

```sml
fun prefix pre = fn post => pre ^ post;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

---

### function calls

```sml
(prefix "Dr. ") "Tomer";
(*val it = "Dr. Tomer" : string*)

prefix "Dr. " "Tomer";
(*val it = "Dr. Tomer" : string*)
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

the rule is:
* a function call `F E1 E2 ... En`
* abbreviates `(...((F E1) E2)...) En`

---

### example

applying infix operator only to one operand

```sml
fun add5 y = op+ (5, y);
(*val add5 = fn: int -> int*)

add5 2;
(*val it = 7 : int*)

fun mul5 y = op* (5, y);
(*val mul5 = fn: int -> int*)
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

now generalize the operator and operand

```sml
fun something5 (f:int*int->int) y = f (5, y);
(*val something5 = fn: (int*int->int) -> int -> int*)

val add5 = something5 op+;
(*val add5 = fn: int -> int*)

fun intsec x (f:int*int->int) y = f(x,y);
(*val intsec = fn : int -> (int * int -> int) -> int -> int*)
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

---

### recursive curried functions

```sml
fun times n m =
    if m=0 then 0
    else n + times n (m-1);
(*val times = fn : int -> int -> int*)

times 4 5;
(*val it = 20 : int*)

val times_4 = times 4;
(*val times_4 = fn : int -> int*)

times_4 8;
(*val it = 32 : int*)
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

---

### composition operator

```sml
infix o;
fun (f o g) x = f (g x);
(*val o = fn : ('a -> 'b) * ('c -> 'a) -> 'c -> 'b*)

Math.sqrt o Math.sqrt;
(*val it = fn : real -> real*)

it (16.0);
(*val it = 2.0 : real*)

(fn x => x - ord #"0") o ord;
(*val it = fn : char -> int*)

it #"1";
(*val it = 1 : int*)
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

---

### exam questions

<!--vert-->

what will be printed?

```sml
fun f1 a b = f1 a b;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

what will be printed?

```sml
fun f2 g x = g (f2 g) x;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

what will be printed?

```sml
fun f3 x y z = (x, x(y), y(z));
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

what will be printed?

```sml
fun f4 f = f f4;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->
