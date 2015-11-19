
set PATH=..\..\..\..\tools\win32\msys\bin;%PATH%.
set PATH=..\..\..\..\..\tools\win32\msys\bin;%PATH%.
set GPERF=gperf.exe

set RUNPATH=%1
%RUNPATH%\generated_files.py %1 "Generated"
