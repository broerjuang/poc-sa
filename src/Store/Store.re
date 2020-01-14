
/* This should live in different module */
module Counter = {
  type state = int;
  type action = [ | `Increment | `Decrement];
  let empty = 0;
};

module OtherStore = {
  type state = {name: option(string)};
  type action = [ | `ChangeName(string)];
  let empty = {name: None};
};

/* Until This line */


/* Imagine this is a root state, root action, and root reducer */
module State = {
  type t = {counter: Counter.state};
  let initial = {counter: Counter.empty};
};

module Action = {
  type t = [ Counter.action];
};

module Reducer = {
  let make = (state, action) => {
    switch (action) {
    | `Increment => (state, None)
    | `Decrement => (state, None)
    | `ChangeName(_name) => (state, None)
    };
  };
};

/* end of root module */

include Renata.Make({
  type state = State.t;
  type action = Action.t;
  let reducer = Reducer.make;
  let enhancer = None;
  let initialState = (State.initial, None);
});
