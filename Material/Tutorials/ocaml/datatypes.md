# OCaml

## datatypes

---

### concrete datatypes

* the keyword `type` can create new types
* these datatypes are **concrete** (not abstract)
* concrete datatypes can be inspected - constructed and taken apart
* OCaml's datatypes have two kinds of values: **atomic** and **composite**

---

### enumeration types

```ocaml
type single = Only;;

Only;;
```
<!-- .element: data-thebe-executable-ocaml -->

* `Only` denotes the only value in the type `single`
* isomorphic to `unit`

<!--vert-->

note that a constructor's name must be capitalized

```ocaml
type single = only;;
```
<!-- .element: data-thebe-executable-ocaml -->

<!--vert-->

order doesn't matter

```ocaml
type bool' = True | False;;

True;;
```
<!-- .element: data-thebe-executable-ocaml -->

<!--vert-->

allows pattern matching

```ocaml
type piece = King | Queen | Rook | Bishop | Knight | Pawn;;

let value = function King -> Float.infinity
  | Queen -> 9.0
  | Rook -> 5.0
  | (Bishop | Knight) -> 3.0
  | Pawn -> 1.0;;

value Bishop;;
```
<!-- .element: data-thebe-executable-ocaml -->

---

### branding

Newton's second law

```ocaml
let a m f = f /. m;;

let body, engine = 0.0122, 50.0;;

a engine body;; (* oops *)
```
<!-- .element: data-thebe-executable-ocaml -->

<!--vert-->

type aliasing doesn't help

```ocaml
type mass = float and force = float and acceleration = float;;

let a (m:mass) (f:force) : acceleration = f /. m;;

a engine body;; (* still oops *)
```
<!-- .element: data-thebe-executable-ocaml -->

<!--vert-->

simulate branding using `type`

```ocaml
type mass = Kg of float;;
type force = Newton of float;;
type acceleration = M_s'2 of float;;

let a (Kg m) (Newton f) = M_s'2 (f /. m);;

let body = Kg 2.0;;
let engine = Newton 50.0;;

a body engine;;

a engine body;;
```
<!-- .element: data-thebe-executable-ocaml -->

---

### variant types

```ocaml
type shape =
    Point
  | Line of float
  | Circle of float
  | Rectangle of float * float;;

let area = function | (Point | Line _) -> 0.0
  | (Circle r) -> Float.pi *. r *. r
  | (Rectangle (w, h)) -> w *. h;;
(*val area : shape -> float = <fun>*)
```
<!-- .element: data-thebe-executable-ocaml -->

<!--vert-->

the arguments of variant types can be defined like records

```ocaml
type shape =
    Point
  | Line of float
  | Circle of float
  | Rectangle of {width: float; height: float};;

let r = Rectangle {width=5.; height=6.}
```
<!-- .element: data-thebe-executable-ocaml -->

---

### pattern matching

```ocaml
let line = Line 5.3;;

let Line length = line;;

let Circle radius = line;;
```
<!-- .element: data-thebe-executable-ocaml -->

---

### recursive datatypes

🛈 every list is either `[]` or `head::tail`

```ocaml
type intlist =
    Nil
  | (::) of int * intlist;;

let rec length = function
  | Nil -> 0
  | (x::xs) -> 1 + length xs;;
```
<!-- .element: data-thebe-executable-ocaml -->

---

### polymorphic datatypes

```ocaml
(*predefined*)
type 'a list =
    [] (*special symbol*)
  | (::) of 'a * ('a list);;

"hello" :: "world" :: [];;
```
<!-- .element: data-thebe-executable-ocaml -->

<!--vert-->

```ocaml
(*predefined*)
type 'a option = None | Some of 'a;;
```

```ocaml
let hd' = function
  | [] -> None
  | (x::_) -> Some x;;

hd' [1; 2; 3];;

hd' [];;
```
<!-- .element: data-thebe-executable-ocaml -->

<!--vert-->

```ocaml
type ('a, 'b) union = Type1 of 'a
  | Type2 of 'b;;

let five = Type1 5;;

let hello = Type2 "hello";;

let five_or_hello = if true then five else hello;;

let int_char_list = [Type1 5; Type2 'a'];;
```
<!-- .element: data-thebe-executable-ocaml -->

---

### trees

```ocaml
type 'a tree = Nil | Br of 'a * ('a tree) * ('a tree);;

let leaf x = Br (x, Nil, Nil);;
let tree2 = Br(2, leaf 1, leaf 3);;
let tree5 = Br(5, leaf 6, leaf 7);;
let tree4 = Br(4, tree2, tree5);;
```
<!-- .element: data-thebe-executable-ocaml -->

<!--vert-->

#### implement `size`

```ocaml
(*val size : 'a tree -> int*)
```
<!-- .element: data-thebe-executable-ocaml -->

test:

```ocaml
size tree4;;
```
<!-- .element: data-thebe-executable-ocaml -->

<!--vert-->

```ocaml
let rec size = function
  | Nil -> 0
  | Br(_, l, r) -> 1 + size l + size r;;
```
<!-- .element: data-thebe-executable-ocaml -->

<!--vert-->

### binary search trees

* implement an associative array using trees
* the keys and values may be anything
* assumption: the tree is ordered

<!--vert-->

#### implement `get`

`get` takes a tree and a key and if the key is present returns an `option` of the associated value otherwise it returns `None`

reminder:

```ocaml
type 'a option = None | Some of 'a;;
```

<!--vert-->

```ocaml
(*val get : ('a * 'b) tree -> 'a -> 'b option*)
```
<!-- .element: data-thebe-executable-ocaml -->

<!--vert-->

```ocaml
let rec get tr k = match tr with
  | Nil -> None
  | Br((nk, nv), left, right) -> match compare nk k with
    | 0 -> Some nv
    | n when n < 0 -> get left k
    | _ -> get right k;;
```
<!-- .element: data-thebe-executable-ocaml -->

<!--vert-->

#### implement `insert`

```ocaml
(*val insert : ('a * 'b) tree -> 'a * 'b -> ('a * 'b) tree = <fun>*)
```
<!-- .element: data-thebe-executable-ocaml -->

<!--vert-->

```ocaml
let rec insert tr (k, v) = match tr with
  | Nil -> leaf (k, v)
  | Br ((nk, nv), left, right) -> match compare nk k with
    | 0 -> Br ((k, v), left, right)
    | n when n < 0 ->
        Br ((nk, nv), insert left (k, v), right)
    | _ ->
        Br ((nk, nv), left, insert right (k, v));;
```
<!-- .element: data-thebe-executable-ocaml -->