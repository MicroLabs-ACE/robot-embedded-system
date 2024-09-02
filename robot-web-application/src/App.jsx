import Navigation from "./components/Navigation.jsx";
import HomePage from "./pages/HomePage.jsx";
import ControllerPage from "./pages/ControllerPage.jsx";
import { Route, Routes } from "react-router-dom";

export default function App() {
  return (
    <>
      <Navigation />
      <Routes>
        <Route path="/" element={<HomePage />} />
        <Route path="/controller" element={<ControllerPage />} />
      </Routes>
    </>
  );
}
