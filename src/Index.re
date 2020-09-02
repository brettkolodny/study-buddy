[@bs.val] external document: Js.t({..}) = "document";
[@bs.val] external _object: Js.t({..}) = "Object";

let makeContainer = (text) => {
  let container = document##createElement("div");
  container##id #= text;

  let () = document##body##appendChild(container);

  container;
};

ReactDOM.render(
    <div id="container"> 
        <div id="top-background"></div>
        <div id="top">
            <h5 id="title">{ReasonReact.string("Study Buddy")}</h5>
            <CreateDeck />
        </div>
        <div id="decks">
            <Deck deckName="Japanese" dueCards=10 newCards=20 />
            <Deck deckName="Biochem" dueCards=15 newCards=20 />
        </div>
    </div>, 
    makeContainer("root"));