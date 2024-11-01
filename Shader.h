#ifndef SHADER_H
#define SHADER_H
// #include "Shader.h"

#include <GL/glew.h>             // GLEW for OpenGL functions
#include <GLFW/glfw3.h>          // GLFW for window and context management
#include <glm/glm.hpp>           // Include all GLM core / GLSL features
#include <glm/ext.hpp>           // Include all GLM extensions
#include <assimp/assimp_functions.h>  // Include specific assimp functions

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

// Vertex
struct Vertex {
    glm::vec3 Position;    // layout (location = 0) position
    glm::vec4 Color;       // layout (location = 1) color
    glm::vec2 Tex;         // layout (location = 2) textures
};

// Shader
struct Shader {

    std::vector<Vertex> vertices;
    std::vector<int> indices;
    std::string vertexShader;
    std::string fragmentShader;
    unsigned int shaderProgramID;
    unsigned int VAO, VBO, EBO;

    // Constructor
    Shader (const std::string& vertexShaderPath, const std::string fragmentShaderPath) : shaderProgramID(0), VBO(0), VAO(0) 
    {
        // Read shaders
        vertexShader = shaderRead(vertexShaderPath);
        fragmentShader = shaderRead(fragmentShaderPath);

        // Intialize vertices with vertex data {position, color, texture} = Input for the Vertex Shader
        vertices = 
        {
            {glm::vec3{-0.5f, -0.5f, 0.0f}, glm::vec4{1.0f, 0.0f, 0.0f, 1.0f}, glm::vec2{0.0f, 1.0f}},
            {glm::vec3{-0.5f, 0.5f, 0.0f}, glm::vec4{0.0f, 1.0f, 0.0f, 1.0f}, glm::vec2{0.0f, 0.0f}},
            {glm::vec3{0.5f, 0.5f, 0.0f}, glm::vec4{0.0f, 0.0f, 1.0f, 1.0f}, glm::vec2{1.0f, 0.0f}},
            {glm::vec3{0.5f, -0.5f, 0.0f}, glm::vec4{0.0f, 0.0f, 1.0f, 1.0f}, glm::vec2{1.0f, 1.0f}},
        };

        indices =
        {
            0, 1, 2,
            2, 3, 0
        };

        shaderProgram();
        shaderBuffer();
    }

    // Reader
    std::string shaderRead (const std::string& filePath)
    {
        std::ifstream shaderFile(filePath);  
        std::stringstream shaderString;
        shaderString << shaderFile.rdbuf(); 
        return shaderString.str();           
    }

    // Compiler
    unsigned int shaderCompile (unsigned int shaderType, const std::string& shaderSourceCode)
    {
        // Shader Creation
        unsigned int shaderID = glCreateShader(shaderType);

        // Read the shader source code
        const char* shaderSourceCodeCstr = shaderSourceCode.c_str();

        // Assigns the shader source code to the shader object identified by shaderID
        glShaderSource(shaderID, 1, &shaderSourceCodeCstr, nullptr);

        // Compile the shader source code into machine GPU code
        glCompileShader(shaderID);

        // Compilation error log
        int success;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
        if (!success) 
        {
            char infoLog[512];
            glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
            std::cout << "Error compiling shader: " << infoLog << std::endl;
        }

        // The function returns the shader's unique identifier
        return shaderID;
    }

    void shaderProgram () 
    {
        // Compile the vertex and fragment shader
        unsigned int vertexShaderID = shaderCompile(GL_VERTEX_SHADER, vertexShader);
        unsigned int fragmentShaderID = shaderCompile(GL_FRAGMENT_SHADER, fragmentShader);

        // Link the unique identifiers of the vertex and fragment shaders to the shaderProgramID
        shaderProgramID = glCreateProgram();
        glAttachShader(shaderProgramID, vertexShaderID);
        glAttachShader(shaderProgramID, fragmentShaderID);
        glLinkProgram(shaderProgramID);

        // Linking error log
        int success;
        glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetProgramInfoLog(shaderProgramID, 512, nullptr, infoLog);
            std::cout << "Error linking shader program: " << infoLog << std::endl;
        }

        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);

    }

    void shaderBuffer () 
    {
        // Generate and Bind Vertex Buffers
        glGenVertexArrays(1, &VAO); // Vertex Array Object (VAO) 
        glGenBuffers(1, &VBO);      // Vertex Buffer Object (VBO) : vertices
        glGenBuffers(1, &EBO);      // Element Buffer Object (EBO) : index

        glBindVertexArray(VAO);

        // VBO
        /* Creates a vertex buffer, allocates memory for storing vertex data, uploads the vertex data to the GPU, 
        and specifies that this data is for static use. */
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

        // EBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), indices.data(), GL_STATIC_DRAW);

        // Vertex attribute pointers = layout, vecn, type, normalized, stride, first pointer
        // Position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
        glEnableVertexAttribArray(0);
        // Color
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));
        glEnableVertexAttribArray(1);
        // Texture
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tex));
        glEnableVertexAttribArray(2);

        // Ubind the VAO
        glBindVertexArray(0);
    }

    void shaderDraw() 
    {
        // Use the shader program
        glUseProgram(shaderProgramID);

        // Bind the VAO
        glBindVertexArray(VAO);

        // glDrawArrays(GL_TRIANGLES, 0, vertices.size());
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    }

    // Bind Uniform 1D
    void bindUniformBool(const std::string& name, bool value)
    {         
        glUniform1i(glGetUniformLocation(shaderProgramID, name.c_str()), (int)value); 
    }

    void bindUniformInt(const std::string& name, int value)
    { 
        glUniform1i(glGetUniformLocation(shaderProgramID, name.c_str()), value); 
    }

    void bindUniformFloat(const std::string& name, float value)
    { 
        glUniform1f(glGetUniformLocation(shaderProgramID, name.c_str()), value); 
    }

    // Destructor
    ~Shader() 
    {
        // Cleanup
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteProgram(shaderProgramID);
    }
    
};

#endif