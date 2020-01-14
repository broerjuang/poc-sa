module Counter = {
  type t = int;
};

module User = {
  type t = {
    name: string,
    age: int,
  };
};

type model = {
  counter: Counter.t,
  user: User.t,
};

type message =
  | NoUpdate
  | UpdateCounter(Counter.t)
  | UpdateUser(User.t);

let update = (model, message) => {
  switch (message) {
  | NoUpdate => model
  | UpdateCounter(counter) => {...model, counter}
  | UpdateUser(user) => {...model, user}
  };
};
