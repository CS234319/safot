# OCaml

## continuations

---

### sss

One way to look at continuation-passing style is to imagine how you would write code if functions weren't allowed to return. You could still make things work by having an extra parameter of each function that tells what you want to do after the function does its computation. I.e., you pass a function that acts as a "continuation" of the overall computation.

The code you give is written exactly this way, and c is the continuation. I.e., it's a function that the caller passes in that tells what to do next after the function does its intended calculation.

Continuation-passing style is completely general, i.e., all computations can be expressed this way. And, in fact, there's a mechanical transformation from ordinary functional code into continuation-passing style.

```ocaml
let rec sumlist lst =
  match lst with
    | [] -> 0
    | (h::t) -> h + (sumlist t);;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

```ocaml
let rec cont_sumlist lst c =
  match lst with
    | [] -> (c 0)
    | (h::t) -> cont_sumlist t (fun x -> c (h + x));;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

in case of `[]` we "return" (i.e. feed) `0` into `c` that we're given, and in case of `(h::t)` we construct the continuation for `cont_sumlist t` so that after the result for `t` (i.e. `x`) is ready, it will be combined with `h` (by `h + x`) and fed further into `c` given to us for `(h::t)`.
