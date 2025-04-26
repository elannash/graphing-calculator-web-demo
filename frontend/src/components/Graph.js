import React, { useRef } from "react";
import { Line } from "react-chartjs-2";
import { Chart, registerables } from "chart.js";
import zoomPlugin from "chartjs-plugin-zoom";
import PropTypes from "prop-types";

Chart.register(...registerables, zoomPlugin);

const Graph = ({ points, domain, range, onDomainRangeChange }) => {
  const debounceTimeout = useRef(null);

  const data = {
    datasets: [
      {
        label: "Graph",
        data: points.map(([x, y]) => ({ x, y })),
        borderColor: "#a5c5d6",
        borderWidth: 2,
        pointRadius: 0,
        showLine: true,
      },
    ],
  };

  const options = {
    responsive: true,
    maintainAspectRatio: false,
    scales: {
      x: {
        type: "linear",
        position: "bottom",
        min: domain[0],
        max: domain[1],
        ticks: {
          color: "#a5c5d6",
          font: {
            family: "'Manifold', sans-serif",
            size: 12,
          },
        },
        grid: {
          color: (ctx) =>
            ctx.tick.value === 0 ? "#a5c5d6" : "rgba(162, 192, 210, 0.2)",
          lineWidth: (ctx) => (ctx.tick.value === 0 ? 2 : 1),
        },
      },
      y: {
        type: "linear",
        position: "left",
        min: range[0],
        max: range[1],
        ticks: {
          color: "#a5c5d6",
          font: {
            family: "'Manifold', sans-serif",
            size: 12,
          },
        },
        grid: {
          color: (ctx) =>
            ctx.tick.value === 0 ? "#a5c5d6" : "rgba(162, 192, 210, 0.2)",
          lineWidth: (ctx) => (ctx.tick.value === 0 ? 2 : 1),
        },
      },
    },
    plugins: {
      legend: { display: false },
      zoom: {
        pan: {
          enabled: true,
          mode: "xy",
          threshold: 10,
          onPanComplete: ({ chart }) => handlePan(chart),
        },
        zoom: {
          wheel: {
            enabled: true,
            speed: 0.08,
          },
          pinch: { enabled: true },
          mode: "xy",
          animation: {
            duration: 0,
          },
          onZoomComplete: ({ chart }) => handleZoom(chart),
        },
      },
    },
    animation: {
      duration: 0,
    },
  };

  const handlePan = (chart) => {
    const xScale = chart.scales.x;
    const yScale = chart.scales.y;
    const newDomain = [xScale.min, xScale.max];
    const newRange = [yScale.min, yScale.max];
    onDomainRangeChange(newDomain, newRange);
  };

  const handleZoom = (chart) => {
    const xScale = chart.scales.x;
    const yScale = chart.scales.y;
    const newDomain = [xScale.min, xScale.max];
    const newRange = [yScale.min, yScale.max];
    clearTimeout(debounceTimeout.current);
    debounceTimeout.current = setTimeout(() => {
      onDomainRangeChange(newDomain, newRange);
    }, 0);
  };

  return (
    <div
      className="crt"
      style={{
        position: "relative",
        width: "100vw",
        height: "100vh",
        backgroundColor: "#061326",
        color: "#A2C0D2",
        fontFamily: "'Manifold', sans-serif",
        textShadow: "0 0 3px #A2C0D2",
        overflow: "hidden",
        imageRendering: "pixelated",
        boxShadow: "0 0 5px rgba(162, 192, 210, 0.3)",
      }}
    >
      <Line data={data} options={options} />

      {/* Radial Vignette */}
      <div
        style={{
          position: "absolute",
          top: 0,
          left: 0,
          width: "100%",
          height: "100%",
          pointerEvents: "none",
          background: "radial-gradient(circle, transparent 85%, #061326 100%)",
          mixBlendMode: "multiply",
        }}
      />

      {/* Inject both scanline + CRT effect CSS */}
      <style>{`
        @keyframes scanline {
          0% { transform: translateY(0); }
          100% { transform: translateY(3px); }
        }

        /* CRT Effect */
        .crt::before {
          content: "";
          display: block;
          position: fixed;
          top: 0; left: 0; right: 0; bottom: 0;
          z-index: 2;
          pointer-events: none;
          background:
            linear-gradient(rgba(18, 16, 16, 0) 50%, rgba(0, 0, 0, 0.25) 50%),
            linear-gradient(90deg, rgba(255, 0, 0, 0.06), rgba(0, 255, 0, 0.02), rgba(0, 0, 255, 0.06));
          background-size: 100% 3px, 4px 100%;
        }

        @keyframes flicker {
          0%  { opacity: 0.27861; }
          5%  { opacity: 0.34769; }
          10% { opacity: 0.23604; }
          15% { opacity: 0.10626; }
          20% { opacity: 0.18128; }
          25% { opacity: 0.10626; }
          30% { opacity: 0.18128; }
          35% { opacity: 0.23604; }
        }

        .crt::after {
          content: "";
          display: block;
          position: fixed;
          top: 0; left: 0; right: 0; bottom: 0;
          z-index: 2;
          pointer-events: none;
          background: rgba(18, 16, 16, 0.1);
          opacity: 0;
          animation: flicker 0.15s infinite;
        }
      `}</style>
    </div>
  );
};

Graph.propTypes = {
  points: PropTypes.arrayOf(PropTypes.arrayOf(PropTypes.number)).isRequired,
  domain: PropTypes.arrayOf(PropTypes.number).isRequired,
  range: PropTypes.arrayOf(PropTypes.number).isRequired,
  onDomainRangeChange: PropTypes.func.isRequired,
};

export default Graph;
