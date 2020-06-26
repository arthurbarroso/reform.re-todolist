open BsReform;


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

  <form
  onSubmit={event => {
    ReactEvent.Synthetic.preventDefault(event);
    submit();
  }}>

  <button onClick={_ => arrayPush(Todos, {content: "", completed: false})}>
    {React.string("Add Task")}
  </button>
  {state.values.todos
   ->Belt.Array.mapWithIndex((index, todo) =>
       <>
         <hr />
         <label>
           <span> {"Content " |> ReasonReact.string} </span>
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
         <span>
           {React.string(" is done? " ++ string_of_bool(todo.completed) ++ " ")}
         </span>
         <button onClick={_ => arrayUpdateByIndex(~field=Todos, ~index, {...todo, completed: !todo.completed})}>
           {React.string("Toggle")}
         </button>
         <button onClick={_ => arrayRemoveByIndex(Todos, index)}>
           {React.string("Remove")}
         </button>
         <hr />
       </>
     )
   ->React.array}
   <a href="/reducer">{"Use React's reducer" |> React.string}</a>
</form>;
};

