[@bs.val] external document: Js.t({..}) = "document";
[@bs.val] external _object: Js.t({..}) = "Object";
[@bs.module "tauri/api/event"] external emit : (string, string) => unit = "emit";
[@bs.module "tauri/api/event"] external listen : (string, 'a => unit) => unit = "listen";

let makeContainer = (text) => {
  let container = document##createElement("div");
  container##id #= text;

  let () = document##body##appendChild(container);

  container;
};

ReactDOM.render(
    <div id="container"> 
        <h5 id="title">{ReasonReact.string("Study Buddy")}</h5>
        <Deck deckName="Japanese" dueCards=10 newCards=20 />
        <Deck deckName="Biochem" dueCards=15 newCards=20 />
        <CreateDeck />
    </div>, 
    makeContainer("root"));


listen("rust-event", reply => {
    Js.log("test");
    let cards = reply##payload##cards;
    Js.log(Array.length(cards));
    Js.log(cards);
});
