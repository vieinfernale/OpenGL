# OpenGL

## Environment
- [Visual Studio](https://visualstudio.microsoft.com/)
- [Visual Studio Code](https://code.visualstudio.com/docs/cpp/config-mingw)

## Libraries
- Window: [GLFW](https://www.glfw.org)
- Functions: [GLEW](https://glew.sourceforge.net/) 
- Windows Libraries: [Microsoft Documentation](https://learn.microsoft.com/en-us/search/)

## Documentation
- [GLFW](https://www.glfw.org/documentation.html)
- [GLEW](https://glew.sourceforge.net/install.html)

# CMD
- Download GLFW and GLEW binaries.
### Include the local headers
```cpp
#include ".\GLEW\include\GL\glew.h"
#include ".\GLFW\include\GLFW\glfw3.h"
```
### Link the libraries
- Link GLFW and GLEW libraries for MinGW64 (GCC) and x64 and include library flags for glfw, glew, opengl, and windows:
```batch
g++ opengl.cpp -o opengl -L"%cd%\GLFW\lib\lib-mingw-w64" -L"%cd%\GLEW\lib\x64" -lglfw3 -lglew32 -lopengl32 -luser32 -lgdi32 -lshell32
```

# Batch Script (Windows: .bat .cmd) Bash Script (Linux MacOS: .sh)
```batch
@echo off
:: Set PROJECT_DIRECTORY to the current directory of the batch file
:: %~dp0 : permanent directory containing the batch script.
:: %cd% : current working directory of the Command Prompt session at the time of execution.
set PROJECT_DIRECTORY=%~dp0
g++ opengl.cpp -o opengl -L"%PROJECT_DIRECTORY%\GLFW\lib\lib-mingw-w64" -L"%PROJECT_DIRECTORY%\GLEW\lib\x64" -lglfw3 -lglew32 -lopengl32 -luser32 -lgdi32 -lshell32 
pause
:: Script to Compile & Run the C++ file with the OpenGL library
```

## Visual Studio
- Download the GLFW and GLEW binaries and put them inside the project or solution directory
- Start a new C++ project inside Visual Studio and add a new .cpp file to the project
- Open the Properties of the OpenGL Project and set to All Configurations
    - Include Directory
        - C/C++ - General - Include Directories: 
            - $(SolutionDir)GLFW\include; 
            - $(SolutionDir)GLEW\include;
    - Library Directory
        - Linker - General - Library Directory:  
            - $(SolutionDir)GLFW\lib-vc2022; 
            - $(SolutionDir)GLEW\lib\Release\x64;
        - Linker - Input - Dependencies: 
            - glfw3.lib; 
            - glew32.lib;
        - Windows Libraries Linker Errors: opengl32.lib; User32.lib; Gdi32.lib; Shell32.lib;
    - GLEW dynamic .dll Library
        - Copy GLEW\bin\Release\x64\glew32.dll and paste inside C:\Windows\System32 (%SystemRoot%\System32)
    - GLEW static Library
        - glew32s.lib
        - C/C++ - Preprocessor - Preprocessor Definitions: GLEW_STATIC;

## Resources
- OpenGL : The Cherno
- Ray Tracing in One Weekend
- Raytracing : Inigo Quilez


