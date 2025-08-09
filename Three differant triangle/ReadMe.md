# OpenGL - Displaying Three Different Triangles in Different Quadrants

## Student Information

- **Name:** Ismam Ahmed
- **ID:** [0432220005101116]
- **Section:** [6B2]
- **University:** University of Information Technology and Sciences (UITS)

---

## Project Description

This project is an **OpenGL (Modern Core Profile)** program written in **C++** that displays three different types of triangles in different quadrants of the screen, each with its own unique color.

### **Requirements from the Question**

1. Display **three different types of triangles**:
   - **Right-Angled Triangle**
   - **Equilateral Triangle**
   - **Isosceles Triangle**
2. Place each triangle in **different coordinates/quadrants**:
   - **First Quadrant:** Equilateral Triangle
   - **Second Quadrant:** Isosceles Triangle
   - **Third Quadrant:** Right-Angled Triangle
3. Assign **three different colors** to the triangles.

---

## Implementation Details

- **Language:** C++
- **Libraries Used:**
  - [GLFW](https://www.glfw.org/) for window and input handling.
  - [GLAD](https://glad.dav1d.de/) for loading OpenGL function pointers.
- **OpenGL Version:** 3.3 Core Profile

### **Triangle Placement & Colors**

| Triangle Type | Quadrant     | Color           |
| ------------- | ------------ | --------------- |
| Equilateral   | 1st Quadrant | Cyan (0, 1, 1)  |
| Isosceles     | 2nd Quadrant | Green (0, 1, 0) |
| Right-Angled  | 3rd Quadrant | Red (1, 0, 0)   |

---

## **How It Works**

1. **Shaders**
   - One **vertex shader** is used for all triangles.
   - Three separate **fragment shaders** are created for different colors.
2. **Vertex Data**
   - Each triangle has its own set of vertex coordinates stored in separate **Vertex Buffer Objects (VBOs)**.
   - Each triangle has its own **Vertex Array Object (VAO)** for rendering.
3. **Rendering Loop**
   - Clears the background with a dark teal color.
   - Draws each triangle using its VAO and its specific shader program for color.

---

## **Controls**

- Press **I** → Exit the program.

---

## **Setup & Compilation**

### **Dependencies**

- Install **GLFW** and **GLAD**.
- Link the following libraries when compiling:
  - `glfw3`
  - `opengl32` (Windows) or `GL` (Linux)
  - `gdi32` (Windows)

### **Example Compilation Command (Linux)**

```bash
g++ main.cpp -o triangles -lglfw -ldl -lGL
./triangles
```
