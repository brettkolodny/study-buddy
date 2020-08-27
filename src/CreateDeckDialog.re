[@bs.module "tauri/api/dialog"] external tauriOpen : unit => Js.Promise.t('a) = "open";
[@bs.module "tauri/api/event"] external emit : (string, string) => unit = "emit";

[@bs.val] external setTimeout: (unit => unit, int) => unit = "setTimeout";

[@bs.val] external document: Dom.document = "document";
[@bs.send.pipe: Dom.document] external getElementById: string => Dom.element = "getElementById";
[@bs.get] external getStyle: Dom.element => Dom.cssStyleDeclaration = "style";

//let downSvg = Utility.require("../assets/svg/down.svg");

[@react.component]
let make = (~setShowDialog, ~setShowCreateCard) => {
    let openDeck = () => {
        let _paths = tauriOpen() 
        |> Js.Promise.then_(value => {
                Js.log(value);
                Js.Promise.resolve(Some(value));
            })
        |> Js.Promise.catch(err => {
                Js.log(err);
                Js.Promise.resolve(None);
            });

    };

    let closeWindow = () => {
        open Webapi.Dom;
        let container = getElementById("create-dialog", document)

        let containerStyle = getStyle(container);
        CssStyleDeclaration.setProperty("margin-top", "100vh", "", containerStyle);

        container -> Element.classList |> DomTokenList.remove("open");
        container -> Element.classList |> DomTokenList.add("close");
        setTimeout(_ => setShowDialog(_ => false), 250);
        Js.log("clicked");
    };

    <div id="create-dialog" className="open">
        <div id="create-buttons">
            <div className="create-button" onClick={_ => Js.log("pressed")}>
                <span>{ReasonReact.string("New")}</span>
            </div>
            <div className="create-button" onClick={_ => openDeck()}>
                <span>{ReasonReact.string("Import")}</span>
            </div>
        </div>
        <img className="down" src="../assets/svg/down.svg" onClick={_ => closeWindow()}/>
    </div>
}
