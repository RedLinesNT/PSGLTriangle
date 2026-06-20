@echo off

echo Creating HDD package for "PSGLTriangle" (Release)...

setlocal 

set PackageFileName=PSGLTriangleRelease.pkg
set TransientFileName=XXYYYY-LGPS12250_00-XXXXXXXXXXXXXXXX.pkg

:: Deleting old working directory / Previous exports
if exist ..\bin\working rmdir /s /q ..\bin\working
if exist %PackageFileName% del /s /q %PackageFileName%
if exist ..\bin\%PackageFileName% del /s /q ..\bin\%PackageFileName%
if exist %TransientFileName% del /s /q %TransientFileName%

:: Create required directories
if not exist ..\bin\working md ..\bin\working
if not exist ..\bin\working\USRDIR md ..\bin\working\USRDIR

:: Copy every files from the "data" folder
xcopy ..\data\** ..\bin\working\USRDIR\ /E

:: Copy required shipping assets to the root of the working directory
xcopy ..\data\shipping\** ..\bin\working /E

:: Copy DEBUG (Fake-Signed) SELF
:: cacacopy ..\bin\PS3_Release\PSGLTriangle.self PSGLTriangle.self

:: Un-(Fake-Signed) SELF it
"%SCE_PS3_ROOT%/host-win32/bin/unfself" ..\bin\PS3_Release\PSGLTriangle.self ..\bin\PS3_Release\PSGLTriangle.elf

:: Create EBOOT
"%SCE_PS3_ROOT%/host-win32/bin/make_fself_npdrm" ..\bin\PS3_Release\PSGLTriangle.elf ..\bin\working\USRDIR\EBOOT.BIN

:: Creating the final Package file
"%SCE_PS3_ROOT%/host-win32/bin/make_package_npdrm" ..\bin\working\Config.txt ..\bin\working > ..\bin\working\BuildOutput.txt
ren %TransientFileName% %PackageFileName%

:: Move the ouput toward the correct output path
xcopy %PackageFileName% ..\bin\%PackageFileName% /F
del /s /q %PackageFileName%

endlocal