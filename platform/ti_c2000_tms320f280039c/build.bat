@echo off

@REM Set the absolute directory of the toolchain tools
set ccs_dir=D:\user_chc\4_app\ccs\2_ws\ti\ccs1271\ccs
set toolchain_sdk_dir=D:\user_chc\4_app\ccs\2_ws\ti\c2000\C2000Ware_4_02_00_00\device_support\f28003x

@REM Set the relative path of the toolchain tools
set toolchain_cpl_dir=%ccs_dir%\tools\compiler\ti-cgt-c2000_22.6.1.LTS
set maketool=%ccs_dir%\utils\bin\gmake
set hextool=%ccs_dir%\tools\compiler\ti-cgt-c2000_22.6.1.LTS\bin\hex2000.exe

@REM Set the project configurations
set prjname=minimal_f280039
set logfile=build.log

echo ################################################################################
echo # Pre-build steps                                                              #
echo ################################################################################
@REM Remove the build folder
if exist build rmdir /s /q build
mkdir build

echo.
echo.
echo.
echo ################################################################################
echo # Build                                                                        #
echo ################################################################################
@REM CMake generate, '2>' means print the stderr and overwrite
cmake -S ./                                   ^
    -B ./build                                ^
    -G "Unix Makefiles"                       ^
    -DCMAKE_MAKE_PROGRAM="%maketool%"         ^
    -DPROJECT_NAME="%prjname%"                ^
    -DTOOLCHAIN_CPL_DIR="%toolchain_cpl_dir%" ^
    -DTOOLCHAIN_SDK_DIR="%toolchain_sdk_dir%" ^
    2> ./build/%logfile%

@REM Build, '2>>' means print the stderr and append
cd build
REM %maketool% -j 20 all -O 2>> %logfile%
cmake --build . -j 20

echo.
echo.
echo.
echo ################################################################################
echo # Post-build steps                                                             #
echo ################################################################################
%hextool% --diag_wrap=off ../platform/ti_c2000_tms320f280039c/script/rom_directive/minimal_f280039.hexcmd 2>> %logfile%

echo.
echo.
echo.
echo ################################################################################
echo # Build log showed below                                                       #
echo ################################################################################
@REM For clangd LSP feature
powershell -Command "(Get-Content compile_commands.json) -replace '--include_path=', '-I' | Out-File -encoding utf8 compile_commands.json"

@REM Show log in terminal
type %logfile%

@REM Back to the root
cd ..

pause
