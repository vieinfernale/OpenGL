@echo off
:: Set PROJECT_DIRECTORY to the current directory of the batch file
:: %~dp0 : permanent directory containing the batch script.
:: %cd% : current working directory of the Command Prompt session at the time of execution.
set PROJECT_DIRECTORY=%~dp0..\..

g++ Triangle.cpp -o Triangle ^
-I"%PROJECT_DIRECTORY%\include" ^
-L"%PROJECT_DIRECTORY%\lib" ^
-lglfw3 -lglew32 -lassimp -lopengl32 -luser32 -lgdi32 -lshell32

pause
:: Script to Compile & Run the C++ file with the OpenGL library