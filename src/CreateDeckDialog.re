[@bs.val] external setTimeout: (unit => unit, int) => unit = "setTimeout";

[@bs.val] external document: Dom.document = "document";
[@bs.send.pipe: Dom.document] external getElementById: string => Dom.element = "getElementById";
[@bs.get] external getStyle: Dom.element => Dom.cssStyleDeclaration = "style";

let downSvg = Utility.require("../assets/svg/down.svg");

[@react.component]
let make = (~setShowDialog, ~setShowNewDeck) => {
    let closeWindow = () => {
        let container = getElementById("create-dialog", document)

        let containerStyle = getStyle(container);
        Webapi.Dom.CssStyleDeclaration.setProperty("margin-top", "100vh", "", containerStyle);

        container -> Webapi.Dom.Element.classList |> Webapi.Dom.DomTokenList.remove("open");
        container -> Webapi.Dom.Element.classList |> Webapi.Dom.DomTokenList.add("close");
        setTimeout(_ => setShowDialog(_ => false), 200);
    };

    let openDeck = () => {
        let _paths = Tauri.openDialog() 
        |> Js.Promise.then_(value => {
                Tauri.importDeck(value);
                closeWindow();
                Js.Promise.resolve(Some(value));
            })
        |> Js.Promise.catch(err => {
                Js.log(err);
                Js.Promise.resolve(None);
            })
    };

    let newClick = () => {
        setShowNewDeck(_ => true);
        setTimeout(_ => setShowDialog(_ => false), 200);
    };

    <div id="create-dialog" className="open">
        <div id="create-buttons">
            <div className="create-button" onClick={_ => newClick()}>
                <span>{ReasonReact.string("New")}</span>
            </div>
            <div className="create-button" onClick={_ => openDeck()}>
                <span>{ReasonReact.string("Import")}</span>
            </div>
        </div>
        <div className="down">
            <img className="down" src=downSvg onClick={_ => closeWindow()}/>
        </div>
    </div>
}