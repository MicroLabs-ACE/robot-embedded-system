import React from "react";
import MapImg from "../images/map.jpg"

export default function MapDiagram() {
  return (
    <div className="w-full relative lg:w-[60%] h-[400px] lg:h-auto md:w-[50%] rounded-3xl bg-[#1B1B1B] border-2 border-[#636263]  flex flex-col gap-5 ">
      <img src={MapImg} alt="map image" className="w-full h-full object-cover " />
      <div className="absolute top-10 left-5 w-[10rem] h-14 bg-[#017AFF] rounded-tl-2xl text-white flex items-center justify-center"> 40km away</div>
    </div>
  );
}
