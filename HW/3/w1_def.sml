signature S1 = sig
  exception ItemNotPresent
  type ('a, 'b) dictionary
  val empty : ('a, 'b) dictionary
  val insert : (''a, 'b) dictionary -> ''a -> 'b -> (''a, 'b) dictionary
  val find : (''a, 'b) dictionary -> ''a -> 'b
  val remove : (''a, 'b) dictionary -> ''a -> (''a, 'b) dictionary
  val get_keys : ('a, 'b) dictionary -> 'a list
  val get_values : ('a, 'b) dictionary -> 'b list
end;
