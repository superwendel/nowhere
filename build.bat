@ECHO OFF
SetLocal EnableDelayedExpansion

REM --- Configuration ---
SET PROJECT_NAME=nowhere

REM --- Directories ---
IF NOT EXIST bin MKDIR bin
IF NOT EXIST obj MKDIR obj

REM --- Build Settings ---
SET compilerFlags=/W1 /O2 /EHsc
SET defines=/DSDL_MAIN_HANDLED /DNDEBUG /D_CRT_SECURE_NO_WARNINGS

REM --- Include Paths ---
SET includeFlags=/IC:\libs\SDL3-3.2.10\include /IC:\libs\glad\include /IC:\libs\freetype-windows-binaries-2.13.3\include /IC:\libs\glfw-3.4.bin.WIN64\include /IC:\libs\glew-2.1.0\include

REM --- Linker Settings ---
SET linkerFlags=/link /subsystem:console ^
/LIBPATH:C:\libs\SDL3-3.2.10\lib\x64 ^
/LIBPATH:C:\libs\freetype-windows-binaries-2.13.3\releasestatic\vs2015-2022\win64 ^
/LIBPATH:C:\libs\glfw-3.4.bin.WIN64\lib-vc2019 ^
/LIBPATH:C:\libs\glew-2.1.0\lib\Release\x64 ^
SDL3.lib freetype.lib glfw3.lib glew32.lib opengl32.lib

REM --- Source Files ---
SET sourceFiles=src\all.cpp C:\libs\glad\src\glad.c

ECHO Building %PROJECT_NAME%...

REM --- Compilation and Linking ---
cl %compilerFlags% %defines% %includeFlags% %sourceFiles% /Fo"obj\\" /Fe"bin\%PROJECT_NAME%.exe" %linkerFlags%

REM --- Post-Build Actions ---
IF %ERRORLEVEL% EQU 0 (
    ECHO %PROJECT_NAME% build success
    REM Copy resources to bin directory
    ECHO Copying resources...
    xcopy /E /I /Y /Q gfx bin\gfx > NUL
    xcopy /E /I /Y /Q shaders bin\shaders > NUL
    ECHO Resource copy complete.
) ELSE (
    ECHO ERROR: Build failed, error code %ERRORLEVEL%
)

EndLocal

ECHO Build process finished.