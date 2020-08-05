'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");

function CreateButton(Props) {
  var setShow = Props.setShow;
  return React.createElement("div", {
              id: "create-deck-button",
              onClick: (function (param) {
                  return Curry._1(setShow, (function (param) {
                                return true;
                              }));
                })
            }, "Create");
}

var make = CreateButton;

exports.make = make;
/* react Not a pure module */
