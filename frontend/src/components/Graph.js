import React, { useRef } from "react";
import { Line } from "react-chartjs-2";
import { Chart, registerables } from "chart.js";
import zoomPlugin from "chartjs-plugin-zoom";

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
            easing: "easeOutQuad",
            duration: 100,
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
      style={{
        position: "relative",
        width: "100vw",
        height: "100vh",
        backgroundColor: "#061326",
        color: "#A2C0D2",
        fontFamily: "'Manifold', sans-serif",
        textShadow: "0 0 3px #A2C0D2",
        border: "2px solid #A2C0D2",
        overflow: "hidden",
        imageRendering: "pixelated",
        boxShadow: "0 0 5px rgba(162, 192, 210, 0.3)",
      }}
    >
      <Line data={data} options={options} />
      <div
        style={{
          position: "absolute",
          top: 0,
          left: 0,
          width: "100%",
          height: "100%",
          pointerEvents: "none",
          background: `repeating-linear-gradient(
            transparent 0px,
            rgba(255, 255, 255, 0.02) 1px,
            transparent 1px,
            transparent 3px
          ),
          repeating-linear-gradient(
            90deg,
            transparent 0px,
            rgba(255, 255, 255, 0.02) 1px,
            transparent 1px,
            transparent 3px
          )`,
        }}
      />

      <div
        style={{
          position: "absolute",
          top: 0,
          left: 0,
          width: "100%",
          height: "100%",
          pointerEvents: "none",
          background: "radial-gradient(circle, transparent 90%, #061326 100%)",
          mixBlendMode: "multiply",
        }}
      />
    </div>
  );
};

export default Graph;
