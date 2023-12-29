# OpenGL

## Environment
- [Visual Studio](https://visualstudio.microsoft.com/)

## Libraries
- Window: [GLFW](https://www.glfw.org)
- Functions: [GLEW](https://glew.sourceforge.net/) 
- Windows Libraries: [Microsoft Documentation](https://learn.microsoft.com/en-us/search/)

## Documentation
- [GLFW](https://www.glfw.org/documentation.html)
- [GLEW](https://glew.sourceforge.net/install.html)

## Setup
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


## Misc
- F5: Build (Compile and Link)
- Open the .sln file with Visual Studio
- Output gives more detail than the Error List
- Copy the name of the Function that gives the error inside Output and search it on the [Microsoft Documentation](https://learn.microsoft.com/en-us/search/) for the Windows Library to add to Linker - Input - Dependencies.

## Git 
- Create a Local Repository inside Visual Studio
- Create a Git Repository without files inside Github
- Add the Remote link to Visual Studio and Push

## Resources
- OpenGL - The Cherno


