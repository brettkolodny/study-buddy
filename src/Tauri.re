type createDeckCommand = {
    cmd: string,
    deckName: string,
    deck: string,
};

type importDeckCommand = {
    cmd: string,
    path: string,
};

type getDecksCommand = {
    cmd: string
};

[@bs.module "tauri/api/tauri"] external createDeckInvoke : createDeckCommand => unit = "invoke";
[@bs.module "tauri/api/tauri"] external importDeckInvoke : importDeckCommand => unit = "invoke";
[@bs.module "tauri/api/tauri"] external getDecksPromisified : getDecksCommand => Js.Promise.t('a) = "promisified";
[@bs.module "tauri/api/event"] external emit : (string, string) => unit = "emit";
[@bs.module "tauri/api/event"] external listen : (string, 'a => unit) => unit = "listen";
[@bs.module "tauri/api/dialog"] external openDialog : unit => Js.Promise.t('a) = "open";

let createDeck = (deckName, deck) => {
    createDeckInvoke({ cmd: "createDeck", deckName: deckName, deck: deck });
};

let importDeck = (path) => {
    importDeckInvoke({ cmd: "importDeck", path: path });
};