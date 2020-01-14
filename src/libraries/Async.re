let let_ = (promise, cb) => {
  promise 
    |> Js.Promise.then_(cb)
}
