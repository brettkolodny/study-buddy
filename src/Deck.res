@react.component
let make = (~deckName, ~dueCards, ~newCards) =>
  <div className="deck">
    <div className="deck-name-div"> <span> {ReasonReact.string(deckName)} </span> </div>
    <div className="deck-due-div">
      <span> {ReasonReact.string(string_of_int(dueCards))} </span>
    </div>
    <div className="deck-new-div">
      <span> {ReasonReact.string(string_of_int(newCards))} </span>
    </div>
  </div>