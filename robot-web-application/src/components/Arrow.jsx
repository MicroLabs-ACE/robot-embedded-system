import React, { useState, useEffect } from "react";
import { useGamepad } from "../hooks/useGamepad";

export default function Arrow() {
  const gamepad = useGamepad();
  const { RT, RB, left, right } = gamepad;

  const [rotation, setRotation] = useState(0);
  const [isConnected, setIsConnected] = useState(false);
  const IP_ADDRESS = "http://192.168.4.1";

  const sendCommand = async (northSouth, eastWest) => {
    const command = `${northSouth}${eastWest}2`;
    try {
      const response = await fetch(`${IP_ADDRESS}/command=${command}`, {
        method: "POST",
      });
      if (response.ok) {
        console.log(`Sent command: ${command}`);
        setIsConnected(true);
      } else {
        console.error("Failed to send command.");
        setIsConnected(false);
      }
    } catch (error) {
      console.error("Error sending command:", error);
      setIsConnected(false);
    }
  };

  function changeRotation(northSouth, eastWest) {
    const direction = `${northSouth}${eastWest}`;
    if (direction === "NO") {
      setRotation(0); // North
    } else if (direction === "NE") {
      setRotation(45); // NorthEast
    } else if (direction === "OE") {
      setRotation(90); // East
    } else if (direction === "SE") {
      setRotation(135); // SouthEast
    } else if (direction === "SO") {
      setRotation(180); // South
    } else if (direction === "SW") {
      setRotation(225); // SouthWest
    } else if (direction === "OW") {
      setRotation(270); // West
    } else if (direction === "NW") {
      setRotation(315); // NorthWest
    }
  }

  useEffect(() => {
    const handleGamepadInput = () => {
      let northSouth = "O";
      let eastWest = "O";

      if (RT) {
        northSouth = "N";
      } else if (RB) {
        northSouth = "S";
      }

      if (left) {
        eastWest = "W";
      } else if (right) {
        eastWest = "E";
      }

      changeRotation(northSouth, eastWest);
      sendCommand(northSouth, eastWest);
    };

    const intervalId = setInterval(handleGamepadInput, 10);

    return () => clearInterval(intervalId);
  }, [RT, RB, left, right]);

  console.log(`Rotation: ${rotation}`);

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
      <p>{isConnected ? "Connected" : "Not connected"}</p>
    </div>
  );
}
