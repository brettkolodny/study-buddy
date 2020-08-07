'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Caml_option = require("bs-platform/lib/js/caml_option.js");
var Dialog = require("tauri/api/dialog");

function CreateDeckDialog(Props) {
  var setShowDialog = Props.setShowDialog;
  var setShowCreateCard = Props.setShowCreateCard;
  return React.createElement("div", {
              id: "create-deck-dialog-container"
            }, React.createElement("div", {
                  id: "create-deck-dialog"
                }, React.createElement("div", {
                      id: "create-deck-dialog-topbar"
                    }, React.createElement("div", {
                          id: "create-deck-dialog-exit",
                          onClick: (function (param) {
                              return Curry._1(setShowDialog, (function (param) {
                                            return false;
                                          }));
                            })
                        })), React.createElement("div", {
                      id: "create-deck-dialog-button-container"
                    }, React.createElement("div", {
                          className: "create-deck-dialog-button",
                          onClick: (function (param) {
                              return Curry._1(setShowCreateCard, (function (param) {
                                            return true;
                                          }));
                            })
                        }, "New"), React.createElement("div", {
                          className: "create-deck-dialog-button",
                          onClick: (function (param) {
                              Dialog.open().then(function (value) {
                                      console.log(value);
                                      return Promise.resolve(Caml_option.some(value));
                                    }).catch(function (err) {
                                    console.log(err);
                                    return Promise.resolve(undefined);
                                  });
                              
                            })
                        }, "Import"))));
}

var make = CreateDeckDialog;

exports.make = make;
/* react Not a pure module */
