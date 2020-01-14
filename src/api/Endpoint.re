open ReludeURL;

let url = (~path, ~query=?, unit) => {
  URI.makeWithLabels(
    ~scheme=Scheme("https"),
    ~authority=Authority.fromHostname(Hostname.make("gw.ruangguru.com")),
    ~path,
    ~query?,
    unit,
  );
};

/* AUTH */

let login =
  url(
    ~path=
      Path.make([
        PathSegment.make("skillacademy"),
        PathSegment.make("auth"),
      ]),
    (),
  );

let register =
  url(
    ~path=
      Path.make([
        PathSegment.make("skillacademy"),
        PathSegment.make("user"),
      ]),
    (),
  );

let forgetPassword =
  url(
    ~path=
      Path.make([
        PathSegment.make("skillacademy"),
        PathSegment.make("user"),
        PathSegment.make("forgot-password"),
      ]),
  );

let passwordRecovery =
  url(
    ~path=
      Path.make([
        PathSegment.make("skillacademy"),
        PathSegment.make("user"),
        PathSegment.make("create-new-password"),
      ]),
    (),
  );

/* CATEGORIES */

let discoveryCategories = query =>
  url(
    ~path=
      Path.make([
        PathSegment.make("skillacademy"),
        PathSegment.make("discovery"),
        PathSegment.make("categories"),
      ]),
    ~query,
    (),
  );

let discoverHome = query =>
  url(
    ~path=
      Path.make([
        PathSegment.make("skillacademy"),
        PathSegment.make("discovery"),
        PathSegment.make("home"),
      ]),
    ~query,
    (),
  );

let discoveryCourses = query =>
  url(
    ~path=
      Path.make([
        PathSegment.make("skillacademy"),
        PathSegment.make("discovery"),
        PathSegment.make("courses"),
      ]),
    ~query,
    (),
  );
