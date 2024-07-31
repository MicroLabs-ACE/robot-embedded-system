import Controls from "./components/Controls.jsx";
import Navigation from "./components/Navigation.jsx";
import MapDiagram from "./components/MapDiagram.jsx";

export default function App() {
  return (
    <div className="flex px-[2rem] items-start w-full md:px-0 md:items-center lg:items-stretch  justify-center py-28 flex-col-reverse  gap-10 lg:gap-0  relative lg:justify-between lg:w-[1000px] min-h-full lg:flex-row ">
      <Controls />
      <MapDiagram />
      <Navigation />
    </div>
  );
}
