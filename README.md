# Graphing Calculator Web Demo

[Web Demo](https://calculator.elannash.com)

## Overview

The **Graphing Calculator Web Demo** is a web-based application for visualizing mathematical equations. Users can input an equation and explore its graph with pan and zoom functionality. This project serves as an interactive and user-friendly tool for visualizing mathematical concepts.

## Features

- **Interactive Graphing**: Pan and zoom through the graph with ease.
- **Equation Input**: Input equations using a clean and responsive UI.
- **Single Equation Support**: Currently supports visualizing one equation at a time.
- **Live Demo**: Try the application at [calculator.elannash.com](https://calculator.elannash.com).

## Technical Details

- **Frontend**: Developed with React and Chart.js for rendering the graphs.
- **Backend**: Written in **C++** and compiled to **WebAssembly** using **Emscripten**, providing high-performance computation of graphing points.
- **Point Count**: Currently limited to 500 points per graph due to single-threaded point generation.

## Background

This project is an updated version of the [previous graphing calculator project](https://github.com/elannash/graphing-calculator). Major updates to the frontend include:

- A more interactive and modern UI with improved graphing capabilities.
- The use of Chart.js for responsive and high-quality graph rendering.

While the backend utilizes WebAssembly for computation, the current version focuses on single-threaded performance for simplicity.

## Future Plans

- **Multithreading**: Introduce Web Workers to enable multithreaded point generation for smoother performance with higher point counts.
- **Multiple Equations**: Add support for graphing multiple equations simultaneously.
- **Enhanced Graphing Options**: Include features like customizable graph styles, annotations, and overlays.

## How to Use

1. **Visit the Web Demo**: Navigate to [calculator.elannash.com](https://calculator.elannash.com).
2. **Input Equation**: Enter a mathematical equation in the input box.
3. **Explore**: Pan and zoom the graph to explore the equation's behavior.

## Technical Challenges and Learnings

1. **WebAssembly Integration**: The backend, written in **C++**, was compiled to **WebAssembly** using **Emscripten**. This allowed high-performance computations in the browser while keeping the application lightweight.
2. **Graph Rendering**: Chart.js provided a straightforward approach to rendering graphs, but performance optimizations remain a priority, especially for higher point counts.
3. **Single-threaded Constraints**: The current version computes points sequentially, but future updates will leverage Web Workers for parallel processing.

## Contribution

This project is open-source, and contributions are welcome! Feel free to submit issues, feature requests, or pull requests via the [GitHub repository](https://github.com/elannash/graphing-calculator-web-demo).

---

Thank you for exploring the Graphing Calculator Web Demo! Feel free to reach out with feedback or feature suggestions.
