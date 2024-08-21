@echo off
setlocal EnableDelayedExpansion

:choose_build_tool
@REM Choose the build tool
echo Choose your build tool:
echo (1) CMake
echo (2) Meson
echo (q) Exit
set /p userinput=Choose:
if %userinput%==1 (
    set buildtool=cmake
    goto exec_build_tool
)
if %userinput%==2 (
    set buildtool=meson
    goto exec_build_tool
)
if %userinput%==q (
    goto exit_build
)
echo.
goto choose_build_tool

:exec_build_tool
@REM Toolchain name
set toolchain=ti_c2000_tms320f280039c

@REM Build
if %buildtool%==cmake (
    if exist .\platform\%toolchain%\build_cmake.bat (
        call .\platform\%toolchain%\build_cmake.bat
        echo.
    ) else (
        echo Error: build_make.bat for the CMake build tool does not exist.
        echo.
    )
)
if %buildtool%==meson (
    if exist .\platform\%toolchain%\build_meson.bat (
        call .\platform\%toolchain%\build_meson.bat
        echo.
    ) else (
        echo Error: build_meson.bat for the Meson build tool does not exist.
        echo.
    )
)
goto choose_build_tool

:exit_build
endlocal
exit
