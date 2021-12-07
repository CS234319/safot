datatype 'a seq = Nil | Cons of 'a * (unit -> 'a seq);

signature S2 = sig
  exception SeqErr
  type 'a biseq
  val new : 'a seq -> 'a biseq
  val prev : 'a biseq -> 'a biseq
  val next : 'a biseq -> 'a biseq
  val curr : 'a biseq -> 'a
  val empty : 'a biseq -> bool
end;