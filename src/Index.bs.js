'use strict';

var React = require("react");
var ReactDom = require("react-dom");
var Deck$StudyBuddy = require("./Deck.bs.js");
var $$Event = require("tauri/api/event");
var Title$StudyBuddy = require("./Title.bs.js");
var CreateDeck$StudyBuddy = require("./CreateDeck.bs.js");

function makeContainer(text) {
  var container = document.createElement("div");
  container.id = text;
  document.body.appendChild(container);
  return container;
}

ReactDom.render(React.createElement("div", undefined, React.createElement(Title$StudyBuddy.make, {}), React.createElement(Deck$StudyBuddy.make, {
              deckName: "Japanese",
              dueCards: 10,
              newCards: 20
            }), React.createElement(Deck$StudyBuddy.make, {
              deckName: "Biochem",
              dueCards: 15,
              newCards: 20
            }), React.createElement(CreateDeck$StudyBuddy.make, {})), makeContainer("root"));

$$Event.listen("rust-event", (function (reply) {
        console.log(reply.payload.data);
        
      }));

exports.makeContainer = makeContainer;
/*  Not a pure module */
