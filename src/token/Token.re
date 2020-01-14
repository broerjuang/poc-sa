type t = string;
let make =
  fun
  | "" => Relude.Result.error("Token is empty")
  | t => Relude.Result.ok(t);
