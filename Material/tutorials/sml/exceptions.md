# Standard ML

## exceptions

---

### exceptions - why?

* an extensive part of code is error handling
* a function can return an answer, or fail to find one, or signal that a solution does not exists

<!--vert-->

### exceptions - alternative

```sml
datatype int_sol = Success of int | Failure | Impossible;

case methodA(problem) of
    Success s  => Int.toString s
  | Failure    => (case methodB(problem) of
                      Success s  => Int.toString s
                    | Failure    => "Both failed"
                    | Impossible => "No Good")
  | Impossible => "No Good"
;
```

it can be tedious and requires explicit handling

sometimes we don't really know what to do with the error, so we'll simply return it

---

### exceptions

* when an error is discovered we will **raise** an exception
* the exception will propagate up until someone **handles** it
* the caller of a function doesn't have to check any error values
* in pseudo code:

```sml
fun inner = do_calculation
    if local_error then raise local_error,
    if global_error then raise global_error;

fun middle = inner(…) handle local_error;

fun outer = middle(…) handle global_error;
```

---

### the exception type `exn`

* we can **raise** only a specific type: `exn`
* `exn` is a special datatype with an **extendable** set of constructors and values

```sml
exception Failure;
Failure;
(*val it = Failure(-) : exn*)

exception Problem of int;
Problem;
(*val it = fn : int -> exn*)
```
<!-- .element: data-thebe-executable-sml -->

<!--vert-->

values of type `exn` have all the privileges of other values

```sml
val x = Failure;
(*val x = Failure(-) : exn*)

val p = Problem 1;
(*val p = Problem(-) : exn*)

map Problem [0, 1, 2];
(*val it = [Problem(-),Problem(-),Problem(-)] : exn ?.list*)

fun whats_the_problem (Problem p) = p;
(*Warning: match nonexhaustive ...*)
(*val whats_the_problem = fn : exn -> int*)
```
<!-- .element: data-thebe-executable-sml -->

... except

```sml
x = x;
(*Error: operator and operand don't agree [equality type required]*)
```
<!-- .element: data-thebe-executable-sml -->

---

### raising exceptions - semantics

```sml
raise Exp
```

* the expression `Exp` of type `exn` evaluates to `e`
* `raise Exp` evaluates to an <span style="color: red;">exception packet</span> containing `e`
* packets are not ML values!

<!--vert-->

* exception packets propagate under the call by value rule
* all of the following evaluate to `raise Exp`

```sml
f (raise Exp)

(raise Exp) arg

raise (Exp1 (raise Exp)) (* Exp1 is a constructor *)

(raise Exp, raise Exp1)  (* or {a=Exp, b=Exp1} *)

let val name = raise Exp in some_expression end

local val name = raise Exp in some_declaration end
```

---

### fixing `hd` and `tl`

```sml
exception Empty;

fun hd (x::_) = x
  | hd []     = raise Empty;
(*val hd = fn : 'a list -> 'a*)

fun tl (_::xs) = xs
  | tl []      = raise Empty;
(*val tl = fn : 'a list -> 'a list*)
```
<!-- .element: data-thebe-executable-sml -->

---

### handling exceptions - syntax

```sml
Exp_0 handle
    P1 => Exp_1
  | ...
  | Pn => Exp_n
```

* all `Exp_i`s must be type-compatible
* all `Pi`s must be valid patterns for the type `exn`

```sml
fun len l = 1 + len (tl l) handle Empty => 0;
```
<!-- .element: data-thebe-executable-sml -->

---

### handling exceptions - semantics

```sml
Exp_0 handle Cons1 x => Exp_1
```

* assume `Exp_0` evaluates to some value `V` then the value of this expressions is
  * `Exp_1` if `Exp_0` evaluates to `raise Cons1 x`
  * `V` otherwise (`V` may be either a normal value or a non-matching raised exception)
* `handle` is short-circuiting
* exactly equivalent to familiar notions from C++

---

### the type of `raise Exp`

* the expression `raise Exp` is of type `'a`
* it is **not** an expression of type `exn`
* it simply puts no restrictions on other parts of the expression

```sml
fun throw _ = raise Empty;
(*val throw = fn : 'a -> 'b*)

fun bar x = if x>0 then x else raise Underflow;
(*val bar = fn : int -> int*)
```
<!-- .element: data-thebe-executable-sml -->

---

### using exception handling

```sml
case methodA(problem) of
    Success s  => Int.toString s
  | Failure    => (case methodB(problem) of
                      Success s  => Int.toString s
                    | Failure    => "Both failed"
                    | Impossible => "No Good")
  | Impossible => "No Good"
```

and now with exceptions:

```sml
toString (methodA problem handle Failure => methodB problem)
  handle Failure => "Both failed"
    | Impossible => "No Good"
```

---

### error messages

```sml
raise Problem;
(*Error: argument of raise is not an exception [tycon mismatch]*)

hd ["good"] handle nil => "bad";
(*Error: handler domain is not exn [tycon mismatch]*)

hd ["good"] handle Empty => false;
(*Error: expression and handler don't agree [tycon mismatch]*)
```
<!-- .element: data-thebe-executable-sml -->

---

### exam questions

```sml
local
    exception E of string;
in
    fun f (E "Hello", E x) = x;
end;
```
<!-- .element: data-thebe-executable-sml -->

<!--vert-->

```sml
let
    exception Exy of int
in
    ( fn 2 => raise Exy 4
       | x => x + x
    ) 2 handle Exy n => n
end;
```
<!-- .element: data-thebe-executable-sml -->

---

### standard exceptions

* `Chr` raised by `(chr k)` if `k<0` or `k>255`
* `Match` raised for failure of pattern matching
* `Bind` raised by `val P = E;` if `E` doesn't match the pattern `P`
