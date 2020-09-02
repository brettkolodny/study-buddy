type createDeckCommand = {
    cmd: string,
    deckName: string,
    deck: string,
};

type importDeckCommand = {
    cmd: string,
    path: string,
};

[@bs.module "tauri/api/tauri"] external createDeckInvoke : createDeckCommand => unit = "invoke";
[@bs.module "tauri/api/tauri"] external importDeckInvoke : importDeckCommand => unit = "invoke";
[@bs.module "tauri/api/event"] external emit : (string, string) => unit = "emit";
[@bs.module "tauri/api/event"] external listen : (string, 'a => unit) => unit = "listen";
[@bs.module "tauri/api/dialog"] external openDialog : unit => Js.Promise.t('a) = "open";

let createDeck = (deckName, deck) => {
    let command = {
        cmd: "createDeck",
        deckName: deckName,
        deck: deck,
    }

    createDeckInvoke(command);
};

let importDeck = (path) => {
    let command = {
        cmd: "importDeck",
        path: path,
    };

    importDeckInvoke(command);
};