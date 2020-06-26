open BsReform;
open Css;

let reformStyle =
  merge([
    style([
      height(`vh(100.0)),
      display(`flex),
      flexDirection(column),
      alignItems(center)
    ]),
    "reformForm-style"
  ]);


module TodoLenses = [%lenses
  type todo = {
    content: string,
    completed: bool
  }
];

module StateLenses = [%lenses
  type state = {
    todos: array(TodoLenses.todo)
  }
];

module TodoForm = ReForm.Make(StateLenses);

[@react.component]
let make = () => {
  let {
    state,
    submit,
    arrayPush,
    arrayUpdateByIndex,
    arrayRemoveByIndex,
  }: TodoForm.api =
  TodoForm.use(
    ~schema={
      TodoForm.Validation.Schema([|
        Custom(
          Todos,
          ({todos}) => {
            let length = Array.length(todos);

            length < 0
            || Belt.Array.some(todos, item =>
                 Js.String.length(item.content) == 0
               )
              ? Error("Invalid todo") : Valid;
          },
        ),
      |]);
    },
    ~onSubmit=({state}) => {
      Js.log2("State", state);
      None;
    },
    ~initialState={
      todos: [||],
    },
    (),
  );

  <div className=reformStyle>
    <form
    onSubmit={event => {
      ReactEvent.Synthetic.preventDefault(event);
      submit();
    }}>

    <Button onClick={_ => arrayPush(Todos, {content: "", completed: false})} text="Add Task" />
    {state.values.todos
    ->Belt.Array.mapWithIndex((index, todo) =>
        <>
          <hr />
          <label>
            <Label text="Content " />
            <input
              value={todo.content}
              onChange={BsReform.Helpers.handleChange(content =>
                arrayUpdateByIndex(
                  ~field=Todos,
                  ~index,
                  {...todo, content},
                )
              )}
            />
          </label>
          <Label text=(" is done?" ++ string_of_bool(todo.completed)) />

          <Button onClick={_ => arrayUpdateByIndex(~field=Todos, ~index, {...todo, completed: !todo.completed})} text="Toggle" />
          <Button onClick={_ => arrayRemoveByIndex(Todos, index)} text="Remove" />
        </>
      )
    ->React.array}
  </form>
  <a href="/reducer">{"Use React's reducer" |> React.string}</a>
  </div>
};

