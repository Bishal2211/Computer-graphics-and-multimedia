#include "glad.h"
#include "glfw3.h"
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include "glm/glm/gtc/type_ptr.hpp"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

// ---------- Function declarations ----------
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// ---------- Window settings ----------
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// ---------- Shaders ----------
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"uniform mat4 transform;\n"
"void main()\n"
"{\n"
"   gl_Position = transform * vec4(aPos, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = ourColor;\n"
"}\0";

// ---------- Game Variables ----------
float boxX = 0.0f, boxY = 0.0f;
float boxW = 0.25f, boxH = 0.25f; // slightly larger base size
bool clicked = false;
bool gotPointThisCycle = false;
int score = 0;
double mouseX, mouseY;
float moveTimer = 0.0f;
float moveInterval = 2.0f;

// Convert screen coords to NDC (-1 to 1)
float toNDC_X(double x) { return (float)(x / (SCR_WIDTH / 2.0) - 1.0); }
float toNDC_Y(double y) { return (float)(1.0 - y / (SCR_HEIGHT / 2.0)); }

// Mouse click callback
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        clicked = true;
}

// ---------- Main ----------
int main()
{
    srand((unsigned)time(0));

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Click The Box (Scaling Visible) ", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD\n";
        return -1;
    }

    // Compile shaders
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Square (2 triangles)
    float vertices[] = {
        -0.2f, -0.2f, 0.0f,
         0.2f, -0.2f, 0.0f,
         0.2f,  0.2f, 0.0f,
         0.2f,  0.2f, 0.0f,
        -0.2f,  0.2f, 0.0f,
        -0.2f, -0.2f, 0.0f
    };

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    float lastTime = glfwGetTime();

    // Random start
    boxX = (float)(rand() % 200 - 100) / 100.0f * 0.7f;
    boxY = (float)(rand() % 200 - 100) / 100.0f * 0.7f;

    // ---------- Render Loop ----------
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        float currentTime = glfwGetTime();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;
        moveTimer += deltaTime;

        // Background
        glClearColor(0.15f, 0.25f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // --- Click check ---
        if (clicked)
        {
            glfwGetCursorPos(window, &mouseX, &mouseY);
            float mx = toNDC_X(mouseX);
            float my = toNDC_Y(mouseY);

            if (mx > boxX - boxW && mx < boxX + boxW &&
                my > boxY - boxH && my < boxY + boxH)
            {
                score++;
                gotPointThisCycle = true;
                std::cout << "✅ Hit! Score: " << score << std::endl;

                // Move immediately when clicked
                boxX = (float)(rand() % 200 - 100) / 100.0f * 0.7f;
                boxY = (float)(rand() % 200 - 100) / 100.0f * 0.7f;
                moveTimer = 0.0f;
            }
            clicked = false;
        }

        // --- Auto move ---
        if (moveTimer >= moveInterval)
        {
            if (!gotPointThisCycle)
            {
                score--;
                std::cout << "❌ Missed! Score: " << score << std::endl;
            }

            boxX = (float)(rand() % 200 - 100) / 100.0f * 0.7f;
            boxY = (float)(rand() % 200 - 100) / 100.0f * 0.7f;
            moveTimer = 0.0f;
            gotPointThisCycle = false;
        }

        // --- Animated Color ---
        float red   = (sin(currentTime * 1.2f) + 1.0f) / 2.0f;
        float green = (cos(currentTime * 1.3f) + 1.0f) / 2.0f;
        float blue  = (sin(currentTime * 0.9f) + 1.0f) / 2.0f;

        // --- Visible Scaling Animation ---
       
        float scaleFactor = sin(glfwGetTime()) * 0.5f + 1.0f; // Sin gives a value between -1 and 1, so scale from 0.5 to 1.5
       

        // --- Draw the Box ---
        glUseProgram(shaderProgram);
        int transformLoc = glGetUniformLocation(shaderProgram, "transform");
        int colorLoc = glGetUniformLocation(shaderProgram, "ourColor");

        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(boxX, boxY, 0.0f));
        transform = glm::scale(transform, glm::vec3(boxW * scaleFactor, boxH * scaleFactor, 1.0f));

        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
        glUniform4f(colorLoc, red, green, blue, 1.0f);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}

// ESC to close
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// Resize viewport
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
