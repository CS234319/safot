open D3

val flatten : 'a list list -> 'a list
val zip : 'a list -> 'b list -> ('a * 'b) list
val map2 : ('a -> 'b -> 'c) -> 'a list -> 'b list -> 'c list
val unique : 'a list -> 'a list
val match_ : pattern -> term -> (string * term) list