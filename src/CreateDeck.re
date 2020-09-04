[@react.component]
let make = (~updateDecks) => {
    let (showDialog, setShowDialog) = React.useState(() => false);
    let (showNewDeck, setShowNewDeck) = React.useState(() => false);

    <div id="create-deck-container" >
        <CreateDeckButton setShow={setShowDialog} />
        {
            if (showDialog) {
                <CreateDeckDialog setShowDialog={setShowDialog} setShowNewDeck={setShowNewDeck} updateDecks=updateDecks />
            } else {
                <div></div>
            };
        }
        {
            if (showNewDeck) {
                <NewDeck setShowNewDeck=setShowNewDeck updateDecks=updateDecks />
            } else {
                <div></div>
            };
        }
    </div>
}