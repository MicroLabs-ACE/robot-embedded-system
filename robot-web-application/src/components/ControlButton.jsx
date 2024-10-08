import { Icon } from "@iconify/react/dist/iconify.js";

export default function ControlButton({ active, icon, onClick }) {
  const activeClass =
    "flex rounded-lg items-center bg-[#017AFF] justify-center py-4 px-6";
  const inactiveClass =
    "flex rounded-lg bg-black items-center justify-center py-4 px-6";
  return (
    <button onClick={onClick} className={active ? activeClass : inactiveClass}>
      <Icon icon={icon} color="white" fontSize={20} />
    </button>
  );
}
