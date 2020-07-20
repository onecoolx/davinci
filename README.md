![Linux Build](https://github.com/onecoolx/davinci/workflows/Linux%20Build/badge.svg)

HOW TO BUILD:

------------------------------------
linux:
./build_proj.sh
cd proj
make

------------------------------------
windows:
1. Install Active Python 2.7 on your windows system and register path environment variables.
   Install Windows SDK 7.1a or above, install Direct 11 SDK or above. (DXSDK_Jun10.exe is recommended)
   Install the Visual C++  which the standard C99 support at least. (Visual C++ 2010 is recommended) 

2. Build project
./build_proj.bat
cd vcproj
<open "all.sln" with visual studio>

