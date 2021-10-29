# Structural Typing

---

## structural equivalence

> types $T$ and $R$ are structurally equivalent if they share all their "features" (up to structural equivalence)

where "feature" =

* field
* method
* ...

<!--vert-->

```cpp
struct A { int x; };
struct B { int x; };
struct C { A x; };
struct D { B x; };
```

* `A` and `B` are structurally equivalent
* `C` and `D` are structurally equivalent

<!--vert-->

### records in standard ML

```sml
fun foo {x=x, y=_} = x;
```

---

## structural subtyping

> type $T$ is a *structural subtype* of type $R$ if $T$ has every "feature" $R$ has

<!--vert-->

`Student` is a structural subtype of `Person`

```cpp
struct Person {
    string name;
    int id;
};
struct Student {
    string name;
    int id;
    string department;
};
```

NOTE: note that structural subtyping is implicit

<!--vert-->

### interfaces in go

```go
type animal interface {
    speak() string
}
type dog struct {
    name string
}
func (d dog) speak() string {
    return "woof"
}
```

`dog` is a subtype of `animal`

NOTE: note that `dog` doesn't explicitly implement `animal`

<!--vert-->

### (TODO)

```go
type robot struct {
    serial int
}
func (r robot) speak() string {
    return "hello human"
}
```

now `robot` is a subtype of `animal`
