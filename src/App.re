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
    <div>
        page
    </div>
}