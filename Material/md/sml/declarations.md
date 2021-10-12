# Standard ML

## declarations

---

### example - circle area

`$$area = \pi \cdot r^2$$`

```sml
val pi = 3.14159;

fun area r = pi * r * r;

area 2.0;
```
<!-- .element: data-thebe-executable-sml -->

---vert---

### identifiers in ML

* `val` declaration binds a name to a value
* a name can not be used to change its value (actually a constant)
* a name can be reused for another purpose

```sml
val pi = "pi";
```
<!-- .element: data-thebe-executable-sml -->

---vert---

if a name is declared again the new meaning is adopted afterwards

```sml
pi;
(*val it = "pi": string*)
```

but does not affect existing uses of the name

```sml
area 1.0;
(*val it = 3.14159: real*)
```

---vert---

### is permanence of names a good feature?

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

what about recursive functions?

```sml
fun f(n) = if n=0 then 1 else n * f(n-1);

val f = fn (n) => if n=0 then 1 else n * ??;

val rec f = fn (n) =>
    if n=0 then 1
    else n * f(n-1);
```
<!-- .element: data-thebe-executable-sml -->

---

### pattern matching

patterns can be used to simplify function definitions

```sml
fun factorial 0 = 1
  | factorial n = n * factorial(n-1);
```
<!-- .element: data-thebe-executable-sml -->

when the function is called, the first pattern to match the actual parameter determines which expression on the right hand side will be evaluated

---vert---

* patterns can consist of
  * constants - int, real, string, ...
  * constructs - tuples, datatype constructors
  * variables - all the rest
  * underscore - a wildcard
* matching is recursive
* any variable in the pattern is bound to the corresponding value in X
* there is no binding where the wildcard is used

---vert---

```sml
fun foo (x,1) = x
  | foo (1,_) = 0
  | foo _ = ~1;
(*val foo = fn : int * int -> int*)
foo(3,1);
(*val it = 3 : int*)
foo(1,3);
(*val it = 0 : int*)
foo(2,2);
(*val it = ~1 : int*)
foo(1,1);
(*val it = ? : int*)
```
<!-- .element: data-thebe-executable-sml -->

---vert---

### patterns using `case`

```sml
case E of P1 => E1 | ... | Pn => En
```

```sml
case p-q of
    0 => "zero"
  | 1 => "one"
  | 2 => "two"
  | n => if n<10 then "lots" else "lots &lots";
```
<!-- .element: data-thebe-executable-sml -->

* if `P1` is the first to match then the result is `E1`
* equivalent to an expression that defines a function by cases and applies it to `E`
* no symbol terminates the case expression
  * enclose in parentheses to eliminate ambiguity

---

### type abbreviation

* you can give a new name to an existing type

* the new name is only an alias

```sml
type vec = real*real;
(*type vec = real * real*)

infix ++;
fun (x1,y1) ++ (x2,y2) : vec = (x1+x2,y1+y2);
(*val ++ = fn: (real * real) * (real * real) -> vec*)

(3.6,0.9) ++ (0.1,0.2) ++ (20.0,30.0);
(*val it = (23.7,31.1) : vec*)
```
<!-- .element: data-thebe-executable-sml -->

---

### declarations inside an expression

```sml
let D in E end
```

```sml
fun fraction (n,d) =
  (n div gcd(n,d), d div gcd(n,d));
(*val fraction = fn: int*int -> int*int*)

fun fraction(n,d)=
  let 
    val com = gcd(n,d)
  in
    (n div com, d div com)
  end;
(*val fraction = fn: int*int -> int*int*)
```
<!-- .element: data-thebe-executable-sml -->

* `D` may be a compound declaration
  * `D1; D2; ...; Dn`
  * semicolons are optional

---vert---

`let` can be simulated using anonymous functions

```sml
fun fraction (n,d) = (fn c => (n div c, d div c))(gcd(n,d));
```
<!-- .element: data-thebe-executable-sml -->

---vert---

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
<!-- .element: data-thebe-executable-sml -->

---vert---

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
end
```
<!-- .element: data-thebe-executable-sml -->

(`D1` is visible only within `D2`)

---vert---

### comparing `let` and `local` (1)

```sml
fun fib n = let
  fun itfib (n, prev, curr): int =
    if n = 1 then curr
    else itfib (n-1, curr, prev + curr)
in
  itfib(n, 0, 1)
end
```
<!-- .element: data-thebe-executable-sml -->

```sml
local
  fun itfib (n, prev, curr): int =
    if n = 1 then curr
    else itfib (n-1, curr, prev + curr)
in
  fun fib n = itfib(n, 0, 1)
end
```
<!-- .element: data-thebe-executable-sml -->

---vert---

### comparing `let` and `local` (2)

```sml
fun pow4 n: int = let
  val n2 = n * n
in
  n2 * n2
end;
```
<!-- .element: data-thebe-executable-sml -->

---vert---

### comparing `let` and `local` (3)

```sml
local
  val x = pow4 5;
in
  val y = x + 2;
  val z = x * x;
end;
```
<!-- .element: data-thebe-executable-sml -->

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
(*val x = 5 : int
  val y = 3 : int*)
```
<!-- .element: data-thebe-executable-sml -->

---vert---

### mutually recursive functions

`$$\frac{\pi}{4}=\sum_{k=0}^\infty \frac{1}{4k+1} - \frac{1}{4k+3} = 1 - \frac{1}{3} + \frac{1}{5} - \frac{1}{7} + \frac{1}{9}$$`

```sml
fun pos d = neg (d-2.0) + 1.0/d
and neg d = if d > 0.0 then pos(d-2.0) - 1.0/d
                       else 0.0;

fun sum (d, one) =
    if d > 0.0
    then sum(d-2.0,~one) + one/d
    else 0.0;
```
<!-- .element: data-thebe-executable-sml -->

---vert---

### emulating `goto` statements

```pascal
var x:=0; y:=0; z:=0;
F: x := x+1; goto G
G: if y<z then goto F else (y:=x+y; goto H)
H: if z>0 then (z:=z-x; goto F) else stop
```

```sml
fun F(x,y,z) = G(x+1,y,z)
and G(x,y,z) = if y < z then F(x,y,z) else H(x,x+y,z)
and H(x,y,z) = if z > 0 then F(x,y,z-x) else (x,y,z);
F(0,0,0);
```
<!-- .element: data-thebe-executable-sml -->
