# OCaml

## modules

---

a module is a collection of bindings

```ocaml
module MyModule = struct
    (*bindings*)
end
```

<!--vert-->

a module can contain any kind of binding

```ocaml
module MyModule = struct
    let answer = 42
    exception Failure of int
    type key = int
end;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

outside a module refer to a binding from another module by:

```ocaml
MyModule.answer;;
(*- : int = 42*)
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

a file `foo.ml` implicitly defines a module `Foo` as if its contents are surrounded by:

```ocaml
module Foo = struct
    (*the contents of foo.ml*)
end
```

<!--vert-->

```ocaml
open MyModule;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

* used to get direct access to the bindings of a module
* considered bad style

---

### local `open`

```ocaml
let word, idx = "OCaml", 2;;

String.sub word idx ((String.length word) - idx);;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

can be rewritten as:

```ocaml
let open String in
sub word idx ((length word) - idx);;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

and there's a more concise syntax

```ocaml
String.(sub word idx ((length word) - idx));;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

the general syntax is:

```ocaml
let open Module in
expr;;
```

or

```ocaml
Module.(expr);;
```
