'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Caml_option = require("bs-platform/lib/js/caml_option.js");
var Dialog = require("tauri/api/dialog");

function CreateDeckDialog(Props) {
  var setShowDialog = Props.setShowDialog;
  Props.setShowCreateCard;
  return React.createElement("div", {
              className: "open",
              id: "create-dialog"
            }, React.createElement("div", {
                  id: "create-buttons"
                }, React.createElement("div", {
                      className: "create-button",
                      onClick: (function (param) {
                          console.log("pressed");
                          
                        })
                    }, React.createElement("span", undefined, "New")), React.createElement("div", {
                      className: "create-button",
                      onClick: (function (param) {
                          Dialog.open().then(function (value) {
                                  console.log(value);
                                  return Promise.resolve(Caml_option.some(value));
                                }).catch(function (err) {
                                console.log(err);
                                return Promise.resolve(undefined);
                              });
                          
                        })
                    }, React.createElement("span", undefined, "Import"))), React.createElement("img", {
                  className: "down",
                  src: "../assets/svg/down.svg",
                  onClick: (function (param) {
                      var container = document.getElementById("create-dialog");
                      var containerStyle = container.style;
                      containerStyle.setProperty("margin-top", "100vh", "");
                      container.classList.remove("open");
                      container.classList.add("close");
                      setTimeout((function (param) {
                              return Curry._1(setShowDialog, (function (param) {
                                            return false;
                                          }));
                            }), 250);
                      console.log("clicked");
                      
                    })
                }));
}

var make = CreateDeckDialog;

exports.make = make;
/* react Not a pure module */
