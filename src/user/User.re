type t = {
  email: Primitives.Email.t,
  name: string,
  shortName: string,
};

type view = {
  email: Primitives.Email.t,
  name: string,
  shortName: string,
};

let make = (~email, ~name, ~shortName): option(t) =>
  Some({email, name, shortName});

let view = (t: t) => {email: t.email, name: t.name, shortName: t.shortName};

let storeCred = dispatch => {
  Api.storeCred(~username="juang", ~token="lala")
  |> Js.Promise.then_(_ => dispatch(`Increment) |> Js.Promise.resolve)
  |> Js.Promise.catch(_ => dispatch(`Decrement) |> Js.Promise.resolve)
  |> ignore;

  None;
};
