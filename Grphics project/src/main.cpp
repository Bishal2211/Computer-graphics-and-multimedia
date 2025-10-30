#include "glad.h"
#include "glfw3.h"
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include "glm/glm/gtc/type_ptr.hpp"
#include <iostream>
#include <cmath>

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"uniform mat4 transform;\n"
"void main()\n"
"{\n"
"   gl_Position = transform * vec4(aPos, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec3 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(ourColor, 1.0);\n"
"}\0";

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Draw rectangle (car body or roof)
void drawRectangle(unsigned int shader, float x, float y, float width, float height, glm::vec3 color, glm::vec3 move);

// Draw circle (wheels)
void drawCircle(unsigned int shader, float x, float y, float r, glm::vec3 color, glm::vec3 move);

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Moving Car Animation", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

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

    glUseProgram(shaderProgram);

    double startTime = glfwGetTime();

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClearColor(0.6f, 0.8f, 1.0f, 1.0f); // sky color
        glClear(GL_COLOR_BUFFER_BIT);

        double currentTime = glfwGetTime();
        float moveX = fmod((float)(currentTime - startTime) * 0.3f, 2.0f) - 1.0f; // Move left to right
        glm::vec3 move(moveX, -0.3f, 0.0f);

        // Color changing
        float colorChange = fabs(sin(currentTime));
        glm::vec3 carColor(colorChange, 0.2f, 1.0f - colorChange);

        // Draw car body
        drawRectangle(shaderProgram, -0.4f, 0.0f, 0.6f, 0.2f, carColor, move);
        // Draw car roof
        drawRectangle(shaderProgram, -0.2f, 0.15f, 0.3f, 0.1f, carColor, move);
        // Draw wheels
        drawCircle(shaderProgram, -0.3f, -0.05f, 0.07f, {0.0f, 0.0f, 0.0f}, move);
        drawCircle(shaderProgram,  0.2f, -0.05f, 0.07f, {0.0f, 0.0f, 0.0f}, move);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void drawRectangle(unsigned int shader, float x, float y, float width, float height, glm::vec3 color, glm::vec3 move)
{
    float vertices[] = {
        x, y, 0.0f,
        x + width, y, 0.0f,
        x + width, y + height, 0.0f,
        x, y + height, 0.0f
    };
    unsigned int indices[] = { 0, 1, 2, 2, 3, 0 };

    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    int colorLoc = glGetUniformLocation(shader, "ourColor");
    int transformLoc = glGetUniformLocation(shader, "transform");

    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, move);

    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
    glUniform3fv(colorLoc, 1, glm::value_ptr(color));

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void drawCircle(unsigned int shader, float x, float y, float r, glm::vec3 color, glm::vec3 move)
{
    const int segments = 40;
    float vertices[(segments + 2) * 3];
    vertices[0] = x; vertices[1] = y; vertices[2] = 0.0f;

    for (int i = 0; i <= segments; i++) {
        float angle = i * 2.0f * 3.14159f / segments;
        vertices[(i + 1) * 3] = x + r * cos(angle);
        vertices[(i + 1) * 3 + 1] = y + r * sin(angle);
        vertices[(i + 1) * 3 + 2] = 0.0f;
    }

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    int colorLoc = glGetUniformLocation(shader, "ourColor");
    int transformLoc = glGetUniformLocation(shader, "transform");

    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, move);

    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
    glUniform3fv(colorLoc, 1, glm::value_ptr(color));

    glDrawArrays(GL_TRIANGLE_FAN, 0, segments + 2);

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
