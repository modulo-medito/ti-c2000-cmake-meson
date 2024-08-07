@echo off
setlocal EnableDelayedExpansion

@REM Set the toolchain
set buildtool=cmake
set toolchain=ti_c2000_tms320f280039c

@REM Build
if %buildtool%==cmake (
    if exist .\platform\%toolchain%\build_cmake.bat (
        .\platform\%toolchain%\build_cmake.bat
    ) else (
        echo Error: build_make.bat for the CMake build tool does not exist.
    )
)
if %buildtool%==meson (
    if exist .\platform\%toolchain%\build_meson.bat (
        .\platform\%toolchain%\build_meson.bat
    ) else (
        echo Error: build_meson.bat for the Meson build tool does not exist.
    )
)

endlocal
pause
