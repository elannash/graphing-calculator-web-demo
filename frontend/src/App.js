import React, { useState, useEffect, useRef } from "react";
import Graph from "./components/Graph";

const initialEquations = ["x*sin(x)", "x^2 - 5", "cos(x) + 2", "log(x + 10)"];
const bufferMultiplier = 2;

const App = () => {
  const [points, setPoints] = useState([]);
  const [domain, setDomain] = useState([-10, 10]);
  const [range, setRange] = useState([-10, 10]);
  const [equation, setEquation] = useState(initialEquations[0]);
  const [equations, setEquations] = useState(initialEquations);
  const [isModuleReady, setIsModuleReady] = useState(false);
  const [editingEquationIndex, setEditingEquationIndex] = useState(0);

  const contentRefs = useRef([]); // Array of refs for contentEditable elements

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

  const addNewEquation = () => {
    setEquations([...equations, ""]); // Add a new blank equation bubble
    setEditingEquationIndex(equations.length); // Set this bubble as editable
    setTimeout(() => {
      contentRefs.current[equations.length]?.focus(); // Automatically focus the new equation
    }, 0);
  };

  const deleteEquation = (index) => {
    const newEquations = equations.filter((_, i) => i !== index);

    if (equations[index] === equation) {
      if (newEquations.length > 0) {
        const newHighlightedIndex = Math.min(index, newEquations.length - 1);
        setEditingEquationIndex(newHighlightedIndex);
        setEquation(newEquations[newHighlightedIndex]);
      } else {
        setEditingEquationIndex(null);
        setEquation("");
      }
    }

    setEquations(newEquations);
  };

  const handleEditEquation = (index) => {
    setEditingEquationIndex(index); // Set the clicked equation to be editable
    setEquation(equations[index]); // Render this equation on the graph
    setTimeout(() => {
      contentRefs.current[index]?.focus(); // Automatically focus the contentEditable element
    }, 0);
  };

  const handleEquationChange = (index, e) => {
    const selectionStart = window.getSelection().getRangeAt(0).startOffset;

    const updatedEquations = [...equations];
    updatedEquations[index] = e.target.innerText.replace(/\n/g, ""); // Remove newlines
    setEquations(updatedEquations);
    setEquation(updatedEquations[index]); // Update graph immediately

    // Restore cursor position
    setTimeout(() => {
      const range = document.createRange();
      range.setStart(e.target.firstChild || e.target, selectionStart);
      range.collapse(true);
      const sel = window.getSelection();
      sel.removeAllRanges();
      sel.addRange(range);
    }, 0);
  };

  const handleKeyDown = (e) => {
    if (e.key === "Enter") {
      e.preventDefault(); // Prevent adding newlines
    }
  };

  // Sidebar drag functions
  const sidebarRef = useRef(null);
  const isDragging = useRef(false);
  const startPosition = useRef({ x: 0, y: 0 });

  const startDrag = (e) => {
    isDragging.current = true;
    startPosition.current = { x: e.clientX, y: e.clientY };
  };

  const drag = (e) => {
    if (!isDragging.current) return;
    const dx = e.clientX - startPosition.current.x;
    const dy = e.clientY - startPosition.current.y;
    sidebarRef.current.style.left = `${sidebarRef.current.offsetLeft + dx}px`;
    sidebarRef.current.style.top = `${sidebarRef.current.offsetTop + dy}px`;
    startPosition.current = { x: e.clientX, y: e.clientY };
  };

  const stopDrag = () => {
    isDragging.current = false;
  };

  return (
    <div
      style={{
        backgroundColor: "#061326",
        height: "100vh",
        position: "relative",
      }}
    >
      <Graph
        points={points}
        domain={domain}
        range={range}
        onDomainRangeChange={handleDomainRangeChange}
      />

      {/* Floating Retro Sidebar */}
      <div
        ref={sidebarRef}
        onMouseDown={startDrag}
        onMouseMove={drag}
        onMouseUp={stopDrag}
        style={{
          position: "absolute",
          top: "10%",
          left: "5%",
          width: "250px",
          height: "80%",
          backgroundColor: "rgba(6, 19, 38, 0.8)",
          borderRadius: "15px",
          padding: "20px",
          color: "#A5C5D6",
          boxShadow: "0 0 15px rgba(162, 192, 210, 0.4)",
          backdropFilter: "blur(8px)",
          fontFamily: "'Manifold', sans-serif",
          fontSize: "16px",
          zIndex: 10,
          overflowY: "auto",
        }}
      >
        <h3 style={{ textAlign: "center", color: "#A5C5D6" }}>
          Equation Controls
        </h3>

        {/* List of Editable Equations */}
        {equations.map((eq, index) => (
          <div
            key={index}
            onClick={() => handleEditEquation(index)}
            style={{
              backgroundColor: "#020B1C",
              color: "#A5C5D6",
              padding: "8px",
              borderRadius: "10px",
              textAlign: "center",
              display: "flex",
              alignItems: "center",
              justifyContent: "center",
              marginBottom: "10px",
              fontFamily: "'Manifold', sans-serif",
              position: "relative",
              cursor: "pointer",
              boxShadow:
                editingEquationIndex === index
                  ? "0 0 10px 2px rgba(65, 77, 84, 1)"
                  : "none",
              minHeight: "30px",
            }}
          >
            <span
              ref={(el) => (contentRefs.current[index] = el)}
              contentEditable
              suppressContentEditableWarning
              onBlur={() => setEditingEquationIndex(null)}
              onInput={(e) => handleEquationChange(index, e)}
              onKeyDown={handleKeyDown}
              onClick={(e) => {
                const range = document.createRange();
                const sel = window.getSelection();

                if (!e.target.contains(sel.anchorNode)) {
                  const textLength = e.target.innerText.length;
                  range.setStart(e.target.firstChild || e.target, textLength);
                  range.collapse(true);
                  sel.removeAllRanges();
                  sel.addRange(range);
                }
              }}
              style={{
                backgroundColor: "#020B1C",
                color: "#A5C5D6",
                border: "none",
                width: "100%",
                fontFamily: "'Manifold', sans-serif",
                textAlign: "center",
                outline: "none",
                whiteSpace: "nowrap",
                overflow: "hidden",
              }}
            >
              {eq}
            </span>

            <span
              onClick={(e) => {
                e.stopPropagation();
                deleteEquation(index);
              }}
              style={{
                color: "#FF6347",
                position: "absolute",
                top: "5px",
                right: "5px",
                cursor: "pointer",
              }}
            >
              ✖
            </span>
          </div>
        ))}

        {/* Add New Equation Button */}
        <div
          onClick={addNewEquation}
          style={{
            cursor: "pointer",
            backgroundColor: "#020B1C",
            color: "#A5C5D6",
            padding: "10px",
            borderRadius: "15px",
            textAlign: "center",
            marginBottom: "10px",
            fontFamily: "'Manifold', sans-serif",
            fontWeight: "bold",
          }}
        >
          +{" "}
        </div>
      </div>
    </div>
  );
};

export default App;
