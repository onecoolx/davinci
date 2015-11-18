
set PATH=..\..\..\..\tools\win32\msys\bin;%PATH%.
set GPERF=..\..\..\..\..\tools\win32\msys\bin\gperf.exe

set RUNPATH=%1
%RUNPATH%\generated_files.py %1 "Generated"
