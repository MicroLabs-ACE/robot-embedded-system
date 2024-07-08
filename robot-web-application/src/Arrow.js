import React from "react";

function Arrow({ angle }) {
  return (
    <>
      <img
        src="arrow.png"
        width={25}
        height={25}
        alt="Arrow"
        style={{ transform: `rotate(${angle}deg)` }}
      />
    </>
  );
}

export default Arrow;
