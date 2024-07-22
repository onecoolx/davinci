set(ICUDT_DIR ${CMAKE_CURRENT_LIST_DIR}/source/data)

set(LIB_ICUDT icudt)

file(GLOB_RECURSE ICUDT_SOURCES ${ICUDT_DIR}/*.cpp)

add_library(${LIB_ICUDT} ${ICUDT_SOURCES})

set_target_properties(${LIB_ICUDT} PROPERTIES VERSION ${VERSION_INFO} SOVERSION 1)

include_directories(${ICUDT_DIR})
