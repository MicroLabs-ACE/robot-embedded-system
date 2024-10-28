import React from "react";
import Controls from "../components/Controls";
import Navigation from "../components/Navigation";
import Map from "../components/Map";

const ControllerPage = () => {
  return (
    <div className="flex px-[2rem] items-start w-full md:px-0 md:items-center lg:items-stretch justify-center py-28 flex-col-reverse gap-10 lg:gap-0 relative lg:justify-between lg:w-[1000px] min-h-full lg:flex-row ">
      <Controls />
      <Map />
      <Navigation />
    </div>
  );
};

export default ControllerPage;
