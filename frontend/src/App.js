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
  const [sidebarVisible, setSidebarVisible] = useState(true);
  const [deleteDelay, setDeleteDelay] = useState(false);
  const sidebarRef = useRef(null);
  const inputRefs = useRef([]);
  const dragState = useRef({
    isDragging: false,
    offsetX: 0,
    offsetY: 0,
  });

  const computeBufferedDomainRange = (domain, range) => {
    const bufferedDomain = [
      domain[0] * bufferMultiplier,
      domain[1] * bufferMultiplier,
    ];
    const bufferedRange = [
      range[0] * bufferMultiplier,
      range[1] * bufferMultiplier,
    ];
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
      script.onerror = () =>
        console.error("Failed to load WebAssembly script!");
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
        const { bufferedDomain, bufferedRange } = computeBufferedDomainRange(
          domain,
          range
        );
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
        const generatedPoints = Array.from(
          { length: wasmPoints.size() },
          (_, i) => {
            const point = wasmPoints.get(i);
            return [point.first, point.second];
          }
        );
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
    if (deleteDelay) return;
    setEquations([...equations, ""]);
    setEditingEquationIndex(equations.length);
    setTimeout(() => {
      if (inputRefs.current[equations.length]) {
        inputRefs.current[equations.length].focus();
      }
    }, 0);
  };

  const deleteEquation = (index) => {
    setDeleteDelay(true);
    setTimeout(() => setDeleteDelay(false), 200);

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

  const handleFocusAndFocusInput = (e, index) => {
    e.preventDefault();
    e.stopPropagation();

    setEditingEquationIndex(index);
    setEquation(equations[index]);
    setTimeout(() => {
      if (inputRefs.current[index]) {
        inputRefs.current[index].readOnly = false;
        inputRefs.current[index].focus();
      }
    }, 100);
  };

  const handleEquationChange = (index, e) => {
    const updatedEquations = [...equations];
    updatedEquations[index] = e.target.value;
    setEquations(updatedEquations);
    setEquation(updatedEquations[index]);
  };

  const toggleSidebar = () => {
    setSidebarVisible(!sidebarVisible);
  };

  const startDrag = (e) => {
    if (e.target.closest(".equation")) return;
    const clientX = e.touches ? e.touches[0].clientX : e.clientX;
    const clientY = e.touches ? e.touches[0].clientY : e.clientY;
    const sidebar = sidebarRef.current;

    dragState.current = {
      isDragging: true,
      offsetX: clientX - sidebar.offsetLeft,
      offsetY: clientY - sidebar.offsetTop,
    };

    document.addEventListener("mousemove", drag);
    document.addEventListener("mouseup", stopDrag);
    document.addEventListener("touchmove", drag);
    document.addEventListener("touchend", stopDrag);
  };

  const drag = (e) => {
    if (!dragState.current.isDragging) return;
    const clientX = e.touches ? e.touches[0].clientX : e.clientX;
    const clientY = e.touches ? e.touches[0].clientY : e.clientY;

    const sidebar = sidebarRef.current;
    const newLeft = clientX - dragState.current.offsetX;
    const newTop = clientY - dragState.current.offsetY;

    sidebar.style.left = `${Math.max(
      0,
      Math.min(window.innerWidth - sidebar.offsetWidth, newLeft)
    )}px`;
    sidebar.style.top = `${Math.max(
      0,
      Math.min(window.innerHeight - sidebar.offsetHeight, newTop)
    )}px`;
  };

  const stopDrag = () => {
    dragState.current.isDragging = false;
    document.removeEventListener("mousemove", drag);
    document.removeEventListener("mouseup", stopDrag);
    document.removeEventListener("touchmove", drag);
    document.removeEventListener("touchend", stopDrag);
  };

  return (
    <div className="app-container">
      <Graph
        points={points}
        domain={domain}
        range={range}
        onDomainRangeChange={handleDomainRangeChange}
      />
      <div
        ref={sidebarRef}
        className={`sidebar ${sidebarVisible ? "" : "collapsed"}`}
        onMouseDown={(e) => startDrag(e)}
        onTouchStart={(e) => startDrag(e)}
      >
        <button className="sidebar-toggle" onClick={toggleSidebar}>
          {sidebarVisible ? (
            <svg viewBox="0 0 24 24">
              <path d="M2 12 C4 6, 8 3, 12 3s8 3,10 9c-2 6-6 9-10 9s-8-3-10-9z M6 12 l12 0" />
            </svg>
          ) : (
            <svg viewBox="0 0 24 24">
              <path d="M2 12 C4 6, 8 3, 12 3s8 3,10 9c-2 6-6 9-10 9s-8-3-10-9z M12 8 a4 4 0 1 1 0 8 a4 4 0 0 1 0-8" />
            </svg>
          )}
        </button>
        {sidebarVisible && (
          <>
            <h3>Equation Controls</h3>
            <button
              className="sidebar-reset-button"
              onClick={resetDomainAndRange}
            >
              Reset Domain & Range
            </button>
            {equations.map((eq, index) => (
              <div
                key={index}
                className="equation"
                onPointerDown={(e) => handleFocusAndFocusInput(e, index)}
              >
                <input
                  ref={(el) => (inputRefs.current[index] = el)}
                  className="equation-editable"
                  type="text"
                  value={eq}
                  onChange={(e) => handleEquationChange(index, e)}
                  readOnly={editingEquationIndex !== index}
                />
                <span
                  onPointerDown={(e) => {
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
          </>
        )}
      </div>
    </div>
  );
};

export default App;
