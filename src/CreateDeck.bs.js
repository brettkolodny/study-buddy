'use strict';

var React = require("react");
var CreateButton$StudyBuddy = require("./CreateButton.bs.js");
var CreateDialog$StudyBuddy = require("./CreateDialog.bs.js");

function CreateDeck(Props) {
  var match = React.useState(function () {
        return false;
      });
  var setShow = match[1];
  return React.createElement("div", {
              id: "create-dialog-button-container"
            }, React.createElement(CreateButton$StudyBuddy.make, {
                  setShow: setShow
                }), match[0] ? React.createElement(CreateDialog$StudyBuddy.make, {
                    setShow: setShow
                  }) : React.createElement("div", undefined));
}

var make = CreateDeck;

exports.make = make;
/* react Not a pure module */
