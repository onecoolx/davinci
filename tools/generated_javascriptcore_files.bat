
set SCRIPT_DIR=%~dp0
set PATH=%SCRIPT_DIR%\win32\msys\bin;%PATH%.

python %SCRIPT_DIR%\generated_javascriptcore_files.py %1 %2
