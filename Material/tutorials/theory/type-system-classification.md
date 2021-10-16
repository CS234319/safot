# type system classification

---

## existence

TODO: delete this section?

<!--vert-->

a language is typed when:

* the set of values can be broken into sets
* each set has uniform behavior under the same operation

examples: C, ML, Java, Python

<!--vert-->

a language is untyped when:

* each value has its own unique set of permissible operations and their semantics are particular to the value

examples: assembly, prolog

---

## sophistication level

<!--vert-->

a type system may:

1. not exist (e.g. assembly)
2. be degenerate (e.g. TODO)
3. be non-recursive (e.g. TODO)
4. be recursive (e.g. Pascal)
5. have function as first-class values (e.g. TODO)
6. have highly advanced type constructors (e.g. TODO)

---

## orthogonality

<!--vert-->

> a type constructor is discriminatory if it cannot be applied to one or more types

example: the array type constructor of Pascal can't be applied to function types

<!--vert-->

> a type is second-class if it's discriminated against

---

## strong vs. weak typing

<!--vert-->

TODO

---

## static vs. dynamic

<!--vert-->

TODO

---

## responsibility

<!--vert-->

> manifest typing - the programmer has to specify types explicitly

examples: Pascal, C

<!--vert-->

> inferred typing - the programmer may leave out type annotations to be inferred

examples: SML, OCaml

<!--vert-->

> semi-implicit typing - (TODO: remove?)

---

## javascript

<!--vert--->

javascript is:

* dynamically typed
* weakly typed

<!--vert-->

certain operations in javascript coerce the operands to make the operation succeed

how bad can it get?

<!--vert-->

what will js do?

```javascript
5 + "10";
```
<!-- .element: data-thebe-executable-javascript -->

<!--vert-->

what will js do?

```javascript
5 * "";
```
<!-- .element: data-thebe-executable-javascript -->

<!--vert-->

what will js do?

```javascript
[] + [];
```
<!-- .element: data-thebe-executable-javascript -->

<!--vert-->

what will js do?

```javascript
5 + [1, ] == 51;
```
<!-- .element: data-thebe-executable-javascript -->
