# OCaml

## declarations

---

### naming entities

entities of different kinds are distinguished by the capitalization of their names:

* uppercase: constructors, variant tags, exceptions, modules
* lowercase: (anything else) values, labels, type constructors, record fields, classes, instances variables, methods

---

### example - circle area

$$area = \pi \cdot r^2$$

```ocaml
let pi = 3.14159;;

let area r = pi *. r *. r;;

area 2.0;;
```
<!-- .element: data-thebe-executable-ocaml -->

<!--vert-->

### identifiers in OCaml

* `let` declaration binds a name to a __value__
* a name can not be used to change its value
  * actually a constant
* a name can be reused for another purpose

    ```ocaml
    let pi = "pi";;
    ```
    <!-- .element: data-thebe-executable-ocaml -->

<!--vert-->

* if a name is declared again the new meaning is adopted afterwards

    ```ocaml
    pi;;
    ```
    <!-- .element: data-thebe-executable-ocaml -->

* but does not affect existing uses of the name

    ```ocaml
    area 1.0;;
    ```
    <!-- .element: data-thebe-executable-ocaml -->

<!--vert-->

### is permanence of names a good feature?

<div style="text-align: left">
👍 redefining cannot damage your program

👎 redefining may have no visible effect

⚠️ when modifying a program, be sure to recompile the entire file
</div>

---

### pattern matching

* patterns can be used to simplify function definition

    ```ocaml
    let rec factorial = function
      | 0 -> 1
      | n -> n * factorial (n - 1);;
    ```
    <!-- .element: data-thebe-executable-ocaml -->

* note the usage of `function` instead of `fun`

* when the function is called, the first pattern to match the actual parameter determines which expression on the right hand side will be evaluated

<!--vert-->

* patterns can consist of
  * constants - int, real, string, ...
  * constructs - tuples, constructors
  * variables - all the rest
  * underscore - a wildcard
* matching is recursive
* any variable in the pattern is bound to the corresponding value
* there is no binding where the wildcard is used

<!--vert-->

```ocaml
let foo = function
  | (x, 1) -> x
  | (1, _) -> 0
  | _ -> -1;;
(*val foo : int * int -> int = <fun>*)
foo(3,1);;
(*- : int = 3*)
foo(1,3);;
(*- : int = 0*)
foo(2,2);;
(*- : int = -1*)
foo(1,1);;
(*- : int = 1*)
```
<!-- .element: data-thebe-executable-ocaml -->

<!--vert-->

### patterns using `match`

```ocaml
match E with | P1 -> E1 | ... | Pn -> En
```

* if `P1` is the first to match then the result is `E1`
* equivalent to an expression that defines a function by cases and applies it to `E`
* no symbol terminates the case expression
  * enclose in parentheses to eliminate ambiguity
  * or enclose in `begin ... end`

<!--vert-->

```ocaml
match Random.int 10 with
  | 0 -> "zero"
  | 1 -> "one"
  | 2 -> "two"
  | n -> if n < 10 then "lots" else "lots &lots";;
```
<!-- .element: data-thebe-executable-ocaml -->

<!--vert-->

match guards using `when`:

```ocaml
match Random.int 10 with
  | 0 -> "zero"
  | 1 -> "one"
  | 2 -> "two"
  | n when n < 10 -> "lots"
  | _ -> "lots &lots";;
```
<!-- .element: data-thebe-executable-ocaml -->

---

### type abbreviation

* you can give a new name to an existing type

* the new name is only an alias

```ocaml
type vec = float * float;;

let (++) (x1, y1) (x2, y2) : vec = (x1 +. x2, y1 +. y2);;

(3.6, 0.9) ++ (0.1, 0.2) ++ (20.0, 30.0);;
```
<!-- .element: data-thebe-executable-ocaml -->

---

### declarations inside an expression

```ocaml
let D in E
```

```ocaml
let rec gcd m n = if m = 0 then n else gcd (n mod m) m;;

let fraction n d =
    (n / (gcd n d), d / (gcd n d));;

let fraction n d =
    let com = gcd n d in
    (n / com, d / com);;
```
<!-- .element: data-thebe-executable-ocaml -->

<!--vert-->

`let ... in` can be simulated using anonymous functions

```ocaml
let fraction n d =
    (fun com -> (n / com, d / com)) (gcd n d);;
```
<!-- .element: data-thebe-executable-ocaml -->

<!--vert-->

### nested scopes

```ocaml
let sq_root a =
  let acc = 1.0e-10 in
  let rec find_root x =
    let next_x = (a /. x +. x) /. 2.0 in
    if Float.abs (x -. next_x) < acc *. x
    then next_x
    else find_root next_x in
  find_root 1.0;;
```
<!-- .element: data-thebe-executable-ocaml -->

---

### simultaneous declarations (collateral)

```ocaml
let ID1 = E1 and ... and IDn = En
```

* evaluates `E1`, ..., `En`
* and only then declares the identifiers `ID1`, ..., `IDn`

```ocaml
let x = 3;;
let y = 5;;
let x = y and y = x;;
```
<!-- .element: data-thebe-executable-ocaml -->

<!--vert-->

### mutually recursive functions

$$\frac{\pi}{4}=\sum_{k=0}^\infty \frac{1}{4k+1} - \frac{1}{4k+3} = 1 - \frac{1}{3} + \frac{1}{5} - \frac{1}{7} + \frac{1}{9}$$

```ocaml
let rec pos d = neg (d -. 2.0) +. 1.0 /. d
and neg d = if d > 0.0
    then pos(d -. 2.0) -. 1.0 /. d
    else 0.0;;

let rec sum d one = if d > 0.0
    then sum (d -. 2.0) (-. one) +. one /. d
    else 0.0;;
```
<!-- .element: data-thebe-executable-ocaml -->

<!--vert-->

### FIXME emulating `goto` statements

```pascal
var x:=0; y:=0; z:=0;
F: x := x+1; goto G
G: if y<z then goto F else (y:=x+y; goto H)
H: if z>0 then (z:=z-x; goto F) else stop
```

```ocaml
let rec f x y z = g (x + 1) y z
and g x y z = if y < z then f x y z else h x (x + y) z
and h x y z = if z > 0 then f x y (z - x) else (x, y, z);;

f 0 0 0;;
```
<!-- .element: data-thebe-executable-ocaml -->