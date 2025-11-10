# 🧑‍🎓 Student Information
**Name:** Ismam Ahmed  
**ID:** 0432220005101116  
**Section:** 6B2  
**University:** University of Information Technology and Sciences (UITS)  

**Group Members:**  
**Tamanna Khokon** – ID: 432310005101082  
**Anas** – ID: 2125051119  

---

# 🧩 Project Description
This project is an **OpenGL (Modern Core Profile)** program written in **C++** that displays an **interactive color-changing box** on the screen.  
The box continuously changes its **color** and **size** over time using smooth sine and cosine animations.  
It also moves to **random positions** automatically every few seconds.  

The player can **click on the moving box** to gain points — if missed, the score decreases.  
The project demonstrates **2D transformation** using **GLM** (`glm::translate`, `glm::scale`) and real-time **uniform updates** in shaders.

---

# 📋 Requirements
- Display a square (box) made of two triangles.  
- The box should move to **random positions** automatically.  
- The **color** and **scale (size)** should change smoothly over time.  
- Clicking the box increases score; missing it decreases score.  
- Use **GLM transformation** (`translate`, `scale`, `value_ptr`).  
- Pressing **Escape (Esc)** should close the window.  
- The window title should display the student’s name.  

---

# ⚙️ Implementation Details
**Language:** C++  
**Libraries Used:**  
- **GLFW** → Window creation and input handling  
- **GLAD** → Load OpenGL function pointers  
- **GLM** → Matrix transformations (`translate`, `scale`, `value_ptr`)  

**OpenGL Version:** 3.3 Core Profile  

---

# 🧱 Box Geometry
The box is made using **two triangles** (6 vertices):

| Triangle | Vertex Coordinates (x, y, z) |
|-----------|------------------------------|
| 1st | (-0.2, -0.2, 0.0), (0.2, -0.2, 0.0), (0.2, 0.2, 0.0) |
| 2nd | (0.2, 0.2, 0.0), (-0.2, 0.2, 0.0), (-0.2, -0.2, 0.0) |

---

# 🎨 Color, Scaling & Translation Animation

### 🔹 Dynamic Color
The fragment shader uses a uniform variable `ourColor` to change color over time:
```cpp
float red   = (sin(currentTime * 1.2f) + 1.0f) / 2.0f;
float green = (cos(currentTime * 1.3f) + 1.0f) / 2.0f;
float blue  = (sin(currentTime * 0.9f) + 1.0f) / 2.0f;
glUniform4f(colorLocation, red, green, blue, 1.0f);
