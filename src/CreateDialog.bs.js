'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Caml_option = require("bs-platform/lib/js/caml_option.js");
var Dialog = require("tauri/api/dialog");

function CreateDialog(Props) {
  var setShow = Props.setShow;
  return React.createElement("div", {
              id: "create-dialog-container"
            }, React.createElement("div", {
                  id: "create-dialog"
                }, React.createElement("div", {
                      id: "create-dialog-topbar"
                    }, React.createElement("div", {
                          id: "create-dialog-exit",
                          onClick: (function (param) {
                              return Curry._1(setShow, (function (param) {
                                            return false;
                                          }));
                            })
                        })), React.createElement("div", {
                      id: "create-dialog-button-container"
                    }, React.createElement("div", {
                          className: "create-dialog-button"
                        }, "New"), React.createElement("div", {
                          className: "create-dialog-button",
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

var make = CreateDialog;

exports.make = make;
/* react Not a pure module */
