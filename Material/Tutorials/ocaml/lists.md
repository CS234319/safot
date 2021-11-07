# OCaml

## lists

---

a list is an __immutable__ finite sequence of elements

```ocaml
([3; 5; 9]: int list);;
(["a"; "list"]: string list);;
(["🍏"; "🍊"; "🍌"]: string list);;
([]: 'a list);;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

order matters

```ocaml
[1; 2; 3] <> [3; 2; 1];;
(*- : bool = true*)
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

and repetitions count

```ocaml
[3; 3; 3] <> [3];;
(*- : bool = true*)
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

elements may have any type

```ocaml
([(1,"One"); (2,"Two")] : (int*string) list);;
([[3.1]; []; [5.7; -0.6]]: float list list);;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

... but all elements must have the same type

```ocaml
[5; "five"];; (*ERROR!*)
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

the empty list has a polymorphic type

```ocaml
([]: 'a list);;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

---

### building a list

a list is either *empty* or *a head followed by a tail*

`[1; 2; 3]` ➭ head: `1` tail: `[2; 3]`

<!--vert-->

use the infix operator `::` (aka. `cons`) to build a list

```ocaml
1 :: [2; 3];;
(*- : int list = [1; 2; 3]*)

1 :: 2 :: 3 :: [];;
(*- : int list = [1; 2; 3]*)
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

`::` associates to the right, so

`x1 :: x2 :: ... :: xn :: nil`

\=

`(x1 :: (x2 :: (... :: (xn :: nil)...)`

<!--vert-->

`::` is a **constructor** so it can be used in patterns

```ocaml
let replace_head = function
  | ((_::t), x) -> x :: t
  | ([], _) -> [];;
(*val replace_head : 'a list * 'a -> 'a list = <fun>*)
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

---

### builtin fundamental functions

<!--vert-->

`List.hd` - evaluates to the head of a non-empty list

```ocaml
let hd = function
  | [] -> raise (Failure "hd")
  | x::_ -> x;;
(*val hd : 'a list -> 'a = <fun>*)
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

`List.tl` - evaluates to the tail of a non-empty list

```ocaml
let tl = function
  | [] -> raise (Failure "tl")
  | _::xs -> xs;;
(*val tl : 'a list -> 'a list = <fun>*)
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

```ocaml
let it = List.hd [ [ [1;2]; [3] ]; [ [4] ] ];;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

```ocaml
let it = List.hd it;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

```ocaml
let it = List.hd it;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

```ocaml
let it = List.tl ["how"; "are"; "you"];;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

```ocaml
let it = List.tl it;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

```ocaml
let it = List.tl it;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

```ocaml
let it = List.tl it;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

---

### building a list of integers

```ocaml
let rec range m n = if m = n
    then []
    else m :: (range (m+1) n);;
(*val range : int -> int -> int list = <fun>*)

range 2 5;;
(*- : int list = [2; 3; 4]*)

let (--) = range;;

2 -- 5;;
(*- : int list = [2; 3; 4]*)
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

---

### `take` and `drop`

$$xs = [x_1, x_2, x_3, \ldots, x_k, x_{k+1}, \ldots, x_n]$$
$$take(k, xs) = [x_1, x_2, x_3, \ldots, x_k]$$
$$drop(k, xs) = [x_{k+1}, \ldots, x_n]$$

<!--vert-->

### the computation of `take`

```ocaml
let rec take n l = match n, l with
  | 0, _ -> []
  | _, [] -> raise (Failure "take")
  | i, x::xs -> x :: take (i - 1) xs;;
(*val take : int -> 'a list -> 'a list = <fun>*)
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

```ocaml
(take 3 [9;8;7;6;5;4])
9 :: (take 2 [8;7;6;5;4])
9 :: 8 :: (take 1 [7;6;5;4])
9 :: 8 :: 7 :: (take 0 [6;5;4])
9 :: 8 :: 7 :: [])
9 :: 8 :: [7]
9 :: [8; 7]
[9; 8; 7]
```

<!--vert-->

### the computation of `drop`

```ocaml
let rec drop n l = match n, l with
  | 0, xs -> xs
  | _, [] -> raise (Failure "drop")
  | i, _::xs -> drop (i - 1) xs;;
(*val drop : int -> 'a list -> 'a list = <fun>*)
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

```ocaml
drop 3 [9; 8; 7; 6; 5; 4]
drop 2    [8; 7; 6; 5; 4]
drop 1       [7; 6; 5; 4]
drop 0          [6; 5; 4]
[6; 5; 4]
```

---

### tail recursion

<!--vert-->

normal recursion

```ocaml
let rec take n l = match n, l with
  | 0, _ -> []
  | _, [] -> raise (Failure "take")
  | i, x::xs -> x :: take (i - 1) xs;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

tail recursion

```ocaml
let rec drop n l = match n, l with
  | 0, xs -> xs
  | _, [] -> raise (Failure "drop")
  | i, _::xs -> drop (i - 1) xs;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

### normal to tail recursive

```ocaml
let rec rec_length = function
  | [] -> 0
  | (_::xs) -> 1 + rec_length xs;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

use an **accumulator** to make it iterative

```ocaml
let rec aux acc = function
  | []    -> acc
  | _::xs -> aux (acc + 1) xs;;

let iter_length xs = aux 0 xs;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

let's test them!

```ocaml
let repeat n =
  let rec aux acc = function
    | 0 -> acc
    | n -> aux (0::acc) (n-1) in
  aux [] n;;

let long_list = repeat 1000000;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

```ocaml
iter_length long_list;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

```ocaml
rec_length long_list;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

---

### builtin append operator

`[x1;...;xm] @ [y1;...;yn] = [x1;...;xm;y1;...;yn]`

```ocaml
let rec (@) l1 l2 = match (l1, l2) with
  | ([], ys) -> ys
  | (x::xs, ys) -> x::(xs @ ys);;
(*val ( @ ) : 'a list -> 'a list -> 'a list = <fun>*)

["Append"; "is"] @ ["never"; "boring"];;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

* is it tail recursive?
* why can't it be used in patterns?

---

### side note - `||` and `&&`

they are short-circuiting boolean operators

```ocaml
B1 && B2 = if B1 then B2  else false;;

B1 ||  B2 = if B1 then true else B2;;
```

<!--vert-->

```ocaml
let even n = n mod 2 = 0;;
(*val even : int -> bool = <fun>*)

let rec powoftwo n =
  (n = 1) ||
  (even n && powoftwo (n / 2));;
(*val powoftwo : int -> bool = <fun>*)
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

is `powoftwo` tail-recursive?

---

### builtin function `map`

```ocaml
let rec map f = function
  | [] -> []
  | x::xs -> (f x) :: (map f xs)
;;
(*val map : ('a -> 'b) -> 'a list -> 'b list = <fun>*)

let sqlist = map (fun x -> x * x);;
(*val sqlist : int list -> int list = <fun>*)

sqlist [1;2;3];;
(*- : int list = [1; 4; 9]*)
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

transposing a matrix using `map`

![transp gif](./../imgs/matrix_transpose.gif)

```ocaml
let rec transp = function
  | []::_ -> []
  | rows -> List.(map hd rows) :: transp List.(map tl rows);;
(*val transp : 'a list list -> 'a list list = <fun>*)

transp [[1;2;3];[4;5;6];[7;8;9]];;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

---

### builtin function `filter`

```ocaml
let rec filter pred = function
  | [] -> []
  | x::xs when (pred x) -> x::(filter pred xs)
  | x::xs -> filter pred xs;;
(*val filter : ('a -> bool) -> 'a list -> 'a list = <fun>*)

filter (fun x -> x mod 2 = 0) [1; 2; 3; 4; 5];;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

---

### builtin function `filter_map`

```ocaml
let rec filter_map f = function
  | [] -> []
  | x::xs -> let tail = filter_map f xs in
    match (f x) with
      | None -> tail
      | Some x' -> x'::tail;;
(*val filter_map : ('a -> 'b option) -> 'a list -> 'b list = <fun>*)
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

### using `filter_map`

a polynomial is represented as a list of `$(coeff,degree)$` pairs

$$5x^3 + 2x + 7$$

```ocaml
type polynomial = (int * int) list;;
let a: polynomial = [(5, 3); (2, 1); (7, 0)];;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

taking the derivative of a polynomial

```ocaml
let aux (coeff, deg) = if deg = 0 then None else Some (coeff*deg, deg-1);;

let derive (p: polynomial): polynomial = List.filter_map aux p;;
(*val derive : polynomial -> polynomial = <fun>*)

derive a;;
(*- : polynomial = [(15, 2); (2, 0)]*)
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

---

### `fold_left` and `fold_right`

<!--vert-->

### builtin function `fold_left`

```ocaml
let rec fold_left f init = function
  | [] -> init
  | x::xs -> fold_left f (f init x) xs;;
(*val fold_left : ('a -> 'b -> 'a) -> 'a -> 'b list -> 'a = <fun>*)
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

computes `$[x_1, x_2, … ,x_n] \rightarrow f(x_n, … ,f(x_2, f(x_1,init)))$`

<!--vert-->

### builtin function `fold_right`

```ocaml
let rec fold_right f init = function
  | [] -> init
  | x::xs -> f (fold_right f init xs) x;;
(*val fold_right : ('a -> 'b -> 'a) -> 'a -> 'b list -> 'a = <fun>*)
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

computes `$[x_1, x_2, … ,x_n] \rightarrow f(x1, … ,f(xn-1, f(xn,init)))$`

<!--vert-->

### using `fold_left` and `fold_right`

let's redefine some functions...

```ocaml
let sum l = List.fold_left (+) 0 l;;
(*val sum : int list -> int = <fun>*)

let reverse l = List.fold_left (fun l x -> x::l) [] l;;
(*val reverse : 'a list -> 'a list = <fun>*)

let (@) xs ys = List.fold_right List.cons xs ys;;
(*val ( @ ) : 'a list -> 'a list -> 'a list = <fun>*)
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

---

### `exists` and `for_all`

<!--vert-->

### builtin function `exists`

```ocaml
let rec exists pred = function
  | [] -> false
  | x::xs -> (pred x) || exists pred xs;;
(*val exists : ('a -> bool) -> 'a list -> bool = <fun>*)
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

checks if the predicate `pred` is satisfied by at least one element of the list

```ocaml
List.exists ((>) 0) [1; 2; -3; 4];;
(*- : bool = true*)
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

### builtin function `for_all`

```ocaml
let rec for_all pred = function
  | [] -> true
  | x::xs -> (pred x) && for_all pred xs;;
(*val for_all : ('a -> bool) -> 'a list -> bool = <fun>*)
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

checks if the predicate `pred` is satisfied by **all** elements of the list

```ocaml
List.for_all ((<=) 0) [1; 2; -3; 4];;
(*- : bool = false*)
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

```ocaml
let disjoint xs ys =
    List.for_all (fun x -> List.for_all ((<>) x) ys) xs;;
(*val disjoint : 'a list -> 'a list -> bool = <fun>*)
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

---

### polymorphic equality

equality is polymorphic

* defined for all values constructed of ints, floats, strings, bools, chars, tuples, lists and datatypes
* will raise an exception for values containing
  * functions: equality is undecidable (halting problem)

```ocaml
(=);;
(*- : 'a -> 'a -> bool = <fun>*)
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

---

### looping over lists

to loop over lists (and other builtin data structures) you may use `iter` and `iteri`

```ocaml
List.iter;;
List.iteri;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

```ocaml
let print_list l =
    let f x = Printf.printf "%d" x in
    List.iter f l
;;

print_list [1; 2; 3; 4];;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

---

### exam questions

<!--vert-->

implement `map` using `fold_left`

```ocaml
val map: ('a -> 'b) -> 'a list -> 'b list
val fold_left: ('a -> 'b -> 'a) -> 'a -> 'b list -> 'a
```

```ocaml
let map f xs = List.fold_left
    _
    _
    xs
;;

let () = assert (map (( * ) 2) [1; 2; 3] = [2; 4; 6]);;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

```ocaml
let map f xs = List.fold_left
    (fun acc x -> acc @ [f x])
    []
    xs
;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

implement `insertion_sort` using `fold_right` (you may define helper functions)

```ocaml
val insertion_sort: ('a -> 'a -> bool) -> 'a list -> 'a list
val fold_right: ('a -> 'b -> 'b) -> 'a list -> 'b -> 'b
```

```ocaml
let insertion_sort lt xs = List.fold_right
    _
    xs
    _
;;

let () = assert (insertion_sort (<) [0;3;2;4;1] = [0;1;2;3;4]);;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

```ocaml
let rec insert x = function
  | [] -> [x]
  | y::ys -> if x < y
      then x::y::ys
      else y::(insert x ys);;

let insertion_sort lt xs = List.fold_right
    insert
    xs
    []
;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

---

### extra questions

<!--vert-->

implement a tail recursive append

```ocaml
let (@) xs ys = match xs with
  | [] -> ys
  | x::xs -> x :: (xs @ ys);;
```

```ocaml
let (@) (*...*)

let () = assert ([1;2;3] @ [4;5;6] = [1;2;3;4;5;6]);;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

```ocaml
let rec aux acc = function
  | [] -> acc
  | x :: xs -> aux (x::acc) xs;;

let (@) xs ys = aux ys (aux [] xs);;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

implement `flatten` using `fold_right`

```ocaml
val flatten: 'a list list -> 'a list
val fold_right: ('a -> 'b -> 'b) -> 'a list -> 'b -> 'b
```

```ocaml
let flatten xs = List.fold_right
    _
    _
    _
;;

let () = assert (flatten [[1;2;3]; [4;5;6]; []; [7;8]] = [1;2;3;4;5;6;7;8]);;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

```ocaml
let flatten xs = List.fold_right
    ( @ )
    xs
    []
;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

implement `flatten` using `fold_left`

```ocaml
let flatten xs = List.fold_left
    _
    _
    _
;;;

let () = assert (flatten [[1;2;3]; [4;5;6]; []; [7;8]] = [1;2;3;4;5;6;7;8]);;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

```ocaml
let flatten xs = List.fold_left
    ( @ )
    []
    xs
;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->
