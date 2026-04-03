@echo off
setlocal

set "BUILD_DIR=build"
set "CONFIG=%~1"

if "%CONFIG%"=="" set "CONFIG=Release"

if /I "%CONFIG%"=="Debug" goto valid
if /I "%CONFIG%"=="Release" goto valid
if /I "%CONFIG%"=="RelWithDebInfo" goto valid
if /I "%CONFIG%"=="MinSizeRel" goto valid

echo Usage: build.bat [Debug^|Release^|RelWithDebInfo^|MinSizeRel]
exit /b 1

:valid
cmake -S . -B "%BUILD_DIR%" -DCMAKE_BUILD_TYPE=%CONFIG%
if errorlevel 1 exit /b %errorlevel%

cmake --build "%BUILD_DIR%" --config %CONFIG%
exit /b %errorlevel%
