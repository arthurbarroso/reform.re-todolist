open Css;
open State;

let itemStyle =
  merge([
    style([
      maxWidth(px(640)),
      alignSelf(center)
    ]),
    "item-style"
  ]);


[@react.component]
let make = (~todo: todo, ~handleCheck, ~handleDelete) =>
  <div key=string_of_int(todo.id) className=itemStyle>
    <h2>{ReasonReact.string("Task: " ++ todo.content)}</h2>
    <p>{ReasonReact.string("Done? " ++ string_of_bool(todo.completed))}</p>
    <Button onClick={_ => handleCheck(todo.id)} text="Mark as done/undone" />
    <Button onClick={_ => handleDelete(todo.id)} text="Delete todo" />
  </div>