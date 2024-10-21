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