[![Linux Build](https://github.com/onecoolx/davinci/actions/workflows/linux.yml/badge.svg)](https://github.com/onecoolx/davinci/actions/workflows/linux.yml)
[![Windows Build](https://github.com/onecoolx/davinci/actions/workflows/windows.yml/badge.svg)](https://github.com/onecoolx/davinci/actions/workflows/windows.yml)

#### HOW TO BUILD:

**linux:**

1. Install required tools and libraries (gperf, flex, bison, libGtk2.0-dev, libgles2-mesa-dev, libegl1-mesa-dev)

For example on ubuntu:

```
sudo apt-get update --fix-missing
sudo apt-get install gperf flex bison make libgtk2.0-dev libgles2-mesa-dev libegl1-mesa-dev ninja-build
```

2. Build project with ninja

```
./build_linux.sh
cd proj
./ninja-build.sh Debug <Release>
```

**windows:**

1. Install Active Python 2.7 on your windows system and register path environment variables.
   Install Windows SDK 7.1a or above, install Direct 11 SDK or above. (DXSDK_Jun10.exe is recommended)
   Install the Visual C++  which the standard C99 support at least. (Visual C++ 2019 is recommended) 

2. Build project

```
./build_windows.bat
cd vcproj
<open "all.sln" with visual studio>
```

