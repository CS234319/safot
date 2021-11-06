# Standard ML

## errors

---

```sml
fun foo x y = x + y;

foo 5 -4;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

```sml
fun foo x y = x + y;
fun bar (x, y) = x * y;

foo 2 bar(1, 2);
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

```sml
fun foo [] = 0
  | foo x::xs = x;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

```sml
case "0" of
    "0" => 0
  | "1" => case 0 of _ => 1
  | "2" => 2
  | _ => 3;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

```sml
fun foo a:{s1: int*int, s2: int*int} = s1;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->
