
set SCRIPT_DIR=%~dp0
set PATH=%SCRIPT_DIR%\win32\msys\bin;%PATH%.
set GPERF=gperf.exe

%SCRIPT_DIR%\generated_webcore_files.py %1 "Generated"
