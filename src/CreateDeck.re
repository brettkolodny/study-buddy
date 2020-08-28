[@react.component]
let make = () => {
    let (showDialog, setShowDialog) = React.useState(() => false);
    let (showNewDeck, setShowNewDeck) = React.useState(() => false);

    <div id="create-deck-container" >
        <CreateDeckButton setShow={setShowDialog} />
        {
            if (showDialog) {
                <CreateDeckDialog setShowDialog={setShowDialog} setShowNewDeck={setShowNewDeck}/>
            } else {
                <div></div>
            };
        }
        {
            if (showNewDeck) {
                <NewDeck setShowNewDeck=setShowNewDeck />
            } else {
                <div></div>
            };
        }
    </div>
}
