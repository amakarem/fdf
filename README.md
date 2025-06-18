# fdf 🗺️

A simple 3D wireframe (fil de fer) viewer built in C using MiniLibX, part of the 42 curriculum, that renders maps of elevation data with interactive controls.

---

## 📌 Overview

- Integrates **file parsing**, **3D projection**, **graphics rendering**, and **input handling**.
- Reads `.fdf` files containing rows of space-separated integers (and optional color codes).
- Displays an **isometric wireframe map** with real-time interactions — rotate, zoom, pan, scale, and change projections :contentReference[oaicite:1]{index=1}.

---

## ⚙️ Features

### ✅ Mandatory

- **Parsing**: Reads and converts input maps into a structured grid with coordinates and colors.
- **Rendering**: Draws map using **miniLibX** images and `put_pixel`.
- **Projection**: Provides **isometric view** by default.
- **Controls**:
  - Exit with `ESC` or the window close button.
  - Window management handles resizing, minimizing, and destroying properly :contentReference[oaicite:2]{index=2}.
  - Zoom: +, - or mouse wheel
  - Move: Arrow keys or W A S D
  - Rotate: mouse
  - Switch projection: P.
  - Reset: /
  - Exit: ESC or close window

### 🌟 Bonus (if implemented)

- Additional projections (e.g., parallel, top, perspective).
- Support for **zoom**, **translation**, and **rotation** via keyboard/mouse.
- **Adjustable height scaling** and color palettes for elevation visualization :contentReference[oaicite:3]{index=3}.

---

## 🛠️ Installation & Building

Dependencies:
- `gcc`
- MiniLibX (native or `mlx42`)
- Standard C libraries (`stdlib.h`, `unistd.h`, `math.h`) :contentReference[oaicite:4]{index=4}

```bash
git clone https://github.com/amakarem/fdf.git
cd fdf
make        # build mandatory part
make bonus  # build with additional features (if available)
