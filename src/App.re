type deckInfo = {
    deckName: string,
    newCards: string,
    dueCards: string,
};

[@react.component]
let make = (~loadedDecks) => {
    let (decks, setDecks) = React.useState(_ => loadedDecks);

    let updateDecks = () => {
        let _ = Tauri.getDecksPromisified({ cmd: "getDecks" })
        |> Js.Promise.then_(newDecks => {
            if (Array.length(newDecks) != 0) {
                setDecks(_ => newDecks)
            };

            Js.Promise.resolve(Some(newDecks));
        })
        |> Js.Promise.catch(err => {
            Js.log(err);
            Js.Promise.resolve(None);
        });
    };
    
    <div id="container"> 
        <div id="top-background"></div>
        <div id="top">
            <h5 id="title">{React.string("Study Buddy")}</h5>
            <CreateDeck updateDecks=updateDecks />
        </div>
        <div id="decks">
            {
                if (Array.length(decks) == 0) {
                    <Deck deckName="Press Create!" dueCards="0" newCards="0" />
                } else {
                    Array.mapi((i, info) => {
                        <Deck deckName=info.deckName dueCards=info.dueCards newCards=info.newCards key={string_of_int(i)} />
                    }, decks) -> React.array
                };
            }
        </div>
    </div>
};