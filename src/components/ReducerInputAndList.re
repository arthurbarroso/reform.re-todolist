open State;
[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer(reducer, initialState);
  let {todos} = state;

  let handleCreate = (content) => {
    dispatch(Add(content));
  };

  let handleDelete = (id) => {
    dispatch(Delete(id));
  };

  let handleCheck = (id) => {
    dispatch(Check(id));
  };

  let allTodos = List.map(todo => <TodoItem todo handleCheck handleDelete />, todos);

  <div>
    <ReducerInput handleCreate/>
    {
      ReasonReact.array(Array.of_list(allTodos))
    }
  </div>
}