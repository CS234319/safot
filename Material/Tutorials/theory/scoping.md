# Lexical and Dynamic Scoping

---

### lexical scoping

* if `g` is defined in `f` then `g` inherits `f`'s bindings
* the environment is defined by static code structure
* what you see in most PLs (C, C++, SML, Java, ...)

<!--vert-->

#### example

[playground](https://play.rust-lang.org/?version=stable&mode=debug&edition=2018&code=fn%20main()%20%7B%0A%20%20%20%20let%20x%20%3D%20%22A%22%3B%0A%20%20%20%20let%20foo%20%3D%20%7C%7C%20x%3B%0A%20%20%20%20let%20bar%20%3D%20%7C%7C%20%7B%0A%20%20%20%20%20%20%20%20let%20x%20%3D%20%22B%22%3B%0A%20%20%20%20%20%20%20%20foo()%0A%20%20%20%20%7D%3B%0A%20%20%20%20println!(%22x%20%3D%20%7B%7D%22%2C%20bar())%3B%0A%7D)

```rust
fn main() {
    let x = "A";
    let foo = || x;
    let bar = || {
        let x = "B";
        foo()
    };
    println!("x = {}", bar());
}
```

prints `x = "A"`

---

### dynamic scoping

* if `f` calls `g` then `g` inherits `f`'s bindings
* the environment is defined by calls
* the scope of bindings is determined dynamically

<!--vert-->

#### example

```lisp
(set 'x '10)

(defun foo (x) (bar))

(defun bar () (print x))

(foo '5)
; 5
```

note that `5` is printed and not `10`

<!--vert-->

#### representation

* local bindings are represented by a dictionary
* dictionary maps names to entities

<!--vert-->

* the environment is represented by a back-pointer to the most recent stack frame
* basically a stack of dictionaries
* search for a name is carried out by searching in the stack of dictionaries

---

### question 1

write a program that prints "DYN" if the language uses dynamic scoping and "LEX" if it uses lexical scoping.

```cpp
...
```
<!-- .element: data-codeblock-editable data-language="C" -->

<!--vert-->

```cpp
const char *x = "LEX";

const char *foo() { return x; }

int main() {
    const char *x = "DYN";
    printf(foo());
}
```

<!--vert-->

### question 2

can a language with static typing use dynamic scoping?

<!--vert-->

answer - it's possible but **very** awkward making it an unlikely combination

```sml
fun foo () = x;
fun bar () = x + 5;
fun baz (x: float) = bar ();
```

* what's the type of `foo`?
* what's the type of `bar`?
* should `baz` pass typechecking?
