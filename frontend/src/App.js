import React, { useState, useEffect, useRef } from "react";
import Graph from "./components/Graph";
import "./App.css";

const initialEquations = ["x*sin(x)", "x^2 - 5", "cos(x) + 2", "log(x + 10)"];
const bufferMultiplier = 2;
const DEFAULT_DOMAIN = [-10, 10];
const DEFAULT_RANGE = [-10, 10];

const App = () => {
  const [points, setPoints] = useState([]);
  const [domain, setDomain] = useState([...DEFAULT_DOMAIN]);
  const [range, setRange] = useState([...DEFAULT_RANGE]);
  const [equation, setEquation] = useState(initialEquations[0]);
  const [equations, setEquations] = useState(initialEquations);
  const [isModuleReady, setIsModuleReady] = useState(false);
  const [editingEquationIndex, setEditingEquationIndex] = useState(null);
  const inputRefs = useRef([]);

  const computeBufferedDomainRange = (domain, range) => {
    const bufferedDomain = [domain[0] * bufferMultiplier, domain[1] * bufferMultiplier];
    const bufferedRange = [range[0] * bufferMultiplier, range[1] * bufferMultiplier];
    return { bufferedDomain, bufferedRange };
  };

  useEffect(() => {
    const preventArrowKeyScroll = (e) => {
      if (
        ["ArrowUp", "ArrowDown", "ArrowLeft", "ArrowRight"].includes(e.key) &&
        e.target.tagName !== "INPUT"
      ) {
        e.preventDefault();
      }
    };
    window.addEventListener("keydown", preventArrowKeyScroll);
    return () => {
      window.removeEventListener("keydown", preventArrowKeyScroll);
    };
  }, []);

  useEffect(() => {
    if (!window.ModuleLoaded) {
      const script = document.createElement("script");
      script.src = "/graphing_calculator.js";
      script.async = true;
      script.onload = () => {
        window.Module().then((moduleInstance) => {
          window.ModuleInstance = moduleInstance;
          window.ModuleLoaded = true;
          setIsModuleReady(true);
        });
      };
      script.onerror = () => console.error("Failed to load WebAssembly script!");
      document.body.appendChild(script);
    } else if (!isModuleReady) {
      setIsModuleReady(true);
    }
  }, [isModuleReady]);

  useEffect(() => {
    if (!isModuleReady || !window.ModuleInstance) return;
    const fetchPoints = async () => {
      try {
        const moduleInstance = window.ModuleInstance;
        const { bufferedDomain, bufferedRange } = computeBufferedDomainRange(domain, range);
        const GraphInfo = new moduleInstance.Graph_Info(
          { first: 800, second: 600 },
          { first: 0, second: 0 },
          { first: bufferedDomain[0], second: bufferedDomain[1] },
          { first: bufferedRange[0], second: bufferedRange[1] },
          equation,
          500
        );
        const Plot = new moduleInstance.Plot(GraphInfo);
        const wasmPoints = Plot.generate_points();
        const generatedPoints = Array.from({ length: wasmPoints.size() }, (_, i) => {
          const point = wasmPoints.get(i);
          return [point.first, point.second];
        });
        setPoints(generatedPoints);
      } catch (error) {
        console.error("Error during WebAssembly execution:", error);
      }
    };
    fetchPoints();
  }, [isModuleReady, domain, range, equation]);

  const handleDomainRangeChange = (newDomain, newRange) => {
    setDomain(newDomain);
    setRange(newRange);
  };

  const resetDomainAndRange = () => {
    setDomain([...DEFAULT_DOMAIN]);
    setRange([...DEFAULT_RANGE]);
  };

  const addNewEquation = () => {
    setEquations([...equations, ""]);
    setEditingEquationIndex(equations.length);
    setTimeout(() => {
      if (inputRefs.current[equations.length]) {
        inputRefs.current[equations.length].focus();
      }
    }, 0);
  };

  const deleteEquation = (index) => {
    const newEquations = equations.filter((_, i) => i !== index);
    const deletingCurrentEquation = equations[index] === equation;
    setEquations(newEquations);
    if (deletingCurrentEquation) {
      if (newEquations.length > 0) {
        const newIndex = Math.max(0, newEquations.length - 1);
        setEquation(newEquations[newIndex]);
        setEditingEquationIndex(newIndex);
      } else {
        setEquation("");
        setEditingEquationIndex(null);
      }
    }
  };

  const handleFocus = (index) => {
    setEditingEquationIndex(index);
    setEquation(equations[index]);
  };

  const handleEquationChange = (index, e) => {
    const updatedEquations = [...equations];
    updatedEquations[index] = e.target.value;
    setEquations(updatedEquations);
    setEquation(updatedEquations[index]);
  };

  const startDrag = (e) => {
    e.currentTarget.dataset.dragging = "true";
    e.currentTarget.dataset.dragStartX = e.clientX;
    e.currentTarget.dataset.dragStartY = e.clientY;
    e.currentTarget.dataset.dragLeft = e.currentTarget.offsetLeft;
    e.currentTarget.dataset.dragTop = e.currentTarget.offsetTop;
  };

  const drag = (e) => {
    if (e.currentTarget.dataset.dragging !== "true") return;
    const startX = Number(e.currentTarget.dataset.dragStartX);
    const startY = Number(e.currentTarget.dataset.dragStartY);
    const startLeft = Number(e.currentTarget.dataset.dragLeft);
    const startTop = Number(e.currentTarget.dataset.dragTop);
    const dx = e.clientX - startX;
    const dy = e.clientY - startY;
    const newLeft = startLeft + dx;
    const newTop = startTop + dy;
    const w = e.currentTarget.offsetWidth;
    const h = e.currentTarget.offsetHeight;
    const clampedLeft = Math.max(0, Math.min(window.innerWidth - w, newLeft));
    const clampedTop = Math.max(0, Math.min(window.innerHeight - h, newTop));
    e.currentTarget.style.left = `${clampedLeft}px`;
    e.currentTarget.style.top = `${clampedTop}px`;
  };

  const stopDrag = (e) => {
    e.currentTarget.dataset.dragging = "false";
  };

  return (
    <div className="app-container">
      <Graph
        points={points}
        domain={domain}
        range={range}
        onDomainRangeChange={handleDomainRangeChange}
      />
      <div className="sidebar" onMouseDown={startDrag} onMouseMove={drag} onMouseUp={stopDrag}>
        <h3>Equation Controls</h3>
        <button onClick={resetDomainAndRange}>Reset Domain & Range</button>

        {equations.map((eq, index) => (
          <div key={index} className="equation">
            <input
              ref={(el) => (inputRefs.current[index] = el)}
              className="equation-editable"
              type="text"
              value={eq}
              onFocus={() => handleFocus(index)}
              onChange={(e) => handleEquationChange(index, e)}
              readOnly={editingEquationIndex !== index}
            />
            <span
              onClick={(e) => {
                e.stopPropagation();
                deleteEquation(index);
              }}
              className="delete-icon"
            >
              ✖
            </span>
          </div>
        ))}

        <div onClick={addNewEquation} className="add-equation">
          +
        </div>
      </div>
    </div>
  );
};

export default App;
