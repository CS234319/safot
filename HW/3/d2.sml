use "d2_def.sml";

functor Tree (S: ITEM_OR_LIST_OF_ITEMS_AND_LISTS) : TREE = struct end;

functor ListOfLists (S: S_EXPRESSION) : ITEM_OR_LIST_OF_ITEMS_AND_LISTS = struct end;

structure S_Expression : S_EXPRESSION = struct end;
