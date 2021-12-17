datatype pattern = Wildcard | Variable of string | PAtom of string | PTuple of pattern list;
datatype term = Atom of string | Tuple of term list;
exception NoMatch;

signature S3 = sig
  val flatten : 'a list list -> 'a list
  val zip : 'a list -> 'b list -> ('a * 'b) list
  val unique : ''a list -> ''a list
  val match : pattern -> term -> (string * term) list
end;
