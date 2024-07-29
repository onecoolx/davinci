set(ICUUC_S_DIR ${CMAKE_CURRENT_LIST_DIR}/source/common)
set(LIB_ICUUC_S icuuc_FDT)

file(GLOB_RECURSE ICUUC_S_SOURCES ${ICUUC_S_DIR}/*.cpp)

add_library(${LIB_ICUUC_S} SHARED ${ICUUC_S_SOURCES})

target_compile_definitions(${LIB_ICUUC_S} PRIVATE U_COMMON_IMPLEMENTATION)

target_link_libraries(${LIB_ICUUC_S} PRIVATE ${LIB_ICUFDT} ${CMAKE_DL_LIBS})

add_dependencies(${LIB_ICUUC_S} ${LIB_ICUFDT})


set(ICUI18N_S_DIR ${CMAKE_CURRENT_LIST_DIR}/source/i18n)
set(LIB_ICUI18N_S icui18n_FDT)

file(GLOB_RECURSE ICUI18N_S_SOURCES ${ICUI18N_S_DIR}/*.cpp)

add_library(${LIB_ICUI18N_S} SHARED ${ICUI18N_S_SOURCES})

target_compile_definitions(${LIB_ICUI18N_S} PRIVATE U_I18N_IMPLEMENTATION)

target_link_libraries(${LIB_ICUI18N_S} PRIVATE ${LIB_ICUUC_S} ${CMAKE_DL_LIBS})

add_dependencies(${LIB_ICUI18N_S} ${LIB_ICUUC_S})


set(ICU_TOOLS_DIR ${CMAKE_CURRENT_LIST_DIR}/source/tools)
set(ICUTU_DIR ${ICU_TOOLS_DIR}/toolutil)

set(LIB_ICUTU icutu)

file(GLOB_RECURSE ICUTU_SOURCES ${ICUTU_DIR}/*.cpp)

add_library(${LIB_ICUTU} SHARED ${ICUTU_SOURCES})

target_compile_definitions(${LIB_ICUTU} PRIVATE U_TOOLUTIL_IMPLEMENTATION U_HAVE_ELF_H=1)

target_link_libraries(${LIB_ICUTU} PRIVATE ${LIB_ICUI18N_S} ${LIB_ICUUC_S} ${LIB_ICUFDT} ${LIB_M} ${CMAKE_DL_LIBS})


include_directories(${ICUTU_DIR} ${ICUUC_S_DIR} ${ICUI18N_S_DIR})

# for macosx  -DU_HAVE_POPEN=0
# build tool
set(TOOL_PKGDATA pkgdata)

add_executable(${TOOL_PKGDATA} ${ICU_TOOLS_DIR}/pkgdata/pkgdata.cpp ${ICU_TOOLS_DIR}/pkgdata/pkgtypes.c)

target_compile_definitions(${TOOL_PKGDATA} PRIVATE U_ATTRIBUTE_DEPRECATED= U_COMMON_IMPLEMENTATION U_I18N_IMPLEMENTATION)

target_link_libraries(${TOOL_PKGDATA} PRIVATE ${LIB_ICUTU} ${LIB_ICUI18N_S} ${LIB_ICUUC_S} ${LIB_ICUFDT} ${LIB_M} ${CMAKE_DL_LIBS})

set(TOOL_ICUPKG icupkg)

add_executable(${TOOL_ICUPKG} ${ICU_TOOLS_DIR}/icupkg/icupkg.cpp)

target_compile_definitions(${TOOL_ICUPKG} PRIVATE U_ATTRIBUTE_DEPRECATED= U_COMMON_IMPLEMENTATION U_I18N_IMPLEMENTATION)

target_link_libraries(${TOOL_ICUPKG} PRIVATE ${LIB_ICUTU} ${LIB_ICUI18N_S} ${LIB_ICUUC_S} ${LIB_ICUFDT} ${LIB_M} ${CMAKE_DL_LIBS})


