REM @echo off

pushd %~dp0

set CMAKEGENERATOR="Visual Studio 15 2017"
set ARCHITECTURE=x64

echo %COMPUTERNAME%

set INSTALL_PREFIX=%~dp0\distro


if "%COMPUTERNAME%" == "DESKTOP-RG9UU05" (
    set CMAKEGENERATOR="Visual Studio 16 2019"
 )

if "%COMPUTERNAME%" == "S1301" (
    set INSTALL_PREFIX=E:/Sources/PythonPackages/progressbar
    REM set QTDIR=E:/Lib/Qt/Qt5.12.5/5.12.5/msvc2017_64
    set QTDIR=C:/ProgramData/Anaconda3/pkgs/qt-5.9.7-vc14h73c81de_0/Library
 )


if exist config.bat (
    call config.bat
)

pushd %~dp0..
set BASE_PATH=%CD%
set BuildDir=build

if exist %BuildDir% (
    echo.
    echo. Deleting %BuildDir%
    rd /s /q %BuildDir%
)

sleep 1

mkdir %BuildDir%
pushd %BuildDir%

cmake -G %CMAKEGENERATOR% -A %ARCHITECTURE%^
    -DCMAKE_INSTALL_PREFIX=%INSTALL_PREFIX%^
    -DQTDIR=%QTDIR%^
    -Wno-dev^
    %BASE_PATH%\src

popd
popd
