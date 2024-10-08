import React, { useRef, useEffect } from "react";
import p5 from "p5";

export default function Map() {
  const sketchRef = useRef(null);

  useEffect(() => {
    let x = 0;
    const sketch = (p) => {
      p.setup = () => {
        p.createCanvas(600, 600);
      };

      p.draw = () => {
        p.background(75);
        p.fill(255, 0, 0);
        p.ellipse(x, p.height / 2, 100, 100);
        x += 2;
        if (x > p.width) {
          x = 0;
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
