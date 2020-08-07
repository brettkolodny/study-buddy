[@bs.module "tauri/api/dialog"] external tauriOpen : unit => Js.Promise.t('a) = "open";
[@bs.module "tauri/api/event"] external emit : (string, string) => unit = "emit";

[@react.component]
let make = (~setShowDialog, ~setShowCreateCard) => {
    let openDeck = () => {
        let paths = tauriOpen() 
        |> Js.Promise.then_(value => {
                Js.log(value);
                Js.Promise.resolve(Some(value));
            })
        |> Js.Promise.catch(err => {
                Js.log(err);
                Js.Promise.resolve(None);
            });

    };

    <div id="create-deck-dialog-container">
        <div id="create-deck-dialog">
            <div id="create-deck-dialog-topbar">
                <div id="create-deck-dialog-exit" onClick={_ => setShowDialog(_ => false)}>
                </div>
            </div>
            <div id="create-deck-dialog-button-container">
                <div className="create-deck-dialog-button" onClick={_ => setShowCreateCard(_ => true)}>{ReasonReact.string("New")}</div>
                <div className="create-deck-dialog-button" onClick={_ => openDeck()}>{ReasonReact.string("Import")}</div>
            </div>
        </div>
    </div>
}
