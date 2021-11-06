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
