[@bs.val] external require: string => string = "require";

type createDeckCommand = {
    cmd: string,
    deckName: string,
    deck: string,
};

type importDeckCommand = {
    deckPath: string
};

[@bs.module "tauri/api/tauri"] external createDeck : createDeckCommand => unit = "invoke";
[@bs.module "tauri/api/tauri"] external importDeck : importDeckCommand => unit = "invoke";