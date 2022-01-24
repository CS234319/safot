# assignment 1

* published: 1.1.1970 00:00
* due: 1.1.1970 00:00
* TA in charge: X
  * email: x@campus.technion.ac.il
  * email's subject: safot-hw0
  * email the TA only about personal logistical matters (miluim, etc.)
* questions about the assignment should be asked on [piazza](https://piazza.com/technion.ac.il/spring2022/236319)
* any update to the assignment will appear here on github
* the dry part must be typed, a scan will not be accepted
* the submission should include only the following files: `dry.pdf`, `q1.ml`, `q2.ml`, `q3.ml`, `q4.ml`

## dry part

## wet part

### intro

* you may write helper functions unless stated otherwise
* you may use any builtin function mentioned in the tutorials
* you may use any function from the modules `Int`, `String` and `Float` (including those not mentioned in the tutorials)
* you may use anything (features, functions, etc.) discussed in tutorials 1-2 and nothing more (unless stated otherwise)
* if you want to use a function defined in the tutorial (that is not a builtin/library function) then define it in your code.

#### goals

* learn how to use dune
* learn how to structure an OCaml project
* get comfortable with OCaml

#### project structure

* clone the git repo [programming-languages](https://link_to_repo)
* this assignment's root directory is `HW/1/`
* the directory structure is:
  * `sol/` - where your solutions go
  * `tests/` - where your tests go

#### dune

dune is a build system for OCaml. you can read about it [here](https://dune.readthedocs.io/en/stable/), but we'll explain all you'll need to know for this assignment.

* the `dune` files instruct `dune` how to build the project. you don't need to touch those in this assignment.
* `_build/` is where `dune` stores compilation artifacts
* to build your project run `dune build`.
  * you might get some errors - ocaml is usually rather helpful with its error messages. if you still don't understand an error google it or ask us.
  * we've set some warnings to be treated as errors. to read about warnings use `ocamlc -warn-help`.

#### testing

we've provided you with some basic tests for exercises 2-4 named `test2.ml`, `test3.ml`, `test4.ml` respectively. use the same files to write your own tests.

to run all tests use `dune runtests tests`.

#### utop

you can use `utop` to write code and test you solution interactively.

if you want to automatically load you implementation simply use `dune utop`.

### exercise 1

in `sol/q1.ml` write functions `foo1`, `foo2`, ..., `foo8` that match the signatures given in `sol/q1.mli`.

* you can't use any type constraints. the following solution won't be accepted:

    ```ocaml
    let foo2 (t: int*float) -> (_: float -> string) =  t = t;;
    ```

* you can't write functions other than `foo1`, ..., `foo8`
* you can't use constants (namely int, float, string, and boolean literals)

### exercise 2

in `sol/q2.ml` implement `is_balanced` (its signature is in `sol/q2.mli`).

`is_balanced` takes a string and returns `true` if and only if the parentheses in the string are balanced.

for examples see `tests/test2.ml`.

### exercise 3

every function in OCaml takes a single argument and returns a single value.

there are, however, two ways to simulate multiple arguments:

* curried: a function that returns a function. OCaml has syntactic sugar for currying:

    ```ocaml
    let foo x y = x + y;;
    (*is equivalent to*)
    let foo x = fun y -> x + y;;
    ```

* uncurried: a function that takes a tuple where each of its elements is considered an argument

    ```ocaml
    let foo (x, y) = x + y;;
    ```

in this exercise you need to implement two functions:

1. `curry`: takes an uncurried function of 2 arguments and returns an equivalent curried function of 2 arguments
2. `uncurry`: takes a curried function of 2 arguments and returns an equivalent uncurried function of 2 arguments

### exercise 4

in `sol/q4.ml` implement `atoi`.

`atoi` takes a string and returns the integer represented by the string. you may assume the argument is valid. namely, that it is comprised of digits only and there's at least one digit.
