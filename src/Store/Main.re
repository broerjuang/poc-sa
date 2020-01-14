type appState =
  | NotReady
  | Ready(SharedState.model)
  | FailedToInitialize;

type model = {appState};

type action =
  | ChangeUserName(SharedState.User.t)
  | Increment;

let init = (NotReady, None);

let updateCounter = model => {
  switch (model.appState) {
  | NotReady => (model, None)
  | Ready(sharedState) =>
    SharedState.(
      {
        appState:
          Ready(
            update(sharedState, UpdateCounter(sharedState.counter + 1)),
          ),
      },
      None,
    )
  | FailedToInitialize => (model, None)
  };
};

let updateUser = (sharedState, user) => {
  switch (sharedState.appState) {
  | NotReady => ({appState: NotReady}, None)
  | Ready(sharedState) =>
    SharedState.(
      {appState: Ready(update(sharedState, UpdateUser(user)))},
      None,
    )
  | FailedToInitialize => (sharedState, None)
  };
};

let update = (model, message) => {
  switch (message) {
  | ChangeUserName(user) => updateUser(model, user)
  | Increment => updateCounter(model)
  };
};
