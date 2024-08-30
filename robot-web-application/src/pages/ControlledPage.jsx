import React from "react";
import Controls from "../components/Controls";
import JoystickDiagram from "../components/JoystickDiagram";

const ControlledPage = () => {
  return (
    <div className="flex px-[2rem] items-start w-full md:px-0 md:items-center lg:items-stretch  justify-center py-28 flex-col-reverse  gap-10 lg:gap-0  relative lg:justify-between lg:w-[1000px] min-h-full lg:flex-row ">
      <Controls />
     <JoystickDiagram/>
    </div>
  );
};

export default ControlledPage;
