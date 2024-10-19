#include <GL/glew.h>                  // GLEW for OpenGL functions
#include <GLFW/glfw3.h>               // GLFW for window and context management
#include <glm/glm.hpp>                // Include all GLM core / GLSL features for math
#include <glm/ext.hpp>                // Include all GLM extensions
#include <assimp/assimp_functions.h>  // Include specific assimp functions for 3D Models (Mesh)
#define STB_IMAGE_IMPLEMENTATION      // Compile stb_image
#include <stb_image/stb_image.h>      // Include stb_image for textures

#include "Shader.h"

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

unsigned int loadTexture (const std::string& imageFilePath) 
{
    unsigned int textureID;
    int width, height, nChannels;

    // Generate and Bind texture ID
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // S-axis Horizontal
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // T-axis Vertical
    // Minification: Texture is displayed smaller than its original size; involves sampling algorithms to determine texel colors
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
    // Magnification: Texture is displayed larger than its original size; involves sampling algorithms to determine texel colors
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // GL_LINEAR produces a smoother pattern where the individual pixels are less visible.

    // Load the image using stb_image.h
    unsigned char* imageData = stbi_load(imageFilePath.c_str(), &width, &height, &nChannels, 0);

    // Process image
    if (imageData != NULL) {
        std::cout << width << height << nChannels << std::endl;
        // Check format
        unsigned int format = (nChannels == 4) ? GL_RGBA : GL_RGB;
        std::cout << format << " " << GL_RGB << std::endl;
        // Upload texture to OpenGL
        /* 2D Texture, 0 - normal 1,2... - small mipmaps, color RGB/RGBA, border=0, color = unsigned bytes, image data pointer */
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, imageData); 
        // Generate Mipmaps: smaller images with lower resolutions
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load the image: " << imageFilePath << std::endl;
    }

    stbi_image_free(imageData);

    return textureID;
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
    unsigned int texture = loadTexture("./Archive/Images/Img.jpg");

    /* Shader */
    Shader Shader("./GLSL/vertex_shader.glsl", "./GLSL/fragment_shader.glsl");

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