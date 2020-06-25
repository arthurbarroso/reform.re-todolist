type todo = {
  id: int,
  content: string,
  completed: bool
};

type state = {
  todos: list(todo)
};

type action =
  | Add(string)
  | Check(int)
  | Delete(int);

let todoId = ref(0);

let createTodo = content => {
  todoId := todoId^ + 1;
  {id: todoId^, completed: false, content};
};

let checkTodo = (id, todos) =>
  List.map(t => t.id == id ? {...t, completed: !t.completed} : t, todos);

let removeTodo = (id, todos) =>
  List.filter(t => t.id !== id, todos);

let initialState = {
  todos: []
};

let reducer = ({todos}, action) =>
  switch(action){
    | Add(content) => { todos:[createTodo(content), ...todos]}
    | Delete(id) => {todos: removeTodo(id, todos)}
    | Check(id) => {todos: checkTodo(id, todos)}
  }