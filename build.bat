@echo off

@REM Set the toolchain
set toolchain=ti_c2000_tms320f280039c

@REM Build
if exist .\platform\%toolchain%\build.bat (
    .\platform\%toolchain%\build.bat
) else (
    echo Error: build.bat of the specified toolchain is not exist.
)

pause
