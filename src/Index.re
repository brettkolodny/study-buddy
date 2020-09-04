[@bs.val] external document: Js.t({..}) = "document";
[@bs.val] external _object: Js.t({..}) = "Object";

let makeContainer = (text) => {
  let container = document##createElement("div");
  container##id #= text;

  let () = document##body##appendChild(container);

  container;
};

let load = () => {
  let _ = Tauri.getDecksPromisified({ cmd: "getDecks" })
  |> Js.Promise.then_(decks => {
      switch( ReactDOM.querySelector("#root")) {
      | Some(root) => ReactDOM.render(<App loadedDecks=decks />, root)
      | None => ()
      };

    Js.Promise.resolve(Some(decks));
  })
  |> Js.Promise.catch(err => {
      Js.log(err);
      Js.Promise.resolve(None);
  });
};

load();