open BsReform;


module StateLenses = [%lenses
  type state = {
    content: string,
  }
];

module TodoAddForm = ReForm.Make(StateLenses);

module FieldString = {
  [@react.component]
  let make = (~field, ~label) => {
    <TodoAddForm.Field
      field
      render={({handleChange, error, value, validate}) =>
        <label>
          <span> {React.string(label)} </span>
          <input
            value
            onChange={Helpers.handleChange(handleChange)}
            onBlur={_ => validate()}
          />
          <p> {error->Belt.Option.getWithDefault("")->React.string} </p>
        </label>
      }
    />;
  };
};

[@react.component]
let make = (~handleCreate) => {
  let reform =
  TodoAddForm.use(
    ~validationStrategy=OnDemand,
    ~schema={
      TodoAddForm.Validation.Schema([|
        StringMin(Content, 20),
      |]);
    },
    ~onSubmit=
      ({state, send}) => {
        handleCreate(state.values.content);
        send(SetFormState(Valid))
        None;
      },
    ~initialState={content: ""},
    (),
  );

  <TodoAddForm.Provider value=reform>
    <form
      onSubmit={event => {
        ReactEvent.Synthetic.preventDefault(event);
        reform.submit();
      }}>
      <FieldString field=StateLenses.Content label="Content" />
      {reform.state.formState == Submitting
         ? <p> {React.string("Saving...")} </p>
         : <button type_="submit"> {"Submit" |> React.string} </button>}
    </form>
  </TodoAddForm.Provider>;

}