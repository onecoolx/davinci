cmake_minimum_required(VERSION 3.16.0)

project(davinci LANGUAGES C CXX ASM HOMEPAGE_URL https://github.com/onecoolx/davinci)

set(BUILD_SHARED_LIBS ON) # build shared library, OFF for static

set(PROJECT_ROOT ${CMAKE_CURRENT_LIST_DIR})
set(PROJECT_OUT ${CMAKE_CURRENT_BINARY_DIR})

set(VERSION_MAJOR 2)
set(VERSION_MINOR 0)
set(VERSION_MICRO 0)
set(VERSION_INFO ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_MICRO})

if(POLICY CMP0135)
  cmake_policy(SET CMP0135 NEW)
endif()

option(OPT_SYSTEM_MALLOC "Build System Memory Allocator (new/delete/malloc/free/realloc/calloc) used support." OFF)

option(OPT_UNITTEST "Build Unit tests" OFF)

if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build Type" FORCE)
endif()

include (${CMAKE_CURRENT_LIST_DIR}/build/configs.cmake)
include (${CMAKE_CURRENT_LIST_DIR}/build/defines.cmake)
include (${CMAKE_CURRENT_LIST_DIR}/third_party/third_party.cmake)
#include (${CMAKE_CURRENT_LIST_DIR}/src/src.cmake)
#include (${CMAKE_CURRENT_LIST_DIR}/include/include.cmake)
#include (${CMAKE_CURRENT_LIST_DIR}/test/test.cmake)
#include (${CMAKE_CURRENT_LIST_DIR}/demos/demos.cmake)

if (OPT_UNITTEST)
enable_testing()
#include (${CMAKE_CURRENT_LIST_DIR}/unittest/unittest.cmake)
endif(OPT_UNITTEST)

include(CheckIncludeFile)
check_include_file(stdint.h HAVE_STDINT_H)

if (OPT_SYSTEM_MALLOC)
    set(ENABLE_SYSTEM_MALLOC 1)
endif(OPT_SYSTEM_MALLOC)

configure_file(
    "${PROJECT_ROOT}/build/mconfig.h.in"
    "${PROJECT_OUT}/include/mconfig.h"
)
