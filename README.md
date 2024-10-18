# OpenGL

## Environment
- [Visual Studio](https://visualstudio.microsoft.com/)
- [Visual Studio Code](https://code.visualstudio.com/docs/cpp/config-mingw)
- [Mingw-w64](https://www.mingw-w64.org/downloads/)

## Libraries
- Window: [GLFW](https://www.glfw.org/download.html)
- Functions: [GLEW](https://glew.sourceforge.net/) 
- Windows Libraries: [Microsoft Documentation](https://learn.microsoft.com/en-us/search/)
- Math: [GLM](https://github.com/g-truc/glm)
- Model Loading: [Assimp](https://github.com/assimp/assimp)

# Build and Compile the Libraries
- [CMake](https://cmake.org/download/)
- Download the binaries or clone the repository, build with cmake and compile with mingw64 (gcc) or visual studio (.sln file).
- Save the library files (.lib .a = static, .dll = dynamic) into the lib directory. 
- GLFW: git clone repository, cd glfw, cmake -G "MinGW Makefiles", mingw32-make, copy libglfw3.a to the lib folder
- GLM: git clone repository, cd glm, mkdir build, cmake ., cd build, cmake --build ., copy glm folder to the include folder
- Assimp: git clone repository, cmake -DBUILD_SHARED_LIBS=OFF ., cmake --build ., copy files in include and lib

### Include the local Header Files (.h or .hpp)
```cpp
#include <GL\glew.h>      // GLEW for OpenGL functions
#include <GLFW\glfw3.h>   // GLFW for window and context management
#include <glm\glm.hpp>                 // GLM for mathematics (vec3, vec4, ...)
#include <assimp\camera.h>
```
### Link the Library Files (.lib, .a, or .dll)
- Libraries contain the compiled implementations of the functions declared in the header files.
- Link the GLFW and GLEW libraries for the Windows C++ Compiler MinGW64 (GCC) and include library flags for glfw, glew, opengl, and windows:

## CMD
```batch
g++ App.cpp -o App -I"%PROJECT_DIRECTORY%\include" -L"%cd%\lib" -lglfw3 -lglew32 -lopengl32 -luser32 -lgdi32 -lshell32
```
## Batch Script (Windows: .bat .cmd) Bash Script (Linux MacOS: .sh)
```batch
@echo off
:: Set PROJECT_DIRECTORY to the current directory of the batch file
:: %~dp0 : permanent directory containing the batch script.
:: %cd% : current working directory of the Command Prompt session at the time of execution.
set PROJECT_DIRECTORY=%~dp0

g++ App.cpp -o App ^
-I"%PROJECT_DIRECTORY%\include" ^
-L"%PROJECT_DIRECTORY%\lib" ^
-lglfw3 -lglew32 -lassimp -lopengl32 -luser32 -lgdi32 -lshell32

pause
:: Script to Compile & Run the C++ file with the OpenGL library
```

## Visual Studio
### Configuration Properties: VC++ Directories
- Include Directories 
    - $(SolutionDir)GLFW\include; 
    - $(SolutionDir)GLEW\include;
- Library Directories  
    - $(SolutionDir)GLFW\lib-vc2022; 
    - $(SolutionDir)GLEW\lib\Release\x64;     
### Linker: Input 
- Additional Dependencies: 
    - glfw3.lib; 
    - glew32.lib;
    - Opengl: opengl32.lib;
    - Windows Libraries: User32.lib; Gdi32.lib; Shell32.lib;


