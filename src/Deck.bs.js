'use strict';

var React = require("react");

function Deck(Props) {
  var deckName = Props.deckName;
  var dueCards = Props.dueCards;
  var newCards = Props.newCards;
  return React.createElement("div", {
              className: "deck"
            }, React.createElement("div", {
                  className: "deck-name-div"
                }, React.createElement("span", undefined, deckName)), React.createElement("div", {
                  className: "deck-due-div"
                }, React.createElement("span", undefined, String(dueCards))), React.createElement("div", {
                  className: "deck-new-div"
                }, React.createElement("span", undefined, String(newCards))));
}

var make = Deck;

exports.make = make;
/* react Not a pure module */
