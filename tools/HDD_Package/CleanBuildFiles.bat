@echo off
echo Cleaning up stuff...

:: Deleting the working directory
if exist working rmdir /s /q working

:: Deleting PKG files
if exist PSGLTriangle_RELEASE.pkg del /q PSGLTriangle_RELEASE.pkg 
if exist PSGLTriangle_DEBUG.pkg del /q PSGLTriangle_DEBUG.pkg 

:: Deleting Build results
if exist BuildOutput.txt del /q BuildOutput.txt