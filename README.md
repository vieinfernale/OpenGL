# OpenGL

## IDE and Compiler
- [Visual Studio](https://visualstudio.microsoft.com/)
- [Visual Studio Code](https://code.visualstudio.com/)
- [Mingw-w64](https://www.mingw-w64.org/downloads/)

## Libraries
- Window: [GLFW](https://www.glfw.org/download.html)
- Functions: [GLEW](https://glew.sourceforge.net/) 
- Windows Libraries: [Microsoft Documentation](https://learn.microsoft.com/en-us/search/)
- Images: [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h)
- Math: [GLM](https://github.com/g-truc/glm)
- 3D Models: [Assimp](https://github.com/assimp/assimp)
- Shader Compiler: [GLSLang](https://www.khronos.org/opengles/sdk/tools/Reference-Compiler/)

## Headers and Libraries

### Build and Compile the Libraries
- [CMake](https://cmake.org/download/)
- Download the binaries or clone the repository, build with cmake and compile with mingw64 (gcc) or visual studio (.sln file).
- Save the library files (.lib .a = static, .dll = dynamic) into the lib directory. 
- GLFW: git clone repository, cd glfw, cmake -G "MinGW Makefiles", mingw32-make, copy the include and libglfw3.a to the lib folder
- GLM: git clone repository, cd glm, mkdir build, cmake ., cd build, cmake --build ., copy glm folder to the include folder
- Assimp: git clone repository, cmake -DBUILD_SHARED_LIBS=OFF ., cmake --build ., copy files in include and lib

### Include the local Header Files (.h or .hpp)
```cpp
#include <GL/glew.h>             // GLEW for OpenGL functions
#include <GLFW/glfw3.h>          // GLFW for window and context management
#include <glm/glm.hpp>           // Include all GLM core / GLSL features
#include <glm/ext.hpp>           // Include all GLM extensions
#include <assimp/assimp_functions.h>  // Include specific assimp functions
#define STB_IMAGE_IMPLEMENTATION      // Compile stb_image (include only inside Textures.h)
#include <stb_image/stb_image.h>      // Include stb_image for textures

#include "Shader.h"              // Shader code

#include <iostream>              // STD Libraries
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
```
#### Include specific headers from a library
```cpp
// assimp_functions.h
#ifndef ASSIMP_FUNCTIONS_H
#define ASSIMP_FUNCTIONS_H

// Include any other specific headers
#include <assimp/Importer.hpp>
#include <assimp/Exporter.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#endif // ASSIMP_FUNCTIONS_H
```

### Link the Library Files (.lib, .a, or .dll)
- Libraries contain the compiled implementations of the functions declared in the header files.
- Link the GLFW and GLEW libraries for the Windows C++ Compiler MinGW64 (GCC) and include library flags for glfw, glew, opengl, and windows:

### CMD
```batch
g++ App.cpp -o App -I"%cd%/include" -L"%cd%/lib" -lglfw3 -lglew32 -lopengl32 -luser32 -lgdi32 -lshell32
```
### Batch Script (Windows: .bat .cmd) Bash Script (Linux MacOS: .sh)
```batch
@echo off
:: Set PROJECT_DIRECTORY to the current directory of the batch file
:: %~dp0 : permanent directory containing the batch script.
:: %cd% : current working directory of the Command Prompt session at the time of execution.
set PROJECT_DIRECTORY=%~dp0

g++ App.cpp -o App ^
-I"%PROJECT_DIRECTORY%/include" ^
-L"%PROJECT_DIRECTORY%/lib" ^
-lglfw3 -lglew32 -lassimp -lopengl32 -luser32 -lgdi32 -lshell32

pause
:: Script to Compile & Run the C++ file with the OpenGL library
```

### Visual Studio
#### Configuration Properties: VC++ Directories
- Include Directories 
    - $(SolutionDir)GLFW\include; 
    - $(SolutionDir)GLEW\include;
- Library Directories  
    - $(SolutionDir)GLFW\lib-vc2022; 
    - $(SolutionDir)GLEW\lib\Release\x64;     
#### Linker: Input 
- Additional Dependencies: 
    - glfw3.lib; 
    - glew32.lib;
    - Opengl: opengl32.lib;
    - Windows Libraries: User32.lib; Gdi32.lib; Shell32.lib;

# Debug: find errors

## Functions
- [Docs.gl](https://docs.gl/)
- [Chatgpt](https://chatgpt.com/) 
### VSCode
- Select the function text and type ```Ctrl + Shift + P```
- Search for ```Show definition preview hover```
- Hover through the function to show the necessary parameters
- ```Ctrl + K + Ctrl + I``` also shows hover information
### OpenGL CPP
```cpp
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
```