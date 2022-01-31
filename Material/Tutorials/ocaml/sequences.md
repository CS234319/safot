# Ocaml

## sequences

---

### sequences = delayed lists

* elements are not evaluated until their values are required
* **may** be infinite
* example: a sequence of all even integers `$0, 2, -2, 4, \ldots$`

<!--vert-->

### sequences in OCaml

defined in the `Seq` module:

```ocaml
type 'a t = unit -> 'a node
and 'a node = 
  | Nil
  | Cons of 'a * 'a t;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

* `Seq.t` is the sequence type
* `Seq.node` is a fully evaluated sequence node

<!--vert-->

a sequence is a **function** that takes `()` and returns a sequence node.

```ocaml
(*`empty` is an empty sequence*)
let empty () = Seq.Nil;;

(*`return v` is a sequence containing only `v`*)
let return v () = Seq.Cons (v, Seq.empty);;

let seq23 () = Seq.Cons (2, Seq.return 3);;

let seq123 () = Seq.Cons (1, seq23);;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

a node holds an element and the tail of the sequence which is a sequence itself.

<!--vert-->

```ocaml
let head xf = match xf () with
  | (Seq.Cons(x,_)) -> x
  | Nil -> raise (Failure "head");;
(*val head : (unit -> 'a Seq.node) -> 'a = <fun>*)

let tail xf = match xf () with
  | Seq.Cons(_, yf) -> yf
  | Nil -> raise (Failure "tail");;
(*val tail : (unit -> 'a Seq.node) -> 'a Seq.t = <fun>*)
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

---

### examples of sequences

```ocaml
let rec from k () = Seq.Cons (k, from (k + 1));;
(*val from : int -> int Seq.t = <fun>*)

head (from 1);;
(*- : int = 1*)

head (tail (from 1));;
(*- : int = 2*)
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

```ocaml
let rec squares s () = match s() with
  | Seq.Nil -> Seq.Nil
  | Seq.Cons (x, xf) -> Seq.Cons (x*x, squares xf);;
(*val squares : int Seq.t -> int Seq.t = <fun>*)

head (tail (tail (tail (tail (squares (from 1))))));;
(*- : int = 25*)
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

---

### side note - chaining operator `|>`

`|>` is a predefined operator for "reverse function application"

```ocaml
let ( |> ) x f = f x;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

`|>` is used for chaining functions

```ocaml
from 1
  |> squares
  |> tail
  |> tail
  |> tail
  |> tail
  |> head;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

isn't it much nicer?

<!--vert-->

the standard library usually puts the "object" last in the parameter list

```ocaml
let open List in
init 10 (fun _ -> Random.int 100)
  |> filter (fun x -> x mod 2 = 0)
  |> map (fun x -> x * x)
  |> sort_uniq Int.compare;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

---

### standard library functions

<!--vert-->

`List.to_seq` takes a list and returns a sequence

```ocaml
List.to_seq [1; 2; 3];;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

`List.of_seq` takes a sequence and returns a list

```ocaml
[1; 2; 3] |> List.to_seq |> List.of_seq;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

`Seq.map`, `Seq.filter`, `Seq.filter_map`, `Seq.fold_left`, `Seq.append` are the sequence equivalents of the known list functions

<!--vert-->

`Seq.unfold` builds a sequence from a "step function" and an initial value

```ocaml
let step n = if n < 0 then None else Some (n, n - 1) in
Seq.unfold step 5 |> List.of_seq;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

---

### elementary sequence processing

adding two sequences

```ocaml
let rec addq s q () = match (s(), q()) with
  | (Seq.Cons(x, xf), Seq.Cons(y, yf))
      -> Seq.Cons(x + y, addq xf yf)
  | _ -> Seq.Nil;;
(*val addq : int Seq.t -> int Seq.t -> int Seq.t = <fun>*)
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

appending two sequences

```ocaml
val append : 'a Seq.t -> 'a Seq.t -> 'a Seq.t
```

```ocaml
let rec append =
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

```ocaml
append (List.to_seq [1; 2; 3]) (List.to_seq [4; 5; 7])
  |> List.of_seq;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

```ocaml
let rec append l r = match l () with
  | Seq.Nil -> r
  | Seq.Cons(x, xf) -> fun () -> Seq.Cons(x, append xf r);;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

what would `(append xq yq)` be if `xq` is infinite?

<!--vert-->

interleaving two sequences

```ocaml
val interleaving : 'a Seq.t -> 'a Seq.t -> 'a Seq.t
```

```ocaml
let rec interleaving =
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

```ocaml
interleaving (List.to_seq [1; 2; 3]) (List.to_seq [4; 5; 7])
  |> List.of_seq;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

```ocaml
let rec interleaving l r = match l () with
  | Seq.Nil -> r
  | Seq.Cons(x, xf) ->
      fun () -> Seq.Cons(x, interleaving r xf);;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

#### `map`

```ocaml
val map : ('a -> 'b) -> 'a Seq.t -> 'b Seq.t
```

```ocaml
let rec map =
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

```ocaml
List.to_seq [1; 2; 3]
  |> map (( * ) 5)
  |> List.of_seq;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

```ocaml
let rec map f seq () = match seq () with
  | Seq.Nil -> Seq.Nil
  | Seq.Cons(x, xf) -> Seq.Cons(f x, map f xf);;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

#### `filter`

```ocaml
val filter : ('a -> bool) -> 'a Seq.t -> 'a Seq.t
```

```ocaml
let rec filter =
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

```ocaml
List.to_seq [1; 2; 3; 4; 5]
  |> filter (fun x -> x mod 2 = 1)
  |> List.of_seq;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

```ocaml
let rec filter pred seq () = match seq () with
  | Seq.Nil -> Seq.Nil
  | Seq.Cons(x, xf) when pred x
      -> Seq.Cons(x, filter pred xf)
  | Seq.Cons(_, xf) -> filter pred xf ();;
```

---

### example - prime numbers

![sieve gif](./../imgs/tut9-sieve.gif)

<!--vert-->

`primes` should be the sequence of all primes

🚩 **reminder** builtin operators `mod`, `<>`

```ocaml
let rec sieve s () =;;

let primes = sieve (from 2);;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

```ocaml
let rec sieve seq () = let open Seq in
    match seq () with
      | Nil -> Nil
      | Cons (n, nf) -> Cons (n, sieve (filter (fun x -> x mod n <> 0) nf));;

let primes = sieve (from 2);;
head (tail (tail (tail (tail primes))));;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

---

### exam questions

---

#### question 1

```ocaml
let rec map_3 f seq () = let open Seq in
  match seq () with
    | Nil -> Nil
    | Cons (x, xf) -> if (x mod 3 = 0)
      then Cons (f x, map_3 f xf)
      else Cons (x, map_3 f xf);;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

```ocaml
let rec mystery_1 f seq () = let open Seq in
  match seq () with
    | Nil -> Nil
    | Cons (x, xf) -> Cons (
        x,
        xf |> map (fun a -> f x a) |> mystery_1 f
      );;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

what would be printed?

```ocaml
mystery_1 ( + ) (from 0) |> tail |> tail |> tail |> head;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

```ocaml
let rec mystery_2 f seq () = let open Seq in
  match seq () with
    | Nil -> Nil
    | Cons (x, xf) -> Cons (
        x,
        xf |> map_3 (fun a -> f x a) |> mystery_2 f
      );;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

what would be printed?

```ocaml
mystery_2 ( + ) (from 0) |> tail |> tail |> tail |> tail |> head;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

---

#### question 2

`is_empty` returns `true` iff the given sequence is empty

```ocaml
let is_empty
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

```ocaml
let is_empty seq = match seq () with
  | Seq.Nil -> true
  | Seq.Cons _ -> false;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

`evens` returns a sequence of the elements at even indices of the given sequence (indexing starts with `1`)

```ocaml

```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

```ocaml
let rec aux seq flag () = match seq () with
  | Seq.Nil -> Seq.Nil
  | Seq.Cons (x, xf) -> let con = aux xf (not flag) in
      if flag
      then Seq.Cons (x, con)
      else con ();;
let evens seq = aux seq false;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

`odds` is the same as `evens` but for odd indices

```ocaml

```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

```ocaml
let odds seq = aux seq true;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

`switch` takes a sequence and swaps every odd-indexed element with the following element (if one exists)

```ocaml
(*...*)
assert ([2;1;4;3;6;5;7] = ([1;2;3;4;5;6;7] |> List.to_seq |> switch |> List.of_seq));;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

```ocaml
let switch seq = interleaving (evens seq) (odds seq);;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

---

#### question 3

`take` takes an integer `n` and a sequence and returns a sequence of the first `n` elements

```ocaml
(*...*)
assert ([1;2;3] = ([1;2;3;4;5;6;7] |> List.to_seq |> take 3 |> List.of_seq));;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

```ocaml
let rec take n s () = if n <= 0
    then Seq.Nil
    else match s () with
      | Seq.Nil -> Seq.Nil
      | Seq.Cons (x, xf) -> Seq.Cons (x, take (n - 1) xf);;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

`drop` takes an integer `n` and a sequence `s` and returns `s` without its first `n` elements

```ocaml
(*...*)
assert ([4;5;6;7] = ([1;2;3;4;5;6;7] |> List.to_seq |> drop 3 |> List.of_seq));;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

```ocaml
let rec drop n s = if n <= 0
    then s
    else match s () with
      | Seq.Nil -> fun () -> Seq.Nil
      | Seq.Cons (x, xf) -> drop (n - 1) xf;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->
