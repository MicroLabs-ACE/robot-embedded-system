import React, { useState, useEffect, useRef } from "react";
import { useGamepad } from "../hooks/useGamepad";

export default function Arrow() {
  const gamepad = useGamepad();
  const { connected, RT, RB, left, right } = gamepad;

  const [rotation, setRotation] = useState(0);
  const [isWebsocket, setIsWebsocket] = useState(false);
  const socketRef = useRef(null);

  useEffect(() => {
    const socket = new WebSocket(`ws://192.168.4.1/ws`);
    socketRef.current = socket;

    socket.addEventListener("open", () => {
      setIsWebsocket(true);
      console.log("Opened websocket");
    });

    socket.addEventListener("error", (error) => {
      setIsWebsocket(false);
      console.error("WebSocket Error:", error);
    });

    socket.addEventListener("message", (event) => {
      console.log("Received:", event.data);
    });

    socket.addEventListener("close", () => {
      setIsWebsocket(false);
      console.log("Closed websocket");
    });

    return () => {
      if (socketRef.current) {
        socketRef.current.close();
      }
    };
  }, []);

  const sendCommand = (northSouth, eastWest) => {
    if (isWebsocket && socketRef.current?.readyState === WebSocket.OPEN) {
      const command = `${northSouth}${eastWest}2`;
      socketRef.current.send(command);
    } else {
      console.log("Websocket not connected or ready.");
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
    </div>
  );
}
