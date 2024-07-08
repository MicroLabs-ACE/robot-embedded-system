import { useState } from "react";

function GearSystem(props) {
  const { numberOfGearLevels } = props;
  const [currentGear, setCurrentGear] = useState("P");

  const handleClick = (event) => {
    const gearText = event.target.textContent;
    const newGear = gearText !== "P" ? Number(gearText) : 0;
    setCurrentGear(newGear);
  };

  const gearLevels = Array.from({ length: 6 }, (_, i) => i);

  return (
    <div>
      {gearLevels.map((gearNumber) => (
        <button key={gearNumber} onClick={handleClick}>
          {gearNumber <= numberOfGearLevels
            ? gearNumber !== 0
              ? gearNumber
              : "P"
            : ""}
        </button>
      ))}
      <p>Current Gear: {currentGear}</p>
    </div>
  );
}

export default GearSystem;
