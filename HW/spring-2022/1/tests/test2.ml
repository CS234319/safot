open Sol

let () = assert (Q2.is_balanced "")

let () = assert (Q2.is_balanced "(()())")

let () = assert (not (Q2.is_balanced "(()"))
