# OCaml

## exceptions

---

### exceptions - why?

* an extensive part of code is error handling
* a function can return an answer, or fail to find one, or signal that a solution does not exists

<!--vert-->

### exceptions - alternative

```ocaml
type int_sol = Success of int | Failure | Impossible;;

match method_a problem with
  | Success s -> Int.to_string s
  | Failure ->
      begin match method_b problem with
        | Success s -> Int.to_string s
        | Failure -> "Both failed"
        | Impossible -> "No Good"
      end
  | Impossible -> "No Good"
;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

it can be tedious and requires explicit handling

sometimes we don't really know what to do with the error, so we'll simply return it

---

### exceptions

* when an error is discovered we will **raise** an exception
* the exception will propagate up until someone **handles** it
* the caller of a function doesn't have to check any error values

---

### the exception type `exn`

* we can **raise** only a specific type: `exn`
* `exn` is a special datatype with an **extendable** set of constructors and values

```ocaml
exception Failure;;
Failure;;
(*- : exn = Failure*)

exception Problem of int;;
Problem 5;;
(*- : exn = Problem 5*)
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

values of type `exn` have all the privileges of other values

```ocaml
let x = Failure;;
(*val x : exn = Failure*)

let p = Problem 1;;
(*val p : exn = Problem 1*)

List.map (fun x -> Problem x) [0; 1; 2];;
(*- : exn list = [Problem 0; Problem 1; Problem 2]*)

let whats_the_problem (Problem p) = p;;
(*Warning 8: this pattern-matching is not exhaustive.*)
(*val whats_the_problem : exn -> int = <fun>*)
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

---

### raising exceptions - semantics

```ocaml
exception Exp;;
raise Exp;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

* the expression `Exp` of type `exn` evaluates to `e`
* `raise Exp` evaluates to an <span style="color: red;">exception packet</span> containing `e`
* packets are not OCaml values!

<!--vert-->

* exception packets propagate under the call by value rule
* all of the following evaluate to `raise Exp`

```ocaml
f (raise Exp);;

(raise Exp) 5;;

raise (Exn1 (raise Exp));; (* Exn1 is a constructor *)

(raise Exp, raise Exp1);;  (* or {a=Exp, b=Exp1} *)

let name = raise Exp in some_expression;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

---

### handling exceptions - syntax

```ocaml
try Exp_0 with
  | P1 -> Exp_1
  | ...
  | Pn -> Exp_n;;
```

* all `Exp_i`s must be type-compatible
* all `Pi`s must be valid patterns for the type `exn`

```ocaml
let rec len l = try 1 + len (tl l) with Failure _ -> 0;;
(*val len : 'a list -> int = <fun>*)
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

---

### handling exceptions - semantics

```ocaml
try Exp_0 with Cons1 x -> Exp_1
```

* assume `Exp_0` evaluates to some value `V` then the value of this expressions is
  * `Exp_1` if `Exp_0` evaluates to `raise Cons1 x`
  * `V` otherwise (`V` may be either a normal value or a non-matching raised exception)
* `try` is short-circuiting
* exactly equivalent to familiar notions from C++

---

### the type of `raise Exp`

* the expression `raise Exp` is of type `'a`
* it is **not** an expression of type `exn`
* it simply puts no restrictions on other parts of the expression

```ocaml
let throw _ = raise (Failure "");;
(*val throw : 'a -> 'b = <fun>*)

let bar x = if x > 0 then x else raise (Failure "");;
(*val bar : int -> int = <fun>*)
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

---

### using exception handling

```ocaml
match method_a problem with
  | Success s -> Int.to_string s
  | Failure ->
      begin match method_b problem with
        | Success s -> Int.to_string s
        | Failure -> "Both failed"
        | Impossible -> "No Good"
      end
  | Impossible -> "No Good"
;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

and now with exceptions:

```ocaml
try Int.to_string begin
    try method_a problem with Failure _ -> method_b problem
end with
  | Failure _ -> "Both failed"
  | Impossible -> "No Good";;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->
