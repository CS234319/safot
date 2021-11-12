# Standard ML

## modules

---

a structure is a collection of bindings

```sml
structure MyModule = struct
    (*bindings*)
end
```

<!--vert-->

a module can contain any kind of binding

```sml
structure MyModule = struct
    val answer = 42
    exception Failure of int
    type key = int
    fun foo x = x
end;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

outside a module refer to a binding from another module by:

```sml
MyModule.answer;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

```sml
open MyModule;
answer;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

* used to get direct access to the bindings of a module
* considered bad style

---

### signatures

a signature is a type for a module

```sml
signature SIGNAME = sig
    (*types for bindings*)
end

structure ModuleName :> SIGNAME = struct
    (*bindings*)
end
```

<!--vert-->

```sml
signature MATHLIB = sig
    val pi: real
    val deg2rad: real -> real
end;

structure MathLib :> MATHLIB = struct
    val pi = 3.14
    fun deg2rad x = x / 180.0 * pi
end;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

a module will not type-check unless it matches the signature

```sml
signature CONSTANTS = sig
    val pi: real
    val e: real
end;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

```sml
structure MathConstants :> CONSTANTS = struct
    val pi = 3.14
end; (*ERROR*)
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

```sml
structure MathConstants :> CONSTANTS = struct
    val pi = 3
    val e = 2.71
end; (*ERROR*)
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

---

### signature matching

```sml
structure Foo :> BAR
```

* every type in `BAR` is provided in `Foo` as specified
* every val binding in `BAR` is provided in `Foo`
* every exception in `BAR` is provided in `Foo`
* `Foo` can have more bindings than specified by `BAR`

---

### functors

a functor is a parameterized module

```sml
functor Functor (Module: SIG) =
  struct
    (*bindings*)
  end;
```

<!--vert-->

applying a functor

```sml
structure FModule = Functor(Module);
```

<!--vert-->

```sml
signature ORDERED_TYPE = sig
  type t
  val compare: t * t -> order
end;

structure Int' = struct
  type t = int
  val compare = Int.compare
end;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

```sml
functor SortedList (Elt: ORDERED_TYPE) = struct
  fun add x [] = [x]
    | add x (hd :: tl) = case Elt.compare (x, hd) of
        EQUAL => hd::tl
      | LESS => x :: hd :: tl
      | GREATER => hd :: (add x tl)
  (*more functions*)
end;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

```sml
structure SortedIntList = SortedList(Int');

open SortedIntList;
add 5 (add 6 (add 2 (add 4 (add 3 (add 1 [])))));
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

```sml
structure SortedStringList = SortedList(struct
  type t = string
  val compare = String.compare
end);
open SortedStringList;
add "abc" (add "hij" (add "efg" (add "nop" (add "klm" []))));
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->
