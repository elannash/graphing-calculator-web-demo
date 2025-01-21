/* eslint-disable no-restricted-globals */

self.onmessage = async function (event) {
    const { equation, domain, range, pointCount, wasmPath } = event.data;
  
    try {
      const wasmModule = await WebAssembly.instantiateStreaming(fetch(wasmPath), {});
      const { generate_points, init_graph_info, set_equation_char } = wasmModule.instance.exports;
  
      init_graph_info(domain[0], domain[1], range[0], range[1], equation.length);
  
      for (let i = 0; i < equation.length; i++) {
        set_equation_char(i, equation.charCodeAt(i));
      }
  
      const points = [];
      const step = (domain[1] - domain[0]) / pointCount;
  
      for (let i = 0; i < pointCount; i++) {
        const x = domain[0] + i * step;
        const y = generate_points(x);
  
        if (y >= range[0] && y <= range[1]) {
          points.push([x, y]);
        }
      }
  
      self.postMessage(points);
    } catch (error) {
      console.error("Error in Web Worker:", error);
      self.postMessage([]);
    }
  };
  