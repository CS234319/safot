# assignment 3

* published: 27.11.2021
* due: 18.12.2021 23:59
* TA in charge: Yair Twito
  * email: twyair@campus.technion.ac.il
  * emails subject: safot-hw3
  * email the TA only about personal logistical matters (miluim, etc.)
* questions about the assignment should be asked on [piazza](https://piazza.com/technion.ac.il/winter2022/236319)
* any update to the assignment will appear here on github
* the dry part must be typed, a scan will not be accepted
* the submission should include only the following files: `dry.pdf` `wet1.sml`

## dry

### question 1

## wet

* unless stated otherwise you may only use material from tutorials 1-6
* the solution to exercise `N` should be in `wetN.sml`

### exercise 1

in this exercise you'll implement a dictionary in SML. a dictionary associates a key with a single value.

#### A

write a datatype definition for `('a, 'b) dictionary`.

define a value `dictionary_empty` that represents an empty dictionary.

```sml
val dictionary_empty = _ : ('a, 'b) dictionary
```

#### B

implement the function `insert` that takes a dictionary `d`, a key `k` and a value `v` and returns a new dictionary `d'` with the same key-value associations as `d` except `d'` associates `k` with `v`.

```sml
val insert = fn : (''a, 'b) dictionary -> ''a -> 'b -> (''a, 'b) dictionary
```

#### C

put the following definition in `w1.sml`:

```sml
exception ItemNotPresent;
```

implement the function `find` that takes a dictionary `d` and a key `k` and returns the value that `d` associates with `k` if one exists and raises `ItemNotPresent` otherwise.

```sml
val find = fn : (''a, 'b) dictionary -> ''a -> 'b
```

#### D

implement the function `remove` that takes a dictionary `d` and a key `k` and returns a new dictionary `d'` which associates keys to the same values as `d` except `k` isn't associated to a value. if `k` isn't present in `d` `remove` should raise `ItemNotPresent`.

```sml
val remove = fn : (''a, 'b) dictionary -> ''a -> (''a, 'b)
```

#### E

implement the function `get_keys` that takes a dictionary and returns a list of its keys.

```sml
val get_keys = fn : ('a, 'b) dictionary -> 'a list
```

note: each key should appear once

#### F

implement the function `get_values` that takes a dictionary and returns a list of the values it holds.

```sml
val get_values = fn : ('a, 'b) dictionary -> 'b list
```

note: the list of values should match the list of keys returned by `get_keys`. that is, given

    ```sml
    val values = get_values d;
    val keys = get_keys d;
    ```

the key at index `i` of `keys` should be associated by `d` to the value at index `i` of `values`.