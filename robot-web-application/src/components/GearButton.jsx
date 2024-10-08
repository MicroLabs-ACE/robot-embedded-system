export default function GearButton({ active, label, onClick }) {
  const activeClass =
    "text-white md:text-[22px] w-[40%] md:w-[100px] py-2 rounded-xl bg-[#017AFF] capitalize";
  const inactiveClass =
    "bg-black md:text-[22px] w-[40%] md:w-[100px] py-2 rounded-xl capitalize";
  return (
    <button onClick={onClick} className={active ? activeClass : inactiveClass}>
      {label}
    </button>
  );
}
