@ECHO OFF
SetLocal EnableDelayedExpansion

REM --- Configuration ---
SET PROJECT_NAME=nowhere
SET CGLM_SUBMODULE_DIR=cglm

REM --- Directories ---
IF NOT EXIST bin MKDIR bin
IF NOT EXIST obj MKDIR obj

REM --- Build Settings ---
SET compilerFlags=/W1 /Zi
SET defines=/DSDL_MAIN_HANDLED /D_DEBUG /D_CRT_SECURE_NO_WARNINGS

REM --- Include Paths ---
SET includeFlags=/IC:\libs\SDL3-3.2.10\include /IC:\libs\glad\include /I%CGLM_SUBMODULE_DIR%\include /IC:\libs\freetype-windows-binaries-2.13.3\include

REM --- Linker Settings ---
SET linkerFlags=/link /subsystem:console ^
/LIBPATH:C:\libs\SDL3-3.2.10\lib\x64 ^
/LIBPATH:C:\libs\freetype-windows-binaries-2.13.3\releasestatic\vs2015-2022\win64 ^
SDL3.lib freetype.lib

REM --- Source Files ---
SET sourceFiles=src\all.c C:\libs\glad\src\glad.c

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