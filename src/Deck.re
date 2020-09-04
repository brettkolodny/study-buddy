[@react.component]
let make = (~deckName, ~dueCards, ~newCards) => {
    <div className="deck">
        <div className="deck-name-div">
            <span>{React.string(deckName)}</span>
        </div>
        <div className="deck-due-div">
            <span>{React.string(dueCards)}</span>
        </div>
        <div className="deck-new-div">
            <span>{React.string(newCards)}</span>
        </div>
    </div>
};