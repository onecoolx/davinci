cmake_minimum_required(VERSION 3.16.0)

PROJECT(sqlite3)
include_directories(${CMAKE_CURRENT_LIST_DIR})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -fPIC")
add_library(sqlite3 STATIC sqlite3.c sqlite3.h sqlite3ext.h)

add_definitions(-DSQLITE_ENABLE_RTREE)
add_definitions(-DSQLITE_ENABLE_GEOPOLY)
add_definitions(-DSQLITE_ENABLE_MATH_FUNCTIONS)
add_definitions(-DSQLITE_ENABLE_FTS4)
add_definitions(-DSQLITE_ENABLE_FTS5)

install(FILES sqlite3.h sqlite3ext.h DESTINATION include)
install(TARGETS sqlite3 LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
