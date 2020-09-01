[@bs.val] external setTimeout: (unit => unit, int) => unit = "setTimeout";
[@bs.val] external document: Dom.document = "document";
[@bs.send.pipe: Dom.document] external getElementById: string => Dom.element = "getElementById";
[@bs.get] external getStyle: Dom.element => Dom.cssStyleDeclaration = "style";
[@bs.get] external getValue: Dom.element => string = "value";
[@bs.set] external setValue: (Dom.element, string) => unit = "value";

let downSvg = Utility.require("../assets/svg/down.svg");
let checkSvg = Utility.require("../assets/svg/icon-check.svg");

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
        let container = getElementById("new-deck", document)

        let containerStyle = getStyle(container);
        Webapi.Dom.CssStyleDeclaration.setProperty("margin-top", "100vh", "", containerStyle);

        container -> Webapi.Dom.Element.classList |> Webapi.Dom.DomTokenList.remove("open");
        container -> Webapi.Dom.Element.classList |> Webapi.Dom.DomTokenList.add("close");
        setTimeout(_ => setShowNewDeck(_ => false), 200);
    };

    let updateDeckName = () => {
        let currentDeckName = getElementById("deck-name", document)
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
        let newDeck = {
            name: deckName,
            cards: Array.of_list(cards),
        };

        let deckJson = Js.Json.stringifyAny(newDeck);

        switch deckJson {
        | Some(v) => {
            let createCmd: Utility.createDeckCommand = {
                cmd: "createDeck",
                deckName: deckName,
                deck: v,
            };
            Utility.createDeck(createCmd);
        }
        | None => ()
        };

        let container = getElementById("new-deck", document)

        let containerStyle = getStyle(container);
        Webapi.Dom.CssStyleDeclaration.setProperty("margin-top", "100vh", "", containerStyle);

        container -> Webapi.Dom.Element.classList |> Webapi.Dom.DomTokenList.remove("open");
        container -> Webapi.Dom.Element.classList |> Webapi.Dom.DomTokenList.add("close");

        setTimeout(_ => setShowNewDeck(_ => false), 200);
    };

    <div id="new-deck" className="open">
        <div id="new-deck-name-div">
            <input type_="text" id="deck-name" placeholder="Untitled" onBlur={_ => updateDeckName()}></input>
        </div>
        <div id="new-deck-body">
            <div id="new-cards-count">
                {
                    let numCards = List.length(cards);
                    if (numCards == 1) {
                        ReasonReact.string("1 card");
                    } else {
                        (numCards -> string_of_int ++ " cards") -> ReasonReact.string;
                    };
                }
            </div>
            <NewCard />
            <div id="new-deck-body">
                <div id ="new-deck-buttons">
                    <div id="discard-button" onClick={_ => closeWindow()}>
                        {ReasonReact.string("discard")}
                    </div>
                    <div id="done-button" onClick={_ => createDeck()}>{ReasonReact.string("Done")}</div>
                    <div id="add-button" onClick={_ => addCard()}>
                        <img src=checkSvg />
                        <div>{ReasonReact.string("Add")}</div>
                    </div>
                </div>
            </div>
        </div>
    </div>
};