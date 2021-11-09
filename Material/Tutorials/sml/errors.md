# Standard ML

## errors

---

```sml
fun foo x y = x + y;

foo 5 -4;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

NOTE: we use `-` and not `~` for negation. actually, ML reads this as `(foo 5) - 4`, so that's why this error is there

<!--vert-->

```sml
fun foo x y = x + y;
fun bar (x, y) = x * y;

foo 2 bar(1, 2);
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

NOTE: curried function application is greedy - ML reads this as 3 arguments for `foo`, and you can't pass `bar` as the second argument to `foo` - that's a type error 

<!--vert-->

```sml
fun foo [] = 0
  | foo x::xs = x;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

NOTE: parentheses - needs to be `(x::xs)`. ML considers this to be a triple of `x`, `::`, `xs` and complains about being given a tuple and not a list.

<!--vert-->

```sml
case "0" of
    "0" => 0
  | "1" => case 0 of _ => 1
  | "2" => 2
  | _ => 3;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

NOTE: parentheses - the inner `case` needs to be `(case 0 of _ => 1)`. also notice that the error is a type error, but it's not to be handled as a type error. ML reads the `"2"` and later `_` case as belonging to the second case and not the first one. 

<!--vert-->

```sml
fun foo (a: {x: int, y: int}) = x;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

NOTE: `x` is not a field. it's part of the type of `a`. the correct way is `#x a`.

<!--vert-->

```sml
type A = {x: int, y: int};
fun foo a = #s1 a;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

NOTE: ML cannot do type inferrence to deduce the entire type of `a`, so it results in an error. ML cannot do partial type inferrence.


<!--vert-->

```sml
Math.pow(2.0, 3.0) - 1;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

NOTE: type mismatch. `pow` returns `real`.

<!--vert-->

```sml
fun f x = Math.sqrt x;
if (f 9.0 = f 9.0) then 1 else 0;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

NOTE: `real` is a not a polymorphic equality type - cannot compare `real`s. this is a type error because in ML types that are able to be compared using `=` are denoted by `''a`, and `real` is `'a` but not `''a`.

<!--vert-->

```sml
fun f g x = if g = g then g x else 0;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

NOTE: ditto. `g` is a function (actually, `'a -> int`) and functions are not polymorphic equality types. however, since it is first used in a comparison and only then as a function, the error will be reported in the function application and not in the equality. it actually concludes it cannot be a function, rather than concluding it cannot be a polyEqual type.

<!--vert-->

```sml
fun f (a:{s: int, r: int}) = {s: (#s a), r: (#r a)};
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

NOTE: `:` denotes type, we need to use `=` in the returned expression to denote a value. another common error: `{{(#s a), (#r a)}`

<!--vert-->

```sml
fun f a:{s: int, r: int} = {s = (#s a), r = (#r a)};
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

NOTE: the type here in the constraint binds to the function - `f`, rather than to `a`, like it may seem. this apparently should not cause an issue, because that is the actual type we are returning, however, it does leave `a` without a precise type constraint and this is a problem because like before, ML cannot do partial type inferrence and it cannot conclude the exact type for `a`, just some of its fields.

<!--vert-->

```sml
local
fun rec (a, _, 0) = a | rec (a, b, n) = rec (a+b, a, n-1)
in
fun fib n = rec (1, 1, n)
end;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

NOTE: `rec` is a keyword...

<!--vert-->

```sml
val x = (1 = 1) and (2 = 2);
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

NOTE: `andalso` is logical AND and not `and`. also, `orelse` and not `or`

<!--vert-->

```sml
val x = "Elad\n";
fun f () = print ("My name is " ^ x);
val x = "Yair\n";
f (); 
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

NOTE: functions freeze the values they refer to, and do not get updated when the identifier is reused.

<!--vert-->

```sml
Math.pow(2.0, 3.0);
floor(it) = 8;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

NOTE: this specifically came up in the home ex. terribly annoying floating-point arithmetic error. when doing integer arithmetic, implement manually with a recursive function.

<!--vert-->

```sml
fun a() = b() and fun b() = a()
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

NOTE: we don't repeat the `fun` keyword after `and`. ditto for `val`, `datatype`.
  
