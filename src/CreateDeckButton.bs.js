'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");

function CreateDeckButton(Props) {
  var setShow = Props.setShow;
  return React.createElement("div", {
              id: "create-deck-button",
              onClick: (function (param) {
                  return Curry._1(setShow, (function (param) {
                                return true;
                              }));
                })
            }, React.createElement("span", undefined, "Create"));
}

var make = CreateDeckButton;

exports.make = make;
/* react Not a pure module */
