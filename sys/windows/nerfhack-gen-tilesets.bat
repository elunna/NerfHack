@echo off
setlocal enabledelayedexpansion
rem nerfhack-gen-tilesets.bat - generate NerfHack's larger tile sheets (Windows).
rem
rem NerfHack's tile art is authored at a fixed 16x16 pixels per tile - there
rem is no separately drawn higher-resolution source art. Larger tile sheets
rem (32x32, 64x64, ...) are produced by building the normal 16x16 sheet and
rem then upscaling it by an integer factor with nearest-neighbor pixel
rem duplication, so pixels stay crisp instead of blurring. See the "Unix"
rem equivalent, sys\unix\nerfhack-gen-tilesets.sh, for the same pipeline on
rem Linux/macOS.
rem
rem Usage:
rem   sys\windows\nerfhack-gen-tilesets.bat [factor ...]
rem
rem With no arguments, generates the traditional set: 32x32 (2x), 64x64
rem (4x), and 128x128 (8x), alongside the base 16x16 (1x) sheet. Pass one or
rem more factors to generate only those, e.g.
rem   sys\windows\nerfhack-gen-tilesets.bat 2 4
rem for just 32x32 and 64x64.
rem
rem Requires a Visual Studio "Developer Command Prompt" (so cl.exe and
rem nmake.exe are on PATH - the same environment used to build NerfHack
rem itself) and Python 3 (https://python.org - check "Add python.exe to
rem PATH" when installing). Output goes to tilesets\tiles_<N>x<N>.bmp under
rem the repository root.

set "REPO_ROOT=%~dp0..\.."

if not exist "%REPO_ROOT%\include\hack.h" (
    echo nerfhack-gen-tilesets.bat: cannot find the repository root >&2
    goto :fail
)

where python >nul 2>nul
if errorlevel 1 (
    echo nerfhack-gen-tilesets.bat: python was not found on PATH. >&2
    echo Install it from https://python.org ^(check "Add python.exe to PATH" >&2
    echo during setup^), then try again. >&2
    goto :fail
)

where nmake >nul 2>nul
if errorlevel 1 (
    echo nerfhack-gen-tilesets.bat: nmake was not found on PATH. >&2
    echo Run this from a "Developer Command Prompt for VS" ^(or after calling >&2
    echo vcvarsall.bat^) - the same environment used to build NerfHack itself. >&2
    goto :fail
)

if not exist "%REPO_ROOT%\src\Makefile" (
    echo Setting up the nmake build files...
    call "%REPO_ROOT%\sys\windows\nhsetup.bat"
)

echo Building tile2bmp.exe...
pushd "%REPO_ROOT%\src"
nmake ..\util\tile2bmp.exe
set "BUILD_ERR=%ERRORLEVEL%"
popd
if not "%BUILD_ERR%"=="0" (
    echo nerfhack-gen-tilesets.bat: failed to build tile2bmp.exe >&2
    goto :fail
)

if not exist "%REPO_ROOT%\tilesets" mkdir "%REPO_ROOT%\tilesets"

set "BASE_TILE_PX=16"
set "BASE_BMP=%REPO_ROOT%\tilesets\tiles_%BASE_TILE_PX%x%BASE_TILE_PX%.bmp"

echo Generating base %BASE_TILE_PX%x%BASE_TILE_PX% tile sheet...
pushd "%REPO_ROOT%\util"
tile2bmp.exe "%BASE_BMP%"
set "GEN_ERR=%ERRORLEVEL%"
popd
if not "%GEN_ERR%"=="0" (
    echo nerfhack-gen-tilesets.bat: tile2bmp.exe failed >&2
    goto :fail
)

set "FACTORS=%*"
if "%FACTORS%"=="" set "FACTORS=1 2 4 8"

for %%F in (%FACTORS%) do (
    if not "%%F"=="1" (
        set /a "SIZE=%BASE_TILE_PX% * %%F"
        set "OUT=%REPO_ROOT%\tilesets\tiles_!SIZE!x!SIZE!.bmp"
        python "%REPO_ROOT%\sys\unix\nerfhack-scale-bmp.py" %%F "%BASE_BMP%" "!OUT!"
    )
)

echo Done. See tilesets\
goto :end

:fail
endlocal
exit /b 1

:end
endlocal

rem pause only if double-clicked (launched via "cmd /c"), so the window
rem doesn't vanish before the user can read the output
set "_pause=N"
for %%x in (%cmdcmdline%) do if /i "%%~x"=="/c" set "_pause=Y"
if "%_pause%"=="Y" pause
