# assignment 3

* published: ??
* due: ??
* TA in charge: ??
  * email: ??
  * emails subject: safot-hw3
  * email the TA only about personal logistical matters (miluim, etc.)
* questions about the assignment should be asked on [piazza](https://piazza.com/technion.ac.il/spring2022/236319)
* any update to the assignment will appear here on github
* the dry part must be typed, a scan will not be accepted
* the submission should include only the following files: `dry.pdf`, `q1.ml`, `q2.ml`, `q3.ml`, `q4.ml`

## dry

## wet

### intro

* you may write helper functions unless stated otherwise
* you may use any builtin function mentioned in the tutorials
* you may use any function from the modules `Int`, `String` and `Float` (including those not mentioned in the tutorials)
* you may use anything (features, functions, etc.) discussed in tutorials 1-5 and nothing more (unless stated otherwise)
* if you want to use a function defined in the tutorial (that is not a builtin/library function) then define it in your code.

#### project structure

* clone the git repo [safot](https://github.com/CS234319/safot)
* this assignment's root directory is `HW/3/`
* the directory structure is:
  * `sol/` - where your solutions go
  * `tests/` - where your tests go

### exercise 1

in this exercise you'll implement a dictionary in OCaml. a dictionary associates a key with a single value.

1. define the type `dictionary`.
2. define a value `empty` that represents an empty dictionary.
3. implement the function `insert` that takes a dictionary `d`, a key `k` and a value `v` and returns a new dictionary `d'` with the same key-value associations as `d` except `d'` associates `k` with `v`.
4. implement the function `find` that takes a dictionary `d` and a key `k` and returns the value that `d` associates with `k` if one exists and raises `ItemNotPresent` otherwise.
5. implement the function `remove` that takes a dictionary `d` and a key `k` and returns a new dictionary `d'` which associates keys to the same values as `d` except `k` isn't associated to a value. if `k` isn't present in `d` `remove` should raise `ItemNotPresent`.
6. implement the function `get_keys` that takes a dictionary and returns a list of its keys.

    note: each key should appear once

7. implement the function `get_values` that takes a dictionary and returns a list of the values it holds.

    note: the list of values should match the list of keys returned by `get_keys`. that is, given

    ```ocaml
    val values = get_values d;
    val keys = get_keys d;
    ```

    the key at index `i` of `keys` should be associated by `d` with the value at index `i` of `values`.

### exercise 2

you are given a definition of a tree type in `d2.ml`. implement the following **tail-recursive** functions.

1. the function `flatten` takes a tree and returns a preorder traversal of it as a list.

    note: you may assume `List.rev` is tail recursive

2. (bonus) the function `map` takes a tree `t` and a function `f` and applies `f` to all values in `t` and returns the resulting tree.

    **hints**:

    1. a recursive `map` can be implemented as:

        ```ocaml
        let map Empty _ = Empty
          | map (BTree (v, l, r)) f = BTree (f v, map l f, map r f);
        ```

    2. it may help to run a recursive implementation by hand

    3. the `either` type may be useful

        ```ocaml
        type ('a, 'b) either = A of 'a | B of 'b;
        ```

### exercise 3

in this exercise you'll implement simple pattern matching.

you are provided with the definitions of `pattern` and `term` in `d3.ml`.

1. implement `flatten` that takes a list of lists and returns all elements in these lists in a singe list. in other words `flatten` flattens the list.
2. implement `zip` that takes two lists `[x1; x2; ...]` and `[y1; y2; ...]` and returns the list `[(x1, y1); (x2, y2); ...]`. the returned list is of the same length as the shorter list.
3. implement `map2` that takes a function `f` and two lists `[x1; x2; ...]` and `[y1; y2; ...]` and returns the list `[(f x1 y1); (f x2 y2); ...]`. the returned list is of the same length as the shorter list.
4. implement `unique` that takes a list and returns it without duplicate elements.
5. implement `match_` that takes a pattern and a term and returns the terms matching the variables in the pattern. `match_` should return a list where each element is a pair of a variable name and a matching term. each variable should appear exactly once. if the given pattern and term don't match raise `NoMatch`.

### exercise 4

in this exercise you'll implement a bi-directional sequence (hereafter: biseq).

a biseq wraps a sequence and allows going forward or back in it. informally, the biseq caches the sequence's elements so that each element is computed at most once. we call the number of elements a biseq passed its `index` (it starts at `0`).

define the following in `q4.ml`:

1. define the type `biseq` - the type of biseq's
2. define an exception `SeqErr`
3. define the function `make` that takes a sequence and returns the corresponding biseq
4. define the function `prev` that takes a biseq and returns an identical biseq but with its index decremented. if its index is `0` raise `SeqErr`.
5. define the function `next` that takes a biseq and returns an identical biseq but with its index incremented. if its index is at the end of the sequence raise `SeqErr`
6. define the function `curr` that takes a biseq and returns the `index`-th element of the sequence.
7. define the function `empty` that takes a biseq and returns `true` iff its index is at the end of the sequence.
