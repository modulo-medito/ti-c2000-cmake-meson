@echo off
setlocal EnableDelayedExpansion

@REM Set the absolute directory of the toolchain tools
set ccs_dir=C:\ti\ccs1260\ccs
set toolchain_sdk_dir=C:\ti\c2000\C2000Ware_4_02_00_00\device_support\f28003x

@REM Set the relative path of the toolchain tools
set toolchain_cpl_dir=%ccs_dir%\tools\compiler\ti-cgt-c2000_22.6.1.LTS
set maketool=%ccs_dir%\utils\bin\gmake
set hextool=%ccs_dir%\tools\compiler\ti-cgt-c2000_22.6.1.LTS\bin\hex2000.exe

@REM Set the project configurations
set prjname=ti_c2000
set buildpath=build\meson
set logfile=build.log

echo ################################################################################
echo # Pre-build steps                                                              #
echo ################################################################################
@REM Remove the build folder
if exist %buildpath% rmdir /s /q %buildpath%
mkdir %buildpath%

echo.
echo.
echo.
echo ################################################################################
echo # Build                                                                        #
echo ################################################################################
meson setup --cross-file .\platform\ti_c2000_tms320f280039c\toolchain_for_meson.ini %buildpath%
cd %buildpath%
ninja 2> %logfile%
cd ..
cd ..

echo.
echo.
echo.
echo ################################################################################
echo # Post-build steps                                                             #
echo ################################################################################
REM Set ROM directive command file name
cd %buildpath%
set rom_directive_file=ti_c2000_hex_gen.dat

REM Make ROM directive command file
echo %prjname%.out                        > %rom_directive_file%
echo --memwidth=16                       >> %rom_directive_file%
echo -i                                  >> %rom_directive_file%
echo --image                             >> %rom_directive_file%
echo ROMS                                >> %rom_directive_file%
echo {                                   >> %rom_directive_file%
echo     APPROM: org = 0x00080000,       >> %rom_directive_file%
echo             len = 0x00030000,       >> %rom_directive_file%
echo             romwidth = 16,          >> %rom_directive_file%
echo             fill = 0xffffffff,      >> %rom_directive_file%
echo             files = {%prjname%.hex} >> %rom_directive_file%
echo }                                   >> %rom_directive_file%

REM TI hex generation
%hextool% --diag_wrap=off %rom_directive_file% 2>> %logfile%
cd ..
cd ..

echo.
echo.
echo.
echo ################################################################################
echo # Build log showed below                                                       #
echo ################################################################################
@REM For clangd LSP feature
REM powershell -Command "(Get-Content compile_commands.json) -replace '--include_path=', '-I' | Out-File -encoding utf8 compile_commands.json"

@REM Show log in terminal
cd %buildpath%
type %logfile%
cd ..
cd ..

endlocal
pause
