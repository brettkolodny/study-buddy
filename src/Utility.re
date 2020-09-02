[@bs.val] external require: string => string = "require";

type createDeckCommand = {
    cmd: string,
    deckName: string,
    deck: string,
};

type importDeckCommand = {
    cmd: string,
    path: string,
};

[@bs.module "tauri/api/tauri"] external createDeck : createDeckCommand => unit = "invoke";
[@bs.module "tauri/api/tauri"] external importDeckInvoke : importDeckCommand => unit = "invoke";

let importDeck = (path) => {
    let command = {
        cmd: "importDeck",
        path: path,
    };

    importDeckInvoke(command);
};