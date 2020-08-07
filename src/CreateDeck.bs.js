'use strict';

var React = require("react");
var NewCardWindow$StudyBuddy = require("./NewCardWindow.bs.js");
var CreateDeckButton$StudyBuddy = require("./CreateDeckButton.bs.js");
var CreateDeckDialog$StudyBuddy = require("./CreateDeckDialog.bs.js");

function CreateDeck(Props) {
  var match = React.useState(function () {
        return false;
      });
  var setShowDialog = match[1];
  var match$1 = React.useState(function () {
        return false;
      });
  return React.createElement("div", {
              id: "create-deck-container"
            }, React.createElement(CreateDeckButton$StudyBuddy.make, {
                  setShow: setShowDialog
                }), match[0] ? React.createElement(CreateDeckDialog$StudyBuddy.make, {
                    setShowDialog: setShowDialog,
                    setShowCreateCard: match$1[1]
                  }) : React.createElement("div", undefined), match$1[0] ? React.createElement(NewCardWindow$StudyBuddy.make, {}) : React.createElement("div", undefined));
}

var make = CreateDeck;

exports.make = make;
/* react Not a pure module */
