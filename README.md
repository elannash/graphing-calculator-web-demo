# Graphing Calculator Web Demo

Visit the [Web Demo](https://calculator.elannash.com) to explore interactive graphing.

## Overview

The **Graphing Calculator Web Demo** is a web-based application for visualizing mathematical equations. Users can input an equation and explore its graph with pan and zoom functionality. This project serves as an interactive and user-friendly tool for visualizing mathematical concepts.

## Features

- **Interactive Graphing**: Pan and zoom through the graph with ease.
- **Equation Input**: Input equations using a clean and responsive UI.
- **Single Equation Support**: Currently supports visualizing one equation at a time.
- **Live Demo**: Experience it at [calculator.elannash.com](https://calculator.elannash.com).

## Technical Details

- **Frontend**: Developed with React and Chart.js for rendering the graphs.
- **Backend**: Written in **C++** and compiled to **WebAssembly** using **Emscripten**, providing high-performance computation of graphing points.
- **Point Count**: Limited to 500 points per graph due to single-threaded point generation.

## Background

This project is an updated version of the [previous graphing calculator project](https://github.com/elannash/graphing-calculator). Major updates include:

- A more interactive and modern UI with improved graphing capabilities.
- Chart.js integration for responsive and high-quality graph rendering.

## Future Plans

- **Multithreading**: Use Web Workers to enable multithreaded point generation for smoother performance with higher point counts.
- **Multiple Equations**: Add support for graphing multiple equations simultaneously.
- **Enhanced Graphing Options**: Include features like customizable graph styles, annotations, and overlays.

## How to Use

1. **Visit the Web Demo**: Open [calculator.elannash.com](https://calculator.elannash.com).
2. **Input an Equation**: Enter a mathematical equation in the input box.
3. **Explore the Graph**: Use pan and zoom to visualize the equation.

## Technical Challenges and Learnings

1. **WebAssembly Integration**: The backend, written in **C++**, was compiled to **WebAssembly** using **Emscripten** for high-performance computation in the browser.
2. **Graph Rendering**: Chart.js enabled smooth graph rendering, but optimizations are needed for handling larger datasets.
3. **Single-threaded Constraints**: While the current version computes points sequentially, future updates will implement Web Workers for parallel processing.

## Contribution

This project is open-source, and contributions are welcome! Submit issues, feature requests, or pull requests via the [GitHub repository](https://github.com/elannash/graphing-calculator-web-demo).

---