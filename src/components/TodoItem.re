open State;
[@react.component]
let make = (~todo: todo, ~handleCheck, ~handleDelete) =>
  <div key=string_of_int(todo.id)>
    <h2>{ReasonReact.string("Task: " ++ todo.content)}</h2>
    <p>{ReasonReact.string("Done? " ++ string_of_bool(todo.completed))}</p>
    <button onClick={_ => handleCheck(todo.id)}>{ReasonReact.string("Mark as done/undone")}</button>
    <button onClick={_ => handleDelete(todo.id)}>{ReasonReact.string("Delete todo")}</button>
  </div>