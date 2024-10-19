#include <GL/glew.h>                  // GLEW for OpenGL functions
#include <GLFW/glfw3.h>               // GLFW for window and context management
#include <glm/glm.hpp>                // Include all GLM core / GLSL features for math
#include <glm/ext.hpp>                // Include all GLM extensions
#include <assimp/assimp_functions.h>  // Include specific assimp functions for 3D Models (Mesh)

#include "Shader.h"
#include "Texture.h"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

// Compile: checkGLError(glFunction)
void checkGLError(const std::string& location) {
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::string error;
        switch (err) {
            case GL_INVALID_ENUM:                  error = "GL_INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                 error = "GL_INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:             error = "GL_INVALID_OPERATION"; break;
            case GL_STACK_OVERFLOW:                error = "GL_STACK_OVERFLOW"; break;
            case GL_STACK_UNDERFLOW:               error = "GL_STACK_UNDERFLOW"; break;
            case GL_OUT_OF_MEMORY:                 error = "GL_OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "GL_INVALID_FRAMEBUFFER_OPERATION"; break;
            default:                               error = "UNKNOWN_ERROR"; break;
        }
        std::cerr << "OpenGL Error (" << error << ") at " << location << std::endl;
    }
}


// Input Window 
void inputWindow(GLFWwindow* window)
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
    GLFWwindow* window = glfwCreateWindow(fullscreen->width, fullscreen->height, "OpenGL", nullptr, nullptr);
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

    /* Texture */
    unsigned int texture = loadTexture("./archive/Images/Img.jpg");

    /* Shader */
    Shader Shader("./shaders/Vertex_Shader/vertex_shader.glsl", "./shaders/Fragment_Shader/fragment_shader.glsl");

    /* Window Loop */
    while (!glfwWindowShouldClose(window))
    {
        inputWindow(window);

        // Frame Color
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Render

        /* Texture */
        // glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        /* Shader */
        Shader.shaderDraw();
        // Shader.setInt("fsTex", 0); 

        // Render and Frozen screen
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}