# OCaml

## functions

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
<!-- .element: data-thebe-executable-ocaml -->

---vert---

the operator can be used as a regular function

```ocaml
(--);;
(*- : float -> float -> float = <fun>*)

(--) 1. 3.;;
(*- : float = 3.16227766016837952*)
```
<!-- .element: data-thebe-executable-ocaml -->

---vert---

precedence and associativity are predefined and determined by the characters used in the operator

![ocaml operators](../imgs/ocaml-operators.png)

---

### currying

any function of two arguments is actually a **curried** function of one argument $$\alpha\rightarrow (\beta \rightarrow \gamma)$$

---vert---

```ocaml
let prefix pre post = pre ^ post;;
(*val prefix : string -> string -> string = <fun>*)
```
<!-- .element: data-thebe-executable-ocaml -->

is equivalent to:

```ocaml
let prefix pre = fun post -> pre ^ post;;
(*val prefix : string -> string -> string = <fun>*)
```
<!-- .element: data-thebe-executable-ocaml -->

---vert---

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
<!-- .element: data-thebe-executable-ocaml -->

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
<!-- .element: data-thebe-executable-ocaml -->

---

### recursive curried functions

```ocaml
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
<!-- .element: data-thebe-executable-ocaml -->

---

### composition operator

```ocaml
let (^^) f g x = f (g x);;
(*val ( ^^ ) : ('a -> 'b) -> ('c -> 'a) -> 'c -> 'b = <fun>*)

let f = sqrt ^^ sqrt;;
(*val f : float -> float = <fun>*)

f 16.0;
(*- : float = 2.*)

let g = (fun x -> x - Char.code '0') ^^ Char.code;;
(*val g : char -> int = <fun>*)

g '1';;
(*- : int = 1*)
```
<!-- .element: data-thebe-executable-ocaml -->

---

### exam questions

#### what will be printed?

---vert---

```ocaml
let rec f1 a b = f1 a b;;
```
<!-- .element: data-thebe-executable-ocaml -->

---vert---

```ocaml
let rec f2 g x = g (f2 g) x;;
```
<!-- .element: data-thebe-executable-ocaml -->

---vert---

```ocaml
let f3 x y z = (x, x y, y z);;
```
<!-- .element: data-thebe-executable-ocaml -->

---vert---

```ocaml
let rec f4 f = f f4;;
```
<!-- .element: data-thebe-executable-ocaml -->
