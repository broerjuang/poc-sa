/* 
   This module is copy paste from https://github.com/MargaretKrutikova/reason-react-elmish.
   Quite like the API but need to adjust with our needs 
 */


module EffectManager = {
  type effect = unit => option(unit => unit);

  type t = {
    listeners: ref(list(unit => unit)),
    effects: ref(array(effect)),
  };

  let create = () => {listeners: ref([]), effects: ref([||])};

  let getEffects = manager => manager.effects^;

  let unsubscribe = (manager, listener, ()) =>
    manager.listeners :=
      Belt.List.keep(manager.listeners^, l => listener !== l);

  let subscribe = (manager, listener) => {
    manager.listeners := [listener, ...manager.listeners^];
    unsubscribe(manager, listener);
  };

  let queueEffect = (manager, effect) => {
    manager.effects := Belt.Array.concat(manager.effects^, [|effect|]);
    Belt.List.forEach(manager.listeners^, listener => listener());
  };

  let runEffects = manager => {
    let cleanupFuncs = Belt.Array.keepMap(manager.effects^, func => func());
    manager.effects := [||];

    cleanupFuncs;
  };
};

type dispatch('message) = 'message => unit;

type effect('message) = dispatch('message) => option(unit => unit);

type update('model, 'message) =
  ('model, 'message) => ('model, option(effect('message)));

type enhancer('action, 'state) =
  (Reductive.Store.t('action, 'state), 'action => unit, 'action) => unit;

type storeEnhancer('action, 'state) =
  (
    ~reducer: ('state, 'action) => 'state,
    ~preloadedState: 'state,
    ~enhancer: enhancer('action, 'state)=?,
    unit
  ) =>
  Reductive.Store.t('action, 'state);

module Make =
       (
         Config: {
           type state;
           type action;
           let reducer: update(state, action);
           let initialState: (state, option(effect(action)));
           let enhancer:
             option(
               storeEnhancer(action, state) => storeEnhancer(action, state),
             );
         },
       ) => {
/*  open Reductive; */
  include ReductiveContext.Make({
    type state = Config.state;
    type action = Config.action;
  });

  let effectManager = EffectManager.create();

  let (initModel, initEffect) = Config.initialState;

  let storeCreator =
    switch (Config.enhancer) {
    | None => Reductive.Store.create
    | Some(enhancer) => enhancer @@ Reductive.Store.create
    };

  let store =
    storeCreator(
      ~reducer=(state, _) => state,
      ~preloadedState=initModel,
      (),
    );

  let customReducer = (state, action) => {
    let (newModel, effect) = Config.reducer(state, action);
    switch (effect) {
    | Some(effectToRun) =>
      EffectManager.queueEffect(effectManager, () =>
        effectToRun(Reductive.Store.dispatch(store))
      )
    | None => ()
    };

    newModel;
  };

  Reductive.Store.replaceReducer(store, customReducer);

  switch (initEffect) {
  | Some(effect) => effect(Reductive.Store.dispatch(store))
  | None => None
  };

  let runEffects = () => {
    open Subscription;

    let source =
      React.useMemo0(() =>
        {
          subscribe: EffectManager.subscribe(effectManager),
          getCurrentValue: () => EffectManager.getEffects(effectManager),
        }
      );

    let effects = useSubscription(source);

    React.useEffect1(
      () => {
        let cleanupFuncs = EffectManager.runEffects(effectManager);
        Belt.Array.length(cleanupFuncs) > 0
          ? Some(() => Belt.Array.forEach(cleanupFuncs, func => func()))
          : None;
      },
      [|effects|],
    );
  };

  module EffectRunner = {
    [@react.component]
    let make = (~children) => {
      runEffects();
      children;
    };
  };

  module RenataProvider = {
    [@react.component]
    let make = (~children) => {
      <Provider store> <EffectRunner> children </EffectRunner> </Provider>;
    };
  };
};
