# Lexical and Dynamic Scoping

---

### lexical scoping

> ~definition: TODO

the environment is defined by static code structure

<!--vert-->

### lexical scoping - example

TODO

```rust
int main
```

---

### dynamic scoping

> ~definition: TODO

the environment is defined by calls

<!--vert-->

### dyanmic scoping - example

TODO

<!--vert-->

* local bindings are represented by a dictionary
* dictionary maps names to entities

<!--vert-->

### dynamic scoping - environment

* the environment is represented by a back-pointer to the most recent stack frame
* basically a stack of dictionaries
* search for a name is carried out by searching in the stack of dictionaries

---

### question 1

write a program that prints "DYN" if the language uses dynamic scoping and "LEX" if it uses lexical scoping.

```cpp
...
```

<!--vert-->

```cpp
bool x = false;

bool foo() { return x; }

int main() {
    bool x = true;
    if (foo()) {
        printf("DYN");
    } else {
        printf("LEX");
    }
}
```

<!--vert-->

### question 2

can a language with static typing use dynamic scoping?

<!--vert-->

TODO: answer
