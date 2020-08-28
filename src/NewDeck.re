[@bs.val] external setTimeout: (unit => unit, int) => unit = "setTimeout";
[@bs.val] external document: Dom.document = "document";
[@bs.send.pipe: Dom.document] external getElementById: string => Dom.element = "getElementById";
[@bs.get] external getStyle: Dom.element => Dom.cssStyleDeclaration = "style";
[@bs.get] external getValue: Dom.element => string = "value";
[@bs.set] external setValue: (Dom.element, string) => unit = "value";

let downSvg = Utility.require("../assets/svg/down.svg");

type card = {
    front: string,
    back: string,
    priority: int,
};

type deck = {
    cards: array(card),
    name: string,
};

[@react.component]
let make = (~setShowNewDeck) => {
    let (cards, setCards) = React.useState(() => []);
    let (deckName, setDeckName) = React.useState(() => "Untitled");

    let closeWindow = () => {
        open Webapi.Dom;
        let container = getElementById("new-deck", document)

        let containerStyle = getStyle(container);
        CssStyleDeclaration.setProperty("margin-top", "100vh", "", containerStyle);

        container -> Element.classList |> DomTokenList.remove("open");
        container -> Element.classList |> DomTokenList.add("close");
        setTimeout(_ => setShowNewDeck(_ => false), 200);
    };

    let updateDeckName = () => {
        open Webapi.Dom;
        let currentDeckName = getElementById("deckName", document)
            |> getValue;
        
        setDeckName(_ => currentDeckName);
    };

    let addCard = () => {
        let front = getElementById("front", document);
        let back = getElementById("back", document);
        let frontValue = getValue(front);
        let backValue = getValue(back);

        let newCard = {
            front: frontValue,
            back: backValue,
            priority: 100,
        };

        setCards(_ => [newCard, ...cards]);

        setValue(front, "");
        setValue(back, "");
    };

    let createDeck = () => {
        open Webapi.Dom;
        let newDeck = {
            name: deckName,
            cards: Array.of_list(cards),
        };

        let deckJson = Js.Json.stringifyAny(newDeck);

        switch deckJson {
        | Some(v) => {
            let createCmd: Utility.command = {
                cmd: "createDeck",
                argument: v,
            };
            Utility.invoke(createCmd);
        }
        | None => ()
        };

        let container = getElementById("new-deck", document)

        let containerStyle = getStyle(container);
        CssStyleDeclaration.setProperty("margin-top", "100vh", "", containerStyle);

        container -> Element.classList |> DomTokenList.remove("open");
        container -> Element.classList |> DomTokenList.add("close");

        setTimeout(_ => setShowNewDeck(_ => false), 200);
    };

    <div id="new-deck" className="open">
        <span>{ReasonReact.string("Cards: " ++ string_of_int(List.length(cards)))}</span>
        <input type_="text" id="deckName" placeholder="Untitled" onBlur={_ => updateDeckName()}></input>
        <NewCard />
        <div id="new-deck-buttons">
                <div onClick={_ => createDeck()}>{ReasonReact.string("Done")}</div>
                <div onClick={_ => addCard()}>{ReasonReact.string("Add")}</div>
        </div>
        <img className="down" src=downSvg onClick={_ => closeWindow()}/>
    </div>
};