import Controls from "./components/Controls.jsx";
import Navigation from "./components/Navigation.jsx";
import MapDiagram from "./components/MapDiagram.jsx";
import Home from "./pages/Home.jsx";
import ControlledPage from "./pages/ControlledPage.jsx";
import { Route, Routes } from "react-router-dom";

export default function App() {
  return (
    // <div className="flex px-[2rem] items-start w-full md:px-0 md:items-center lg:items-stretch  justify-center py-28 flex-col-reverse  gap-10 lg:gap-0  relative lg:justify-between lg:w-[1000px] min-h-full lg:flex-row ">
    //   <Controls />
    //   <MapDiagram />
    //   <Navigation />
    // </div>
    <>
      <Navigation />
      <Routes>
        <Route path="/" element={<Home />} />
        <Route path="/directedView" element={<ControlledPage />} />
      </Routes>
    </>
  );
}
