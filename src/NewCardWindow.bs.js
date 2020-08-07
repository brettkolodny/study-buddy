'use strict';

var React = require("react");

function NewCardWindow(Props) {
  React.useState(function () {
        return /* [] */0;
      });
  return React.createElement("div", {
              id: "create-dialog-container"
            }, React.createElement("div", {
                  id: "create-dialog"
                }, React.createElement("div", {
                      id: "create-dialog-topbar"
                    }, React.createElement("div", {
                          id: "create-dialog-exit"
                        })), React.createElement("div", {
                      id: "create-dialog-button-container"
                    }, React.createElement("div", {
                          className: "create-dialog-button"
                        }), React.createElement("div", {
                          className: "create-dialog-button"
                        }))));
}

var make = NewCardWindow;

exports.make = make;
/* react Not a pure module */
