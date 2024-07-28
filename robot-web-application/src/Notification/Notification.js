import { Icon } from "@iconify/react/dist/iconify.js";
import React, { useState } from "react";

const Notification = () => {
  const icons = [
    {
      id: "1",
      name: "material-symbols:home-outline",
    },
    {
      id: "2",
      name: "mdi:gamepad-circle-outline",
    },
    {
      id: "3",
      name: "basil:chat-outline",
    },
    {
      id: "4",
      name: "material-symbols:help-outline",
    },
  ];
  const [activeIcon, setActiveIcon] = useState(0);
  return (
    <div className="fixed rounded-3xl  bottom-0 py-5 justify-center w-full left-0 right-0 mx-autop bg-black ">
      <div className="flex w-[70%] md:w-[400px] mx-auto justify-between">
        {icons.map((icon, index) => {
          if (index === activeIcon)
            return (
              <button
                onClick={() => setActiveIcon(index)}
                className=" flex rounded-lg items-center bg-[#017AFF] justify-center py-4 px-6 "
              >
                <Icon icon={icon.name} color="white" fontSize={18} />
              </button>
            );
          return (
            <button
              onClick={() => setActiveIcon(index)}
              className=" flex rounded-lg bg-black  items-center justify-center py-4 px-6 "
            >
              <Icon icon={icon.name} color="#646464" fontSize={18} />
            </button>
          );
        })}
      </div>
    </div>
  );
};

export default Notification;
