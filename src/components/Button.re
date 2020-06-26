open Css;

let textColor = (isHovering: bool) => isHovering ? hex("fcba03") : hex("fff");

type state = {isHovering: bool};
type action =
  | ToggleHover;

let centerButtonStyle = (isHovering: bool) => {
  let usedColor = textColor(isHovering);

  merge([
    style([
      alignSelf(center),
      background(hex("333")),
      color(usedColor),
      borderRadius(px(4)),
      borderWidth(px(0)),
      height(px(48)),
      padding(px(8)),
      width(px(246)),
      marginRight(px(20)),
      cursor(`pointer)
    ]),
    "center-button"
  ]);
};


[@react.component]
let make = (~onClick, ~text) => {
  let (state, dispatch) =
  React.useReducer(
    (state, action) =>
      switch (action) {
        | ToggleHover => {isHovering: !state.isHovering}
      },
    {isHovering: false},
  );
  <button className=centerButtonStyle(state.isHovering)
    onClick
    onMouseOver={_event => dispatch(ToggleHover)}
    onMouseOut={_event => dispatch(ToggleHover)}>
      {text |> React.string}
  </button>
}