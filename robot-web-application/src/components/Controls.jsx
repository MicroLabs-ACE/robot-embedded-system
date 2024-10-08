import React, { useState } from "react";
import GearButton from "./GearButton";
import ControlButton from "./ControlButton";
import EnergyInfo from "./EnergyInfo";
import RecordingModal from "./RecordingModal";

export default function Controls() {
  const [gear, setGear] = useState(0);
  const [wifi, setWifi] = useState(false);
  const [power, setPower] = useState(false);
  const [voice, setVoice] = useState(false);
  const [speaker, setSpeaker] = useState(false);

  return (
    <div className="w-full md:w-[50%] lg:w-[38%] border-2 border-[#636263] rounded-3xl items-start flex flex-col gap-5 p-4">
      <img src="robot.png" alt="robot" className="w-full mx-auto" />

      <div className="flex w-full justify-between">
        <div className="pl-3 flex justify-between flex-col w-[46%] rounded-xl py-2 bg-[#017AFF] text-white">
          <span className="md:text-xl capitalize">speed</span>
          <p className="text-3xl text-white md:text-6xl">
            40 <span className="text-[10px] ml-[-0.5rem]">km/h</span>
          </p>
        </div>

        <div className="flex w-[46%] self-end text-white flex-col gap-1">
          <div className="flex justify-between md:gap-4">
            <GearButton
              active={gear === 0}
              label="P"
              onClick={() => setGear(0)}
            />
            <GearButton
              active={gear === 1}
              label="1"
              onClick={() => setGear(1)}
            />
          </div>
          <div className="flex justify-between md:gap-4">
            <GearButton
              active={gear === 2}
              label="2"
              onClick={() => setGear(2)}
            />
            <GearButton
              active={gear === 3}
              label="3"
              onClick={() => setGear(3)}
            />
          </div>
        </div>
      </div>

      <div className="flex py-2 bg-[#017AFF] px-3 flex-col gap-4 rounded-xl items-start w-full">
        <span className="capitalize text-white">energy consumption</span>
        <div className="w-full flex justify-between">
          <EnergyInfo value="0" unit="km/h" label="remaining" />
          <EnergyInfo value="0" unit="%" label="average" />
          <EnergyInfo value="100" unit="km/h" label="full capacity" />
        </div>
      </div>

      <div className="md:flex w-full flex-col gap-5 items-start">
        <div className="flex w-full justify-between lg:gap-6">
          <ControlButton
            active={power}
            icon="humbleicons:power"
            onClick={() => setPower(!power)}
          />
          <ControlButton
            active={wifi}
            icon="bi:wifi"
            onClick={() => setWifi(!wifi)}
          />
          <ControlButton
            active={voice}
            icon="solar:microphone-outline"
            onClick={() => setVoice(true)}
          />
          <ControlButton
            active={speaker}
            icon="fluent:speaker-2-20-regular"
            onClick={() => setSpeaker(!speaker)}
          />
        </div>
      </div>

      <RecordingModal open={voice} onClose={() => setVoice(false)} />
    </div>
  );
}
