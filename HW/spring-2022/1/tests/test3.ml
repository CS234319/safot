open Sol

let () = assert (Q3.curry (Q3.uncurry ( + )) 5 3 = 8)
