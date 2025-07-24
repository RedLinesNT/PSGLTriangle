@echo off

echo The project must be compiled in DEBUG mode!
echo Creating HDD Package file...

setlocal

set PackageFileName=PSGLTriangle_DEBUG.pkg
set TransientFileName=XXYYYY-LGPS00001_00-XXXXXXXXXXXXXXXX.pkg

:: Deleting old working directory
if exist working rmdir /s /q working

:: Create required directories
if not exist working md working
if not exist working\USRDIR md working\USRDIR

:: Delete previous results
if exist %PackageFileName% del /s /q %PackageFileName%
if exist %TransientFileName% del /s /q %TransientFileName%

:: Copy every files from the "assets" folder
xcopy ..\..\assets\** working\USRDIR\ /E

:: Copy required static PKG assets
xcopy pkg_static\** working /E

:: Copy RELEASE (Fake-Signed) SELF
copy ..\..\bin\PS3-Debug\PSGLTriangle.self PSGLTriangle.self

:: Un-(Fake-Signed) SELF it
"%SCE_PS3_ROOT%/host-win32/bin/unfself" PSGLTriangle.self PSGLTriangle.elf

:: Create EBOOT
"%SCE_PS3_ROOT%/host-win32/bin/make_fself_npdrm" PSGLTriangle.elf working\USRDIR\EBOOT.BIN

:: Delete temp files
del /q PSGLTriangle.self
del /q PSGLTriangle.elf

:: Creating the final Package file
"%SCE_PS3_ROOT%/host-win32/bin/make_package_npdrm" Config.txt working > BuildOutput.txt
ren %TransientFileName% %PackageFileName%

endlocal


