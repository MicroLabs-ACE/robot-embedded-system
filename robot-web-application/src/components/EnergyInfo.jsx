export default function EnergyInfo({ value, unit, label }) {
  return (
    <div className="flex flex-col items-center gap-1">
      <p className="text-white text-[18px]">
        {value} <span className="text-[10px]">{unit}</span>
      </p>
      <span className="text-sm md:text-[13px] text-white capitalize">
        {label}
      </span>
    </div>
  );
}
