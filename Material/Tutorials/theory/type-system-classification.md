# type system classification

---

## sophistication level

<!--vert-->

a type system may:

1. be degenerate (e.g. Prolog)
2. be non-recursive
3. be recursive (e.g. Pascal)
4. have functions as first-class values (e.g. ML)
5. have highly advanced type constructors

---

## orthogonality

<!--vert-->

> a type constructor is **discriminatory** if it cannot be applied to one or more types

example: the array type constructor of Pascal can't be applied to function types

<!--vert-->

> a type is **second-class** if it's discriminated against

---

## strong vs. weak typing

<!--vert-->

a language is **strongly typed** if:

* it is impossible to break the association of a value with its type
* it is impossible to subject a value to an operation unacceptable for its type

examples: Java, Pascal, Python

<!--vert-->

a language is **weakly typed** if it's possible to break the association of a value with its type

examples: Javascript

---

## static vs. dynamic

<!--vert-->

a laguage is **statically typed** if:

* type rules are enforced at compile time
* every variable and every parameter have an associated type

examples: C, Pascal, SML

<!--vert-->

a language is **dynamically typed** if:

* type rules are enforced at runtime
* variables expressions have no associated types
* only values have fixed types

examples: Python, Smalltalk

---

## responsibility

<!--vert-->

> manifest typing - the programmer has to specify types explicitly

examples: Pascal, C

<!--vert-->

> inferred typing - the programmer may leave out type annotations to be inferred

examples: SML, OCaml

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
<!-- .element: data-thebe-executable-javascript data-language="text/x-javascript" -->

<!--vert-->

what will js do?

```javascript
5 * "";
```
<!-- .element: data-thebe-executable-javascript data-language="text/x-javascript" -->

<!--vert-->

what will js do?

```javascript
[] + [];
```
<!-- .element: data-thebe-executable-javascript data-language="text/x-javascript" -->

<!--vert-->

what will js do?

```javascript
5 + [1, ] == 51;
```
<!-- .element: data-thebe-executable-javascript data-language="text/x-javascript" -->
