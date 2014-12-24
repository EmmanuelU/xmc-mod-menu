@echo off
setLocal EnableDelayedExpansion
::Example yourmod.sco = enter in compiler = "yourmod"
set compiler=xmc_modmenu
set out=%compiler%.sco
set /A value=0
set /A sum=0
mode con:cols=45 lines=10
::set /A divide=1024
set "outsco=*.sco"

COLOR 0b
Title Emmanuel Utomi's SCO Compiler

if not exist *.c (
if not exist *.cpp goto nofile
)
if not exist ../../out_sco (
cd ../../
mkdir out_sco
cd workspace/%compiler%/
)
if exist ../../out_sco/%compiler%.sco (
echo Cleaning prior scripts ...
echo.
cd ../../out_sco/
del -f %compiler%.sco
cd ../workspace/%compiler%/
)
if exist build.txt (
echo Cleaning prior build log ...
echo.
del -f build.txt
)
if exist ../../out_sco/%compiler%.newsco (
echo.
cd ../../out_sco/
del -f %compiler%.newsco
cd ../workspace/%compiler%/
)
if exist ../../out_sco/%compiler%.s (
echo Cleaning prior failed scripts ...
echo.
cd ../../out_sco/
del -f %compiler%.s
cd ../workspace/%compiler%/
)
if not defined %%1 goto compile_menu
goto compile_custom

:compile_menu
mode con:cols=45 lines=10
COLOR 0b
echo Compiling %compiler%.c ...
echo.
if not exist *.c (
if not exist *.cpp goto nofile
)
..\..\bin\scocl_old.exe GTAIV "%compiler%.c" "..\..\out_sco/" > build.txt
if not exist build.txt goto err_log
::..\..\bin\scocl_new.exe GTAIV "%compiler%" "..\..\out_sco/" > build.txt
mode con:cols=50 lines=10
for /f "tokens=* delims= skip=1" %%a in (build.txt) do ( set log="%%a" )
del -f build.txt > nul
set log=%log:"=%
cls
echo %log%
if not exist ../../out_sco/%out% goto err_build
cd ../../out_sco/
ren "%compiler%.sco" "%out%"
echo.
for %%A in (%out%) do (
set /A value=%%~zA
set /A value /=1024
set /A value +=1
echo Size of "%out%" is !value!kb
)
::for %%A in (%outsco%) do echo.New compressed Size of "%out%" is %%~zI bytes
::for %%A in (%outsco%) do echo.Size of "%out%" is %%~zA bytes
cd ../workspace/%compiler%/
echo Press any key to launch sco compressor
pause > nul
cls
..\..\bin\compress.exe ../../out_sco/%out%.sco
goto compress

:compress
mode con:cols=60 lines=10
cls
echo Waiting for compressed sco ...
if not exist ../../out_sco/%out%.newsco goto compressloop
echo Cleaning Renaming compressed file ...
echo.
cd ../../out_sco/
del -f %out%
ren "%out%.newsco" "%out%"
cd ../workspace/%compiler%/
cls
cd ../../out_sco/
for %%A in (%out%) do (
set /A value=%%~zA
set /A value /=1024
echo Compressed size of "%out%" is !value!kb
)
cd ../workspace/%compiler%/
echo.
echo Completed compile job, your sco is named %out%
::for %%A in (%outsco%) do echo.New compressed Size of "%out%" is %%~zA bytes
if exist compiler (
del -f compiler
)
echo.Press any key to exit, or you can sit here like a dumbass :D
pause > nul
exit 1

:compressloop
ping localhost -n 2 >nul
goto compress

:compile_custom
echo.
if %%1 NEQ *.c goto err_custom
echo Compiling %%1 ...
..\..\bin\scocl_old.exe TBOGT "%%1" "..\..\out_sco/"
if not exist *.sco goto err_build
pause
exit 1

:err_custom
echo.
echo Your custom script is not a .c or .cpp file, please try again
pause
exit 1

:err_build
COLOR 0C
mode con:cols=90 lines=15
echo %log%
echo.
echo FATAL ERROR
echo Your custom script did not build
echo make your changes, then press any key to try again
pause >nul 
cls
goto compile_menu

:err_log
cls
COLOR 0C
mode con:cols=90 lines=10
echo FATAL ERROR
echo No build log found.
pause >nul 
cls
goto compile_menu

:nofile
cls
echo No .c Files found in local directory
pause 
exit 1