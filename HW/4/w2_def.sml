structure AST = struct
  datatype t = List of t list | Atom of string;
end;

structure S_Expression = struct
  datatype t = Atom of string | Cons of t * t;
end;

signature A_LIST = sig
  type t
  val make: unit -> t
  val insert: t -> string -> S_Expression.t -> t
  val find: t -> string -> S_Expression.t option
end;

structure A_List: A_LIST = struct
  type t = (string, S_Expression.t) HashTable.hash_table;
  exception Undefined;
  fun make () = HashTable.mkTable (HashString.hashString, op=) (10, Undefined);
  fun insert l s e = let
        val l = HashTable.copy l
      in
        HashTable.insert l (s, e);
        l
      end;
  fun find l s = HashTable.find l s;
end;

signature S2 = sig
  datatype error = Undefined | NotAPair | WrongNumberOfArguments | NotAFunction
  exception Error of error
  val eval: A_List.t -> AST.t -> S_Expression.t
end;
