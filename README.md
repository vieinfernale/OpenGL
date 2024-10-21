# OpenGL

## IDE and Compiler
- [Visual Studio](https://visualstudio.microsoft.com/)
- [Visual Studio Code](https://code.visualstudio.com/)
- [Mingw-w64](https://www.mingw-w64.org/downloads/)
- [GLSLang](https://github.com/KhronosGroup/glslang)

## Libraries
- Window: [GLFW](https://www.glfw.org/download.html)
- Functions: [GLEW](https://glew.sourceforge.net/) 
- Windows Libraries: [Microsoft Documentation](https://learn.microsoft.com/en-us/search/)
- Images: [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h)
- Math: [GLM](https://github.com/g-truc/glm)
- 3D Models: [Assimp](https://github.com/assimp/assimp)
- Shader Compiler: [GLSLang](https://www.khronos.org/opengles/sdk/tools/Reference-Compiler/)

## Repository

```bash
/archive           Old code
/include           Header files (.h)
/lib               Library files (.lib .a)
/bin               Shader Compiler (glslang.exe)
/shaders           Shaders (.glsl)
.gitattributes     
.gitignore         
App.cpp            C++ / OpenGL
App.exe            
Build.cmd          Compiler CMD Script   
README.md
Shader.h           Shader
Texture.h          Texture
```

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

#include "Shader.h"              // Shader
#include "Texture.h"             // Texture

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
glslang -V -S vert "vertex_shader.glsl" -o "vertex_shader.spv"
glslang -V -S frag "fragment_shader.glsl" -o "fragment_shader.spv"
```
### Batch Script (Windows: .bat .cmd) Bash Script (Linux MacOS: .sh)
```batch
@echo off
:: Set project_dir to the current directory of the batch file
:: %~dp0 : permanent directory containing the batch script.
:: %cd% : current working directory of the Command Prompt session
set project_dir=%~dp0

:: Compile C++ / OpenGL
echo Compiling C++ / OpenGL
g++ App.cpp -o App ^
-I"%project_dir%/include" ^
-L"%project_dir%/lib" ^
-lglfw3 -lglew32 -lassimp -lopengl32 -luser32 -lgdi32 -lshell32

if errorlevel 1 (
    echo Error
) else (
    echo Compiled
)

:: Compile Shaders
set bin_dir=%project_dir%bin
set shader_dir=%project_dir%shaders

:: Vertex Shader
echo Compiling Vertex Shader
%bin_dir%/glslang -V -S vert "%shader_dir%/vertex_shader/vertex_shader.glsl" -o "%shader_dir%/vertex_shader/vertex_shader.spv"

if errorlevel 1 (
    echo Error
) else (
    echo Compiled
)

:: Fragment Shader
echo Compiling Fragment Shader
%bin_dir%/glslang -V -S frag "%shader_dir%/fragment_shader/fragment_shader.glsl" -o "%shader_dir%/fragment_shader/fragment_shader.spv"

if errorlevel 1 (
    echo Error
) else (
    echo Compiled
)

pause
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

## Debug
### Shader
- GLSLang
- NVIDIA Nsight Graphics
### Functions
- [Docs.gl](https://docs.gl/)
- [Chatgpt](https://chatgpt.com/) 