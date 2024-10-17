#include ".\GLEW\include\GL\glew.h"      // GLEW for OpenGL functions
#include ".\GLFW\include\GLFW\glfw3.h"   // GLFW for window and context management
#include ".\glm\glm.hpp"                 // GLM for mathematics (vec3, vec4, ...)

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

// Vertex structure (matching the layout in the vertex shader)
struct vertex {
    glm::vec3 vp;    // layout (location = 0) position
    glm::vec4 vc;    // layout (location = 1) color
    glm::vec2 vt;    // layout (location = 2) textures
};

struct Shader {
    std::vector<vertex> vertices;
    std::string vertexShader;
    std::string fragmentShader;
    unsigned int shaderProgramID;
    unsigned int VAO, VBO;

    /* ShaderProgram = ID that represents the combination of the vertex shader ID and the fragment shader ID together after they are compiled. 
    The ID stored in the ShaderProgram will be used to render objects with the created shaders.
    VBO = Vertex Buffer Object = stores the vertex data (position, color, normal, texture coordinates, etc.) in the GPU's memory.
    VAO = Vertex Array Object = stores information about the VBO's vertices: 
    number of components in each vertex attribute (3 for position, 4 for color, 2 for texture, ...),
    data type (float),
    stride (the size in bytes between consecutive vertices),
    offset (where each attribute starts within the VBO).) */

    // Reader
    std::string shaderRead (const std::string& filePath)
    {
        std::ifstream shaderFile(filePath);  // Open the .glsl shader file at the given path 
        std::stringstream shaderString;
        shaderString << shaderFile.rdbuf();  // Read data of the .glsl files stored in shaderFile's internal buffer and transfer it to shaderString 
        return shaderString.str();           // Return the file content as a string
    }

    // Initialization
    Shader (const std::string& vertexShaderPath, const std::string fragmentShaderPath) : shaderProgramID(0), VBO(0), VAO(0) 
    {
        /* Shader is a constructor member initializer list (special function within struct).
        The constructor must have the same name as the struct to properly initialize objects of that type.
        Initializing shaderProgram, VBO, and VAO means that the unitialized variables will not hold garbage values and 0 signifies that no valid object is
        currently bound or initialized */

        // Read shaders
        vertexShader = shaderRead(vertexShaderPath);
        fragmentShader = shaderRead(fragmentShaderPath);

        // Intialize vertices with vertex data {position, color, texture}
        vertices = 
        {
            {glm::vec3{0.0f, 0.5f, 0.0f}, glm::vec4{1.0f, 0.0f, 0.0f, 1.0f}, glm::vec2{0.0f, 0.0f}},
            {glm::vec3{0.5f, -0.5f, 0.0f}, glm::vec4{0.0f, 1.0f, 0.0f, 1.0f}, glm::vec2{1.0f, 1.0f}},
            {glm::vec3{-0.5f, -0.5f, 0.0f}, glm::vec4{0.0f, 0.0f, 1.0f, 1.0f}, glm::vec2{0.0f, 1.0f}}
        };
    }

    // Creation and Compilation
    unsigned int shaderCompile (unsigned int shaderType, const std::string& shaderSourceCode)
    {
        /*type = GL_VERTEX_SHADER for vertex shaders, GL_FRAGMENT_SHADER for fragment shaders, GL_GEOMETRY_SHADER for geometry shaders, etc. */
        
        /* shaderID is a unique identifier for the shader object of the specified type created with glCreateShader */

        // Shader Creation
        unsigned int shaderID = glCreateShader(shaderType);

        /* OpenGL requires the shader source code to be passed as a C-string (const char*). 
        The source.c_str() method converts the C++ std::string into a C-style string. */

        // Read the shader source code
        const char* shaderSourceCodeCstr = shaderSourceCode.c_str();

        /* This function assigns the shader source code to the shader object identified by shaderID. 
        The first parameter is the shader object ID, the second is the number of strings being passed (1 in this case), 
        and the third is the address of the source code string. 
        The nullptr for the final argument indicates that OpenGL can automatically determine the length of the source code string. */

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

        // The function returns the shader's unique identifier, which is required for linking the shader object to an OpenGL shader program.
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
            std::cerr << "Error linking shader program: " << infoLog << std::endl;
        }

        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);

    }

    void shaderBuffers () 
    {
        // Generate and bind Vertex Array Object (VAO) and Vertex Buffer Object (VBO)
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        // Bind the VBO and upload the vertex data
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex), vertices.data(), GL_STATIC_DRAW);

        // Set up vertex attribute pointers
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, vp));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, vc));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, vt));
        glEnableVertexAttribArray(2);

        glBindVertexArray(0);
    }

    void draw() 
    {
        // Use the shader program
        glUseProgram(shaderProgramID);

        // Bind the VAO and draw the triangle
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    }

    ~Shader() 
    {
        // Cleanup
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteProgram(shaderProgramID);
    }
};

int main()
{
    // Initialize GLFW
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a window
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr);
    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    /* Shader */
    Shader Shader("vertex_shader.glsl", "fragment_shader.glsl");
    Shader.shaderProgram();
    Shader.shaderBuffers();

    /* Window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Shader */
        Shader.draw();

        // Render and Frozen screen
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}