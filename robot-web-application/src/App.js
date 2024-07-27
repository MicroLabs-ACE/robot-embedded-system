import "../src/index.css";
import LeftNav from "./LeftNav/LeftNav";
import MapDiagram from "./MapDiagram/MapDiagram";
import Notification from "./Notification/Notification";

function App() {
  return (
    <div className="flex px-[2rem] items-start w-full md:px-0 md:items-center lg:items-stretch  justify-center py-28 flex-col-reverse  gap-10 lg:gap-0  relative lg:justify-between lg:w-[1000px] min-h-full lg:flex-row ">
      <LeftNav />
      <MapDiagram />
      <Notification />
    </div>
  );
}

export default App;
