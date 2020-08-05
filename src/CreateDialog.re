[@bs.module "tauri/api/dialog"] external tauriOpen : unit => Js.Promise.t('a) = "open";
[@bs.module "tauri/api/event"] external emit : (string, string) => unit = "emit";

[@react.component]
let make = (~setShow) => {
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

    <div id="create-dialog-container">
        <div id="create-dialog">
            <div id="create-dialog-topbar">
                <div id="create-dialog-exit" onClick={_ => setShow(_ => false)}>
                </div>
            </div>
            <div id="create-dialog-button-container">
                <div className="create-dialog-button">{ReasonReact.string("New")}</div>
                <div className="create-dialog-button" onClick={_ => openDeck()}>{ReasonReact.string("Import")}</div>
            </div>
        </div>
    </div>
}
