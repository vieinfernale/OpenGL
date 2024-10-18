#include <GL/glew.h>             // GLEW for OpenGL functions
#include <GLFW/glfw3.h>          // GLFW for window and context management
#include <glm/glm.hpp>           // Include all GLM core / GLSL features
#include <glm/ext.hpp>           // Include all GLM extensions
#include <assimp/assimp_functions.h>  // Include specific assimp functions

#include "Shader.h"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

// Input Window 
void inputWindow(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// Resize Window
void sizeWindow(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// Create Window
GLFWwindow* createWindow () {

    // GLFW
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return nullptr;
    }

    // Monitor and Screensize
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* fullscreen = glfwGetVideoMode(monitor);

    // Window
    GLFWwindow* window = glfwCreateWindow(fullscreen->width, fullscreen->height, "OpenGL", monitor, nullptr);
    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    // Context and Resize
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, sizeWindow);

    return window;
}

int main()
{  
    // GLFW 
    GLFWwindow* window = createWindow();
    if (!window) return -1;

    // GLEW
    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    /* Shader */
    Shader Shader("./GLSL/vertex_shader.glsl", "./GLSL/fragment_shader.glsl");

    /* Window Loop */
    while (!glfwWindowShouldClose(window))
    {
        inputWindow(window);

        // Frame Color
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        /* Render */
        Shader.shaderDraw();

        // Render and Frozen screen
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}