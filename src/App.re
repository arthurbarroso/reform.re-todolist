open Css;

let baseStyle =
  merge([
    style([
      height(`vh(100.0)),
      display(`flex),
      flexDirection(column),
      alignItems(center)
    ]),
    "base-style"
  ]);

[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();
  let page =
    switch(url.path){
    | [] => <ReformInputAndList />;
    | ["reducer"] => <ReducerInputAndList />;
    | ["reform"] => <ReformInputAndList />;
    | _ => <div>{"Page not found" |> ReasonReact.string}</div>;
    };
    <div className=baseStyle>
        page
    </div>
}