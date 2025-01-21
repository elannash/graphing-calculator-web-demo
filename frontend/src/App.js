import React, { useState, useEffect, useRef } from "react";
import Graph from "./components/Graph";
import "./App.css";

const initialEquations = ["x*sin(x)", "x^2 - 5", "cos(x) + 2", "log(x + 10)", "x^2-sin(x*max(2,x))", "-sin(1/x^3)"];
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
          { first: 800, second: 800 },
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
        inputRefs.current[equations.length].readOnly = false;
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
        <button
          className="sidebar-toggle"
          onClick={toggleSidebar}
        >
          {sidebarVisible ? (
            <svg
              xmlns="http://www.w3.org/2000/svg"
              width="64"
              height="64"
              viewBox="734.44 514.03 461.46 304.94"
            >
              <path
                stroke="#A5C5D6"
                fill="#A5C5D6"
                strokeWidth="1"
                d="M1186.13, 646.47L1188.3, 648.88L1190.18, 651.44L1191.78, 654.14L1193.08, 656.96L1194.09, 659.86L1194.82, 662.83L1195.25, 665.85L1195.4, 668.89L1195.26, 671.93L1194.82, 674.94L1194.1, 677.92L1193.08, 680.82L1191.78, 683.63L1190.19, 686.33L1188.3, 688.89L1186.13, 691.3L1176.5, 700.92L1170.66, 706.61L1164.7, 712.11L1158.61, 717.44L1152.4, 722.58L1146.06, 727.55L1139.6, 732.33L1133.03, 736.94L1126.34, 741.36L1099.97, 723.53L1107.44, 719.07L1114.8, 714.34L1122.02, 709.36L1129.12, 704.11L1136.08, 698.6L1142.9, 692.83L1149.56, 686.8L1156.07, 680.5L1165.69, 670.87L1166.31, 669.95L1166.52, 668.89L1166.31, 667.83L1165.69, 666.9L1156.07, 657.27L1149.81, 651.21L1143.41, 645.39L1136.86, 639.81L1130.19, 634.48L1123.38, 629.39L1116.45, 624.54L1109.4, 619.93L1102.24, 615.56L1094.98, 611.44L1087.62, 607.56L1080.17, 603.92L1072.63, 600.52L1065.01, 597.36L1057.32, 594.45L1049.56, 591.78L1041.73, 589.35L1033.92, 587.18L1026.06, 585.25L1018.14, 583.55L1010.18, 582.1L1002.18, 580.87L994.15, 579.89L986.08, 579.15L977.99, 578.65L965.17, 578.35L956.65, 578.48L948.15, 578.88L939.67, 579.54L931.21, 580.47L922.79, 581.67L914.41, 583.12L906.07, 584.84L897.79, 586.83L866.84, 565.91L878.75, 562.03L890.78, 558.68L902.93, 555.83L915.19, 553.5L927.56, 551.69L940.01, 550.39L952.55, 549.61L965.17, 549.35L979.67, 549.69L994.08, 550.72L1008.36, 552.44L1022.52, 554.84L1036.54, 557.92L1050.4, 561.68L1064.1, 566.11L1077.62, 571.22L1091.34, 577.18L1104.7, 583.81L1117.68, 591.07L1130.27, 598.98L1142.45, 607.52L1154.23, 616.68L1165.58, 626.46L1176.5, 636.85L1186.13, 646.47"
              />
              <path
                stroke="#A5C5D6"
                fill="none"
                strokeWidth="1"
                d="M1041.73, 748.43L1033.92, 750.6L1026.05, 752.53L1018.14, 754.22L1010.18, 755.68L1002.18, 756.9L994.14, 757.88L986.07, 758.62L977.99, 759.12L965.17, 759.43L952.35, 759.12L944.26, 758.62L936.2, 757.88L928.16, 756.9L920.15, 755.68L912.19, 754.22L904.27, 752.52L896.4, 750.59L888.59, 748.42L880.77, 745.99L873.01, 743.32L865.32, 740.41L857.7, 737.25L850.16, 733.85L842.71, 730.21L835.36, 726.33L828.1, 722.21L820.94, 717.84L813.89, 713.23L806.97, 708.38L800.16, 703.29L793.48, 697.96L786.93, 692.38L780.53, 686.56L774.27, 680.5L764.64, 670.87L764.02, 669.94L763.82, 668.89L764.02, 667.83L764.64, 666.9L774.27, 657.27L782.12, 649.72L790.2, 642.56L798.49, 635.77L806.99, 629.37L815.67, 623.34L824.54, 617.69L833.57, 612.42L842.77, 607.53L896.53, 643.74L894.51, 649.87L893.04, 656.22L892.14, 662.77L891.83, 669.5L892.21, 676.93L893.31, 684.15L895.1, 691.12L897.55, 697.8L900.61, 704.15L904.25, 710.15L908.44, 715.74L913.13, 720.91L918.29, 725.6L923.89, 729.78L929.89, 733.43L936.24, 736.49L942.93, 738.93L949.89, 740.73L957.11, 741.83L964.55, 742.21L971.62, 741.87L978.5, 740.87L985.15, 739.25L991.55, 737.03L997.66, 734.25L1003.45, 730.93L1008.9, 727.12L1013.96, 722.83L1048.74, 746.26L1041.73, 748.43"
              />
              <path
                stroke="#A5C5D6"
                fill="none"
                strokeWidth="1"
                d="M927.05, 664.3L983.47, 702.29L979.02, 704.48L974.34, 706.07L969.5, 707.03L964.55, 707.34L960.68, 707.15L956.92, 706.58L953.29, 705.64L949.82, 704.37L946.51, 702.78L943.39, 700.88L940.47, 698.7L937.78, 696.26L935.34, 693.57L933.16, 690.66L931.26, 687.54L929.67, 684.23L928.39, 680.76L927.46, 677.13L926.89, 673.37L926.69, 669.5L927.05, 664.3"
              />
              <path
                stroke="#A5C5D6"
                fill="#A5C5D6"
                strokeWidth="1"
                d="M1167.84, 793.34L1169.98, 795.12L1171.67, 797.23L1172.9, 799.58L1173.65, 802.11L1173.91, 804.73L1173.65, 807.37L1172.88, 809.95L1171.56, 812.41L1169.79, 814.55L1167.68, 816.24L1165.32, 817.47L1162.8, 818.22L1160.17, 818.47L1157.53, 818.22L1154.94, 817.44L1152.49, 816.13L1078.4, 766.23L1077.62, 766.55L1064.1, 771.66L1050.4, 776.09L1036.54, 779.85L1022.52, 782.93L1008.36, 785.33L994.08, 787.05L979.67, 788.09L965.17, 788.43L950.66, 788.09L936.26, 787.05L921.97, 785.34L907.82, 782.94L893.8, 779.85L879.93, 776.1L866.24, 771.66L852.71, 766.55L838.99, 760.59L825.63, 753.96L812.65, 746.7L800.07, 738.79L787.88, 730.25L776.1, 721.09L764.75, 711.31L753.83, 700.92L744.21, 691.3L742.04, 688.89L740.16, 686.33L738.57, 683.63L737.26, 680.82L736.25, 677.91L735.52, 674.94L735.09, 671.92L734.94, 668.89L735.09, 665.85L735.52, 662.83L736.25, 659.86L737.26, 656.95L738.57, 654.14L740.16, 651.44L742.04, 648.88L744.21, 646.47L753.84, 636.84L760.94, 629.98L768.22, 623.37L775.69, 617.02L783.34, 610.94L791.17, 605.13L799.17, 599.58L807.35, 594.3L815.69, 589.29L741.98, 539.66L739.84, 537.88L738.15, 535.77L736.92, 533.42L736.17, 530.89L735.92, 528.27L736.17, 525.63L736.95, 523.05L738.26, 520.59L740.04, 518.45L742.15, 516.76L744.5, 515.53L747.03, 514.78L749.65, 514.53L752.3, 514.78L754.88, 515.56L757.34, 516.87L811.24, 553.18L843.72, 575.04L872.7, 594.57L910.98, 620.35L940.53, 640.25L1000.7, 680.77L1030.26, 700.68L1079.78, 734.03L1107.31, 752.57L1136.96, 772.55L1167.84, 793.34"
              />
            </svg>
          ) : (
            <svg
              xmlns="http://www.w3.org/2000/svg"
              width="64"
              height="64"
              viewBox="120.68 546.46 461.45 240.08"
            >
              <path
                stroke="#A5C5D6"
                fill="#A5C5D6"
                strokeWidth="1"
                d="M551.93, 668.48L542.3, 678.12L536.04, 684.18L529.64, 690L523.09, 695.57L516.41, 700.91L509.61, 706L502.68, 710.85L495.63, 715.46L488.47, 719.83L481.21, 723.95L473.86, 727.83L466.4, 731.47L458.87, 734.87L451.25, 738.03L443.56, 740.94L435.79, 743.61L427.97, 746.04L417.04, 749L406.02, 751.5L394.91, 753.54L383.72, 755.11L372.49, 756.22L361.21, 756.86L349.91, 757.04L338.59, 756.74L330.5, 756.24L322.43, 755.49L314.39, 754.51L306.39, 753.29L298.43, 751.83L290.51, 750.13L282.64, 748.2L274.83, 746.03L267.01, 743.6L259.25, 740.93L251.55, 738.02L243.94, 734.86L236.4, 731.47L228.95, 727.83L221.59, 723.94L214.33, 719.82L207.18, 715.45L200.13, 710.85L193.2, 706L186.39, 700.9L179.71, 695.57L173.17, 689.99L166.76, 684.18L160.5, 678.12L150.87, 668.48L150.26, 667.55L150.05, 666.49L150.26, 665.44L150.87, 664.51L160.5, 654.88L166.76, 648.82L173.17, 643L179.72, 637.42L186.4, 632.09L193.2, 626.99L200.13, 622.14L207.18, 617.54L214.34, 613.17L221.6, 609.04L228.96, 605.16L236.41, 601.52L243.94, 598.12L251.56, 594.97L259.26, 592.05L267.02, 589.38L274.84, 586.95L282.65, 584.79L290.52, 582.86L298.43, 581.16L306.4, 579.7L314.4, 578.48L322.43, 577.5L330.5, 576.76L338.59, 576.26L351.4, 575.96L364.23, 576.26L372.32, 576.76L380.38, 577.5L388.42, 578.48L396.42, 579.71L404.38, 581.16L412.3, 582.86L420.16, 584.79L427.97, 586.96L435.79, 589.39L443.56, 592.06L451.25, 594.97L458.87, 598.13L466.41, 601.53L473.86, 605.17L481.22, 609.05L488.48, 613.17L495.63, 617.54L502.68, 622.15L509.61, 627L516.42, 632.09L523.1, 637.42L529.64, 643L536.05, 648.82L542.3, 654.88L551.93, 664.51L552.55, 665.44L552.75, 666.49L552.55, 667.55L551.93, 668.48"
              />
              <path
                stroke="#A5C5D6"
                fill="#A5C5D6"
                strokeWidth="1"
                d="M572.37, 644.08L574.54, 646.49L576.42, 649.05L578.01, 651.75L579.32, 654.57L580.33, 657.47L581.05, 660.44L581.49, 663.46L581.63, 666.5L581.49, 669.54L581.05, 672.56L580.33, 675.53L579.32, 678.43L578.01, 681.24L576.42, 683.94L574.54, 686.5L572.37, 688.91L562.73, 698.54L551.81, 708.93L540.46, 718.71L528.69, 727.87L516.51, 736.41L503.92, 744.31L490.94, 751.58L477.58, 758.2L463.86, 764.16L450.34, 769.27L436.64, 773.71L422.77, 777.47L408.76, 780.55L394.6, 782.95L380.31, 784.67L365.91, 785.7L351.4, 786.04L336.9, 785.7L322.5, 784.67L308.21, 782.95L294.05, 780.55L280.04, 777.47L266.17, 773.71L252.47, 769.27L238.95, 764.16L225.22, 758.2L211.87, 751.58L198.89, 744.31L186.3, 736.4L174.12, 727.87L162.34, 718.71L150.99, 708.93L140.07, 698.54L130.45, 688.91L128.28, 686.5L126.39, 683.94L124.8, 681.24L123.5, 678.43L122.48, 675.53L121.76, 672.56L121.32, 669.54L121.18, 666.5L121.32, 663.46L121.76, 660.44L122.48, 657.47L123.5, 654.57L124.8, 651.75L126.39, 649.05L128.28, 646.49L130.45, 644.08L140.07, 634.46L150.99, 624.07L162.34, 614.29L174.12, 605.13L186.3, 596.59L198.89, 588.68L211.87, 581.42L225.22, 574.8L238.95, 568.83L252.47, 563.72L266.17, 559.29L280.04, 555.53L294.05, 552.45L308.21, 550.05L322.5, 548.33L336.9, 547.3L351.4, 546.96L365.91, 547.3L380.31, 548.33L394.6, 550.05L408.76, 552.45L422.77, 555.53L436.64, 559.29L450.34, 563.72L463.86, 568.83L477.58, 574.8L490.94, 581.42L503.92, 588.68L516.5, 596.59L528.69, 605.13L540.46, 614.29L551.81, 624.07L562.73, 634.46L572.37, 644.08"
              />
              <path
                stroke="#A5C5D6"
                fill="#A5C5D6"
                strokeWidth="1"
                d="M351.4, 705.57L347.53, 705.38L343.78, 704.81L340.15, 703.87L336.67, 702.6L333.36, 701.01L330.24, 699.11L327.33, 696.93L324.64, 694.49L322.2, 691.8L320.02, 688.89L318.12, 685.77L316.53, 682.46L315.25, 678.99L314.32, 675.36L313.75, 671.6L313.55, 667.73L313.75, 663.86L314.32, 660.11L315.25, 656.48L316.53, 653L318.12, 649.7L320.02, 646.58L322.2, 643.66L324.64, 640.98L327.33, 638.53L330.24, 636.36L333.36, 634.46L336.67, 632.87L340.15, 631.59L343.78, 630.66L347.53, 630.09L351.4, 629.89L355.27, 630.09L359.03, 630.66L362.66, 631.59L366.14, 632.87L369.45, 634.46L372.57, 636.36L375.48, 638.53L378.17, 640.98L380.62, 643.66L382.8, 646.58L384.69, 649.7L386.28, 653L387.56, 656.48L388.49, 660.11L389.06, 663.86L389.26, 667.73L389.06, 671.6L388.49, 675.36L387.56, 678.99L386.28, 682.46L384.69, 685.77L382.8, 688.89L380.62, 691.8L378.17, 694.49L375.48, 696.93L372.57, 699.11L369.45, 701.01L366.14, 702.6L362.66, 703.87L359.03, 704.81L355.27, 705.38L351.4, 705.57"
              />
              <path
                stroke="#A5C5D6"
                fill="#A5C5D6"
                strokeWidth="1"
                d="M351.4, 595.03L358.84, 595.41L366.06, 596.51L373.03, 598.3L379.71, 600.75L386.07, 603.81L392.06, 607.45L397.66, 611.63L402.83, 616.33L407.52, 621.49L411.71, 627.08L415.35, 633.08L418.41, 639.43L420.86, 646.11L422.65, 653.08L423.75, 660.3L424.13, 667.73L423.75, 675.17L422.65, 682.39L420.86, 689.35L418.41, 696.03L415.35, 702.39L411.71, 708.38L407.52, 713.98L402.83, 719.14L397.66, 723.83L392.06, 728.02L386.07, 731.66L379.71, 734.72L373.03, 737.17L366.06, 738.96L358.84, 740.06L351.4, 740.43L343.97, 740.06L336.75, 738.96L329.78, 737.17L323.1, 734.72L316.74, 731.66L310.75, 728.02L305.15, 723.83L299.99, 719.14L295.29, 713.98L291.11, 708.38L287.46, 702.39L284.4, 696.03L281.96, 689.35L280.16, 682.39L279.06, 675.17L278.69, 667.73L279.06, 660.3L280.16, 653.08L281.96, 646.11L284.4, 639.43L287.46, 633.08L291.11, 627.08L295.29, 621.49L299.99, 616.33L305.15, 611.63L310.75, 607.45L316.74, 603.81L323.1, 600.75L329.78, 598.3L336.75, 596.51L343.97, 595.41L351.4, 595.03"
              />
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
                  onClick={() => inputRefs.current[index]?.focus()}
                  onFocus={() => setEditingEquationIndex(index)}
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
