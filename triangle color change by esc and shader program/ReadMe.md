# OpenGL - Upside-Down Triangle with Color Transition

## Student Information

**Name:** Ismam Ahmed
**ID:** \[0432220005101116]
**Section:** \[6B2]
**University:** University of Information Technology and Sciences (UITS)

---

## Project Description

This project is an OpenGL (Modern Core Profile) program written in C++ that displays a single **upside-down triangle** at the center of the screen. The triangle smoothly transitions its color from **cyan** to **white** and back. Pressing the **Escape key** immediately changes the triangle color to **red**.

---

## Requirements from the Question

* Display an **upside-down triangle** at the center of the window.
* Triangle color should **gradually transition**: Cyan ↔ White.
* Pressing the **Escape key** changes the triangle color to **red**.
* Window title should display the **student’s ID**.

---

## Implementation Details

**Language:** C++
**Libraries Used:**

* GLFW for window creation and input handling.
* GLAD for loading OpenGL function pointers.
  **OpenGL Version:** 3.3 Core Profile

---

## Triangle Placement & Colors

| Triangle Type   | Position | Initial Color  | Color Transition |
| --------------- | -------- | -------------- | ---------------- |
| Upside-Down     | Center   | Cyan (0, 1, 1) | Cyan ↔ White     |
| On Escape Press | Center   | Red (1, 0, 0)  | Stays Red        |

---

## How It Works

### Shaders

* **Vertex Shader:** Passes vertex positions directly to the fragment shader.
* **Fragment Shader:** Uses a uniform variable `ourColor` to set the triangle’s color dynamically.

### Vertex Data

* Triangle vertex coordinates define an **upside-down triangle**.
* Vertex coordinates are stored in a **Vertex Buffer Object (VBO)**.
* A **Vertex Array Object (VAO)** is used to render the triangle.

### Color Transition

* The red channel is calculated using a **sine wave**:

```cpp
float mixValue = (sin(glfwGetTime()) / 2.0f) + 0.5f;
float r = mixValue;  // 0 → 1 over time
float g = 1.0f;      // constant
float b = 1.0f;      // constant
```

* When `r = 0` → Triangle is **Cyan** `(0,1,1)`
* When `r = 1` → Triangle is **White** `(1,1,1)`
* Smoothly oscillates back and forth, creating a **dynamic color transition**.

### Escape Key Behavior

* Pressing **Escape** sets a flag `escPressed = true`.
* When this flag is true, the triangle color immediately changes to **Red (1,0,0)** and remains red.

### Rendering Loop

1. Clears the screen with a **black background**.
2. Updates the triangle color based on **time or Escape flag**.
3. Draws the triangle using its **VAO** and **shader program**.
4. Polls for keyboard input and updates the window.

---

## Controls

* **Escape Key (Esc)** → Change triangle color to **red**.

---

## Setup & Compilation

### Dependencies

* Install **GLFW** and **GLAD**.

### Linking Libraries

* **Windows:** glfw3, opengl32, gdi32
* **Linux:** glfw, GL

### Compilation

* Compile your C++ code with **OpenGL, GLFW, and GLAD** linked.
* Run the executable → window title shows your **student ID**, triangle displays at the center with **cyan ↔ white** transition.

---

## Folder Structure Suggestion

```
0432220005101116_OpenGL_Triangle/
│
├── main.cpp        # Main OpenGL code
├── glad/           # GLAD loader files
├── glfw/           # GLFW library
└── README.md       # This file
```
