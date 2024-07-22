set(ICUFDT_DIR ${CMAKE_CURRENT_LIST_DIR}/source/stubdata)

set(LIB_ICUFDT icufdt)

file(GLOB_RECURSE ICUFDT_SOURCES ${ICUFDT_DIR}/*.cpp)

add_library(${LIB_ICUFDT} ${ICUFDT_SOURCES})

include_directories(${ICUFDT_DIR})
