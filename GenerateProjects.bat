@echo off
call vendor\premake5\premake5.exe vs2019
IF %ERRORLEVEL% NEQ 0 (
   PAUSE
)