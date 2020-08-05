'use strict';

var React = require("react");

function Title(Props) {
  return React.createElement("h5", {
              id: "title"
            }, "Study Buddy");
}

var make = Title;

exports.make = make;
/* react Not a pure module */
