module Cred = {
  [@decco]
  type t = {
    token: string,
    username: string,
  };
};

let storeCred = (~username, ~token) => {
  let cred = Cred.t_encode({username, token})->Js.Json.stringify;
  ReactNative.AsyncStorage.setItem("user", cred);
};

let logout = () => {
  ReactNative.AsyncStorage.removeItem("user");
};
