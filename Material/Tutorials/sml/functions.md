# Standard ML

## Functions

---

### Side note - operators

A function of two arguments can be treated as an infix operator

```sml
fun d (x,y) = Math.sqrt (x*x + y*y);
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

Convert to an infix operator

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
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

```sml
op d;

op d(1.0,3.0);
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

---

### Curried functions

Curry = Haskell Curry (1900-1982), who invented the "trick"

any function of two arguments `$(\alpha * \beta)\rightarrow \gamma$` can be expressed as a **curried** function of one argument `$\alpha\rightarrow (\beta \rightarrow \gamma)$`

```sml
fun prefix (pre, post) = pre ^ post;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

the curried version

```sml
fun prefix pre = fn post => pre^post;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

Reminder: `->` is right associative

```sml
val prefix = fn : string -> string -> string
(*is equivalent to*)
val prefix = fn : string -> (string -> string)
```

---

### partial application

AKA=partial evaluation

You don't have to provide subsequent arguments

```sml
prefix "Dr. ";

it "Watson";
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

as always, functions are values

```sml
val doctorify = prefix "Dr. ";

doctorify "Jekyll";
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

### Invoking a function

```sml
(prefix "Dr. ") "Watson";

prefix "Dr. " "Watson";
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

the rule is:

* a function invocation `F E1 E2 ... En`
* abbreviates `(...((F E1) E2)...) En`

---

### Example of partial application

applying infix operator only to one operand

```sml
fun add5 y = op+ (5, y);

add5 2;

fun mul5 y = op* (5, y);
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

Now, generalize the operator and operand

```sml
fun something5 (f:int*int->int) y = f (5, y);

val add5 = something5 op+;

fun intsec x (f:int*int->int) y = f(x,y);
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

---

### Recursive curried functions

```sml
fun times n m =
    if m=0 then 0
    else n + times n (m-1);

times 4 5;

val times_4 = times 4;

times_4 8;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

---

### Function composition operator

```sml
infix o;
fun (f o g) x = f (g x);

Math.sqrt o Math.sqrt;

it (16.0);

(fn x => x - ord #"0") o ord;

it #"1";
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

---

### Questions from exams

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
