module Login = {
  [@decco.encode]
  type t = {
    username: string,
    password: string,
    [@decco.key "type"]
    type_: string,
    role: string,
    [@decco.key "client_secret"] clientSecret: string,
    [@decco.key "client_id"] clientId: string
  };
};



