import React from "react";
import JoystickImg from "../images/joystick.png";

export default function JoystickDiagram() {
  return (
    <div className="w-full relative lg:w-[60%] h-[400px] lg:h-auto md:w-[50%] rounded-3xl bg-[#1B1B1B] border-2 border-[#636263]  flex flex-col gap-5 ">
      <img
        src={JoystickImg}
        alt="map image"
        className="w-[300px] md:w-[500px] mx-auto object-cover "
      />
    </div>
  );
}
