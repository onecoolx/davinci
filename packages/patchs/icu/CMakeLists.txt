cmake_minimum_required(VERSION 3.16.0)

project(icu LANGUAGES C CXX ASM)

set(BUILD_SHARED_LIBS ON) # build shared library, OFF for static

set(VERSION_INFO 75.1)

include (${CMAKE_CURRENT_LIST_DIR}/icuuc.cmake)
include (${CMAKE_CURRENT_LIST_DIR}/icui18n.cmake)
include (${CMAKE_CURRENT_LIST_DIR}/icuio.cmake)

