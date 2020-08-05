[@react.component]
let make = (~setShow) => {
    <div id="create-deck-button" onClick={_ => setShow(_ => true)}>{ReasonReact.string("Create")}</div>
}
