[@bs.val] external require: string => string = "require";

type command = {
    cmd: string,
    argument: string,
};

[@bs.module "tauri/api/tauri"] external invoke : command => unit = "invoke";