import GearSystem from "./GearSystem";
import Switch from "./Switch";
import Map from "./Map";

function App() {
  return (
    <>
      <Switch />
      <GearSystem numberOfGearLevels={5} />
      <Map />
    </>
  );
}

export default App;
