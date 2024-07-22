set(ICU_TOOLS_DIR ${CMAKE_CURRENT_LIST_DIR}/source/tools)
set(ICUTU_DIR ${ICU_TOOLS_DIR}/toolutil)

set(LIB_ICUTU icutu)

file(GLOB_RECURSE ICUTU_SOURCES ${ICUTU_DIR}/*.cpp)

add_definitions(-DU_TOOLUTIL_IMPLEMENTATION)

add_library(${LIB_ICUTU} ${ICUTU_SOURCES})

include_directories(${ICUTU_DIR})

# build tool
set(TOOL_PKGDATA pkgdata)

add_definitions(-DU_ATTRIBUTE_DEPRECATED=)

add_definitions(-DU_HAVE_ELF_H=1)

add_executable(${TOOL_PKGDATA} ${ICU_TOOLS_DIR}/pkgdata/pkgdata.cpp ${ICU_TOOLS_DIR}/pkgdata/pkgtypes.c)

target_link_libraries(${TOOL_PKGDATA} PRIVATE ${LIB_ICUTU} ${LIB_ICUI18N} ${LIB_ICUUC} ${LIB_ICUFDT} ${LIB_M} ${CMAKE_DL_LIBS})


