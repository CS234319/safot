datatype 'a btree = empty | btree of 'a * 'a btree * 'a btree;

signature S2 = sig
  val map : 'a btree -> ('a -> 'b) -> 'b btree
  val flatten : 'a btree -> 'a list
  val unfold : ('b -> ('a * 'b * 'b) option) -> 'b -> 'a btree
end;
