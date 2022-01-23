exception ItemNotPresent

module type S1 = sig
  type ('k, 'v) dictionary
  val empty: ('k, 'v) dictionary
  val insert: ('k, 'v) dictionary -> 'k -> 'v -> ('k, 'v) dictionary
  val find: ('k, 'v) dictionary -> 'k -> 'v
  val remove: ('k, 'v) dictionary -> 'k -> ('k, 'v) dictionary
  val get_keys: ('k, 'v) dictionary -> 'k list
  val get_values: ('k, 'v) dictionary -> 'v list
end