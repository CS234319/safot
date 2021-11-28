signature S_EXPRESSION = sig
  type t (* New abstract data type *)
  eqtype symbol (* Built upon symbols *)
  exception DestructionOfAtom (* When should it be raised? *)
  val leaf: symbol -> t
  val cons: t * t -> t
  val car: t -> t
  val cdr: t -> t
  val atom: t -> bool
  val eq: t * t -> bool
  val T: t
  val NIL: t
end;

signature ITEM_OR_LIST_OF_ITEMS_AND_LISTS = sig
  type t
  type symbol
  exception Empty
  exception NotAList
  val empty: t
  val vacuous: t -> bool (* A single item is not vacous *)
  val item: symbol -> t (* Create an item *)
  val push: t * t -> t (* Adds the first argument to the list represented by
    the second; Raises an exception if an item is treated as a list *)
  val head: t -> t (* Raises an exception if argument is an item or an empty list *)
  val tail: t -> t (* Raises an exception if argument is an item or an empty list *)
end;

signature TREE = sig
  type t
  type symbol
  exception DestructionOfLeaf
  exception NoNext
  val leaf: symbol -> t
  val add_child: t * t -> t (*add_child (child, tree) :: adds child as tree's first child*)
  val tree: t -> t (*tree c :: creates a tree with a single node c*)
  val first_child: t -> t
  val next_sibling: t -> t
end;
