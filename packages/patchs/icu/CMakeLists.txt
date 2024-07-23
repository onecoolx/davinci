cmake_minimum_required(VERSION 3.16.0)

project(icu LANGUAGES C CXX ASM)

set(BUILD_SHARED_LIBS ON) # build shared library, OFF for static

set(VERSION_INFO 75)
set(VERSION_MICRO 1)

set(U_ENDIAN_CHAR l) # little endian defaulta b is big endian

include (${CMAKE_CURRENT_LIST_DIR}/icuuc.cmake)
include (${CMAKE_CURRENT_LIST_DIR}/icui18n.cmake)
include (${CMAKE_CURRENT_LIST_DIR}/icuio.cmake)
include (${CMAKE_CURRENT_LIST_DIR}/icufdt.cmake)
include (${CMAKE_CURRENT_LIST_DIR}/icutu.cmake)
include (${CMAKE_CURRENT_LIST_DIR}/icudt.cmake)

