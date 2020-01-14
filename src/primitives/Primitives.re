module Result =
  Relude.Result.WithError({
    type t = [
      | `DecoderError(Decco.decodeError)
      | `EmailIsInvalid
      | `EmailCannotBeEmpty
    ];
  });

module type EMAIL = {
  type t;
  let make: string => Result.t(t);
  let encode: t => Js.Json.t;
  let decode: Js.Json.t => Result.t(t);
};



module Email: EMAIL with type t = string = {
  [@decco]
  type t = string;

  let make = email => {
    /* it only checks whether the email field has @ or not */
    let emailRegex = [%bs.re {|/.*@.*\..+/|}];
    switch (email) {
    | "" => Relude.Result.error(`EmailCannotBeEmpty)
    | email when !Js.Re.test_(emailRegex, email) =>
      Relude.Result.error(`EmailIsInvalid)
    | email => Relude.Result.ok(email)
    };
  };

  let encode = t_encode;
  let decode = t => {
    switch (t_decode(t)) {
    | Belt.Result.Ok(email) => make(email)
    | Belt.Result.Error(error) => Relude.Result.error(`DecoderError(error))
    };
  };
};



