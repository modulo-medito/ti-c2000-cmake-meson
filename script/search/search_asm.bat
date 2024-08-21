@echo off
setlocal EnableDelayedExpansion

cd %P1%
REM cd src

for /r %%i in (*) do (
    set fname=%%i
    REM echo !fname!
    for %%e in (!fname!) do (
        set fext=%%~xe
        REM echo !fext!
        if !fext! == .asm (
            REM echo %P1%/!fname!
            echo !fname!
        )
    )
)
endlocal

REM pause
