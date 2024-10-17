# OpenGL

## Environment
- [Visual Studio](https://visualstudio.microsoft.com/)
- [Visual Studio Code](https://code.visualstudio.com/docs/cpp/config-mingw)
- C++ Compiler: MinGW64 / GCC

## Libraries
- Window: [GLFW](https://www.glfw.org)
- Functions: [GLEW](https://glew.sourceforge.net/) 
- Windows Libraries: [Microsoft Documentation](https://learn.microsoft.com/en-us/search/)
- Math: [GLM](https://github.com/g-truc/glm)

# Build (Compile and Run)

- Download GLFW and GLEW binaries.
- Download GLM and include the glm directory with the headers inside the project directory.

### Include the local Header Files (.h or .hpp)
```cpp
#include ".\GLEW\include\GL\glew.h"
#include ".\GLFW\include\GLFW\glfw3.h"
#include ".\glm\glm.hpp"
```
### Link the Library Files (.lib, .a, or .dll)
- Libraries contain the compiled implementations of the functions declared in the header files.
- Link the GLFW and GLEW libraries for the Windows C++ Compiler MinGW64 / GCC and include library flags for glfw, glew, opengl, and windows:

## CMD
```batch
g++ App.cpp -o App -L"%cd%\GLFW\lib\lib-mingw-w64" -L"%cd%\GLEW\lib\x64" -lglfw3 -lglew32 -lopengl32 -luser32 -lgdi32 -lshell32
```
## Batch Script (Windows: .bat .cmd) Bash Script (Linux MacOS: .sh)
```batch
@echo off
:: Set PROJECT_DIRECTORY to the current directory of the batch file
:: %~dp0 : permanent directory containing the batch script.
:: %cd% : current working directory of the Command Prompt session at the time of execution.
set PROJECT_DIRECTORY=%~dp0
g++ App.cpp -o App -L"%PROJECT_DIRECTORY%\GLFW\lib\lib-mingw-w64" -L"%PROJECT_DIRECTORY%\GLEW\lib\x64" -lglfw3 -lglew32 -lopengl32 -luser32 -lgdi32 -lshell32 
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
### Include the local Header Files (.h or .hpp)
```cpp
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include ".\glm\glm.hpp"
```


