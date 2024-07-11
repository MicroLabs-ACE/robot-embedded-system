import { useState } from "react";

function Switch() {
  const [onOffState, setOnOffState] = useState(false);

  const handleChange = (event) => {
    setOnOffState(event.currentTarget.checked);
  };

  return (
    <label>
      <input type="checkbox" checked={onOffState} onChange={handleChange} />
      {onOffState ? "On" : "Off"}
    </label>
  );
}

export default Switch;