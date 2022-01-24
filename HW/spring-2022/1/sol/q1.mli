val foo1: 'a -> 'b -> ('a * 'b -> 'b) -> 'b

val foo2: int * float -> (float -> string) -> bool

val foo3: ('a -> 'b -> 'c) -> 'a -> 'b -> 'd -> 'c

val foo4: 'a -> 'b -> int -> int -> int

val foo5: ('a -> 'b) -> 'a -> ('b * 'b -> 'c) -> 'c

val foo6: unit -> unit -> unit

val foo7: 'a -> 'a * 'a -> 'a

val foo8: int * (string * string) -> int * string * string