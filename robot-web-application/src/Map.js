import React, { useEffect, useState } from "react";
import Arrow from "./Arrow";

import dijkstra_computation from "./graph";

function EditAndSetButton({ onToggle, isEditing }) {
  return <button onClick={onToggle}>{isEditing ? "Set" : "Edit"}</button>;
}

function RunAndSetButton({ onToggle, isRunning }) {
  return <button onClick={onToggle}>{isRunning ? "Set" : "Run"}</button>;
}

function LengthAndWidthForm({ onChange }) {
  const [isEditing, setIsEditing] = useState(false);
  const [length, setLength] = useState("5");
  const [width, setWidth] = useState("5");

  const handleToggle = () => {
    setIsEditing(!isEditing);
    if (isEditing) {
      onChange({ length: Number(length), width: Number(width) });
    }
  };

  return (
    <form onSubmit={(e) => e.preventDefault()}>
      <label>
        Length:
        <input
          type="number"
          value={length}
          onChange={(e) => setLength(e.target.value)}
          readOnly={!isEditing}
        />
      </label>
      <label>
        Width:
        <input
          type="number"
          value={width}
          onChange={(e) => setWidth(e.target.value)}
          readOnly={!isEditing}
        />
      </label>
      <EditAndSetButton onToggle={handleToggle} isEditing={isEditing} />
    </form>
  );
}

function StartAndEndForm({ onChange }) {
  const [isRunning, setIsRunning] = useState(false);
  const [start, setStart] = useState("0-0");
  const [end, setEnd] = useState("5-5");

  const handleToggle = () => {
    setIsRunning(!isRunning);
    if (isRunning) {
      onChange({ start, end });
    }
  };

  return (
    <form onSubmit={(e) => e.preventDefault()}>
      <label>
        Start:
        <input
          type="text"
          value={start}
          onChange={(e) => setStart(e.target.value)}
          readOnly={!isRunning}
        />
      </label>
      <label>
        End:
        <input
          type="text"
          value={end}
          onChange={(e) => setEnd(e.target.value)}
          readOnly={!isRunning}
        />
      </label>
      <RunAndSetButton onToggle={handleToggle} isRunning={isRunning} />
    </form>
  );
}

function MapArea({ gridLength, gridWidth, start, end }) {
  const circleSize = 15;
  const circleSpacing = 30;

  const handleCircleClick = (event) => {
    const isOpaque = event.target.getAttribute("data-is-opaque") === "true";
    event.target.setAttribute("data-is-opaque", (!isOpaque).toString());
    event.target.style.opacity = isOpaque ? 0.3 : 1;
  };

  const circles = {};
  for (let i = 0; i < gridLength; i++) {
    for (let j = 0; j < gridWidth; j++) {
      circles[`${i}-${j}`] = (
        <div
          key={`circle-${i}-${j}`}
          data-key={`${i}-${j}`}
          data-is-opaque="false"
          style={{
            position: "absolute",
            left: `${j * circleSpacing}px`,
            top: `${i * circleSpacing}px`,
            width: `${circleSize}px`,
            height: `${circleSize}px`,
            borderRadius: "50%",
            backgroundColor: "white",
            border: "1px solid black",
            cursor: "pointer",
            opacity: 0.3,
          }}
        />
      );
    }
  }

  circles["0-0"] = <Arrow angle={180} />;

  const mapArea = (
    <div
      style={{
        position: "relative",
        width: "630px",
        height: "630px",
        backgroundColor: "lightgray",
        overflow: "hidden",
      }}
      onClick={handleCircleClick}
    >
      {Object.values(circles)}
    </div>
  );

  return mapArea;
}

function Map() {
  const [dimensions, setDimensions] = useState({ length: 5, width: 5 });
  const [path, setPath] = useState({ start: "0-0", end: "5-5" });

  return (
    <>
      <LengthAndWidthForm onChange={setDimensions} />
      <StartAndEndForm onChange={setPath} />
      <MapArea
        gridLength={dimensions.length}
        gridWidth={dimensions.width}
        start={path.start}
        end={path.end}
      />
    </>
  );
}

export default Map;
