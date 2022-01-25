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
* the submission should include only the following files: `dry.pdf`, `q1.ml`, `q2.ml`, `q3.ml`

## dry part

## wet part

### intro

* you may write helper functions unless stated otherwise
* you may use any builtin function mentioned in the tutorials
* you may use any function from the modules `Int`, `String` and `Float` (including those not mentioned in the tutorials)
* you may use anything (features, functions, etc.) discussed in tutorials 1-4 and nothing more (unless stated otherwise)
* if you want to use a function defined in the tutorial (that is not a builtin/library function) then define it in your code.

#### project structure

* clone the git repo [safot](https://github.com/CS234319/safot)
* this assignment's root directory is `HW/2/`
* the directory structure is:
  * `sol/` - where your solutions go
  * `tests/` - where your tests go

### question 1

1. implement the function `nth: int -> 'a list -> 'a` that takes an index and a list and returns the element in the given index

    ```ocaml
    nth 3 [1; 2; 3; 4];;
    (*- : int = 4*)
    nth 1 [1; 2; 3; 4];;
    (*- : int = 2*)
    ```

2. implement the function `sum_at_indices: int list -> int list -> int` that takes a list of indices `indices` and a list of integers `ns` and returns the sum of the elements of `ns` at the indices in `indices`

    ```ocaml
    sum_at_indices [1; 7; 2] [1;-3;9;6;-35;15;18;0;4];
    (*- : int = 6*)
    sum_at_indices [6; 8; 1] [14;7;15;1;6;3;4;7;2;1;5;13];;
    (*- : int = 13*)
    ```

### question 2

an anagram is a word that is a permutation of an existing word

in this question you are required to implement a function that checks whether a pair of words are case-insensitive anagrams of each other

by case-insensitive anagrams we mean that when ignoring case the words can be considered anagrams

note: the strings in this question are made up of english letters only (namely, a-z and A-Z)

1. implement the function `to_lower: string -> string` that takes a string and returns the same string with all of its characters lower-cased

    ```ocaml
    to_lower "AnaGRam";;
    (*- : string = "anagram"*)
    to_lower "anagram";;
    (*- : string = "anagram"*)
    ```

2. implement the function `count_occurrences: string -> char -> int` that takes a string and a **lower-case** english character and returns the number of occurrences of the character (upper or lower case) in the string

    ```ocaml
    count_occurrences "AnaGRam" 'a';;
    (*- : int = 3*)
    count_occurrences "AnaGRam" 'b';;
    (*- : int = 0*)
    ```

3. implement the function `get_all_occurrences: string -> (char * int) list` that takes a string and returns a list of pairs of a lower-case english character and the number of its (lower or upper case) occurrences in the string

    the returned list should have all (lower-case) english characters in alphabetical order

    ```ocaml
    get_all_occurrences "AnaGRam";;
    (*- : (Char.t * int) list =
    [('a', 3); ('b', 0); ('c', 0); ('d', 0); ('e', 0); ('f', 0); ('g', 1);
    ('h', 0); ('i', 0); ('j', 0); ('l', 0); ('k', 0); ('m', 1); ('n', 1);
    ('o', 0); ('p', 0); ('q', 0); ('r', 1); ('s', 0); ('t', 0); ('u', 0);
    ('v', 0); ('w', 0); ('x', 0); ('y', 0); ('z', 0)]*)
    ```

4. implement the function `are_anagrams: string -> string -> bool` that takes two strings and returns `true` iff they are (case-insensitive) anagrams of each other

    ```ocaml
    are_anagrams "AnaGRam" "maraaNg";;
    (*- : bool = true*)
    ```

### question 3

HILBERT
