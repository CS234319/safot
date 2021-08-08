# Standard ML

## introduction

---

### loading and Saving

* interpreter
* first prompt (-) and secondary prompt (=)
* semicolon terminated

```text
Standard ML of New Jersey v110.79 [built: Sat Oct 26 12:27:04 2019]
- 5 + 5;
val it = 10 : int
```

---vert---

* create a file named `myfile.sml`
* start ML and

    ```sml
    use "c:\\myfile.sml";
    ```

* or redirect the input and output

    ```bash
    sml < myfile.sml > output
    ```

---

### a simple tutorial

* ML is usually used as an interpreter (a compiler is also available)
* expressions followed by a semicolon yield a response

    ```sml
    2 + 2;
    ```
    <!-- .element: data-thebe-executable -->

* doing simple arithmetic

    ```sml
    3.2 - 2.3;
    ```
    <!-- .element: data-thebe-executable -->

---

### declaring constants

---vert---

naming constants

```sml
val seconds = 60;
```
<!-- .element: data-thebe-executable -->

---vert---

using names in expressions

```sml
val minutes = 60;

val hours = 24;

seconds * minutes * hours;
```
<!-- .element: data-thebe-executable -->

---vert---

the identifier `it`

```sml
seconds * minutes * hours;

it div 24;

val secs_in_hour = it;
```
<!-- .element: data-thebe-executable -->

---

### legal names

---vert---

### alphabetic names

* begins with a letter
* followed by letters, digits, underscore, or single quotes
* case sensitive

```sml
x
x'
uB40
hamlet_prince_of_denmark
h''3_H
```

---vert---

### symbolic names

* permitted over the characters:

    ```sml
    ! % & $ # + - * / : < = > ? @ \ ~ \ ^ |
    ```

* should not be one of:

    ```sml
    : _ | = => -> #
    ```

* allowed wherever an alphabetic name is
* try to avoid using it

```sml
val +-+-+ = 1415;
```
<!-- .element: data-thebe-executable -->

---

### ML keywords

`abstype` | `and` | `andalso` | `as` | `case` | `datatype` | `do` | `else` | `end |` `eqtype` | `exception` | `fn` | `fun` | `functor` | `handle` | `if` | `in |` `include` | `infix` | `infixr` | `let` | `local` | `nonfix` | `of` | `op` | `open |` `orelse` | `raise` | `rec` | `sharing` | `sig` | `signature` | `struct |` `structure` | `then` | `type` | `val` | `while` | `with` | `withtype`

---

### ML Primitive Types

`int`, `real`, `string`, `char`, `bool`, `unit`

---

### int

* constants
  * sequence of digits
    * 0
    * 01234
  * `~` for a unary minus sign
    * `~23`
    * `~85601435654638`
* infix operations: `+` `-` `*` `div` `mod`

---vert---

* conventional precedence (parenthesis can be dropped without change of meaning)

    ```sml
    (((m * n) * l) - (m div j)) + j
    ```

---

### real

* constants
  * decimal point
    * `0.01`
    * `2.718281828`
  * e notation
    * `7E~5`
    * `~1.2E12`
    * `~123.4E~2` is the same as `~1.234`
* infix operators: `+` `-` `*` `/`

---vert---

* functions
  * `floor(r)` converts `real` to `int`
  * `real(i)` converts `int` to `real`
  * `sqrt`, `sin`, `cos`, `tan`, `exp`, `ln` all of type `real->real`
  * all need the `Math.` prefix: `Math.sqrt`

---

### strings

---vert---

constants are written in double quotes

```sml
"ML is the best";
```
<!-- .element: data-thebe-executable -->

special characters `\n`, `\t`, `\"`, `\\`

---vert---

concatenation

```sml
"Standard" ^ " ML";
```
<!-- .element: data-thebe-executable -->

---vert---

comparison

```sml
"abc" < "cba";

"zzz" > "aaa";
```
<!-- .element: data-thebe-executable -->

---vert---

`size` returns the number of characters

```sml
size "SML";
```
<!-- .element: data-thebe-executable -->

---

### characters

---vert---

chars are distinguished from strings of length 1 by `#`

```sml
"0";

#"0";
```
<!-- .element: data-thebe-executable -->

---vert---

conversion between strings and chars

```sml
str #"0";

String.sub("hello", 0);
```
<!-- .element: data-thebe-executable -->

---vert---

conversion between chars and ASCII

```sml
ord #"0";

chr it;
```
<!-- .element: data-thebe-executable -->

---

### boolean

the two values are

```sml
true;

false;
```
<!-- .element: data-thebe-executable -->

---

### tuples - cartesian product type

* the n-tuple whose components are `x1`, ..., `xn`:

    ```sml
    (x1, x2, ..., xn)
    ```

* the components can be of any type, including tuples

```sml
val a = (1.5, 6.8);

(1, 1.5);

("str",1,true,(#"0",0.1));
```
<!-- .element: data-thebe-executable -->

---

### records

* records have components (fields) identified by name

    ```sml
    val me = { name="Ofir", age=30 };
    ```
    <!-- .element: data-thebe-executable -->

* type lists each field as `label : type`
* enclosed in braces `{...}`

---vert---

* selecting a field

    ```sml
    #name me;
    ```
    <!-- .element: data-thebe-executable -->

* tuples **can be seen as** records with numbers as implicit field labels

    ```sml
    #2 ("one", "two", "three");
    ```
    <!-- .element: data-thebe-executable -->

* note that the numbering starts with 1

---

### lists

* a list is a finite sequence of elements

    ```sml
    [3, 5, 9];
    ["a", "list"];
    [];
    ```
    <!-- .element: data-thebe-executable -->

* elements may appear more than once

    ```sml
    [3,4,3];
    ```
    <!-- .element: data-thebe-executable -->

* elements may have any type but all elements must have the same type

    ```sml
    [(1, "one"), (2, "two")] : (int*string) list
    [[3.1], [], [5.7, ~0.6]] : (real list) list
    ```
    <!-- .element: data-thebe-executable -->

---

### mapping - functions

```sml
fun sq(x: int) = x*x;
```
<!-- .element: data-thebe-executable -->

* keyword `fun` starts the function declaration
* `sq` is the function name
* `x:int` is the formal parameter with type constraint
* `x*x` is the body and it is an **expression**

---vert---

* the result of the function is the result of evaluating the **expression** of the function body with the actual parameter
* `int->int` is the standard mathematical notation for a function type that takes an integer and returns an integer

---

### applying a function

* simple function call

    ```sml
    (sq 3);
    ```
    <!-- .element: data-thebe-executable -->

* when a function is called the parameter is evaluated and then passed to the function

    ```sml
    sq (sq 3);
    ```
    <!-- .element: data-thebe-executable -->

* the parentheses are optional

    ```sml
    sq 3;
    ```
    <!-- .element: data-thebe-executable -->

---vert---

* parentheses are also optional in function definitions

    ```sml
    fun sq x:int = x*x;
    ```
    <!-- .element: data-thebe-executable -->

---

### arguments and results

* every function has one argument and one result
* any type can be passed/returned!!!
* tuples are used to pass/return several arguments

```sml
val a = (3.0, 4.0);

fun lengthvec (x:real, y:real) = Math.sqrt(x*x + y*y);

lengthvec a;

lengthvec (5.0, 12.0);
```
<!-- .element: data-thebe-executable -->

---

### functions as values

* anonymous functions with `fn` notation

    ```sml
    fn x:int => x*x;

    it 3;
    ```
    <!-- .element: data-thebe-executable -->

* the following declarations are identical

    ```sml
    fun sq x:int = x*x;
    val sq = fn x:int => x*x;
    ```
    <!-- .element: data-thebe-executable -->

---

### returning functions

* functions can also be __returned__ from other functions

    ```sml
    fun inttwice(f: (int->int)) =
        fn x => f (f x);
    ```
    <!-- .element: data-thebe-executable -->

* the arrow is right associative so the type of `inttwice` is equivalent to:

    ```sml
    val inttwice = fn : (int -> int) -> (int -> int)
    ```

* example

    ```sml
    inttwice (fn x => x*x);

    it 3;
    ```
    <!-- .element: data-thebe-executable -->

---

### type inference

* ML deduces the types in expressions
* type checking the function:

    ```sml
    fun facti (n, p) =
        if n=0 then p else facti (n-1, n*p);
    (*val facti = fn : int * int -> int*)
    ```
    <!-- .element: data-thebe-executable -->

  * constants `0` and `1` have type `int`.</span>
  * therefore `n=0` and `n-1` involve integers so `n` has type `int`</span>
  * `n*p` must be integer multiplication, so `p` has type `int`</span>
  * `facti` returns type `int`</span>

---

### type constraints

* certain functions are overloaded, e.g. `abs`, `+`, `-`, `~`, `*`, `<`
* the type of an overloaded function is determined from context, or is set to `int` by default
* types can be stated explicitly

---
<!-- .slide: data-background-iframe="http://localhost:8888/notebooks/tut2-type_constraints.ipynb" data-background-interactive -->

---

### polymorphic type checking

|                           |        | flexibility | security |
|:-------------------------:|:------:|:-----------:|:--------:|
|        weakly typed       |  lisp  |      ✔      |          |
|       strongly typed      | Pascal |             |     ✔    |
| polymorphic type checking |   ML   |      ✔      |     ✔    |

and in ML most types are deduced automatically 😎

---

### polymorphic function definitions

* an object is polymorphic if it can be regarded as having any kind of type
* If type inference leaves some types completely unconstrained then the definition is polymorphic
* A polymorphic type contains a type variable, e.g. 'a, 'b

```sml
fun pairself x = (x, x);

pairself 4.0;

fun pair (x,y) = (y,x);
```
<!-- .element: data-thebe-executable -->

---

### functions as values - the polymorphic case

---vert---
<!-- .slide: data-background-iframe="http://localhost:8888/notebooks/tut2-functions-polymorphic.ipynb" data-background-interactive -->

---vert---

* sometimes ML gives us a hard time when we give a polymorphic value to a polymorphic function.

    ```sml
    fun twice f = fn x => f (f x);
    fun ident x = x;
    twice ident;
    ```
    <!-- .element: data-thebe-executable -->

* you usually may ignore it. or use a workaround:

    ```sml
    fn x => (twice ident) (x);
    ```
    <!-- .element: data-thebe-executable -->

---

### functional vs. imperative

* imperative - using commands to change the state
* functional - stateless. using expressions recursively to calculate the result
* example: Euclid's algorithm for the Greatest Common Divisor (GCD) of two natural numbers:

`$$gcd(m,n) = \begin{cases}n,\;m = 0&\\gcd(n\;mod\;m,m), \;m>0\end{cases}$$`

---vert---

### GCD - Pascal vs. ML

* an imperative Pascal program:

    ```pascal
    function gcd(m,n: integer): integer;
    var prevm: integer;
    begin
        while m<>0 do begin
            prevm := m;
            m := n mod m;
            n := prevm
        end;
        gcd := n
    end;
    ```

* a functional program in Standard ML:

    ```sml
    fun gcd(m,n) =
        if m=0 then n else gcd(n mod m, m);
    ```

* which one is more efficient? 🧐
