use "w3.sml";
use "utils.sml";

open W3;

assert (flatten [[1, 2], [], [3]] = [1, 2, 3]);

assert (zip [1, 2, 3] ["a", "b", "c"] = [(1, "a"), (2, "b"), (3, "c")]);

assert (zip [1, 2, ] ["a", "b", "c"] = [(1, "a"), (2, "b")]);

assert (match (PTuple[Variable "x", Variable "y"]) (Tuple[Atom "s", Atom "t"]) = [("x",Atom "s"),("y",Atom "t")]);
