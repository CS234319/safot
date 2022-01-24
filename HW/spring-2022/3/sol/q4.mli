type 'a biseq
exception SeqErr
val make: 'a Seq.t -> 'a biseq
val prev: 'a biseq -> 'a biseq
val next: 'a biseq -> 'a biseq
val curr: 'a biseq -> 'a
val empty: 'a biseq -> bool
