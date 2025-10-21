# 🧑‍🎓 Student Information
**Name:** Ismam Ahmed  
**ID:** 0432220005101116  
**Section:** 6B2  
**University:** University of Information Technology and Sciences (UITS)

---

# 🧩 Project Description
This project is an **OpenGL (Modern Core Profile)** program written in **C++** that displays a **moving green square** on the screen.  
The square continuously moves in both **X** and **Y** directions using a smooth sine-wave motion.  
Its **green color intensity** also changes over time, creating a glowing animation.  

The project demonstrates **2D transformation** using **GLM** (`glm::translate`) and real-time **uniform color updates** in shaders.

---

# 📋 Requirements
- Display a square made of two triangles.  
- The square should move smoothly in both **X** and **Y** directions.  
- Color should change dynamically over time.  
- Use **GLM transformation** (translate matrix).  
- Pressing **Escape (Esc)** should close the window.  
- The window title should display the student’s name.

---

# ⚙️ Implementation Details
**Language:** C++  
**Libraries Used:**
- **GLFW** → Window creation and input handling  
- **GLAD** → Load OpenGL function pointers  
- **GLM** → Matrix transformations (`translate`, `value_ptr`)  
- **stb_image.h** → Image loading header (included but not used)

**OpenGL Version:** 3.3 Core Profile  

---

# 🧱 Square Geometry
The square is made using **two triangles** (6 vertices):

| Triangle | Vertex Coordinates (x, y, z) |
|-----------|------------------------------|
| 1st | (0.5, 0.5, 0.0), (0.5, -0.5, 0.0), (-0.5, -0.5, 0.0) |
| 2nd | (0.5, 0.5, 0.0), (-0.5, -0.5, 0.0), (-0.5, 0.5, 0.0) |

---

# 🎨 Color & Transformation Animation

### 🔹 Dynamic Color
The fragment shader uses a uniform variable `ourColor` to set color:
```cpp
float timeValue = glfwGetTime();
float greenValue = sin(timeValue) / 2.0 + 0.5;
glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
