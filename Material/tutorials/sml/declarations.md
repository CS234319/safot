# Standard ML

## declarations

---

### example - circle area

$$area = \pi \cdot r^2$$

```sml
val pi = 3.14159;

fun area r = pi * r * r;

area 2.0;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

### identifiers in ML

* `val` declaration binds a name to a value
* a name can not be used to change its value (actually a constant)
* a name can be reused for another purpose

```sml
val pi = "pi";
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

if a name is declared again the new meaning is adopted afterwards

```sml
pi;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

but does not affect existing uses of the name

```sml
area 1.0;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

### is it a good feature?

<div style="text-align: left">
👍 redefining cannot damage your program

👎 redefining may have no visible effect

⚠️ when modifying a program, be sure to recompile the entire file
</div>

---

### `val` and `val rec`

we can define a function using val

```sml
val sq = fn x => x * x;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

what about recursive functions?

```sml
fun f(n) = if n=0 then 1 else n * f(n-1);

val f = fn (n) => if n=0 then 1 else n * ??;
```

```sml
val rec f = fn (n) =>
    if n=0 then 1
    else n * f(n-1);
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

---

### pattern matching

patterns can be used to simplify function definitions

```sml
fun factorial 0 = 1
  | factorial n = n * factorial(n-1);
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

when the function is called, the first pattern to match the argument determines which expression on the right hand side will be evaluated

<!--vert-->

* patterns can consist of
  * constants - int, real, string, ...
  * constructs - tuples, datatype constructors
  * variables - all the rest
  * underscore - a wildcard
* matching is recursive
* any variable in the pattern is bound to the corresponding value in X
* there is no binding where the wildcard is used

<!--vert-->

what will be printed?

```sml
fun foo (x,1) = x
  | foo (1,_) = 0
  | foo _ = ~1;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

```sml
foo(3,1);
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

```sml
foo(1,3);
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

```sml
foo(2,2);
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

```sml
foo(1,1);
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

### patterns using `case`

```sml
case E of P1 => E1 | ... | Pn => En
```

```sml
case 7 of
    0 => "zero"
  | 1 => "one"
  | 2 => "two"
  | n => if n<10 then "lots" else "lots &lots";
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

* if `P1` is the first to match then the result is `E1`
* equivalent to an expression that defines a function by cases and applies it to `E`
* no symbol terminates the case expression
  * enclose in parentheses to eliminate ambiguity

---

### type aliasing

* you can give a new name to an existing type
* the new name is only an alias

```sml
type vec = real*real;

infix ++;
fun (x1,y1) ++ (x2,y2) : vec = (x1+x2,y1+y2);

(3.6,0.9) ++ (0.1,0.2) ++ (20.0,30.0);
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

---

### declarations inside an expression

```sml
let D in E end
```

```sml
fun gcd (n, m) = if m=0 then n else gcd(n mod m, m);

fun fraction (n,d) =
  (n div gcd(n,d), d div gcd(n,d));

fun fraction(n,d)=
  let 
    val com = gcd(n,d)
  in
    (n div com, d div com)
  end;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

`D` may be a compound declaration

```sml
let
  val x = 5
  val y = 17
in
  x * y
end;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

`let` can be simulated using anonymous functions

```sml
fun fraction (n,d) = (fn c => (n div c, d div c))(gcd(n,d));
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

### nested scopes

```sml
fun sqroot a =
  let  
    val acc=1.0e~10
    fun findroot x =
      let 
        val nextx = (a/x + x)/2.0
      in 
        if abs (x - nextx) < acc*x
        then nextx
        else findroot nextx
      end
  in 
    findroot 1.0 
  end;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

### `local`

```sml
local D1 in D2 end
```

```sml
local
  fun itfib (n, prev, curr): int =
    if n = 1 then curr
    else itfib (n-1, curr, prev + curr)
in
  fun fib n = itfib(n, 0, 1)
end;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

(`D1` is visible only within `D2`)

<!--vert-->

### comparing `let` and `local` (1)

```sml
fun fib n = let
  fun itfib (n, prev, curr): int =
    if n = 1 then curr
    else itfib (n-1, curr, prev + curr)
in
  itfib(n, 0, 1)
end;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

```sml
local
  fun itfib (n, prev, curr): int =
    if n = 1 then curr
    else itfib (n-1, curr, prev + curr)
in
  fun fib n = itfib(n, 0, 1)
end;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

### comparing `let` and `local` (2)

```sml
fun pow4 n: int = let
  val n2 = n * n
in
  n2 * n2
end;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

### comparing `let` and `local` (3)

```sml
local
  val x = pow4 5;
in
  val y = x + 2;
  val z = x * x;
end;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

---

### simultaneous declarations (collateral)

```sml
val ID1 = E1 and ... and IDn = En
```

* evaluates `E1`, ..., `En`
* and only then declares the identifiers `ID1`, ..., `IDn`

```sml
val x = 3;
val y = 5;
val x = y and y = x;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

### mutually recursive functions

$$\frac{\pi}{4}=\sum_{k=0}^\infty \frac{1}{4k+1} - \frac{1}{4k+3} = 1 - \frac{1}{3} + \frac{1}{5} - \frac{1}{7} + \frac{1}{9} - \cdots$$

```sml
fun pos d = neg (d-2.0) + 1.0/d
and neg d = if d > 0.0 then pos(d-2.0) - 1.0/d
                       else 0.0;

fun sum (d, one) =
    if d > 0.0
    then sum(d-2.0,~one) + one/d
    else 0.0;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->
