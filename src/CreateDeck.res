@react.component
let make = () => {
  let (showDialog, setShowDialog) = React.useState(() => false)
  let (showNewDeck, setShowNewDeck) = React.useState(() => false)

  <div id="create-deck-container">
    <CreateDeckButton setShow=setShowDialog />
    {if showDialog {
      <CreateDeckDialog setShowDialog setShowNewDeck />
    } else {
      <div />
    }}
    {if showNewDeck {
      <NewDeck setShowNewDeck />
    } else {
      <div />
    }}
  </div>
}