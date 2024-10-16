@echo off
set PROJECT_DIRECTORY=C:\Users\Wes\Desktop\OpenGL
g++ opengl.cpp -o opengl -L"%PROJECT_DIRECTORY%\GLFW\lib\lib-mingw-w64" -L"%PROJECT_DIRECTORY%\GLEW\lib\x64" -lglfw3 -lglew32 -lopengl32 -luser32 -lgdi32 -lshell32 
pause
:: Script to Compile & Run the C++ file with the OpenGL library