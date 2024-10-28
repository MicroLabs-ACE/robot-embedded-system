import React, { useRef, useEffect, useState } from "react";
import p5 from "p5";
import { MapGraph } from "../utils/mapGraph.js";

export default function Map() {
  const [isWebsocket, setIsWebsocket] = useState(false);
  const sketchRef = useRef(null);
  const graphRef = useRef(null);
  const socketRef = useRef(null);
  const isWebsocketRef = useRef(false);

  useEffect(() => {
    const socket = new WebSocket(`ws://192.168.4.1/ws`);
    socketRef.current = socket;

    socket.addEventListener("open", () => {
      setIsWebsocket(true);
      isWebsocketRef.current = true;
      console.log("Opened websocket");
    });

    socket.addEventListener("error", (error) => {
      setIsWebsocket(false);
      isWebsocketRef.current = false;
      console.error("WebSocket Error:", error);
    });

    socket.addEventListener("message", (event) => {
      console.log("Received:", event.data);
    });

    socket.addEventListener("close", () => {
      setIsWebsocket(false);
      isWebsocketRef.current = false;
      console.log("Closed websocket");
    });

    return () => {
      if (socketRef.current) {
        socketRef.current.close();
      }
    };
  }, []);

  const sendCommand = (northSouth, eastWest) => {
    if (
      isWebsocketRef.current &&
      socketRef.current?.readyState === WebSocket.OPEN
    ) {
      const command = `${northSouth}${eastWest}2`;
      socketRef.current.send(command);
      console.log(`Sent command: ${command}`);
    } else {
      console.log("Websocket not connected or ready.");
    }
  };

  useEffect(() => {
    const CANVAS_LENGTH = 600;
    const CANVAS_WIDTH = 600;
    const CIRCLE_RADIUS = 10;
    const GRAPH_LENGTH = 15;
    const UNIT_LENGTH = 40;
    const X_OFFSET = 20;
    const Y_OFFSET = 15;

    const sketch = (p) => {
      p.setup = () => {
        p.createCanvas(CANVAS_LENGTH, CANVAS_WIDTH);
        p.background(0);
        graphRef.current = new MapGraph(GRAPH_LENGTH, GRAPH_LENGTH);
      };

      p.draw = () => {
        p.fill("white");
        for (let x = 0; x < GRAPH_LENGTH; x++) {
          for (let y = 0; y < GRAPH_LENGTH; y++) {
            p.circle(
              UNIT_LENGTH * x + X_OFFSET,
              UNIT_LENGTH * y + Y_OFFSET,
              CIRCLE_RADIUS
            );
          }
        }
      };
    };

    const p5Instance = new p5(sketch, sketchRef.current);
    return () => {
      p5Instance.remove();
    };
  }, []);

  useEffect(() => {
    const intervalId = setInterval(() => sendCommand("N", "O"), 2500);

    return () => clearInterval(intervalId);
  }, []);

  return <div ref={sketchRef} />;
}
