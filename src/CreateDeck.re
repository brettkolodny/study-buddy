[@react.component]
let make = () => {
    let (showDialog, setShowDialog) = React.useState(() => false);
    let (showCreateCard, setShowCreateCard) = React.useState(() => false);

    <div id="create-deck-container" >
        <CreateDeckButton setShow={setShowDialog} />
        {
            if (showDialog) {
                <CreateDeckDialog setShowDialog={setShowDialog} setShowCreateCard={setShowCreateCard}/>
            } else {
                <div></div>
            };
        }
        {
            if (showCreateCard) {
                <NewCardWindow />
            } else {
                <div></div>
            };
        }
    </div>
}
