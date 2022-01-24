type pattern = Wildcard | Variable of string | PAtom of string | PTuple of pattern list
type term = Atom of string | Tuple of term list
exception NoMatch
