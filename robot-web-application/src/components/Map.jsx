import React, { useRef, useEffect } from "react";
import p5 from "p5";
import { MapGraph } from "../utils/mapGraph.js";

export default function Map() {
  const sketchRef = useRef(null);
  const graphRef = useRef(null);

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
              CIRCLE_RADIUS,
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

  return <div ref={sketchRef} />;
}
