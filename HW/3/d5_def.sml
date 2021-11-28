signature UNARY = sig
  type t
  val zero: t
  val one: t
  val plus : t * t -> t
  val power: t * t -> t
end;
