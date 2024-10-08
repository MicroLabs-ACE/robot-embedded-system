import { Icon } from "@iconify/react/dist/iconify.js";
import React, { useState } from "react";
import { useLocation, useNavigate } from "react-router-dom";

export default function Navigation() {
  const icons = [
    {
      id: "1",
      name: "material-symbols:home-outline",
      href: "/",
    },
    {
      id: "2",
      name: "mdi:gamepad-circle-outline",
      href: "/controller",
    },
    {
      id: "3",
      name: "basil:chat-outline",
      href: "/chat",
    },
    {
      id: "4",
      name: "material-symbols:help-outline",
      href: "/help",
    },
  ];

  const navigate = useNavigate();
  const location = useLocation();
  const pathname = location.pathname;

  return (
    <div className="fixed z-10 rounded-3xl bottom-0 py-5 w-full bg-black">
      <div className="flex w-[70%] md:w-[400px] mx-auto justify-between">
        {icons.map((icon) => {
          const isActive = pathname === icon.href; // Check if the icon is active
          return (
            <button
              key={icon.id}
              onClick={() => icon.href && navigate(icon.href)}
              className={`flex rounded-lg items-center justify-center py-4 px-6 ${
                isActive ? "bg-[#017AFF]" : "bg-black"
              }`}
            >
              <Icon
                icon={icon.name}
                color={isActive ? "white" : "#646464"}
                fontSize={18}
              />
            </button>
          );
        })}
      </div>
    </div>
  );
}
