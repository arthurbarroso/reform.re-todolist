open Css;

let labelStyle =
  merge([
    style([
      fontSize(px(18)),
      marginRight(px(8))
    ]),
    "label-style"
  ]);

[@react.component]
let make = (~text) => {
  <label className=labelStyle>
   {text |> React.string}
  </label>
};