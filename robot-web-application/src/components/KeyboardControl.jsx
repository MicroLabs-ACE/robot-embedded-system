import React, { useState, useEffect } from "react";
import { sendCommand } from "../utils/sendCommand";

export default function KeyboardControl() {
  const [rotation, setRotation] = useState(0);

  const handleKeyPress = (event) => {
    let northSouth = "O";
    let eastWest = "O";

    switch (event.key.toLowerCase()) {
      case "w":
        northSouth = "N";
        break;
      case "s":
        northSouth = "S";
        break;
      case "j":
        eastWest = "W";
        break;
      case "l":
        eastWest = "E";
        break;
      default:
        return;
    }

    changeRotation(northSouth, eastWest);
    sendCommand(northSouth, eastWest);
  };

  function changeRotation(northSouth, eastWest) {
    const direction = `${northSouth}${eastWest}`;
    switch (direction) {
      case "NO":
        setRotation(0); // North
        break;
      case "NE":
        setRotation(45); // NorthEast
        break;
      case "OE":
        setRotation(90); // East
        break;
      case "SE":
        setRotation(135); // SouthEast
        break;
      case "SO":
        setRotation(180); // South
        break;
      case "SW":
        setRotation(225); // SouthWest
        break;
      case "OW":
        setRotation(270); // West
        break;
      case "NW":
        setRotation(315); // NorthWest
        break;
      default:
        break;
    }
  }

  useEffect(() => {
    window.addEventListener("keydown", handleKeyPress);
    return () => {
      window.removeEventListener("keydown", handleKeyPress);
    };
  }, []);

  return (
    <div
      className={`w-full relative lg:w-[60%] h-[400px] lg:h-auto md:w-[50%] rounded-3xl bg-[#1B1B1B] border-2 border-[#636263] flex flex-col items-center justify-center gap-5`}
    >
      <img
        src="arrow.png"
        alt="arrow"
        className="w-[20%]"
        style={{ transform: `rotate(${rotation}deg)` }}
      />
    </div>
  );
}
