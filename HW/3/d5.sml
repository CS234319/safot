use "d2_def.sml";
use "d5_def.sml";

functor Unary (S: ITEM_OR_LIST_OF_ITEMS_AND_LISTS): UNARY = struct
  type t = S.t
  val zero = S.empty
  val one = S.push (S.empty, S.empty)
end;
