cmake_minimum_required(VERSION 3.16.0)

PROJECT(sqlite3)
include_directories(${CMAKE_CURRENT_LIST_DIR})
add_library(sqlite3 STATIC sqlite3.c sqlite3.h sqlite3ext.h)
add_executable(sqlite sqlite3.c shell.c sqlite3.h sqlite3ext.h)

add_definitions(-DSQLITE_ENABLE_RTREE)
add_definitions(-DSQLITE_ENABLE_GEOPOLY)
add_definitions(-DSQLITE_ENABLE_MATH_FUNCTIONS)
add_definitions(-DSQLITE_ENABLE_FTS4)
add_definitions(-DSQLITE_ENABLE_FTS5)

if(WIN32)
  add_custom_command(TARGET sqlite POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:sqlite> ${CMAKE_CURRENT_BINARY_DIR}/sqlite3.exe
    DEPENDS sqlite
  )
  install(FILES sqlite3.exe DESTINATION bin)
else()
  include(FindThreads)
  target_link_libraries(sqlite m ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS})
  install(TARGETS sqlite RUNTIME DESTINATION bin)
endif()

install(FILES sqlite3.h sqlite3ext.h DESTINATION include)
install(TARGETS sqlite3 LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
